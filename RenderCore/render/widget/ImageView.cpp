//
// Created by furture on 2018/8/25.
//
#include "ImageView.h"

namespace weexuikit {


    ImageView::ImageView(UIContext *context, Node *node) : View(context, node) {

    }

    void ImageView::applyDefault(blink::RenderObject *parent) {
        if(parent->isRenderParagraph() || parent->isRenderInline()){
            mNode->styles()->insert({Html::Style::STYLE_DISPLAY, Html::Style::STYLE_DISPLAY_INLINE});
        }
    }


    blink::RenderObject* ImageView::createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle) {
        PassOwnPtr<blink::RenderImageResource> imageResource = blink::RenderImageResource::create();
        std::string imgUrl = getSrc();
        imageResource->setImageUrl(imgUrl);
        imageResource->getImageInfo()->setPlaceholder(getPlaceHolder());
        imageResource->getImageInfo()->setRenderCtx(mContext);
        imageResource->getImageInfo()->setNode(mNode);
        imageResource->getImageInfo()->setScaleType(getImageScaleType());
        renderImage = new blink::RenderImage();
        renderImage->setImageResource(imageResource);
        renderImage->setStyle(renderStyle);
        if(renderStyle->width().isAuto()){
            renderStyle->setWidth({blink::LengthType::FillAvailable});
        }
        if(renderStyle->height().isAuto()){
            renderStyle->setHeight({blink::LengthType::FillAvailable});
        }
        return renderImage;
    }



    void ImageView::updateAttr(const std::string& key, const std::string& value) {
        if(Html::Attr::ATTR_SRC == key){
           renderImage->imageResource()->setImageUrl(value);
           return;
        }else if(Html::Attr::ATTR_PLACE_HOLDER == key || Html::Attr::ATTR_PLACEHOLDER == key){
           renderImage->imageResource()->getImageInfo()->setPlaceholder(value);
        }
        View::updateAttr(key, value);
    }


    const std::string ImageView::getSrc(){
        if(mNode->attrs() != nullptr) {
            std::map<std::string, std::string>::iterator it = mNode->attrs()->find(Html::Attr::ATTR_SRC);
            if (it != mNode->attrs()->end()) {
                return it->second;
            }
        }
        return "";
    }


    const std::string ImageView::getPlaceHolder(){
        if(mNode->attrs() != nullptr) {
            std::map<std::string, std::string>::iterator it = mNode->attrs()->find(Html::Attr::ATTR_PLACEHOLDER);
            if (it != mNode->attrs()->end()) {
                return it->second;
            }
            it = mNode->attrs()->find(Html::Attr::ATTR_PLACE_HOLDER);
            if (it != mNode->attrs()->end()) {
                return it->second;
            }
        }
        return "";
    }



    const blink::ImageScaleType ImageView::getImageScaleType(){
        std::map<std::string, std::string>::iterator it = mNode->attrs()->find(Html::Attr::ATTR_RESIZE);
        if (it != mNode->attrs()->end()) {
            if (it->second == Html::Attr::ATTR_RESIZE_COVER) {
                return blink::ImageScaleType::CENTER_CROP;
            } else if (it->second == Html::Attr::ATTR_RESIZE_CONTAIN) {
                return blink::ImageScaleType::CENTER_FIT;
            }
        }
        return blink::ImageScaleType::STRETCH;
    }


}