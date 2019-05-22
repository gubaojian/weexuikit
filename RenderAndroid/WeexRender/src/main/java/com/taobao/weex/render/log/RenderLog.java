/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
package com.taobao.weex.render.log;

import android.util.Log;

import org.json.JSONObject;

import java.util.Collection;
import java.util.Map;

/**
 * Render Log for recording render command and replay render action command.
 * This Should Move To C++, Will Be Delete
 * Created by furture on 2018/9/1.
 */
public class RenderLog {

    public static final String RENDER_LOG_TAG  = "RenderLog";

    private static boolean isDebugLogEnabled = true;
    private static boolean isErrorLogEnabled = true;
    private static  boolean isRenderLogEnabled = false;

    public static final void openRenderLog(boolean enabled){
        isRenderLogEnabled = enabled;
    }

    public static final void openDebugLog(boolean enabled){
        isDebugLogEnabled = enabled;
    }

    public static final void openErrorLog(boolean enabled){
        isErrorLogEnabled = enabled;
    }

    public static boolean isDebugLogEnabled(){
        return isDebugLogEnabled;
    }

    public static void actionCreateBody(String pageId, String ref, Map<String, String> style, Map<String, String> attrs, Collection<String> events) {
       if(isRenderLogEnabled){
           Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " + pageId + "actionCreateBody;" + ref + ";"+ toJSON(style) + ";" + toJSON(attrs)
                   + ";" + toJSON(events));
       }
    }

    public static void actionAddElement(String pageId, String ref, String componentType, String parentRef, int index, Map<String, String> style, Map<String, String> attrs, Collection<String> events){
        if(isRenderLogEnabled){
            Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " + pageId + "actionAddElement;" + ref + ";" + componentType + ";" + parentRef + ";" + index + ";"
                    + toJSON(style) + ";" + toJSON(attrs)
                    + ";" + toJSON(events));
        }
    }


    public static void actionUpdateStyles(String pageId,  String ref, Map<String, String> styles) {
        if(isRenderLogEnabled) {
            Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " + pageId + "actionUpdateStyle;" + ref + ";" + toJSON(styles));
        }
    }

    public static void actionUpdateAttrs(String pageId, String ref, Map<String, String> attrs){
        if(isRenderLogEnabled) {
            Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " +  pageId + "actionUpdateAttrs;" + ref + ";" + toJSON(attrs));
        }
    }


    public static void actionAddEvent(String pageId, String ref, String event){
        if(isRenderLogEnabled) {
            Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " + pageId + "actionAddEvent;" + ref + ";" + event);
        }
    }

    public static void actionRemoveEvent(String pageId, String ref, String event){
        if(isRenderLogEnabled) {
            Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " +  pageId + "frameRemoveEvent;" + ref + ";" + event);
        }
    }


    public static void actionMoveElement(String pageId, String ref, String parentRef, int index){
        if(isRenderLogEnabled) {
            Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " + pageId + "actionMoveElement;" + ref + ";" + parentRef + ";" + index);
        }
    }


    public static void actionRemoveElement(String pageId, String ref){
        if(isRenderLogEnabled) {
            Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " + pageId + "actionRemoveElement;" + ref);
        }
    }

    public static void actionLayoutExecute(String pageId){
        if(isRenderLogEnabled) {
            Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " + pageId + "actionLayoutExecute;");
        }
    }

    public static void actionInvalidate(String pageId){
        if(isRenderLogEnabled) {
            Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " + pageId + "actionInvalidate;");
        }
    }


    public static void onError(String message , Throwable throwable){
        if(isErrorLogEnabled){
            Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " + message,  throwable);
        }
    }


    public static void debug(String log) {
        if(isDebugLogEnabled) {
            Log.e(RENDER_LOG_TAG, RENDER_LOG_TAG + " " + log);
        }
    }

    private static final String toJSON(Map<String, String> style){
        if(style == null){
            return "null";
        }
        return new JSONObject(style).toString();
    }

    private static String toJSON(Collection<String> events) {
        if(events == null){
            return "null";
        }
        return new org.json.JSONArray(events).toString();
    }
}
