package com.test.weex.render.task;

import android.text.TextUtils;
import android.util.Log;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import com.taobao.weex.render.frame.RenderFrame;

import java.io.BufferedReader;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by furture on 2018/9/1.
 */

public class RenderFrameLogTask implements Runnable {



    private String log;
    private RenderFrame renderFrame;

    public RenderFrameLogTask(RenderFrame renderFrame, String log) {
        this.renderFrame = renderFrame;
        this.log = log;
    }

    @Override
    public void run() {
        try {

            BufferedReader bufferedReader = new BufferedReader(new StringReader(log));
            String line = null;
            int position = 0;
            int actionStart = 0;
            String[] actions;
            line = bufferedReader.readLine();
            Map<String,JSONObject> doms = new HashMap<>();
            Set<String> historyRefs = new HashSet<>();
            JSONObject root = new JSONObject();
            long offset = -1;
            while (line != null){
                if(renderFrame.isDestroy()){
                    break;
                }
                if(!TextUtils.isEmpty(line)){
                    if(offset > 0){
                        long time = getTimeOffset(line);
                        if(time > 0){
                            if((time - offset) > 0) {
                                Thread.sleep(time - offset);
                                offset = time;
                            }
                        }
                    }
                    if(line.indexOf("documentAction") > 0){
                        line = line.replaceAll("documentAction", "action");
                    }
                    position = line.indexOf("actionCreateBody");
                    if(position > 0){
                        Thread.sleep(1000);
                        actionStart = line.indexOf(';', position);
                        String bodyAction = line.substring(actionStart + 1, line.length());
                        actions = bodyAction.split(";");

                        doms.clear();
                        root = new JSONObject();
                        root.put("ref", actions[0]);
                        root.put("type", "div");
                        root.put("style", toMap(JSON.parseObject(actions[1])));
                        root.put("attr", toMap(JSON.parseObject(actions[2])));
                        root.put("event", toList(JSON.parseArray(actions[3])));
                        doms.put(actions[0], root);
                        historyRefs.add(actions[0]);
                        renderFrame.actionCreateBody(actions[0], toMap(JSON.parseObject(actions[1])), toMap(JSON.parseObject(actions[2])), toList(JSON.parseArray(actions[3])));
                    }

                    position = line.indexOf("actionAddElement");
                    if(position > 0){

                        actionStart = line.indexOf(';', position);
                        String createElementAction = line.substring(actionStart + 1, line.length());
                        actions = createElementAction.split(";");

                        String type = actions[1];
                        Map<String, String> attrs = toMap(JSON.parseObject(actions[5]));
                        if("text".equals(type)){
                            if(attrs == null){
                                attrs = new HashMap<>();
                            }
                            if(!attrs.containsKey("value")){
                            }
                        }

                        JSONObject element = new JSONObject();
                        String ref = actions[0];
                        element.put("ref", ref);
                        element.put("type", actions[1]);
                        element.put("style", toMap(JSON.parseObject(actions[4])));
                        element.put("attr", attrs);
                        element.put("event", toList(JSON.parseArray(actions[6])));
                        historyRefs.add(ref);
                        String parentRef = actions[2];
                        int index = Integer.parseInt(actions[3]);
                        renderFrame.actionAddElement(actions[0], actions[1], parentRef, index, toMap(JSON.parseObject(actions[4])), attrs, toList(JSON.parseArray(actions[6])));

                        JSONObject parent = doms.get(parentRef);
                        if(parent == null){
                            throw new RuntimeException("parent ref " + parentRef);
                        }
                        JSONArray children = parent.getJSONArray("children");
                        if(children == null){
                            children = new JSONArray();
                            parent.put("children", children);
                        }
                        if(index >= 0){
                            children.add(index, element);
                        }else{
                            children.add(element);
                        }
                        doms.put(ref, element);
                    }
                    position = line.indexOf("actionUpdateStyle");
                    if(position > 0){
                        actionStart = line.indexOf(';', position);
                        String createElementAction = line.substring(actionStart + 1, line.length());
                        actions = createElementAction.split(";");
                        String ref = actions[0];
                        JSONObject styles = JSON.parseObject(actions[1]);
                        JSONObject element = doms.get(ref);
                        if(element == null){
                            if(historyRefs.contains(ref)){
                                line = bufferedReader.readLine();
                                continue;
                            }
                            throw new RuntimeException("element ref " + ref);
                        }
                        if(element.getJSONObject("style") == null){
                            element.put("style", styles);
                        }else {
                            JSONObject save = element.getJSONObject("style");
                            save.putAll(styles);
                            element.put("style", save);
                        }
                        renderFrame.actionUpdateStyles(ref, toMap(styles));
                    }

                    position = line.indexOf("actionUpdateAttrs");
                    if(position > 0){
                        actionStart = line.indexOf(';', position);
                        String createElementAction = line.substring(actionStart + 1, line.length());
                        actions = createElementAction.split(";");
                        String ref = actions[0];
                        JSONObject attrs = JSON.parseObject(actions[1]);
                        JSONObject element = doms.get(ref);
                        if(element == null){
                            if(historyRefs.contains(ref)){
                                line = bufferedReader.readLine();
                                continue;
                            }
                            throw new RuntimeException("element ref " + ref);
                        }
                        if(element.getJSONObject("attr") == null){
                            element.put("attr", attrs);
                        }else {
                            JSONObject save = element.getJSONObject("attr");
                            save.putAll(attrs);
                            element.put("attr", save);
                        }
                        renderFrame.actionUpdateAttrs(ref, toMap(attrs));
                    }
                }

                if(line.contains("actionLayoutExecute")){
                    Thread.sleep(1000);
                }
                line = bufferedReader.readLine();
            }
            Log.e("weex", "renderFrame action " + root.toString());
        }catch (Exception e){
            throw new RuntimeException(e);
        }
    }


    public Map<String, String> toMap(JSONObject style){
        if(style == null){
            return null;
        }
        Map<String, String> maps = new HashMap<>();
        Set<Map.Entry<String,Object>> entries = style.entrySet();
        for(Map.Entry<String,Object> entry: entries){
            if(entry.getValue() == null){
                continue;
            }
            maps.put(entry.getKey(), entry.getValue().toString());
        }
        return maps;
    }


    public List<String> toList(JSONArray array){
        if(array == null){
            return null;
        }
        List<String> list = new ArrayList<>();
        for(Object object : array){
            if(object == null){
                continue;
            }
            list.add(object.toString());
        }
        return list;
    }


    private static long getTimeOffset(String time){
        Pattern pattern = Pattern.compile("[\\d]{2}:[\\d]{2}:[\\d]{2}\\.\\d+");
        Matcher matcher = pattern.matcher(time);
        if(!matcher.find()){
            return -1;
        }
        String offset= time.substring(matcher.start(), matcher.end());
        int pos = offset.lastIndexOf('.');
        String minus = offset.substring(pos + 1);
        String hous = offset.substring(0, pos);
        String [] hms =hous.split(":");
        long second =  Long.parseLong(hms[0])*60*60 + Long.parseLong(hms[1])*60
                + + Long.parseLong(hms[2]);
        return second*1000 + Long.parseLong(minus);
    }

}
