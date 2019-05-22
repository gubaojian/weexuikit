package com.test.weex.render.picasso;

import android.net.Uri;

import com.squareup.picasso.MemoryPolicy;
import com.squareup.picasso.Picasso;
import com.squareup.picasso.RequestCreator;
import com.taobao.weex.render.image.RequestImage;
import com.taobao.weex.render.image.ImageAdapter;
import com.taobao.weex.render.manager.RenderManager;
import com.taobao.weex.render.frame.RenderFrame;

/**
 * Created by furture on 2018/8/10.
 */

public class PicassoImageAdapter extends ImageAdapter {

    @Override
    public RequestImage requestImage(String requestKey, String pageId, String ref, String url, final int width, final int height, long callbackId) {
        if(url.startsWith("//")){
            url = "https:" + url;
        }
        final String realUrl = url;
        PicassoImageTarget picassoRequestImage = new PicassoImageTarget(requestKey, pageId, ref, url, width, height, callbackId);
        final PicassoImageTarget requestTarget  = picassoRequestImage;
        RenderManager.getInstance().getUiHandler().post(new Runnable() {
            @Override
            public void run() {
                RequestCreator creator = Picasso.get().load(Uri.parse(realUrl));
                if(width > 0 && height > 0){
                    creator.resize(width, height);
                }
                creator.into(requestTarget);
            }
        });
        return picassoRequestImage;
    }
}
