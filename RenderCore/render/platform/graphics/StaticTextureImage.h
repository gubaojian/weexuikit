// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef StaticBitmapImage_h
#define StaticBitmapImage_h

#include "render/platform/graphics/Image.h"
#include "render/platform/graphics/ImageInfo.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkImage.h"

namespace blink {
    /**
     * None Bitmap, Image Is Always Texture
     * */
    class PLATFORM_EXPORT StaticTextureImage : public Image {

    public:
        virtual ~StaticTextureImage();

        static PassRefPtr<StaticTextureImage> create(ImageInfo* imageInfo);

        virtual bool currentFrameKnownToBeOpaque() override;

        virtual IntSize size() const override;


        virtual bool canRender() override;

        virtual void draw(GraphicsContext*, const FloatRect& dstRect, const FloatRect& srcRect, CompositeOperator, WebBlendMode) override;

        virtual void drawPattern(GraphicsContext*,
                                     const FloatRect&,
                                     const FloatSize&,
                                     const FloatPoint& phase,
                                     CompositeOperator,
                                     const FloatRect&,
                                     WebBlendMode = WebBlendModeNormal,
                                     const IntSize& repeatSpacing = IntSize()) override;
    private:
        StaticTextureImage(ImageInfo*);
        ImageInfo*  mImageInfo;

    };

} // namespace blink

#endif
