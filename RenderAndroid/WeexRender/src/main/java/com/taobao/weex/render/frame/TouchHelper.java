package com.taobao.weex.render.frame;

import android.view.MotionEvent;

import com.taobao.weex.render.bridge.RenderBridge;
import com.taobao.weex.render.sdk.RenderSDK;

public class TouchHelper {

    /**
     * dispatch Touch Event Helper
     * */
    public static void dispatchTouchEvent(String pageId, MotionEvent event){
        if(pageId == null){
            return;
        }
        int pointerAction = createPointer(event);
        int pointerCount = event.getPointerCount();
        float density = RenderSDK.getInstance().getDensity();
        if(pointerAction != ActionPointerMove){
            for(int i=0; i<pointerCount; i++){
                float x = event.getX(i)/density;
                float y = event.getY(i)/density;
                int pointerId = event.getPointerId(i);
                RenderBridge.getInstance().actionTouchEvent(pageId,
                        pointerAction, pointerId, x, y, System.currentTimeMillis());
            }
        }else{
            for(int i=0; i<pointerCount; i++){
                float x = event.getX(i)/density;
                float y = event.getY(i)/density;
                int pointerId = event.getPointerId(i);
                RenderBridge.getInstance().actionTouchEvent(pageId,
                        pointerAction, pointerId, x, y, System.currentTimeMillis());
            }
        }
    }


    private static int createPointer(MotionEvent motionEvent){
        int pointerAction = ActionPointerMove;
        int actionMask = motionEvent.getActionMasked();
        if(actionMask == MotionEvent.ACTION_DOWN
                || actionMask == MotionEvent.ACTION_POINTER_DOWN){
            pointerAction = ActionPointerDown;
        }else if(actionMask == MotionEvent.ACTION_UP
                || actionMask == MotionEvent.ACTION_POINTER_UP){
            pointerAction = ActionPointerUp;
        }else if(actionMask == MotionEvent.ACTION_CANCEL){
            pointerAction = ActionPointerCancel;
        }else{
            pointerAction = ActionPointerMove;
        }
        return pointerAction;
    }

    /**
     * Same Value As PointerEvent.cpp in C++ Source
     * */
    private static final int ActionPointerDown = 0;
    private static final int ActionPointerMove = 1;
    private static final int ActionPointerUp = 2;
    private static final int ActionPointerCancel = 3;


}
