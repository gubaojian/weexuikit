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
package com.taobao.weex.render.frame;

import android.content.Context;
import android.view.MotionEvent;
import com.taobao.weex.render.event.OnFrameSizeChangedListener;
import com.taobao.weex.render.bridge.RenderBridge;
import com.taobao.weex.render.event.FrameAdapter;
import com.taobao.weex.render.image.RequestImage;

import java.util.Collection;
import java.util.Map;


/**
 * Sureface Render For OpenGL Context
 * Created by furture on 2018/7/23.
 */
public class RenderFrame {

    private String mPageId;
    private int frameHeight;
    private int frameWidth;
    private Context mContext;
    private FrameAdapter mFrameAdapter;
    private Object instance;
    private boolean mDestroy;



    public RenderFrame(Context context){
        this.mContext = context;
        this.mDestroy  = false;
    }


    public void actionCreateBody(String ref, Map<String, String> style, Map<String, String> attrs, Collection<String> events){
        if(mPageId == null){
            throw new NullPointerException("Please Set PageId First");
        }
        RenderBridge.getInstance().actionCreateBody(mPageId, ref, style, attrs, events);
    }

    public void actionAddElement(String ref, String componentType, String parentRef, int index, Map<String, String> style, Map<String, String> attrs, Collection<String> events){
        RenderBridge.getInstance().actionAddElement(mPageId, ref,  componentType, parentRef, index, style, attrs, events);
    }

    public void actionUpdateAttrs(String ref, Map<String, String> attrs){
        if(attrs == null){
            return;
        }
        RenderBridge.getInstance().actionUpdateAttrs(mPageId, ref, attrs);
    }

    public void actionUpdateStyles(String ref, Map<String, String> styles){
        if(styles == null || styles.size() <= 0){
            return;
        }
        RenderBridge.getInstance().actionUpdateStyles(mPageId, ref, styles);
    }

    public void actionAddEvent(String ref, String event){
        RenderBridge.getInstance().actionAddEvent(mPageId, ref, event);
    }

    public void actionRemoveEvent(String ref, String event){
        RenderBridge.getInstance().actionRemoveEvent(mPageId, ref, event);
    }


    public void actionMoveElement(String ref, String parentRef, int index){
        RenderBridge.getInstance().actionMoveElement(mPageId, ref, parentRef, index);
    }


    public void actionRemoveElement(String ref){
        RenderBridge.getInstance().actionRemoveElement(mPageId, ref);
    }

    public void actionOnTouchEvent(MotionEvent event){
        TouchHelper.dispatchTouchEvent(mPageId, event);
    }

    public void actionRefreshFont(String fontFaimly) {
        RenderBridge.getInstance().actionRefreshFont(getPageId(), fontFaimly);

    }


    public void requestFrame(){
       // markDirty();
    }


    /**
     * when load image target complete, call this method
    public void onLoadFrameImage(RequestImage frameImage){
        if(frameImage == null){
            return;
        }


        if(frameImage.getBitmap() != null){
            requestFrame();
        }
        if(frameImage.isPlaceholder()){
            return;
        }
        if(mFrameAdapter != null && mFrameAdapter.getImgLoadListener() != null){
            mFrameAdapter.getImgLoadListener().onLoadImage(frameImage);
        }
    } * */

    public Context getContext() {
        return  mContext;
    }


    public String getPageId() {
        return mPageId;
    }

    public void setPageId(String pageId){
        mPageId = pageId;
    }

    public void setPause(boolean mPause) {
        /**
        if(this.mPause != mPause){
            this.mPause = mPause;
            this.mFrameRender = null;
            if(mPause){
                //FrameImageCache.getInstance().cacheFrameImages(mFrameKey, frameImageMap);
                frameImageMap.clear();
            }
        }*/
    }


    public int getFrameHeight() {
        return frameHeight;
    }

    public int getFrameWidth() {
        return frameWidth;
    }

    public Object getInstance() {
        return instance;
    }

    public void setInstance(Object instance) {
        this.instance = instance;
    }

    public void setFrameAdapter(FrameAdapter documentAdapter) {
        this.mFrameAdapter = documentAdapter;
    }

    public FrameAdapter getFrameAdapter() {
        return mFrameAdapter;
    }


    //FIXME Remove Frame Size Listener
    private void setRenderFrameSize(final int width, final int height) {
        if(width <= 0 || height <= 0){
            return;
        }
        if(frameWidth == width
                && frameHeight == height){
            return;
        }

        frameWidth = width;
        frameHeight = height;
        final FrameAdapter frameAdapter = mFrameAdapter;
        if(frameAdapter == null){
            return;
        }
        final OnFrameSizeChangedListener frameSizeChangedListener = frameAdapter.getDocumentSizeChangedListener();
        if(frameSizeChangedListener == null){
            return;
        }
        if(!frameAdapter.isRequireFrameSizeChangedOnMainThread()){
            frameSizeChangedListener.onSizeChanged(RenderFrame.this, width, height);
            return;
        }
        /**
        mainHandler.post(new Runnable() {
            @Override
            public void run() {
                frameSizeChangedListener.onSizeChanged(RenderFrame.this, width, height);
            }
        });*/
    }



    public  void destory(){
        synchronized (this){
            if(!isDestroy()){
                RenderBridge.getInstance().actionDestroyPage(getPageId());
                mDestroy = true;
            }
        }
    }

    public boolean isDestroy(){
        return mDestroy;
    }

    @Override
    protected void finalize() throws Throwable {
        if(mPageId != null){
            if(!isDestroy()){
                destory();
            }
        }
        super.finalize();
    }
}
