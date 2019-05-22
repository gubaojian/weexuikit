//
// Created by furture on 2018/9/8.
//

#include <render/platform/Length.h>
#include <render/core/parser/StyleParser.h>
#include "render/core/rendering/style/StyleGradientImage.h"


namespace blink {


    LayoutSize StyleGradientImage::imageSize(const RenderObject *renderer) const {
        return m_containerSize;
    }

    void StyleGradientImage::computeIntrinsicDimensions(const RenderObject *renderer,
                                                         Length &intrinsicWidth,
                                                         Length &intrinsicHeight,
                                                         FloatSize &intrinsicRatio) {
        IntSize size = flooredIntSize(imageSize(renderer));
        intrinsicWidth = Length(size.width(), LengthType::Fixed);
        intrinsicHeight = Length(size.height(), LengthType::Fixed);
        intrinsicRatio = size;
    }


    void StyleGradientImage::setContainerSizeForRenderer(const RenderObject *,
                                                          const IntSize &containerSize) {
        if(m_containerSize.width() != containerSize.width()
                || m_containerSize.height() != containerSize.height()){
            m_containerSize = containerSize;
            m_GradientImage = nullptr;
        }
    }

    PassRefPtr<Image> StyleGradientImage::image(RenderObject *renderObject, const IntSize &size){
        return getGradientImage(renderObject, size);
    }

    Image* StyleGradientImage::getGradientImage(RenderObject *renderObject, const IntSize &size) {
        if(m_GradientImage && m_GradientImage.get()){
            return m_GradientImage.get();
        }
        std::string liearImage = mCssValue;
        m_GradientImage = weexuikit::StyleParser::parseGradientImage(liearImage, size);
        return m_GradientImage.get();
    }


    bool StyleGradientImage::knownToBeOpaque(const RenderObject *) const {
        return false;
    }


    WrappedImagePtr StyleGradientImage::data() const {
        return (WrappedImagePtr) this;
    }

}