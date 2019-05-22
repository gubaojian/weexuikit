// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <render/platform/common/log.h>
#include <render/frame/UIContextImpl.h>
#include <render/frame/SkiaShareContext.h>
#include <render/frame/ImageManager.h>
#include <third_party/skia/include/core/SkPictureRecorder.h>
#include "render/platform/graphics/StaticTextureImage.h"
#include "render/public/platform/Platform.h"
#include "render/platform/graphics/GraphicsContext.h"
#include "render/platform/graphics/ImageObserver.h"
#include "third_party/skia/include/core/SkImage.h"
#include "third_party/skia/include/core/SkPaint.h"
#include "third_party/skia/include/core/SkShader.h"
#include "third_party/skia/include/core/SkBitmap.h"



namespace blink {

    PassRefPtr<StaticTextureImage> StaticTextureImage::create(ImageInfo* imageInfo)
    {
        return adoptRef(new StaticTextureImage(imageInfo));
    }

    StaticTextureImage::StaticTextureImage(ImageInfo* imageInfo) : mImageInfo(imageInfo)
    {
    }

    StaticTextureImage::~StaticTextureImage() { }

    IntSize StaticTextureImage::size() const
    {
        if(mImageInfo == nullptr){
            return IntSize(0, 0);
        }
        if(mImageInfo->getUseSourceSize()){
            sk_sp<SkImage> image = weexuikit::ImageManager::getInstance()->getImage(mImageInfo);
            if(image.get() != nullptr){
                return IntSize(image->width(), image->height());
            }
        }
        return mImageInfo->getContentSize();
    }

    bool StaticTextureImage::canRender() {
        if(!mImageInfo || mImageInfo == nullptr){
            return false;
        }

        sk_sp<SkImage> image = weexuikit::ImageManager::getInstance()->getImage(mImageInfo);
        if(image.get() == nullptr){
            return false;
        }
        return true;
    }

    bool StaticTextureImage::currentFrameKnownToBeOpaque()
    {
        if(mImageInfo != nullptr){
            return mImageInfo->getOpaque();
        }
        return false;
    }

    void StaticTextureImage::draw(GraphicsContext* ctx, const FloatRect& dstRectLazy, const FloatRect& srcRectLazy, CompositeOperator compositeOp, WebBlendMode blendMode)
    {
        if(!mImageInfo || mImageInfo == nullptr){
            return;
        }

        sk_sp<SkImage> image = weexuikit::ImageManager::getInstance()->getImage(mImageInfo);
        if(image.get() == nullptr){
            return;
        }

        FloatRect dstRect = dstRectLazy;
        FloatRect srcRect = FloatRect(0, 0, image->width(), image->height());

        if(mImageInfo->getScaleType() == ImageScaleType::CENTER_CROP){
            float dwidth = srcRect.width();
            float dheight = srcRect.height();
            float vwidth = dstRect.width();
            float vheight = dstRect.height();
            if (dwidth * vheight > vwidth * dheight) {
                float scale = (float) vheight / (float) dheight;
                float width = vwidth/scale;
                srcRect.setX((srcRect.width() - width)/2);
                srcRect.setWidth(width);
            } else {
                float scale = (float) vwidth / (float) dwidth;
                float height = vheight/scale;
                srcRect.setY((srcRect.height() - height)/2);
                srcRect.setHeight(height);
            }
        }else if(mImageInfo->getScaleType() == ImageScaleType::CENTER_FIT){
            float dwidth = srcRect.width();
            float dheight = srcRect.height();
            float vwidth = dstRect.width();
            float vheight = dstRect.height();
            if (dwidth * vheight > vwidth * dheight) {
                float scale = (float) vwidth / (float) dwidth;
                float height = dheight*scale;
                dstRect.setY(dstRect.y() + (dstRect.height() - height)/2);
                dstRect.setHeight(height);
            } else {
                float scale = (float) vheight / (float) dheight;
                float width = dwidth*scale;
                dstRect.setX(dstRect.x() + (dstRect.width() - width)/2);
                dstRect.setWidth(width);
            }
        }

        FloatRect normDstRect = adjustForNegativeSize(dstRect);
        FloatRect normSrcRect = adjustForNegativeSize(srcRect);


        if (normSrcRect.isEmpty() || normDstRect.isEmpty()){
            return; // Nothing to draw.
        }

        {
            SkPaint paint;
            ctx->preparePaintForDrawRectToRect(&paint, srcRect, dstRect, compositeOp, blendMode, !currentFrameKnownToBeOpaque());

            SkRect srcSkRect = WebCoreFloatRectToSKRect(normSrcRect);
            SkRect dstSkRect = WebCoreFloatRectToSKRect(normDstRect);

            SkCanvas* canvas = ctx->canvas();
            canvas->drawImageRect(image, srcSkRect, dstSkRect, &paint);

        }

        if (ImageObserver* observer = imageObserver()){
            observer->didDraw(this);
        }
    }


