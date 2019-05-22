package com.test.weex.render.activity;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.taobao.weex.uikit.demo.R;
import com.taobao.weex.render.event.FrameAdapter;
import com.taobao.weex.render.event.OnFrameEventListener;
import com.taobao.weex.render.event.OnFrameImageListener;
import com.taobao.weex.render.image.RequestImage;
import com.taobao.weex.render.frame.RenderFrame;
import com.taobao.weex.render.frame.RenderView;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class WeexActivity extends AppCompatActivity {


    RenderView renderFrameView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_weex);
        renderFrameView = findViewById(R.id.weex_container);
        //doTestNormalImage();
        doJumpTest();

        findViewById(R.id.add_event).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                renderFrameView.getRenderFrame().actionAddEvent("567", "click");
            }
        });

        findViewById(R.id.remove_event).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                renderFrameView.getRenderFrame().actionRemoveEvent("567", "click");
            }
        });


        findViewById(R.id.add_element).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                renderFrameView.getRenderFrame().actionAddElement("568", "text","491", 0,
                        toMap("{\"fontSize\":\"40\",\"textAlign\":\"center\"}"),
                        toMap("{\"@styleScope\":\"data-v-4c58460d\",\"value\":\"酒鬼到了意大利，收不住的红酒心\"}"),
                        new ArrayList<String>());

            }
        });


        findViewById(R.id.remove_element).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                renderFrameView.getRenderFrame().actionRemoveElement("568");
            }
        });

        findViewById(R.id.move_element).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                renderFrameView.getRenderFrame().actionMoveElement("568", "491", 0);
            }
        });
    }

    private void doJumpTest(){
        RenderView renderFrameView = findViewById(R.id.weex_container);
        RenderFrame renderFrame = new RenderFrame(getBaseContext());
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
        renderFrame.setFrameAdapter(renderFrameAdapter);
        renderFrameView.setRenderViewFrame(renderFrame);
        renderFrame.actionCreateBody("1", toMap("{\n" +
                "                \"flexDirection\": \"column\",\n" +
                "                \"justifyContent\": \"center\",\n" +
                "                \"height\": \"1000\"\n" +
                "            }"), new HashMap<String, String>(), new ArrayList<String>());


        renderFrame.actionAddElement("2", "a","1", 0,
                toMap(" {\n" +
                        "                \"width\": \"450\",\n" +
                        "                \"marginTop\": \"30\",\n" +
                        "                \"marginLeft\": \"150\",\n" +
                        "                \"paddingTop\": \"20\",\n" +
                        "                \"paddingBottom\": \"20\",\n" +
                        "                \"borderWidth\": \"2\",\n" +
                        "                \"borderStyle\": \"solid\",\n" +
                        "                \"borderColor\": \"#DDDDDD\",\n" +
                        "                \"backgroundColor\": \"#F5F5F5\"\n" +
                        "            }"),
                toMap("{}"),
                new ArrayList<String>());

        renderFrame.actionAddElement("3", "text","2", 0,
                toMap("{\n" +
                        "                \"fontSize\": \"60\",\n" +
                        "                \"color\": \"#666666\",\n" +
                        "                \"textAlign\": \"center\",\n" +
                        "                \"alignSelf\": \"center\"\n" +
                        "            }"),
                toMap("{\"@styleScope\":\"data-v-4c58460d\",\"value\":\"Jump\"}"),
                new ArrayList<String>());


        renderFrame.actionAddEvent("3", "click");

    }

    private void doTestNormalImage(){
        try{
            RenderView renderFrameView = findViewById(R.id.weex_container);
            RenderFrame renderFrame = new RenderFrame(getBaseContext());
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
            renderFrame.setFrameAdapter(renderFrameAdapter);
            renderFrameView.setRenderViewFrame(renderFrame);
            renderFrame.actionCreateBody("491", new HashMap<String, String>(), new HashMap<String, String>(), new ArrayList<String>());


            renderFrame.actionAddElement("567", "text","491", 0,
                    toMap("{\"fontSize\":\"80\",\"textAlign\":\"center\"}"),
                    toMap("{\"@styleScope\":\"data-v-4c58460d\",\"value\":\"酒鬼到了意大利，收不住的红酒心\"}"),
                    new ArrayList<String>());

            HashMap<String, String> styles = new HashMap<String, String>();
            styles.put("color", "#DC143C");
            renderFrame.actionUpdateStyles("567", styles);


            renderFrame.actionAddEvent("567", "click");





            /**
            documentView.actionAddElement("494", "div","491", 0,
                    new HashMap<String, String>(),
                    new HashMap<String, String>(),
                    new ArrayList<String>());


            List<String> event = new ArrayList<String>();
            event.add("click");
            documentView.actionAddElement("497", "image","494", 0,
                    toMap("{\"backgroundColor\":\"#666666\",\"borderColor\":\"#41B883\",\"borderStyle\":\"solid\",\"borderWidth\":\"2\",\"height\":\"280\",\"width\":\"500\"}"),
                    toMap("{\"@styleScope\":\"data-v-1e780a93\",\"is_document\":\"true\",\"resize\":\"cover\",\"src\":\"https://gw.alicdn.com/tfs/TB1dZ4WowoQMeJjy0FnXXb8gFXa-950-1267.jpg\"}"),
                    event);

            documentView.actionAddElement("499", "text","494", -1,
                    toMap("{\"color\":\"#666666\",\"fontSize\":\"60\",\"textAlign\":\"center\",\"width\":\"500\"}"),
                    toMap("{\"@styleScope\":\"data-v-4c58460d\",\"value\":\"cover\"}"),
                    event);


            documentView.actionAddElement("502", "div","491", 0,
                    new HashMap<String, String>(),
                    new HashMap<String, String>(),
                    new ArrayList<String>());

            documentView.actionAddElement("505", "image","502", 0,
                    toMap("{\"backgroundColor\":\"#666666\",\"borderColor\":\"#41B883\",\"borderStyle\":\"solid\",\"borderWidth\":\"2\",\"height\":\"280\",\"width\":\"500\"}"),
                    toMap("{\"@styleScope\":\"data-v-1e780a93\",\"is_document\":\"true\",\"resize\":\"contain\",\"src\":\"https://gw.alicdn.com/tfs/TB1dZ4WowoQMeJjy0FnXXb8gFXa-950-1267.jpg\"}"),
                    new ArrayList<String>());

            documentView.actionAddElement("507", "text","502", 0,
                    toMap("{\"color\":\"#666666\",\"fontSize\":\"60\",\"textAlign\":\"center\",\"width\":\"500\"}"),
                    toMap("{\"@styleScope\":\"data-v-4c58460d\",\"value\":\"contain\"}"),
                    new ArrayList<String>());

            documentView.actionAddElement("510", "div","491", 0,
                    new HashMap<String, String>(),
                    new HashMap<String, String>(),
                    new ArrayList<String>());

            documentView.actionAddElement("513", "image","510", 0,
                    toMap(" {\"backgroundColor\":\"#666666\",\"borderColor\":\"#41B883\",\"borderStyle\":\"solid\",\"borderWidth\":\"2\",\"height\":\"280\",\"width\":\"500\"}"),
                    toMap("{\"@styleScope\":\"data-v-1e780a93\",\"is_document\":\"true\",\"resize\":\"stretch\",\"src\":\"https://gw.alicdn.com/tfs/TB1dZ4WowoQMeJjy0FnXXb8gFXa-950-1267.jpg\"}"),
                    new ArrayList<String>());

            documentView.actionAddElement("515", "a","510", 0,
                    toMap(" {\"fontSize\":\"60\",\"textAlign\":\"center\",\"width\":\"500\"}"),
                    toMap("{\"@styleScope\":\"data-v-4c58460d\",\"value\":\"stretch\"}"),
                    new ArrayList<String>());

            documentView.actionAddElement("567", "text","515", 0,
                    toMap("{\"fontSize\":\"60\",\"textAlign\":\"center\",\"width\":\"500\"}"),
                    toMap("{\"@styleScope\":\"data-v-4c58460d\",\"value\":\"stretch\"}"),
                    new ArrayList<String>());


            documentView.actionUpdateAttrs("567", toMap("{\"@styleScope\":\"data-v-4c58460d\",\"value\":\"stretch update\"}"));
             */
        }catch (Exception e){
            Log.e("Weex", "weex", e);
        }
    }

    private void doTestNormalText(){
        try{
            RenderView renderFrameView = findViewById(R.id.weex_container);
            RenderFrame renderFrame = renderFrameView.getRenderFrame();
            renderFrame.actionCreateBody("63", new HashMap<String, String>(), new HashMap<String, String>(), new ArrayList<String>());

            renderFrame.actionAddElement("66", "div","63", 0,
                    toMap("{\"alignItems\":\"center\",\"backgroundColor\":\"rgba(0,180,255,0.4)\",\"height\":\"700\",\"justifyContent\":\"center\",\"width\":\"700\"}"),
                    new HashMap<String, String>(),
                    new ArrayList<String>());

            renderFrame.actionAddElement("69", "div","66", 0,
                    toMap("{\"alignItems\":\"center\",\"backgroundColor\":\"rgba(0,180,255,0.4)\",\"height\":\"500\",\"justifyContent\":\"center\",\"width\":\"500\"}"),
                    new HashMap<String, String>(),
                    new ArrayList<String>());

            renderFrame.actionAddElement("72", "div","69", 0,
                    toMap("{\"alignItems\":\"center\",\"backgroundColor\":\"rgba(0,180,255,0.4)\",\"height\":\"300\",\"justifyContent\":\"center\",\"width\":\"300\"}"),
                    new HashMap<String, String>(),
                    new ArrayList<String>());


            renderFrame.actionAddElement("73", "text","72", 0,
                    new HashMap<String, String>(),
                    toMap("{\"@styleScope\":\"data-v-4c58460d\",\"value\":\"hello 中国\"}"),
                    new ArrayList<String>());

        }catch (Exception e){
            Log.e("Weex", "weex", e);
        }
    }

    private Map<String,String> toMap(String json){
        JSONObject object = JSON.parseObject(json);
        Set<String> keys = object.keySet();
        Map<String,String> map = new HashMap<>();
        for(String key : keys){
            map.put(key, object.getString(key));
        }
        return map;
    }


}
