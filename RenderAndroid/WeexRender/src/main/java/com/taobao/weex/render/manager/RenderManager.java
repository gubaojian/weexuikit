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
package com.taobao.weex.render.manager;

import android.app.Activity;
import android.os.Handler;
import android.os.Looper;

import com.taobao.weex.render.bridge.RenderBridge;
import com.taobao.weex.render.frame.RenderView;
import com.taobao.weex.render.image.ImageManager;
import com.taobao.weex.render.threads.FrameThread;
import com.taobao.weex.render.threads.IoThread;

import java.lang.ref.WeakReference;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Created by furture on 2018/7/24.
 */

public class RenderManager{

    private Map<String,WeakReference<RenderView>> renderViewMap;
    private Handler uiHandler;
    private Handler frameHandler;
    private Handler ioHandler;

    private RenderManager(){
        renderViewMap = new ConcurrentHashMap<>();
        uiHandler = new Handler(Looper.getMainLooper());
        frameHandler = new Handler(FrameThread.getThread().getLooper());
    }

    public Handler getUiHandler(){
        return uiHandler;
    }

    public void registerRenderView(String pageId, RenderView renderView){
        WeakReference<RenderView> surfaceRenderWeakReference = new WeakReference<RenderView>(renderView);
       renderViewMap.put(pageId, surfaceRenderWeakReference);
    }

    public void removeRenderView(String pageId){
        renderViewMap.remove(pageId);
    }


    public RenderView getRenderView(String pageId){
        WeakReference<RenderView> surfaceRenderWeakReference = renderViewMap.get(pageId);
        if(surfaceRenderWeakReference == null){
            return null;
        }
        return surfaceRenderWeakReference.get();
    }

    public Map<String,WeakReference<RenderView>> getRenderViewMap(){
         return renderViewMap;
    }


    public void onActivityResumed(Activity activity) {
        Set<Map.Entry<String,WeakReference<RenderView>>> entries = renderViewMap.entrySet();
        for(Map.Entry<String,WeakReference<RenderView>> entry : entries){
            RenderView renderView = entry.getValue().get();
            if(renderView == null){
                continue;
            }
            if(isAcivityRenderView(renderView, activity)){
                renderView.onActivityResume();
            }
        }
    }

    public void onActivityPaused(Activity activity) {
        Set<Map.Entry<String,WeakReference<RenderView>>> entries = renderViewMap.entrySet();
        for(Map.Entry<String,WeakReference<RenderView>> entry : entries){
            RenderView renderView = entry.getValue().get();
            if(renderView == null){
                continue;
            }
            if(isAcivityRenderView(renderView, activity)){
                renderView.onActivityPause();
            }
        }
    }

    public void onActivityDestroyed(Activity activity) {
        Set<Map.Entry<String,WeakReference<RenderView>>> entries = renderViewMap.entrySet();
        for(Map.Entry<String,WeakReference<RenderView>> entry : entries){
            RenderView renderView = entry.getValue().get();
            if(renderView == null){
                continue;
            }
            if(isAcivityRenderView(renderView, activity)){
                renderView.onActivityDestroyed();
            }
        }
    }


    public void onLowMemory() {
        ImageManager.getInstance().clear();
        RenderBridge.getInstance().onLowMemory();
    }

    private boolean isAcivityRenderView(RenderView renderView, Activity activity){
        if(renderView.getContext() == activity || renderView.getContext() == activity.getBaseContext()){
            return true;
        }
        return false;
    }




    public Handler getFrameHandler() {
        return frameHandler;
    }

    public Handler getIoHandler(){
        if(ioHandler == null){
            synchronized (this){
                if(ioHandler == null) {
                    ioHandler = new Handler(IoThread.getThread().getLooper());
                }
            }
        }
        return ioHandler;
    }

    public static RenderManager getInstance(){
        if(renderManager == null){
            synchronized (RenderManager.class){
                if(renderManager == null) {
                    renderManager = new RenderManager();
                }
            }
        }
        return renderManager;
    }

    private static RenderManager renderManager;
}
