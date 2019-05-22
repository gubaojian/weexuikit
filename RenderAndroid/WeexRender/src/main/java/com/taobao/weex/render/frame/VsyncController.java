package com.taobao.weex.render.frame;

import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.view.Choreographer;

import java.lang.ref.WeakReference;

public class VsyncController implements Runnable{

    private WeakReference<VsyncListener> mVsyncListenerRef;
    private Choreographer.FrameCallback mVSyncFrameCallback;
    private boolean mStart;
    private Handler mHandler;


    public VsyncController(VsyncListener vsyncListener) {
        this.mVsyncListenerRef = new WeakReference<>(vsyncListener);
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.JELLY_BEAN) {
            mHandler = new Handler(Looper.getMainLooper());
        }else{
            mVSyncFrameCallback = new Choreographer.FrameCallback(){
                @Override
                public void doFrame(long frameTimeNanos) {
                    VsyncController.this.onVsyncFrame(frameTimeNanos);
                    if(!mStart){
                        return;
                    }
                    Choreographer.getInstance().postFrameCallback(mVSyncFrameCallback);
                }
            };
        }
    }

    public void start(){
        if(!mStart){
            mStart = true;
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN) {
                Choreographer.getInstance().postFrameCallback(mVSyncFrameCallback);
            }else{
                mHandler.post(this);
            }
        }
    }
    public void stop() {
        if (mStart) {
            mStart = false;
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN) {
                Choreographer.getInstance().removeFrameCallback(mVSyncFrameCallback);
            }else{
                mHandler.removeCallbacks(this);
            }
        }
    }

    public void onVsyncFrame(long frameTimeNanos) {
        VsyncListener vsyncListener = mVsyncListenerRef.get();
        if(vsyncListener == null){
            return;
        }
        if(!mStart){
            return;
        }
        vsyncListener.onVsync(frameTimeNanos);
    }

    @Override
    public void run() {
        long start = System.currentTimeMillis();
        long frameTimeNanos = start*1000000;
        onVsyncFrame(frameTimeNanos);
        long used = System.currentTimeMillis()-start;
        requestNextFrame(used);
    }

    private void requestNextFrame(long used) {
        long nextFrameTime = 16 - used -1;
        if(nextFrameTime <= 0){
            mHandler.post(this);
        }else{
            mHandler.postDelayed(this, nextFrameTime);
        }
    }


    public interface VsyncListener {
        void onVsync(long frameTimeMS);
    }
}
