package com.test.weex.render.activity;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
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
import com.test.weex.render.task.RenderFrameLogTask;

public class RenderLogActivity extends AppCompatActivity {

    private RenderView renderView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_render_log);

        String log = null;
        if(!TextUtils.isEmpty(getIntent().getStringExtra("fileName"))){
            log =  FileUtils.loadAsset(getIntent().getStringExtra("fileName"), this);
        }
        if(TextUtils.isEmpty(log)){
            Toast.makeText(getBaseContext(), "Please Pass FileName", Toast.LENGTH_SHORT).show();
            finish();
            return;
        }

        renderView = findViewById(R.id.render_view);
        renderView.createSurfaceView();
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
                Toast.makeText(getBaseContext(), "load image success " + imageTarget.getUrl(), Toast.LENGTH_SHORT).show();
            }
        });
        renderFrameAdapter.setOnFrameSizeChangedListener(new OnFrameSizeChangedListener() {
            @Override
            public void onSizeChanged(RenderFrame renderFrame, int width, int height) {
                ViewGroup.LayoutParams params = renderView.getLayoutParams();
                params.width = width;
                params.height = height;
                renderView.setLayoutParams(params);
            }
        });
        renderFrame.setFrameAdapter(renderFrameAdapter);
        renderFrame.setPageId(String.valueOf(this.hashCode()));
        renderView.setRenderViewFrame(renderFrame);
        new Thread(new RenderFrameLogTask(renderFrame, log)).start();

    }
}
