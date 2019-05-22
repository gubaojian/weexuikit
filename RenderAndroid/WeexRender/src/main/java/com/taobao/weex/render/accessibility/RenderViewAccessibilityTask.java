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
package com.taobao.weex.render.accessibility;

import android.graphics.Rect;
import android.support.v4.widget.ExploreByTouchHelper;
import android.text.TextUtils;

import com.taobao.weex.render.frame.RenderFrame;

import java.util.concurrent.CountDownLatch;

/**
 * Created by furture on 2018/8/21.
 */

public class RenderViewAccessibilityTask implements  Runnable{


    private int x;
    private int y;
    private String ref;
    private String type;
    private String role;
    private String contentDescription;
    private boolean hasClick;
    private Rect bounds;
    private CountDownLatch countDownLatch;
    private RenderFrame renderFrame;

    public RenderViewAccessibilityTask(RenderFrame renderFrame, int x, int y) {
        this.renderFrame = renderFrame;
        this.x = x;
        this.y = y;
        this.bounds = new Rect();
    }


    @Override
    public void run() {
        /**
        String pageId = renderFrame.getPageId();
        if(pageId == null){
            countDownLatch.countDown();
            return;
        }
        ref = RenderBridge.getInstance().actionHitTestEvent(pageId, AccessibilityConstants.EVENT_TYPE_ACCESSIBILITY, x, y);
        if(!TextUtils.isEmpty(ref)){
            type = RenderBridge.getInstance().getNodeType(pageId, ref);
            role = RenderBridge.getInstance().getNodeAttr(pageId, ref, AccessibilityConstants.ROLE);
            contentDescription = RenderBridge.getInstance().getNodeAttr(pageId, ref, AccessibilityConstants.ARIA_LABEL);
            int left = RenderBridge.getInstance().getBlockLayout(pageId, ref, 0);
            int top = RenderBridge.getInstance().getBlockLayout(pageId, ref, 1);
            int width = RenderBridge.getInstance().getBlockLayout(pageId, ref, 2);
            int height = RenderBridge.getInstance().getBlockLayout(pageId, ref, 3);
            this.bounds.set(left, top, left + width, top + height);
            hasClick = RenderBridge.getInstance().nodeContainsEvent(pageId, ref, AccessibilityConstants.EVENT_CLICK);
        }*/
        countDownLatch.countDown();
    }


    public boolean updatePoint(int x, int y){
        if(this.x != x || this.y != y){
            this.x = x;
            this.y = y;
            return true;
        }
        return false;
    }

    public int getViewId(){
        if(TextUtils.isEmpty(ref) || TextUtils.isEmpty(contentDescription)){
            return ExploreByTouchHelper.INVALID_ID;
        }
        if(bounds.height() <= 0 || bounds.width() <= 0){
            return ExploreByTouchHelper.INVALID_ID;
        }
        return ref.hashCode();
    }

    public String getRole() {
        return role;
    }

    public String getContentDescription() {
        if(contentDescription == null){
            contentDescription = "none content";
        }
        return contentDescription;
    }

    public Rect getBounds() {
        return bounds;
    }

    public String getType() {
        return type;
    }

    public boolean hasClick() {
        return hasClick;
    }

    public void waitComplete(){
        try {
            countDownLatch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void resetCountDown() {
        this.countDownLatch = new CountDownLatch(1);
    }

}
