package com.test.weex.render.view;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.widget.RecyclerView;
import android.util.AttributeSet;

public class RenderRecyclerView extends RecyclerView {

    private int maxVelocityY = 8000;

    public RenderRecyclerView(@NonNull Context context) {
        super(context);
        initMaxVelocity();
    }

    public RenderRecyclerView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initMaxVelocity();
    }

    public RenderRecyclerView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        initMaxVelocity();
    }

    private void initMaxVelocity(){
        maxVelocityY = getMaxFlingVelocity()/2;
        if(maxVelocityY == 0){
            maxVelocityY = 8000;
        }
    }

    @Override
    public boolean fling(int velocityX, int velocityY) {
        /**
        if(velocityY > maxVelocityY){
            velocityY = maxVelocityY;
        }
        if(velocityY < -maxVelocityY){
            velocityY = -maxVelocityY;
        }*/
        return super.fling(velocityX, velocityY);
    }
}
