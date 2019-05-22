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
package com.taobao.weex.render.bridge;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.SurfaceTexture;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.os.Build;
import android.text.TextUtils;
import android.util.Log;
import android.view.Surface;
import android.view.ViewGroup;
import android.view.ViewParent;

import com.taobao.weex.render.frame.RenderView;
import com.taobao.weex.render.image.ImageManager;
import com.taobao.weex.render.image.RequestImage;
import com.taobao.weex.render.manager.RenderManager;
import com.taobao.weex.render.platform.PlatformView;
import com.taobao.weex.render.sdk.RenderSDK;
import com.taobao.weex.render.threads.FrameThread;

import java.io.UnsupportedEncodingException;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

import javax.microedition.khronos.opengles.GL10;

import static android.opengl.GLES11Ext.GL_TEXTURE_EXTERNAL_OES;

/**
 * Created by furture on 2018/7/24.
 */

public class RenderBridge {

    private static final RenderBridge renderBridge = new RenderBridge();

    public static RenderBridge getInstance(){
        return renderBridge;
    }

    /**
     * @param pageId pageId key
     * @param url imageUrl
     * @param width content image layout width
     * @param height content image layout height
     * the method is called in gpu thread
     * */
    public static void getImage(String pageId, String ref, String url, int width, int height, long callbackId){
         RenderBridge.getInstance().getBitmap(pageId, ref, url, width, height, callbackId);
    }


     //FIXME, MOVE This Logical To C++, Simply Code.
     public static void createPlatformView(String pageId, final String ref, final String type,
                                           final Map<String,String> attrs, final Map<String,String> style, final List<String> events){
         final RenderView renderView = RenderManager.getInstance().getRenderView(pageId);
         if(renderView == null){
             return;
         }
         RenderManager.getInstance().getUiHandler().post(new Runnable() {
             @Override
             public void run() {
                 renderView.getPlatformViewManager().createPlatformView(ref, type, attrs,  style, events);
             }
         });
     }

    /**
     * Syc System View Info
     * */
    public static void paintPlatformView(String pageId, final String ref, final int x, final int y, final int width, final int height, boolean attached){
        try{

            final RenderView renderView = RenderManager.getInstance().getRenderView(pageId);
            if(renderView == null){
                return;
            }
            if(!attached){
                RenderManager.getInstance().getUiHandler().post(new Runnable() {
                    @Override
                    public void run() {
                        /**
                        PlatformView platformView =  renderView.getPlatformViewManager().getView(ref);
                        if(platformView == null){
                            return;
                        }
                        platformView.onDetach();
                        if(platformView.getView() != null){
                            ViewParent parent = platformView.getView().getParent();
                            if(parent != null && parent instanceof ViewGroup){
                                 ((ViewGroup) parent).removeView(platformView.getView());
                            }
                        }*/
                    }
                });
                return;
            }
            if(!renderView.getPlatformViewManager().hasTransformUpdate(ref, x, y, width, height)){
                return;
            }
            final CountDownLatch countDownLatch = new CountDownLatch(1);
            RenderManager.getInstance().getUiHandler().postAtFrontOfQueue(new Runnable() {
                @Override
                public void run() {
                    renderView.getPlatformViewManager().paintPlatformView(ref, x, y, width, height);
                    countDownLatch.countDown();
                }
            });
            countDownLatch.await(80, TimeUnit.MILLISECONDS);
        }catch (Exception e){
            Log.e("WeexUIKit", "WeexUIKit Exception", e);
        }
    }

    public static void createExternalTexturePresentation(String pageId, final String ref, final String type,final Map<String,String> attrs, final Map<String,String> style, final List<String> events){


    }

    public static int updateExternalTexturePresentation(String pageId, String ref){

        return 0;
    }

    public static void deleteExternalTexturePresentation(String pageId, String ref){

    }


    public static boolean isImagePremultiplied(Bitmap bitmap){
        if(bitmap == null){
            return true;
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
            return bitmap.isPremultiplied();
        }
        return  true;
    }


    static SurfaceTexture surfaceTexture;
    static Surface surface;

    public static int testImageTexture(){
        final Bitmap bitmap = BitmapFactory.decodeFile("/data/local/tmp/test.png");
        int n = 1;
        int[] textureHandle = new int[n];
        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);

        GLES20.glGenTextures(n, textureHandle, 0);

