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
package com.taobao.weex.render.image;

import com.taobao.weex.render.frame.RenderFrame;

/**
 * Created by furture on 2018/8/10.
 */

public abstract class ImageAdapter {


    public abstract RequestImage requestImage(String requestKey, String pageId, String ref, String url, int width, int height, long callbackId);


    public String genRequestKey(String url, int width, int height){
        StringBuilder stringBuilder = new StringBuilder(url);
        stringBuilder.append('@');
        stringBuilder.append(width);
        stringBuilder.append('@');
        stringBuilder.append(height);
        return stringBuilder.toString();
    }


}
