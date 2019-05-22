package com.test.weex.render.activity;

import android.graphics.PointF;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.LinearSmoothScroller;
import android.support.v7.widget.RecyclerView;
import android.text.TextUtils;
import android.util.Log;

import com.taobao.weex.uikit.demo.R;

import static android.widget.NumberPicker.OnScrollListener.SCROLL_STATE_FLING;

public class RecycleViewListJSONActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_textture_list);

        String json = null;
        if(!TextUtils.isEmpty(getIntent().getStringExtra("fileName"))){
            json =  FileUtils.loadAsset(getIntent().getStringExtra("fileName"), this);
        }
        if(TextUtils.isEmpty(json)){
            json = ListTextureViewAdapter.getRichText(this);
        }
        final RecyclerView recyclerView =  findViewById(R.id.recycle_view);
        ListTextureViewAdapter  listTextureViewAdapter = new ListTextureViewAdapter();
        listTextureViewAdapter.setJson(json);
        recyclerView.setAdapter(listTextureViewAdapter);
        recyclerView.setLayoutManager(new LinearLayoutManager(this){
            @Override
            protected int getExtraLayoutSpace(RecyclerView.State state) {
                int space = super.getExtraLayoutSpace(state);
                return  space + getBaseContext().getResources().getDisplayMetrics().widthPixels;
            }

            @Override
            public void smoothScrollToPosition(RecyclerView recyclerView, RecyclerView.State state, int position) {

                final LinearSmoothScroller linearSmoothScroller = new LinearSmoothScroller(recyclerView.getContext()) {

                    @Override
                    public PointF computeScrollVectorForPosition(int targetPosition) {
                        return super.computeScrollVectorForPosition(targetPosition);
                    }

                };

                linearSmoothScroller.setTargetPosition(position);
                startSmoothScroll(linearSmoothScroller);
            }
        });
        recyclerView.setClipToPadding(false);
        recyclerView.setClipChildren(false);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            recyclerView.setClipToOutline(false);
        }
        recyclerView.getAdapter().notifyDataSetChanged();
        recyclerView.getLayoutManager().setItemPrefetchEnabled(true);
        recyclerView.addOnScrollListener(new RecyclerView.OnScrollListener() {
            @Override
            public void onScrollStateChanged(RecyclerView recyclerView, int newState) {
                super.onScrollStateChanged(recyclerView, newState);
                Log.e("Weex", "Weex state " + newState);
                if(newState == SCROLL_STATE_FLING){
                    //RenderFrameView.isIde = false;
                }else{
                   // RenderFrameView.isIde = false;
                    //RenderFrameView.isIde = true;
                }
            }
        });

    }
}