        for(int i=0; i<n; i++){
            // Bind to the texture in OpenGL
            //int textureFormat = GL_TEXTURE_EXTERNAL_OES;
            int textureFormat = GLES20.GL_TEXTURE_2D;
            GLES20.glBindTexture(textureFormat, textureHandle[i]);

            // Set filtering
            GLES20.glTexParameteri(textureFormat, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
            GLES20.glTexParameteri(textureFormat, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_NEAREST);
            GLES20.glTexParameteri(textureFormat, GL10.GL_TEXTURE_WRAP_S, GL10.GL_CLAMP_TO_EDGE);
            GLES20.glTexParameteri(textureFormat, GL10.GL_TEXTURE_WRAP_T, GL10.GL_CLAMP_TO_EDGE);

            // Load the bitmap into the bound texture.
            GLUtils.texImage2D(textureFormat, 0, bitmap, 0);

            /**
             surfaceTexture = new SurfaceTexture(textureHandle[i]);
             if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1) {
             surfaceTexture.setDefaultBufferSize(500, 500);
             }
             if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN) {
             //surfaceTexture.detachFromGLContext();
             }

             if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN) {
             //surfaceTexture.attachToGLContext(textureHandle[i]);
             }

             surface = new Surface(surfaceTexture);

             new Thread(new Runnable() {
            @Override
            public void run() {
            while (true){
            Canvas canvas = surface.lockCanvas(null);
            Paint paint = new Paint();
            paint.setColor(Color.GREEN);
            canvas.drawText("Hello World", 100, 100, paint);
            surface.unlockCanvasAndPost(canvas);
            //Log.e("Weex", " Weex RenderTexture::paintReplace paint to Surface");
            }
            }
            }).start();*/

        }
        Log.e("Weex", " Weex RenderTexture::paintReplaced id " + textureHandle[0]);
        //GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        //GLES20.glBindTexture(GL_TEXTURE_EXTERNAL_OES, textureHandle[0]);
        return textureHandle[0];
    }

    public static int testSurfaceTexture(){
        int n = 1;
        int[] textureHandle = new int[n];
        GLES20.glGenTextures(n, textureHandle, 0);

        for(int i=0; i<n; i++){
            // Bind to the texture in OpenGL
            int textureFormat = GL_TEXTURE_EXTERNAL_OES;
            //int textureFormat = GLES20.GL_TEXTURE_2D;
            GLES20.glBindTexture(textureFormat, textureHandle[i]);

            // Set filtering
            //GLES20.glTexImage2D(textureFormat, 0, GL_RGBA8_OES, 500, 500, 0, GL_RGBA8_OES, GL_UNSIGNED_BYTE, null);
            GLES20.glTexParameteri(textureFormat, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
            GLES20.glTexParameteri(textureFormat, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_NEAREST);
            GLES20.glTexParameteri(textureFormat, GL10.GL_TEXTURE_WRAP_S, GL10.GL_CLAMP_TO_EDGE);
            GLES20.glTexParameteri(textureFormat, GL10.GL_TEXTURE_WRAP_T, GL10.GL_CLAMP_TO_EDGE);



             surfaceTexture = new SurfaceTexture(textureHandle[i]);
             surfaceTexture.setOnFrameAvailableListener(new SurfaceTexture.OnFrameAvailableListener() {
                 @Override
                 public void onFrameAvailable(SurfaceTexture surfaceTexture) {
                     Log.e("Weex", "Weex onFrameAvailable");
                 }
             });
             if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1) {
                surfaceTexture.setDefaultBufferSize(1080, 200);
             }
             if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN) {
                //surfaceTexture.detachFromGLContext();
             }

             if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN) {
                //surfaceTexture.attachToGLContext(textureHandle[i]);
             }

             surface = new Surface(surfaceTexture);

             //new Thread(new Runnable() {
               // @Override
               // public void run() {
                   // while (true){
                        Canvas canvas = surface.lockCanvas(null);
                        Paint paint = new Paint();
                        paint.setColor(Color.GREEN);
                        canvas.drawText("Hello World", 100, 100, paint);
                        surface.unlockCanvasAndPost(canvas);
                    //Log.e("Weex", " Weex RenderTexture::paintReplace paint to Surface");
                    //}
                //}
            //}).start();
            //GLES20.glBindTexture(textureFormat, 0);

