package com.test.weex.render.activity;

import android.content.Context;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by furture on 2018/8/2.
 */

public class DataUtils {

    private static JSONArray images;

    public static void initImgs(Context context){
        try {
            images  = new JSONArray(FileUtils.loadAsset("imgs.json", context));
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    private static JSONArray getImgs(){
        return images;
    }

    public static String getImgs(JSONObject jsonObject, int position){
        if(position == 0){
            return jsonObject.toString();
        }
        JSONArray childsOne = jsonObject.optJSONArray("children");
        for(int i=0; i<childsOne.length(); i++){
            JSONObject divChild = childsOne.optJSONObject(i);
            if(divChild == null){
                break;
            }
            if(position%2 == 0){
                try {
                    JSONObject style  = divChild.optJSONObject("style");
                    divChild.put("height", "560");
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }else{
                try {
                    JSONObject style  = divChild.optJSONObject("style");
                    divChild.put("height", "320");
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
            JSONArray divChilds = divChild.optJSONArray("children");
            if(divChilds == null){
                break;
            }
            for(int j=0; j<divChilds.length(); j++){
                JSONObject subDiv = divChilds.optJSONObject(j);
                if(subDiv.optJSONArray("children") == null
                        || subDiv.optJSONArray("children").length() <= 0){
                    continue;
                }
                JSONObject img = subDiv.optJSONArray("children").optJSONObject(0);
                JSONArray imgs = getImgs();
                int index = (position*divChilds.length() + j)%imgs.length();
                String src = imgs.optString(index);
                try {
                    if(img.getJSONObject("attr") == null){
                        continue;
                    }
                    img.getJSONObject("attr").put("src", src);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        }
        if(position%2 == 0){
            try {
                JSONObject style  = jsonObject.optJSONObject("style");
                style.put("height", "680");
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }else{
            try {
                JSONObject style  = jsonObject.optJSONObject("style");
                style.put("height", "340");
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
        return jsonObject.toString();
    }
}
