package com.test.weex.render.activity;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import com.taobao.weex.uikit.demo.R;
import com.taobao.weex.render.event.FrameAdapter;
import com.taobao.weex.render.event.OnFrameSizeChangedListener;
import com.taobao.weex.render.event.OnFrameEventListener;
import com.taobao.weex.render.event.OnFrameImageListener;
import com.taobao.weex.render.image.RequestImage;
import com.taobao.weex.render.frame.RenderView;
import com.taobao.weex.render.frame.RenderFrame;
import com.test.weex.render.task.RenderFrameJSONTask;

public class RenderJsonActivity extends AppCompatActivity {


    private RenderView renderView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rich_text_demo);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
        String json = null;
        String fileName =  getIntent().getStringExtra("fileName");

        renderView =  findViewById(R.id.render_view);
        renderView.createSurfaceView();
        if(!TextUtils.isEmpty(getIntent().getStringExtra("imagetest"))){
            //RenderBridge.image_test = true;
        }

        if(!TextUtils.isEmpty(fileName)){
            long start = System.currentTimeMillis();
            json =  FileUtils.loadAsset(fileName, this);
            Log.e("Render", "Render read used " + (System.currentTimeMillis() -start));
        }
        if(TextUtils.isEmpty(json)){
            json = ListTextureViewAdapter.getRichText(this);
            fileName = "richText";
        }

        final RenderFrame renderFrame = new RenderFrame(this);
        FrameAdapter renderFrameAdapter = new FrameAdapter();
        renderFrameAdapter.setOnFrameEventListener(new OnFrameEventListener() {
            @Override
            public void onClick(String ref, int x, int y, int width, int height) {
                Toast.makeText(getBaseContext(), " ref " + ref, Toast.LENGTH_SHORT).show();
            }
        });
        renderFrameAdapter.setOnImgLoadListener(new OnFrameImageListener() {
            @Override
            public void onLoadImage(RequestImage imageTarget) {
               // Toast.makeText(getBaseContext(), "load image success " + imageTarget.getUrl(), Toast.LENGTH_SHORT).show();
            }
        });
        renderFrameAdapter.setOnFrameSizeChangedListener(new OnFrameSizeChangedListener() {
            @Override
            public void onSizeChanged(RenderFrame renderFrame, int width, int height) {
                ViewGroup.LayoutParams params = renderView.getLayoutParams();
                //params.width = width;
                //params.height = height;
                //renderView.setLayoutParams(params);
            }
        });
        renderFrame.setFrameAdapter(renderFrameAdapter);
        renderFrame.setPageId(String.valueOf(this.hashCode()));
        renderView.setRenderViewFrame(renderFrame);

        new Thread(new RenderFrameJSONTask(fileName, json, renderFrame)).start();







        /**
        DisplayManager displayManager = (DisplayManager) getBaseContext().getSystemService(Context.DISPLAY_SERVICE);
        DisplayMetrics displayMetrics = getBaseContext().getResources().getDisplayMetrics();
        SurfaceTexture surfaceTexture = new SurfaceTexture(10);
        Surface surface = new Surface(surfaceTexture);
        VirtualDisplay virtualDisplay = displayManager.createVirtualDisplay("love", 100, 100,
                displayMetrics.densityDpi, surface, 0);
        Display[] displays = displayManager.getDisplays();
        Presentation presentation = new Presentation(this, displays[1]);
        FrameLayout frameLayout = new FrameLayout(this);
        TextView textView = new TextView(this);
        textView.setText("Hello World");
        frameLayout.addView(textView);

        presentation.setContentView(frameLayout);
        RVideoPlayer video = new RVideoPlayer(this);
        video.createIfNotExist();
        video.setVideoURI(Uri.parse("http://flv2.bn.netease.com/videolib3/1611/01/XGqSL5981/SD/XGqSL5981-mobile.mp4"));
        frameLayout.addView(video, new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, 200));

        REditText editText = new REditText(this);
        frameLayout.addView(editText, new FrameLayout.LayoutParams(400, 400));
        video.start();
        frameLayout.requestFocus();
        editText.requestFocus();
        presentation.show();


        /***/




    }






}
