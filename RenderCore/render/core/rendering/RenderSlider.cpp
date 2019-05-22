//
// Created by furture on 2019/3/6.
//

#include <render/platform/common/log.h>
#include <render/platform/transforms/TranslateTransformOperation.h>
#include "RenderSlider.h"

namespace blink {

    RenderSlider::RenderSlider() {
        mCurrentIndex = 0;
        mOffsetValue = -0.3;
    }

    RenderSlider::~RenderSlider(){

    }

    const char* RenderSlider::renderName() const {
        return "RenderSlider";
    }

    void RenderSlider::layout() {
        onOffsetTransformUpdatepdate();
        ASSERT(needsLayout());
        simplifiedLayout();
        updateLogicalWidth();
        updateLogicalHeight();
        RenderBlock::layout();
        m_overflow.clear();
        addVisualEffectOverflow();
        updateLayerTransformAfterLayout();
        clearNeedsLayout();
    }


    void RenderSlider::paintChildren(blink::PaintInfo &paintInfo, const blink::LayoutPoint &paintOffset,
                                     Vector<blink::RenderBox *> &layers) {
        blink::RenderBlock* leftItem = getLeftItem();
        blink::RenderBlock* currentItem = getCurrentItem();
        blink::RenderBlock* rightItem = getRightItem();
        if(leftItem->hasLayer()){
            layers.append(leftItem);
        }else{
            leftItem->paint(paintInfo, paintOffset, layers);
        }
        if(currentItem->hasLayer()){
            layers.append(currentItem);
        }else{
            currentItem->paint(paintInfo, paintOffset, layers);
        }
        if(rightItem->hasLayer()){
            layers.append(rightItem);
        }else{
            rightItem->paint(paintInfo, paintOffset, layers);
        }
    }

    static void setRenderObjectTranslateY(RenderObject* renderObject, FloatPoint point){
        RefPtr<RenderStyle> renderStyle  = RenderStyle::clone(renderObject->style());
        TransformOperations operations;
        operations.operations().append(TranslateTransformOperation::create({point.x(), LengthType::Fixed},
                                                                           {point.y(), LengthType::Fixed},
                                                                           TransformOperation::OperationType::Translate));
        renderStyle->setTransform(operations);
        renderObject->setStyle(renderStyle);
        renderObject->layoutIfNeeded();
    }

    void RenderSlider::onOffsetTransformUpdatepdate() {
        blink::RenderBlock* leftItem = getLeftItem();
        blink::RenderBlock* currentItem = getCurrentItem();
        blink::RenderBlock* rightItem = getRightItem();


        int width = pixelSnappedWidth();
        FloatPoint leftItemLocation  = {-(1-mOffsetValue)*width, 0};
        FloatPoint currentItemLocation  = {mOffsetValue*width, 0};
        FloatPoint rightItemLocation  = {(1+mOffsetValue)*width, 0};

        setRenderObjectTranslateY(leftItem, leftItemLocation);
        setRenderObjectTranslateY(currentItem, currentItemLocation);
        setRenderObjectTranslateY(rightItem, rightItemLocation);
    }


    void RenderSlider::setCurrentOffset(float offset) {
        if(offset > 1){
            offset = 1;
        }
        if(offset < -1){
            offset = -1;
        }
        if(mOffsetValue == offset){
            return;
        }
        mOffsetValue = offset;
        setNeedsPositionedMovementLayout();
        layout();
    }

    void RenderSlider::setCurrentIndex(int index) {
        mCurrentIndex = index;
    }


    blink::RenderBlock* RenderSlider::getLeftItem() {
        if(mCurrentIndex <= 0){
            return (RenderBlock *)(lastChild());
        }
        return (RenderBlock *)childAt(mCurrentIndex-1);
    }

    blink::RenderBlock* RenderSlider::getCurrentItem() {
        return (RenderBlock *)(childAt(mCurrentIndex));
    }

    blink::RenderBlock* RenderSlider::getRightItem() {
        if(childAt(mCurrentIndex)->nextSibling() == nullptr){
            return (RenderBlock *)firstChild();
        }
        return (RenderBlock*)(childAt(mCurrentIndex + 1));
    }

}