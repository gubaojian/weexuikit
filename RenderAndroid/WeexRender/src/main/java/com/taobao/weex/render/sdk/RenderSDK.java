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
package com.taobao.weex.render.sdk;

import android.app.Application;
import android.content.Context;
import android.text.TextUtils;
import android.util.DisplayMetrics;

import com.taobao.weex.render.bridge.RenderBridge;
import com.taobao.weex.render.download.DownloadUtils;
import com.taobao.weex.render.image.ImageAdapter;
import com.taobao.weex.render.lifecycle.RenderLifecycleCallback;
import com.taobao.weex.render.log.RenderLog;
import com.taobao.weex.render.manager.RenderManager;
import com.taobao.weex.render.threads.FrameThread;
import com.taobao.weex.render.threads.IoThread;
import java.io.File;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

/**
 * Created by furture on 2018/8/31.
 */

public class RenderSDK {

    private static final String WEEX_RENDER = "weexrender";
    private static final String WEEX_RENDER_URL =  null;// "https://gw.alicdn.com/bao/uploaded/TB1TgSAcrvpK1RjSZFqXXcXUVXa.zip?spm=a1z3i.a4.0.0.7d68eb1dNJtnCa&file=TB1TgSAcrvpK1RjSZFqXXcXUVXa.zip";
    private static final String WEEX_RENDER_SO_MD5 = "5ae1ca197e10bad886e1fac093975c26";

    private Application mApplication;
    private ImageAdapter mImageAdapter;
    private boolean isInited = false;
    private RenderLifecycleCallback renderLifecycleCallback;
    private OnRenderSDKInitListener sdkOnInitListener;
    private static RenderSDK renderSDK;
    private  float density;
    private int mScreenHeight;

    private RenderSDK(){
        renderLifecycleCallback = new RenderLifecycleCallback();
    }

    public static RenderSDK getInstance(){
        if(renderSDK == null){
            synchronized (RenderSDK.class){
                if(renderSDK == null){
                    renderSDK = new RenderSDK();
                }
            }
        }
        return renderSDK;
    }

    public float getDensity() {
        return density;
    }

    public Application getApplication() {
        return mApplication;
    }

    public RenderSDK setApplication(Application mApplication) {
        this.mApplication = mApplication;
        return this;
    }

    public ImageAdapter getmImageAdapter() {
        return mImageAdapter;
    }

    public RenderSDK setmImageAdapter(ImageAdapter mImageAdapter) {
        this.mImageAdapter = mImageAdapter;
        return this;
    }

    public RenderSDK setSdkOnInitListener(OnRenderSDKInitListener sdkOnInitListener){
        this.sdkOnInitListener = sdkOnInitListener;
       return this;
    }

    public OnRenderSDKInitListener getSdkOnInitListener(){
        return sdkOnInitListener;
    }

    public void init(){
        RenderManager.getInstance().getFrameHandler().post(new Runnable() {
            @Override
            public void run() {
                initSdk();
            }
        });
    }

    public void initSync(){
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        RenderManager.getInstance().getFrameHandler().post(new Runnable() {
            @Override
            public void run() {
                try{
                    initSdk();
                }finally {
                    countDownLatch.countDown();
                }
            }
        });
        try {
            countDownLatch.await(3000, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public boolean isInited(){
        return isInited;
    }


    private void initSdk(){
        if(!isInited){
            synchronized (this){
                if(isInited){
                    return;
                }
                if(Thread.currentThread() != FrameThread.getThread()){
                    throw new RuntimeException("RenderSDK InitSdk Must be called on FrameThread");
                }
                if(mApplication == null){
                    throw new RuntimeException("RenderSDK setmApplication Should be called When Application Init");
                }
                mApplication.unregisterActivityLifecycleCallbacks(renderLifecycleCallback);
                mApplication.unregisterComponentCallbacks(renderLifecycleCallback);
                mApplication.registerActivityLifecycleCallbacks(renderLifecycleCallback);
                mApplication.registerComponentCallbacks(renderLifecycleCallback);
                try {
                    boolean loadSO = loadSoFromNetwork(mApplication);
                    if(!loadSO){
                        System.loadLibrary(WEEX_RENDER);
                    }
                    DisplayMetrics displayMetrics = mApplication.getResources().getDisplayMetrics();
                    density = displayMetrics.density;
                    mScreenHeight = displayMetrics.heightPixels;
                    isInited = RenderBridge.getInstance().initSDK(displayMetrics.widthPixels, displayMetrics.heightPixels, displayMetrics.density);
                    if(sdkOnInitListener != null){
                        sdkOnInitListener.onInit(isInited);
                    }

                }catch (Throwable e){
                    RenderLog.onError("RenderSDK Init Exception", e);
                    if(sdkOnInitListener != null){
                        sdkOnInitListener.onInit(false);
                    }
                }
                sdkOnInitListener = null;
            }
        }
    }

    private boolean loadSoFromNetwork(Context context){
        if(!TextUtils.isEmpty(WEEX_RENDER_URL)){
            String path = context.getFilesDir().getPath();
            String zipFile = path + "/lib/libweexrender.zip";
            String soPath = path + "/lib/libweexrender.so";
            File soFile = new File(soPath);

            if(soFile.exists()){
                String soMd5 = DownloadUtils.fileMd5(soPath);
                if(!soMd5.equals(WEEX_RENDER_SO_MD5)){
                    soFile.delete();
                }
            }
            if(!soFile.exists()){
                if(DownloadUtils.download(WEEX_RENDER_URL,  zipFile)){
                    DownloadUtils.unzip(zipFile, path + "/lib/");
                    DownloadUtils.deleteFile(zipFile);
                }
            }

            if(soFile.exists()){
                String soMd5 = DownloadUtils.fileMd5(soPath);
                if(soMd5.equals(WEEX_RENDER_SO_MD5)){
                    System.load(soFile.getAbsolutePath());
                    return true;
                }
            }
        }
        return false;
    }

    public void destory(){
        try{
            mApplication.unregisterActivityLifecycleCallbacks(renderLifecycleCallback);
            mApplication.unregisterComponentCallbacks(renderLifecycleCallback);
            FrameThread.getThread().quit();
            IoThread.getThread().quit();
        }catch (Exception e){
            RenderLog.onError("RenderSDK Destory Exception",e);
        }
    }

    public int getScreenHeight() {
        return mScreenHeight;
    }

    public boolean isDebug() {
        return false;
    }
}
