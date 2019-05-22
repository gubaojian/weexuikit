package com.taobao.weex.render.platform.view.video;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.MediaController;

public class RMediaController extends MediaController {

    private boolean hasTouched;

    public RMediaController(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public RMediaController(Context context, boolean useFastForward) {
        super(context, useFastForward);
    }

    public RMediaController(Context context) {
        super(context);
    }

    @Override
    public void show() {
        if(hasTouched){
            try{
                super.show();
            }catch (Exception e){}
        }
    }


    public void setHasTouched(boolean hasTouched) {
        this.hasTouched = hasTouched;
    }
}
