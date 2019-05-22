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
package com.taobao.weex.render.event;

/**
 * Created by furture on 2018/8/21.
 */

public class FrameAdapter {

    private OnFrameEventListener onFrameEventListener;
    private OnFrameImageListener onImgLoadListener;
    private OnFrameSizeChangedListener onFrameSizeChangedListener;

    private boolean requireFrameSizeChangedOnMainThread = true;

    public OnFrameEventListener getFrameEventListener() {
        return onFrameEventListener;
    }

    public void setOnFrameEventListener(OnFrameEventListener eventListener) {
        this.onFrameEventListener = eventListener;
    }

    public OnFrameImageListener getImgLoadListener() {
        return onImgLoadListener;
    }

    public void setOnImgLoadListener(OnFrameImageListener onImgLoadListener) {
        this.onImgLoadListener = onImgLoadListener;
    }

    public OnFrameSizeChangedListener getDocumentSizeChangedListener() {
        return onFrameSizeChangedListener;
    }

    public void setOnFrameSizeChangedListener(OnFrameSizeChangedListener onFrameSizeChangedListener) {
        this.onFrameSizeChangedListener = onFrameSizeChangedListener;
    }

    public boolean isRequireFrameSizeChangedOnMainThread() {
        return requireFrameSizeChangedOnMainThread;
    }

    public void setRequireFrameSizeChangedOnMainThread(boolean requireFrameSizeChangedOnMainThread) {
        this.requireFrameSizeChangedOnMainThread = requireFrameSizeChangedOnMainThread;
    }
}
