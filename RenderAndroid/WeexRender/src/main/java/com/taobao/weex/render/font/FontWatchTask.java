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
package com.taobao.weex.render.font;

import android.text.TextUtils;

import com.taobao.weex.render.bridge.RenderBridge;
import com.taobao.weex.render.manager.RenderManager;
import com.taobao.weex.render.frame.RenderFrame;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by furture on 2018/8/30.
 */

public class FontWatchTask implements  Runnable{

    private List<RenderFrame> mFrames;
    private boolean isLoaded;
    private String mFontFaimly;
    private String mFontUrl;
    private String mFontPath;
    private boolean isLoading;

    public FontWatchTask(String fontFaimly, String fontUrl) {
        this.mFontFaimly = fontFaimly;
        this.mFontUrl = fontUrl;
        this.mFrames = new ArrayList<>();
        this.isLoaded = false;
    }

    public void notifyFontReadyWithFilePath(String filePath){
        this.mFontPath = filePath;
        RenderManager.getInstance().getFrameHandler().post(this);
    }


    boolean isSame(String fontFaimly, String fontUrl){
        return this.mFontFaimly.equals(fontFaimly) && this.mFontUrl.equals(fontUrl);
    }


    @Override
    public void run() {
        if(TextUtils.isEmpty(mFontPath)){
            synchronized (mFrames){
                mFrames.clear();
            }
            return;
        }
        if(isLoaded){
            return;
        }
        this.isLoaded = true;
        if(new File(mFontPath).exists()){
            if(!RenderBridge.getInstance().hasFont(mFontFaimly, mFontPath)){
                RenderBridge.getInstance().addFont(mFontFaimly, mFontPath);
                synchronized (mFrames){
                    for(RenderFrame renderFrame : mFrames){
                        renderFrame.actionRefreshFont(mFontFaimly);
                    }
                }
            }
        }
        synchronized (mFrames){
            mFrames.clear();
        }
    }

    public void addWatchFrame(RenderFrame documentView){
        if(isLoaded){
            return;
        }
        synchronized (mFrames){
            mFrames.add(documentView);
        }
    }

    public boolean isLoaded() {
        return isLoaded;
    }

    public boolean isLoading() {
        return isLoading;
    }

    public void setLoading(boolean loading) {
        isLoading = loading;
    }

    public String getFontFaimly() {
        return mFontFaimly;
    }

    public String getFontUrl() {
        return mFontUrl;
    }

    public String getFontPath() {
        return mFontPath;
    }
}
