package com.test.weex.render.task;

import android.os.AsyncTask;
import android.util.Log;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import com.taobao.weex.render.font.FontManager;
import com.taobao.weex.render.font.FontWatchTask;
import com.taobao.weex.render.frame.RenderFrame;
import com.taobao.weex.render.log.RenderLog;

import java.io.FileOutputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Created by furture on 2018/8/20.
 */

public class RenderFrameJSONTask implements Runnable {

    private static Map<String,JSONObject> bodys = new HashMap<>();
    private String json;
    private String mFileName;
    private RenderFrame mFrame;

    public RenderFrameJSONTask(String fileName, String json, RenderFrame frame) {
        this.json = json;
        this.mFrame = frame;
        this.mFileName = fileName;
    }


    @Override
    public void run() {
        long start = System.currentTimeMillis();
        JSONObject body  = bodys.get(mFileName);
        if(body == null){
            body = JSON.parseObject(json);
           // bodys.put(mFileName, body);
        }
        Log.e("Weex", "Weex parse used " + (System.currentTimeMillis() - start));
        Map<String, String>  style = toMap(body.getJSONObject("style"));
        style.put("width", "750");
        mFrame.actionCreateBody(body.getString("ref"), style, toMap(body.getJSONObject("attr")), toList(body.getJSONArray("event")));
        sendChild(body, true);

        Log.e(RenderLog.RENDER_LOG_TAG, "Render send json used " + (System.currentTimeMillis() - start) + " ms ");


        final FontWatchTask fontWatchTask = FontManager.getInstance().getFontWatchTask("iconfont", "http://at.alicdn.com/t/font_lf2urtr9li110pb9.ttf");
        if(!fontWatchTask.isLoaded()){
            fontWatchTask.addWatchFrame(mFrame);
            AsyncTask.execute(new Runnable() {
                @Override
                public void run() {
                    String fontPath = mFrame.getContext().getFilesDir().getAbsolutePath()
                            + "/font_lf2urtr9li110pb9.ttf";
                    try {
                        InputStream inputStream = mFrame.getContext().getAssets().open("font_lf2urtr9li110pb9.ttf");
                        byte[] bts = new byte[1024];
                        FileOutputStream outputStream = new FileOutputStream(fontPath);
                        int count = 0;
                        while ((count = inputStream.read(bts)) > 0){
                            outputStream.write(bts, 0, count);
                        }
                        inputStream.close();
                        outputStream.close();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                    fontWatchTask.notifyFontReadyWithFilePath(fontPath);
                }
            });
        }

        //testTextUpdate();

    }

    private void testTextUpdate(){
        Map<String,String> attrs = new HashMap<>();
        String value = "11111111112222222";
        for(int i=0 ;i<10; i++){
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if(i % 2 == 0){
                value += " 88888888888888615555555855888888888888888888888888800";
            }else {
                value  = "";
            }
            attrs.put("value", value + i);
            mFrame.actionUpdateAttrs("13", attrs);
        }
    }

    private void sendChild(JSONObject parent, boolean first){
        JSONArray children = parent.getJSONArray("children");
        if(children == null || children.size() == 0){
            return;
        }
        for(int i=0; i<children.size(); i++){
            JSONObject jsonNode = children.getJSONObject(i);
            if(jsonNode == null){
                return;
            }
            int m = -1;
            if(i == 0){
                m = 0;
            }
            mFrame.actionAddElement(jsonNode.getString("ref"), jsonNode.getString("type"), parent.getString("ref"), m,
                    toMap(jsonNode.getJSONObject("style")), toMap(jsonNode.getJSONObject("attr")), toList(jsonNode.getJSONArray("event")));
            sendChild(jsonNode, false);
        }
    }

    public Map<String, String> toMap(JSONObject style){
        if(style == null){
            return new HashMap<>();
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
}
