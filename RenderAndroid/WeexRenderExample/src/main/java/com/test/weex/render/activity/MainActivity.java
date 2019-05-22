package com.test.weex.render.activity;

import android.content.Intent;
import android.os.Debug;
import android.os.Trace;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.taobao.weex.render.log.RenderLog;
import com.taobao.weex.render.sdk.RenderSDK;
import com.taobao.weex.uikit.demo.R;
import com.test.weex.render.picasso.PicassoImageAdapter;

import java.lang.reflect.Method;

public class MainActivity extends AppCompatActivity {




    private String[][] demoList = {
            {"Weex List Demo", "weexlist.json"},
            {"Slider Demo", "slider.json"},
            {"You Hao Huo Demo", "youhaohuo.json"},
            {"Horizontal List Demo", "youhaohuoHorizontal.json"},
            {"Star Bucks Demo", "starBucks.json"},
            {"Native Video View List", "videoList.json"},
            {"Native Input View List", "inputList.json"},
            {"Native WebView List", "webList.json"},
            {"Full Border Style", "borderStyles.json"},
            {"Box Shadow", "boxshadow.json"},
            {"RichText Demo", "richtext.json"},
            {"TextStyle Demo", "textstyle.json"},
            {"Text Shadow", "textshadow.json"},
            {"Background Linear", "backgroundLinear.json"},
            {"Background Image", "backgroundImage.json"},
            {"Background Size", "backgroundSizeImage.json"},
            {"Background Position", "backgroundPosition.json"},
            {"ZIndex", "zindex.json"},
            {"Transform", "transform.json"},
            {"TransformSkew", "transformSkew.json"},
            {"TransformMatrix", "transformMatrix.json"},
            {"TransformOrigin", "transformOrigin.json"},
            {"TransformStyle", "transformStyle.json"},
            {"Transition", "transition.json"},
            {"Opacity", "opacity.json"},
            {"Absolute", "absolute.json"},
            {"Button Click", "json/buttonClick.json"},
            {"Animation Demo", "animation.json"},
            {"Texture Demo", "texture.json"},
            {"BenchMark Text 786", "bench786.json"},
            {"BenchMark Text 12948", "bench12948.dat"},
            {"Item Card Demo", "card.json"},
            {"Item Card Demo2", "cardshopitem.json"},
            {"IconFont Demo", "iconfont.json"},
            {"FlexBasis", "flexbasis.json"},
            {"Fei Zu", "log/feizu.log"},
            {"Da Tong", "log/datong.log"},
            {"Hao Dian", "log/haodian.log"},
            {"Shen Dian", "log/shendian.log"},
            {"Shop Header", "log/shopheader.log"},
            {"Tmall", "log/tmall.log"},
            {"Xianyu", "log/xianyucard.log"},
            {"JiYouJia", "log/jiyoujia.log"},
            {"Tmall", "tmall.json"},
            {"Jin Kou", "log/jinkou.log"},
            {"Chao Liu Qing Dan", "log/chaoliuchuanda.log"},
            {"Ka Quan", "log/kaquan.log"},
            {"Me Nu", "log/menu.log"},
            {"Promotion", "log/promotion.log"},
            {"Shu Ma", "log/shumaheader.log"},
            {"Shu Ma2", "log/shumaheader2.log"},
            {"Yu Sou Card", "log/yusoucard.log"},
            {"JinDian Card", "log/jindiancard.log"},
            {"JinDian", "jindian.json"},
            {"Bug Header", "bugheader.json"},
            {"Scroller", "scroller.json"},
            {"Scroller Image", "scrollerlist.json"},
            {"Weex List Small Demo", "weexlistsmall.json"},
            {"Weex Animation", "weexlistAnimation.json"},
            {"HuiChang Demo", "huichang.json"},
            {"Input", "input.json"},
            {"¥ 29.8", "¥ 29.8"},
            {"Demo", "Demo"},
            {"Scroller Clip", "scrollerclip.json"},
            {"FontSize Style", "json/fontSize.json"},
    };


    private RecyclerView recycle_view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        DataUtils.initImgs(this);
        RenderLog.openDebugLog(true);
        RenderSDK.getInstance().setmImageAdapter(new PicassoImageAdapter()).setApplication(getApplication()).init();

        System.setProperty("ro.debuggable", "1");


        try{
            Method setAppTracingAllowedMethod = Trace.class.getMethod("setAppTracingAllowed", boolean.class);
            if(setAppTracingAllowedMethod != null){
                setAppTracingAllowedMethod.invoke(null, true);
            }
            Method setTracingEnabledMethod = Trace.class.getMethod("setTracingEnabled", boolean.class);
            if(setTracingEnabledMethod != null){
                setTracingEnabledMethod.invoke(null, true);
            }
        }catch (Exception e){
            Log.e("Weex", "Weex render" ,e);
        }

        recycle_view = findViewById(R.id.recycle_view);
        recycle_view.setLayoutManager(new LinearLayoutManager(getBaseContext()));
        recycle_view.setAdapter(new RecyclerView.Adapter<RecyclerItemDemoViewHolder>(){
            @NonNull
            @Override
            public RecyclerItemDemoViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int position) {

                View view = LayoutInflater.from(getBaseContext()).inflate(R.layout.demo_recycleview_item, null);
                return new RecyclerItemDemoViewHolder(view);
            }

            @Override
            public void onBindViewHolder(@NonNull RecyclerItemDemoViewHolder viewHolder, final int position) {
                TextView textView = viewHolder.itemView.findViewById(R.id.demo_text);


                textView.setText(demoList[position][0]);
                View.OnClickListener showInCardOnClickListener = new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        String[] item = demoList[position];
                        if(item[1].endsWith(".log")){
                            Intent intent = new Intent(getBaseContext(), RenderLogActivity.class);
                            intent.putExtra("fileName", item[1]);
                            startActivity(intent);
                        }else{
                            Intent intent = new Intent(getBaseContext(), RenderJsonActivity.class);
                            intent.putExtra("fileName", item[1]);
                            startActivity(intent);
                        }
                    }
                };
                viewHolder.itemView.setOnClickListener(showInCardOnClickListener);
                viewHolder.itemView.findViewById(R.id.show_in_card).setOnClickListener(showInCardOnClickListener);

                View.OnClickListener showInListOnClickListener = new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        String[] item = demoList[position];
                        if(item[1].endsWith(".log")){
                            return;
                        }
                        Intent intent = new Intent(getBaseContext(), RecycleViewListJSONActivity.class);
                        intent.putExtra("fileName", item[1]);
                        startActivity(intent);
                    }
                };
                viewHolder.itemView.findViewById(R.id.show_in_list).setOnClickListener(showInListOnClickListener);


            }

            @Override
            public int getItemCount() {
                return demoList.length;
            }
        });

        recycle_view.setOnFlingListener(new RecyclerView.OnFlingListener() {
            @Override
            public boolean onFling(int x, int y) {
                return false;
            }
        });

    }
}
