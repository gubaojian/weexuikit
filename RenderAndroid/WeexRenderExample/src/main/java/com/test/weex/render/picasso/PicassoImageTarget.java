package com.test.weex.render.picasso;

import android.graphics.Bitmap;
import android.graphics.drawable.Drawable;

import com.squareup.picasso.Picasso;
import com.squareup.picasso.Target;
import com.taobao.weex.render.image.ImageManager;
import com.taobao.weex.render.image.ImageProcessor;
import com.taobao.weex.render.frame.RenderFrame;
import com.taobao.weex.render.image.RequestImage;

/**
 * Created by furture on 2018/7/24.
 */

public class PicassoImageTarget implements RequestImage, Target {
    private String mRequestKey;
    private String mPageId;
    private String mRef;
    private String mUrl;
    private int mWidth;
    private int mHeight;
    private long mCallbackId;
    private int mLoadingState;

    private Bitmap mBitmap;

    public PicassoImageTarget(String requestKey, String pageId, String ref, String url, int width, int height, long callbackId) {
        this.mRequestKey = requestKey;
        this.mPageId = pageId;
        this.mRef = ref;
        this.mUrl = url;
        this.mWidth = width;
        this.mHeight = height;
        this.mCallbackId = callbackId;
        this.mLoadingState = LOADING;
    }

    @Override
    public String getRequestKey() {
        return mRequestKey;
    }

    @Override
    public String getPageId() {
        return mPageId;
    }

    @Override
    public String getRef() {
        return mRef;
    }

    @Override
    public String getUrl() {
        return mUrl;
    }

    @Override
    public int getWidth() {
        return mWidth;
    }

    @Override
    public int getHeight() {
        return mHeight;
    }

    @Override
    public long getCallbackId() {
        return mCallbackId;
    }

    @Override
    public Bitmap getBitmap() {
        return mBitmap;
    }

    @Override
    public int getLoadingState() {
        return mLoadingState;
    }


    @Override
    public void onBitmapLoaded(Bitmap bitmap, Picasso.LoadedFrom from) {
        mBitmap = bitmap;
        ImageProcessor.toRenderSupportImage(this);
    }

    @Override
    public void onSupportedBitmap(Bitmap bitmap) {
        mBitmap = bitmap;
        mLoadingState  = LOADING_SUCCESS;
        ImageManager.getInstance().onLoadImage(this);
    }

    @Override
    public void onBitmapFailed(Exception e, Drawable errorDrawable) {
        mLoadingState  = LOADING_FAILED;
        ImageManager.getInstance().onLoadImage(this);
    }

    @Override
    public void onPrepareLoad(Drawable placeHolderDrawable) {

    }
}
