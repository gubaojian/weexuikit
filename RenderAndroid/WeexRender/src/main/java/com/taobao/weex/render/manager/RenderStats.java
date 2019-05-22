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
package com.taobao.weex.render.manager;

import android.app.Activity;
import android.content.Context;

import com.taobao.weex.render.log.RenderLog;

import java.util.concurrent.atomic.AtomicInteger;

public class RenderStats {

    private static AtomicInteger elgNum = new AtomicInteger(0);

    public static AtomicInteger getElgNum(){
        return elgNum;
    }

    public static void showRenderStats() {
        if(RenderLog.isDebugLogEnabled()){
            RenderLog.debug("RenderStats stats frameNum "
                            + RenderManager.getInstance().getRenderViewMap().size()
                            + " dettach num " + periodDettachNum
                            + " eglNum " + elgNum.get());
        }
    }

    public static int getPeriodDettachNum() {
        return periodDettachNum;

    }


    /**
     * when fast fling,render when don't block main thread like normal view.
     * which lead to scroll so fast. and async render not responsive to screen.
     * so when fling too fast. when sleep while, which like normal view's layout and draw cost
     * and wait render to screen.
     * */
    public static void countPeriodDettachNum(Context context) {
        if(context instanceof Activity){
            Activity activity = (Activity) context;
            if(activity.isFinishing()){
                periodDettachNum = 0;
                return;
            }
        }
        if((System.currentTimeMillis() - lastDettachCountTime) > DETTACH_COUNT_PERIOD_TIME){
            lastDettachCountTime = System.currentTimeMillis();
            periodDettachNum = 1;
        }else{
            periodDettachNum++;
            if(periodDettachNum > MAX_DETTACH_NUM_ONE_PERIOD){
                if(sleepTime > 0){
                    try {
                        Thread.sleep(sleepTime);
                    } catch (InterruptedException e) {}
                }
            }
        }
        if(RenderLog.isDebugLogEnabled()){
            RenderLog.debug("RenderStats second dettach num " + periodDettachNum);
        }
    }

    /**
     * when fast fling,render when don't block main thread like normal view.
     * which lead to scroll so fast. and async render not responsive to screen.
     * so when fling too fast. when sleep while, which like normal view's layout and draw cost
     * and wait render to screen.
     * */
    private static int periodDettachNum;
    private static long lastDettachCountTime;
    private static long DETTACH_COUNT_PERIOD_TIME = 1600;
    public static int MAX_DETTACH_NUM_ONE_PERIOD = 12;
    public static long sleepTime = 4;
}