            surfaceTexture.updateTexImage();
        }
        Log.e("Weex", " Weex RenderTexture::paintReplaced id " + textureHandle[0]);
        //GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        //GLES20.glBindTexture(GL_TEXTURE_EXTERNAL_OES, textureHandle[0]);
        return textureHandle[0];
    }

    public static int testTexture(){
       return testSurfaceTexture();
    }

    public boolean initSDK(int screenWidth, int screenHeight, float density){
        return nativeInitSDK(screenWidth, screenHeight, density);
    }


    public void actionDestroyPage(String pageId) {
        nativeActionDestroyPage(pageId);
    }

    public void actionCreateBody(String pageId, String ref, Map<String,String> styles, Map<String,String> attrs, Collection<String> events){
        nativeActionCreateBody(pageId, ref, toNativeMap(styles), toNativeMap(attrs), toNativeSet(events));
    }

    public void actionAddElement(String pageId, String ref, String type, String parentRef, int index, Map<String,String> styles, Map<String,String> attrs, Collection<String> events){
        nativeActionAddElement(pageId, ref, type, parentRef, index, toNativeMap(styles), toNativeMap(attrs), toNativeSet(events));
    }

    public void actionUpdateAttrs(String pageId, String ref, Map<String, String> attrs) {
        nativeActionUpdateAttrs(pageId, ref, toNativeMap(attrs));
    }

    public void actionUpdateStyles(String pageId, String ref, Map<String, String> styles) {
        nativeActionUpdateStyles(pageId, ref, toNativeMap(styles));
    }

    public void actionAddEvent(String pageId, String ref, String event) {
        if(TextUtils.isEmpty(event) || TextUtils.isEmpty(ref)){
            return;
        }
        nativeActionAddEvent(pageId, ref, event);
    }

    public void actionRemoveEvent(String pageId, String ref, String event) {
        if(TextUtils.isEmpty(event) || TextUtils.isEmpty(ref)){
            return;
        }
        nativeActionRemoveEvent(pageId, ref, event);
    }


    public void actionRemoveElement(String pageId, String ref) {
        nativeActionRemoveElement(pageId, ref);
    }


    public void actionMoveElement(String pageId, String ref, String parentRef, int index){
        nativeActionMoveElement(pageId, ref, parentRef, index);
    }

    public void actionRefreshFont(final String pageId, final String fontFamilyName){
        if(Thread.currentThread() != FrameThread.getThread()){
            RenderManager.getInstance().getFrameHandler().post(new Runnable() {
                @Override
                public void run() {
                    actionRefreshFont(pageId, fontFamilyName);
                }
            });
            return;
        }
        nativeRefreshFont(pageId, fontFamilyName);
    }


    public String actionHitTestEvent(String pageId, int type, int x, int y) {
        //return nativeHitTestEvent(mNativeFrame, type, x, y);
        return null;
    }

    public void actionTouchEvent(String pageId, int action, int pointerId, float x, float y, long timeStamp){
        nativeActionTouchEvent(pageId, action, pointerId, x, y, timeStamp);
    }



    public void addFont(final String fontFamilyName, final String fontPath){
        if(Thread.currentThread() != FrameThread.getThread()){
            RenderManager.getInstance().getFrameHandler().post(new Runnable() {
                @Override
                public void run() {
                    addFont(fontFamilyName, fontPath);
                }
            });
            return;
        }
        nativeAddFont(fontFamilyName, fontPath);
    }


    public boolean hasFont(final String fontFamilyName, final String fontPath){
        return nativeHasFont(fontFamilyName, fontPath);
    }


    public long frameRenderAttach(String pageId, Surface surface, boolean isSurfaceView, int width, int height){
        if(height > RenderSDK.getInstance().getScreenHeight()*2){
            if(RenderSDK.getInstance().isDebug()){
                throw new IllegalArgumentException("Surface Height Two Large" + height + " screen height " + RenderSDK.getInstance().getScreenHeight());
            }
        }
        return nativeFrameRenderAttach(pageId,surface, isSurfaceView, width, height);
    }

    public void frameRenderSizeChanged(String pageId, int width, int height) {
        nativeFrameRenderSizeChanged(pageId, width, height);
    }

    public void frameRenderDettach(long nativeInfo, String pageId, Surface surface){
        nativeFrameRenderDettach(nativeInfo, pageId, surface);
    }

    public void frameRenderOnVsync(String pageId,  long frameTimeMs){
        nativeFrameRenderOnVsync(pageId, frameTimeMs);
    }


    public void frameRenderOnResume(String pageId){
        nativeFrameRenderOnResume(pageId);
    }


    public void frameRenderOnPause(String pageId){
        nativeFrameRenderOnPause(pageId);
    }


    public void actionOnLoadImage(RequestImage requestImage) {
        nativeActionOnLoadImage(requestImage.getBitmap(), requestImage.getPageId(), requestImage.getRef(),
                requestImage.getUrl(), requestImage.getWidth(),
                requestImage.getHeight(), requestImage.getCallbackId());
    }

    public void onLowMemory() {
        nativeOnLowMemory();
    }




    public int frameWidth(long ptr){
        return nativeRenderFrameWidth(ptr);
    }
    public int frameHeight(long ptr){
        return nativeRenderFrameHeight(ptr);
    }

    public int getBlockLayout(long ptr, String ref, int edge){
        return nativeGetBlockLayout(ptr, ref, edge);
    }

    public String getNodeAttr(long ptr, String ref, String key){
        byte [] bts =  nativeGetNodeAttr(ptr, ref, key);
        if(bts == null){
            return null;
        }
        try {
            return new String(bts, "UTF-8");
        } catch (UnsupportedEncodingException e) {
            return null;
        }
    }

    public String getNodeType(long ptr, String ref){
        return nativeGetNodeType(ptr, ref);
    }

    public boolean nodeContainsEvent(long ptr, String ref, String event){
        return nativeNodeContainsEvent(ptr, ref, event);
    }

    public long toNativeMap(Map<String,String> styles){
        long map = nativeNewMap();
        if(styles != null){
            Set<Map.Entry<String,String>> entrySet = styles.entrySet();
            for(Map.Entry<String,String> entry : entrySet){
                if(entry.getValue() == null){
                    continue;
                }
                nativeMapPut(map, entry.getKey(), entry.getValue());
            }
        }
        return map;
    }

    public long toNativeSet(Collection<String> events){
        long set = nativeNewSet();
        if(events != null){
            for(String envent : events){
                nativeSetAdd(set, envent);
            }
        }
        return set;
    }




    public void getBitmap(String pageId, String ref, final String url, int width, int height, long callbackId){
        if(TextUtils.isEmpty(url)){
            return;
        }
        if(RenderSDK.getInstance().getmImageAdapter() == null){
            return;
        }

        String requestKey = RenderSDK.getInstance().getmImageAdapter().genRequestKey(url, width, height);

        RequestImage  requestImage = ImageManager.getInstance().getRequestImage(requestKey);
        if(requestImage != null){
            if(requestImage.getBitmap() != null && requestImage.getLoadingState() == RequestImage.LOADING_SUCCESS){
                ImageManager.getInstance().onLoadImage(requestImage);
                return;
            }
            if(requestImage.getLoadingState()== RequestImage.LOADING){
                return;
            }
        }
        requestImage = RenderSDK.getInstance().getmImageAdapter().requestImage(requestKey, pageId, ref, url, width, height, callbackId);
        ImageManager.getInstance().onRequestImage(requestKey, requestImage);
    }



    private native boolean nativeInitSDK(int screenWidth, int screenHeight, float density);
    private native String nativeHitTestEvent(long mNativeDocument, int type, int x, int  y);

    private native int nativeRenderFrameWidth(long ptr);
    private native int nativeRenderFrameHeight(long ptr);



    private native void nativeActionOnLoadImage(Bitmap bitmap, String pageId, String ref, String url, int width, int height, long callbackId);


    private native void nativeActionTouchEvent(String pageId, int action, int pointerId, float x, float y, long timeStamp);


    private native long nativeFrameRenderAttach(String pageId, Surface surface, boolean isSurfaceView, int width, int height);
    private native void nativeFrameRenderSizeChanged(String pageId,  int width, int height);
    private native void nativeFrameRenderDettach(long nativeFrameRender, String pageId, Surface surface);
    private native void nativeFrameRenderOnVsync(String pageId, long frameTimeMs);
    private native void nativeFrameRenderOnResume(String pageId);
    private native void nativeFrameRenderOnPause(String pageId);

    private native void nativeActionDestroyPage(String pageId);
    private native void nativeActionCreateBody(String pageId, String ref, long styles, long attrs, long events);
    private native void nativeActionAddElement(String pageId, String ref, String type, String parentRef, int index, long styles, long attrs, long events);
    private native void nativeActionUpdateAttrs(String pageId, String ref, long attrs);
    private native void nativeActionUpdateStyles(String pageId, String ref, long styles);
    private native void nativeActionAddEvent(String pageId, String ref, String event);
    private native void nativeActionRemoveEvent(String pageId, String ref, String event);
    private native void nativeActionRemoveElement(String pageId, String ref);
    private native void nativeActionMoveElement(String pageId, String ref, String parentRef, int index);
    private native void nativeRefreshFont(String pageId, String fontFamilyName);
    private native void nativeOnLowMemory();

    private native void nativeAddFont(String fontFamilyName, String fontPath);
    private native boolean nativeHasFont(String fontFamilyName, String fontPath);
    private native int nativeGetBlockLayout(long ptr, String ref, int edge);
    private native byte[] nativeGetNodeAttr(long ptr, String ref, String key);
    private native String nativeGetNodeType(long ptr, String ref);
    private native boolean nativeNodeContainsEvent(long ptr, String ref, String event);
    private native long nativeNewMap();
    private native void nativeMapPut(long ptr, String key, String value);
    private native long nativeNewSet();
    private native void nativeSetAdd(long ptr, String value);

}
