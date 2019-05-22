package com.test.weex.render.activity;

import android.content.Context;
import android.os.AsyncTask;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.taobao.weex.uikit.demo.R;
import com.taobao.weex.render.event.FrameAdapter;
import com.taobao.weex.render.event.OnFrameSizeChangedListener;
import com.taobao.weex.render.frame.RenderView;
import com.taobao.weex.render.frame.RenderFrame;
import com.test.weex.render.task.RenderFrameJSONTask;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;


/**
 * Created by furture on 2018/5/28.
 */

public class ListTextureViewAdapter extends RecyclerView.Adapter<ItemViewHolder> {


    private JSONObject jsonSource;
    private List<String> arrays;

    @Override
    public ItemViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.activity_list_texture_item, parent, false);
        return new ItemViewHolder(view);
    }

    @Override
    public void onBindViewHolder(final ItemViewHolder holder, int position) {
        final RenderView normalView  = holder.itemView.findViewById(R.id.canvas_container);
       long start = System.currentTimeMillis();


        AsyncTask.execute(new RenderFrameJSONTask(String.valueOf(position), arrays.get(position), normalView.getRenderFrame()));
        FrameAdapter renderFrameAdapter = new FrameAdapter();
        renderFrameAdapter.setOnFrameSizeChangedListener(new OnFrameSizeChangedListener() {
            @Override
            public void onSizeChanged(RenderFrame renderFrame, int x, int y) {
                if(renderFrame.getFrameHeight() <= 0
                        || renderFrame.getFrameWidth() <= 0){
                    return;
                }
                if(normalView.getWidth() != renderFrame.getFrameWidth()
                        || normalView.getHeight() != renderFrame.getFrameHeight()){
                    LinearLayout.LayoutParams params = (LinearLayout.LayoutParams) normalView.getLayoutParams();
                    params.width = renderFrame.getFrameWidth();
                    params.height = renderFrame.getFrameHeight();
                    normalView.setLayoutParams(params);
                }
            }
        });
        normalView.getRenderFrame().setFrameAdapter(renderFrameAdapter);

        LinearLayout.LayoutParams params = (LinearLayout.LayoutParams) normalView.getLayoutParams();
        if(normalView.getRenderFrame().getFrameHeight() > 0) {
            params.width = normalView.getRenderFrame().getFrameWidth();
            params.height = normalView.getRenderFrame().getFrameHeight();
        }
        normalView.setLayoutParams(params);

    }

    @Override
    public int getItemViewType(int position) {
        return position;
    }

    @Override
    public int getItemCount() {
        return 100;
    }



    public void setJson(String json) {
        try {
            this.jsonSource = new JSONObject(json);
            arrays = new ArrayList<>();
            for(int i=0; i<getItemCount(); i++){
                arrays.add(DataUtils.getImgs(jsonSource, i));
            }
        } catch (JSONException e) {
            e.printStackTrace();
            Log.e("Weex", "Weex setJSON" ,e);
        }
    }

    public static final String getRichText(Context context){
        if(richText == null){
            richText = FileUtils.loadAsset("richtext.json", context);
        }
        return richText;
    }
    private static String richText = null;


    public static final String getRichTextSmall(Context context){
        if(richTextSmall == null){
            richTextSmall = FileUtils.loadAsset("richtextsmall.json", context);
        }
        return richTextSmall;
    }
    private static String richTextSmall = null;
}
