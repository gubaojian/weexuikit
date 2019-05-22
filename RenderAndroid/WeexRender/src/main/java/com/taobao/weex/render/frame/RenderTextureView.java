package com.taobao.weex.render.frame;

import android.content.Context;
import android.util.AttributeSet;
import android.view.TextureView;
import android.view.View;

public class RenderTextureView extends TextureView {


    public RenderTextureView(Context context) {
        super(context);
        initView();
    }

    public RenderTextureView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public RenderTextureView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    public RenderTextureView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        initView();
    }

    private void initView(){
        if(getLayerType() != View.LAYER_TYPE_HARDWARE) {
            setLayerType(View.LAYER_TYPE_HARDWARE, null);
        }
    }
}
