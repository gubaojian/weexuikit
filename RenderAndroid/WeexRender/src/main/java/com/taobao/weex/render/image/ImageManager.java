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

import android.util.LruCache;

import com.taobao.weex.render.bridge.RenderBridge;
import com.taobao.weex.render.sdk.RenderSDK;

import java.lang.ref.WeakReference;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Created by furture on 2018/8/20.
 */

public class ImageManager {

    private LruCache<String,WeakReference<RequestImage>> mImageLruCaches;
    private ConcurrentHashMap<String, RequestImage> mRequestImages;

    private ImageManager(){
         mImageLruCaches = new LruCache<>(256);
         mRequestImages = new ConcurrentHashMap<>();
    }


    private static ImageManager cacheInstance;

    public static ImageManager getInstance(){
        if(cacheInstance == null){
            synchronized (ImageManager.class){
                if(cacheInstance == null) {
                    cacheInstance = new ImageManager();
                }
            }
        }
        return cacheInstance;
    }


    public RequestImage getRequestImage(String key){
        WeakReference<RequestImage> imageCacheRef = mImageLruCaches.get(key);
        if(imageCacheRef == null){
            return null;
        }
        return imageCacheRef.get();
    }



    public void clear(){
        mImageLruCaches.evictAll();
    }


    public void onRequestImage(String requestKey, RequestImage requestImage) {
        mRequestImages.put(requestKey, requestImage);
    }

    public void onLoadImage(RequestImage requestImage){
        String requestKey = requestImage.getRequestKey();
        //FIXME DO CALLLBACK
        RenderBridge.getInstance().actionOnLoadImage(requestImage);
        mRequestImages.remove(requestKey);
    }
}
