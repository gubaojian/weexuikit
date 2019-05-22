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
import android.os.Bundle;
import android.support.v4.view.accessibility.AccessibilityNodeInfoCompat;
import android.support.v4.widget.ExploreByTouchHelper;
import android.text.TextUtils;
import android.view.accessibility.AccessibilityNodeInfo;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.taobao.weex.render.manager.RenderManager;
import com.taobao.weex.render.frame.RenderView;

import java.util.List;

/**
 * Created by furture on 2018/8/21.
 */

public class RenderViewAccessibilityHelper extends ExploreByTouchHelper {

    private RenderView renderFrameView;
    private RenderViewAccessibilityTask renderFrameViewAccessibilityTask;

    public RenderViewAccessibilityHelper(RenderView documentTextureView) {
        super(documentTextureView);
        this.renderFrameView = documentTextureView;
    }

    @Override
    protected int getVirtualViewAt(float x, float y) {
        if(!renderFrameView.hasRenderFrame()){
            return ExploreByTouchHelper.HOST_ID;
        }
        this.renderFrameViewAccessibilityTask = new RenderViewAccessibilityTask(renderFrameView.getRenderFrame(),0, 0);
        if(!renderFrameViewAccessibilityTask.updatePoint((int)x, (int)y)){
            return renderFrameViewAccessibilityTask.getViewId();
        }
        renderFrameViewAccessibilityTask.resetCountDown();
        RenderManager.getInstance().getFrameHandler().postAtFrontOfQueue(renderFrameViewAccessibilityTask);
        renderFrameViewAccessibilityTask.waitComplete();
        return renderFrameViewAccessibilityTask.getViewId();
    }

    @Override
    protected void getVisibleVirtualViews(List<Integer> virtualViewIds) {
        if(renderFrameViewAccessibilityTask != null){
            virtualViewIds.add(renderFrameViewAccessibilityTask.getViewId());
        }
    }


    @Override
    protected void onPopulateNodeForVirtualView(int virtualViewId, AccessibilityNodeInfoCompat node) {
        node.setClassName(TextView.class.getName());
        if(renderFrameViewAccessibilityTask != null
                && virtualViewId == renderFrameViewAccessibilityTask.getViewId()){
            String type = renderFrameViewAccessibilityTask.getType();
            if(AccessibilityConstants.TAG_IMAGE.equals(type) || AccessibilityConstants.TAG_IMG.equals(type)){
                node.setClassName(ImageView.class.getName());
            }else if(AccessibilityConstants.TAG_A.equals(type)){
                node.setClassName(Button.class.getName());
            }else {
                node.setClassName(TextView.class.getName());
            }
            if(!TextUtils.isEmpty(renderFrameViewAccessibilityTask.getRole())){
                node.setRoleDescription(renderFrameViewAccessibilityTask.getRole());
            }
            node.setText( renderFrameViewAccessibilityTask.getContentDescription());
            node.setContentDescription( renderFrameViewAccessibilityTask.getContentDescription());
            node.setBoundsInParent(renderFrameViewAccessibilityTask.getBounds());
            if(renderFrameViewAccessibilityTask.hasClick()){
                node.addAction(AccessibilityNodeInfo.ACTION_CLICK);
                node.setClassName(Button.class.getName());
            }
        }else{
            node.setBoundsInParent(new Rect(0,0, renderFrameView.getRenderFrame().getFrameWidth(),
                     renderFrameView.getRenderFrame().getFrameHeight()));
            node.setContentDescription("");
        }
        node.addAction(AccessibilityNodeInfo.ACTION_FOCUS);
    }


    @Override
    protected boolean onPerformActionForVirtualView(int virtualViewId, int action, Bundle arguments) {
        return false;
    }
}
