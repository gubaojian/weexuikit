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
import android.graphics.PixelFormat;
import android.graphics.Rect;
import android.graphics.SurfaceTexture;
import android.os.Build;
import android.support.v4.view.ViewCompat;
import android.util.AttributeSet;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.TextureView;
import android.view.View;
import android.widget.FrameLayout;

import com.taobao.weex.render.accessibility.RenderViewAccessibilityHelper;
import com.taobao.weex.render.bridge.RenderBridge;
import com.taobao.weex.render.fling.FlingControl;
import com.taobao.weex.render.manager.RenderManager;
import com.taobao.weex.render.manager.RenderStats;
import com.taobao.weex.render.platform.PlatformViewManager;


/**
 * Created by furture on 2018/7/23.
 */

public class RenderView extends FrameLayout implements  TextureView.SurfaceTextureListener,
        SurfaceHolder.Callback, VsyncController.VsyncListener{


    private View mSurfaceView;
    private VsyncController mVsyncController;
    private RenderFrame mRenderFrame;
    private boolean mUseSurfaceView = true;

    private boolean mHasAttachToWindow;
    private RenderViewAccessibilityHelper mRenderFrameAccessibilityHelper;
    private SurfaceTextureHolder mSurfaceTextureHolder;
    private long mNativeSurface;
    private PlatformViewManager mPlatformViewManager;

    public RenderView(Context context) {
        super(context);
    }

    public RenderView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public RenderView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public RenderView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
    }



    public void createSurfaceView() {
        try{
            mRenderFrameAccessibilityHelper = new RenderViewAccessibilityHelper(this);
            ViewCompat.setAccessibilityDelegate(this, mRenderFrameAccessibilityHelper);
        }catch (Exception e){}
        if(mUseSurfaceView){
            SurfaceView surfaceView = new RenderSurfaceView(getContext());
            surfaceView.setZOrderOnTop(true);
            surfaceView.getHolder().setFormat(PixelFormat.TRANSPARENT);
            surfaceView.getHolder().addCallback(this);
            mSurfaceView = surfaceView;
        }else{
            TextureView textureView = new RenderTextureView(getContext());
            textureView.setOpaque(false);
            textureView.setSurfaceTextureListener(this);
            mSurfaceView = textureView;
        }
        addView(mSurfaceView, new FrameLayout.LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.MATCH_PARENT));
        mVsyncController = new VsyncController(this);
    }



    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        return mRenderFrameAccessibilityHelper.dispatchKeyEvent(event) ||super.dispatchKeyEvent(event);
    }

    @Override
    protected boolean dispatchHoverEvent(MotionEvent event) {
        return mRenderFrameAccessibilityHelper.dispatchHoverEvent(event) || super.dispatchHoverEvent(event);
    }



    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if(mRenderFrame != null){
            mRenderFrame.actionOnTouchEvent(event);
        }
        super.onTouchEvent(event);
        return true;
    }

    @Override
    public void onFocusChanged(boolean gainFocus, int direction, Rect previouslyFocusedRect) {
        super.onFocusChanged(gainFocus, direction, previouslyFocusedRect);
        mRenderFrameAccessibilityHelper.onFocusChanged(gainFocus, direction, previouslyFocusedRect);
    }

    @Override
    public void onSurfaceTextureAvailable(final SurfaceTexture surfaceTexture, final int width, final int height) {
        if(mRenderFrame == null){
            return;
        }
        mRenderFrame.setPause(false);
        mSurfaceTextureHolder = new SurfaceTextureHolder(surfaceTexture, width, height);
        mSurfaceTextureHolder.createSurface();
        mNativeSurface = RenderBridge.getInstance().frameRenderAttach(mRenderFrame.getPageId(), mSurfaceTextureHolder.getSurface(), mUseSurfaceView, width, height);
        mVsyncController.start();
    }



    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surfaceTexture, int width, int height) {
        if(mRenderFrame != null){
            mSurfaceTextureHolder.setSurfaceTexture(surfaceTexture, width, height);
            RenderBridge.getInstance().frameRenderSizeChanged(mRenderFrame.getPageId(), width, height);
        }
    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surfaceTexture) {
        mVsyncController.stop();
        if(mSurfaceTextureHolder != null){
            RenderBridge.getInstance().frameRenderDettach(mNativeSurface, mRenderFrame.getPageId(), mSurfaceTextureHolder.getSurface());
            mSurfaceTextureHolder.getSurface().release();
            RenderStats.countPeriodDettachNum(getContext());
        }
        mSurfaceTextureHolder = null;
        return true;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surfaceTexture) {

    }


    @Override
    protected void onAttachedToWindow() {
        mHasAttachToWindow = true;
        super.onAttachedToWindow();
        FlingControl.setParentMaxFling(this);
    }

    @Override
    protected void onDetachedFromWindow() {
        mHasAttachToWindow = false;
        super.onDetachedFromWindow();
    }

    @Override
    protected void onWindowVisibilityChanged(int visibility) {
        super.onWindowVisibilityChanged(visibility);
    }



    public boolean ismHasAttachToWindow() {
        return mHasAttachToWindow;
    }




    public boolean hasRenderFrame(){
        return mRenderFrame != null;
    }

    public PlatformViewManager getPlatformViewManager() {
        if(mPlatformViewManager == null){
            mPlatformViewManager = new PlatformViewManager(this);
        }
        return mPlatformViewManager;
    }

    public RenderFrame getRenderFrame(){
        if(mRenderFrame == null){
            mRenderFrame = new RenderFrame(getContext());
        }
        return mRenderFrame;
    }


    public void setRenderViewFrame(RenderFrame mRenderFrame) {
        if(mRenderFrame.getPageId() == null){
            throw new RuntimeException("Frame Should Have One Pade Id, Should be be remove first");
        }
        this.mRenderFrame = mRenderFrame;
        if(mHasAttachToWindow){
            throw new RuntimeException("setRenderViewFrame should be be remove first");
        }
        RenderManager.getInstance().registerRenderView(mRenderFrame.getPageId(), this);
   }




    public void destroy(){
        if(mRenderFrame != null){
            mRenderFrame.destory();
        }
    }



    @Override
    protected void finalize() throws Throwable {
        destroy();
        super.finalize();
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        if(mRenderFrame == null){
            return;
        }
        if(width == 0 || height == 0){
            return;
        }
        mRenderFrame.setPause(false);
        if(mSurfaceTextureHolder == null){
            mSurfaceTextureHolder = new SurfaceTextureHolder(null, width, height);
            mSurfaceTextureHolder.setSurface(holder.getSurface());
            mNativeSurface = RenderBridge.getInstance().frameRenderAttach(mRenderFrame.getPageId(), mSurfaceTextureHolder.getSurface(), mUseSurfaceView, width, height);
        }else{
            RenderBridge.getInstance().frameRenderSizeChanged(mRenderFrame.getPageId(), width, height);
        }
        mVsyncController.start();
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        mVsyncController.stop();
        if(mSurfaceTextureHolder != null){
             RenderBridge.getInstance().frameRenderDettach(mNativeSurface, mRenderFrame.getPageId(), mSurfaceTextureHolder.getSurface());
        }
        mSurfaceTextureHolder = null;
    }

    @Override
    public void onVsync(long frameTimeMS) {
        if(mSurfaceTextureHolder == null){
            return;
        }
        if(mRenderFrame == null){
            return;
        }
        RenderBridge.getInstance().frameRenderOnVsync(mRenderFrame.getPageId(), frameTimeMS);
    }

    public void onActivityResume(){
        if(mSurfaceTextureHolder != null){
            RenderBridge.getInstance().frameRenderOnResume(mRenderFrame.getPageId());
            mVsyncController.start();
        }
        if(mPlatformViewManager != null){
            mPlatformViewManager.onResume();
        }
    }

    public void onActivityPause(){
        if(mSurfaceTextureHolder != null){
            RenderBridge.getInstance().frameRenderOnPause(mRenderFrame.getPageId());
        }
        mVsyncController.stop();
        if(mPlatformViewManager != null){
            mPlatformViewManager.onPause();
        }
    }

    public void onActivityDestroyed(){
        mVsyncController.stop();
        if(mRenderFrame != null){
            RenderManager.getInstance().removeRenderView(mRenderFrame.getPageId());
            mRenderFrame.destory();
        }
    }

    public boolean isUseSurfaceView() {
        return mUseSurfaceView;
    }

    public View getSurfaceView(){
        return mSurfaceView;
    }

    public void setUseSurfaceView(boolean useSurfaceView) {
        this.mUseSurfaceView = useSurfaceView;
    }
}
