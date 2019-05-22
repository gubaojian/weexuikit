//
// Created by furture on 2018/9/8.
//

#ifndef WEEXRENDERER_STYLEGENERATEDIMAGE_H
#define WEEXRENDERER_STYLEGENERATEDIMAGE_H
#include "render/core/rendering/style/StyleImage.h"
#include "render/platform/graphics/Image.h"
#include "render/platform/graphics/Gradient.h"
#include "render/platform/graphics/GeneratedImage.h"
#include "render/platform/graphics/GradientGeneratedImage.h"

namespace blink {

    class StyleGradientImage final :  public  StyleImage {

    public:
        static PassRefPtr<StyleGradientImage> create(std::string  cssValue){
            return adoptRef(new StyleGradientImage(cssValue));
        };

        virtual LayoutSize imageSize(const RenderObject*) const override;
        virtual void computeIntrinsicDimensions(const RenderObject*, Length& intrinsicWidth, Length& intrinsicHeight, FloatSize& intrinsicRatio) override;

        virtual bool imageHasRelativeWidth() const override { return false; }
        virtual bool imageHasRelativeHeight() const override { return false; }
        virtual bool usesImageContainerSize() const override { return true; }

        virtual void setContainerSizeForRenderer(const RenderObject*, const IntSize& containerSize) override;

        virtual void addClient(RenderObject*) override{};


        virtual WrappedImagePtr data() const override;

        virtual void removeClient(RenderObject*) override{};


        virtual PassRefPtr<Image> image(RenderObject*, const IntSize&) override;

        virtual bool knownToBeOpaque(const RenderObject*) const override;

    protected:
        Image* getGradientImage(RenderObject*, const IntSize&);
        StyleGradientImage(std::string cssValue):mCssValue(cssValue){
            m_isGeneratedImage = true;
        }
        std::string mCssValue;
        IntSize m_containerSize;
        RefPtr<Image> m_GradientImage;
    };
}



#endif //WEEXRENDERER_STYLEGENERATEDIMAGE_H