    void StaticTextureImage::drawPattern(GraphicsContext* context,
                                         const FloatRect& floatSrcRect,
                                         const FloatSize& scale,
                                         const FloatPoint& phase,
                                         CompositeOperator compositeOp,
                                         const FloatRect& destRect,
                                         WebBlendMode blendMode,
                                         const IntSize& repeatSpacing) {
        if(!mImageInfo || mImageInfo == nullptr){
            return;
        }

        sk_sp<SkImage> image = weexuikit::ImageManager::getInstance()->getImage(mImageInfo);
        if(image.get() == nullptr){
            return;
        }

        FloatRect normSrcRect = floatSrcRect;
        normSrcRect.intersect(FloatRect(0, 0, width(), height()));
        if (destRect.isEmpty() || normSrcRect.isEmpty())
            return; // nothing to draw

        AffineTransform ctm = context->getCTM();
        SkScalar ctmScaleX = ctm.xScale();
        SkScalar ctmScaleY = ctm.yScale();


        InterpolationQuality resampling = InterpolationLow;
        resampling = limitInterpolationQuality(context, resampling);
        SkMatrix localMatrix;
        // We also need to translate it such that the origin of the pattern is the
        // origin of the destination rect, which is what WebKit expects. Skia uses
        // the coordinate system origin as the base for the pattern. If WebKit wants
        // a shifted image, it will shift it from there using the localMatrix.
        const float adjustedX = phase.x() + normSrcRect.x() * scale.width();
        const float adjustedY = phase.y() + normSrcRect.y() * scale.height();
        localMatrix.setTranslate(SkFloatToScalar(adjustedX), SkFloatToScalar(adjustedY));

        sk_sp<SkShader> shader;
        SkFilterQuality filterQuality = static_cast<SkFilterQuality> (resampling);


        // Because no resizing occurred, the shader transform should be
        // set to the pattern's transform, which just includes scale.
        localMatrix.preScale(scale.width(), scale.height());


        // No need to resample before drawing.
        sk_sp<SkImage> subImage = image->makeSubset(enclosingIntRect(normSrcRect));
        if(subImage.get() == nullptr){
            return;
        }

        if (repeatSpacing.isZero()) {
            shader = subImage->makeShader(SkShader::kRepeat_TileMode, SkShader::kRepeat_TileMode, &localMatrix);
        } else {
            // Arbitrary tiling is currently only supported for SkPictureShader, so we use
            // that instead of a plain bitmap shader to implement spacing.
            const SkRect tile_rect = SkRect::MakeWH(image->width() + repeatSpacing.width() * ctmScaleX,
                                                    image->height() + repeatSpacing.height() * ctmScaleY);
            SkPictureRecorder framePictureRecorder;
            SkCanvas* canvas = framePictureRecorder.beginRecording(tile_rect, nullptr, 0);
            SkPaint paint;
            paint.setFilterQuality(filterQuality);
            paint.setAntiAlias(context->shouldAntialias());
            canvas->drawImage(subImage, 0, 0, &paint);
            sk_sp<SkPicture> picture = framePictureRecorder.finishRecordingAsPicture();
            shader = SkShader::MakePictureShader(picture, SkShader::kRepeat_TileMode, SkShader::kRepeat_TileMode, &localMatrix, &tile_rect);
        }

        {
            SkPaint paint;
            paint.setShader(shader);
            paint.setBlendMode(WebCoreCompositeToSkiaComposite(compositeOp, blendMode));
            paint.setFilterQuality(filterQuality);
            context->drawRect(destRect, paint);
        }
    }

} // namespace blink
