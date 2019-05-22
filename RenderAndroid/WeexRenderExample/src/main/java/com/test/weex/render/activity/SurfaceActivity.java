package com.test.weex.render.activity;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.SurfaceView;

import com.taobao.weex.uikit.demo.R;

public class SurfaceActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_surface);


        SurfaceView surfaceView = findViewById(R.id.flutter_surface);



    }

}
