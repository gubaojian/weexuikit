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
package com.taobao.weex.render.fling;

import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.AbsListView;
import android.widget.HorizontalScrollView;
import android.widget.ScrollView;

import java.lang.reflect.Field;


public class FlingControl {



    /**
     * limit
     * */
    public static int getLimitMaxFlingVelocity(int maxFlingVelocity){
        return (int) (maxFlingVelocity*mLimitFactor);
    }

    /**
     * return velocity between[-maxFlingVelocity, maxFlingVelocity]
     * */
    public static int getVelocity(int velocity, int maxFlingVelocity){
        if(velocity > maxFlingVelocity){
            velocity = maxFlingVelocity;
        }
        if(velocity < -maxFlingVelocity){
            velocity = -maxFlingVelocity;
        }
        return velocity;
    }

    /**
     * auto slow down max fling speed.
     * */
    public static void setParentMaxFling(View view){
        View parent = view;
        while (parent != null){
            if(parent instanceof MaxFlingVelocity){
                ((MaxFlingVelocity) parent).setMaxFlingVelocityEnabled(true);
                break;
            }
            if(parent instanceof RecyclerView){
                setRecycleViewMaxFlingVelocity((RecyclerView) parent);
                break;
            }
            if(parent instanceof ScrollView){
                setScrollViewMaxFlingVelocity((ScrollView) parent);
                break;
            }
            if(parent instanceof HorizontalScrollView){
                setHScrollViewMaxFlingVelocity((HorizontalScrollView) parent);
                break;
            }

            if(parent instanceof AbsListView){
                setAbsListViewMaxFlingVelocity((AbsListView) parent);
                break;
            }
            if(parent.getParent() instanceof View){
                parent = (View) parent.getParent();
            }else{
                break;
            }
        }
    }


    private static void setRecycleViewMaxFlingVelocity(RecyclerView recyclerView){
        if(mMaxFlingVelocityForRecyclerView == 0){
            mMaxFlingVelocityForRecyclerView = recyclerView.getMaxFlingVelocity();
        }
        try{
            Field field = RecyclerView.class.getDeclaredField("mMaxFlingVelocity");
            field.setAccessible(true);
            int velocity = (int) (mMaxFlingVelocityForRecyclerView* mMaxFactor);
            if(velocity > 0){
                field.setInt(recyclerView, velocity);
            }
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private static void setScrollViewMaxFlingVelocity(ScrollView scrollView){
        try{
            Field field = ScrollView.class.getDeclaredField("mMaximumVelocity");
            field.setAccessible(true);
            if(mMaxFlingVelocityForScrollView == 0){
                mMaxFlingVelocityForScrollView = field.getInt(scrollView);
            }
            int velocity = (int) (mMaxFlingVelocityForScrollView* mMaxFactor);
            if(velocity > 0){
                field.setInt(scrollView, velocity);
            }
        }catch (Exception e){}
    }


    private static void setHScrollViewMaxFlingVelocity(HorizontalScrollView scrollView){
        try{
            Field field = HorizontalScrollView.class.getDeclaredField("mMaximumVelocity");
            field.setAccessible(true);
            if(mMaxFlingVelocityForHScrollView == 0){
                mMaxFlingVelocityForHScrollView = field.getInt(scrollView);
            }
            int velocity = (int) (mMaxFlingVelocityForHScrollView* mMaxFactor);
            if(velocity > 0){
                field.setInt(scrollView, velocity);
            }
        }catch (Exception e){}
    }
    private static void setAbsListViewMaxFlingVelocity(AbsListView listView) {
        try{
            Field field = AbsListView.class.getDeclaredField("mMaximumVelocity");
            field.setAccessible(true);
            if(mMaxFlingVelocityForAbsList == 0){
                mMaxFlingVelocityForAbsList = field.getInt(listView);
            }
            int velocity = (int)(mMaxFlingVelocityForAbsList* mMaxFactor);
            if(velocity > 0){
                field.setInt(listView, velocity);
            }
        }catch (Exception e){}
    }

    private static int mMaxFlingVelocityForRecyclerView = 0;
    private static int mMaxFlingVelocityForScrollView = 0;
    private static int mMaxFlingVelocityForHScrollView = 0;
    private static int mMaxFlingVelocityForAbsList = 0;
    private static float mMaxFactor = 0.48f;
    private static float mLimitFactor = 0.4f;
}
