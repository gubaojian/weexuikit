//
// Created by furture on 2018/10/29.
//

#include <render/platform/common/log.h>
#include <render/platform/transforms/TranslateTransformOperation.h>
#include "RenderScrollView.h"
#include "RenderLayer.h"
#include "RenderSliverBody.h"


namespace blink{

    RenderScrollView::RenderScrollView() {
        mRenderScrollBody = new RenderSliverBody();
        addChild(mRenderScrollBody);
        onUpdateScrollDirection();
    }

    RenderScrollView::~RenderScrollView() {
        if(mRenderScrollBody != nullptr){
            mRenderScrollBody = nullptr;
        }
    }

    const char* RenderScrollView::renderName() const {
        return "RenderScrollView";
    }

    
    void RenderScrollView::onUpdateScrollDirection(){
        if(getScrollDirection() == ScrollDirection::Vertical){
            mRenderScrollBody->style()->setFlexDirection(blink::EFlexDirection::FlowColumn);
            mRenderScrollBody->style()->setLogicalHeight(blink::LengthType::MinContent);
            mRenderScrollBody->style()->setLogicalWidth(blink::LengthType::Auto);
        }else{
            mRenderScrollBody->style()->setFlexDirection(blink::EFlexDirection::FlowRow);
            mRenderScrollBody->style()->setLogicalWidth(blink::LengthType::MinContent);
            mRenderScrollBody->style()->setLogicalHeight(blink::LengthType::Auto);
        }
    }

    void RenderScrollView::layoutSliver() {
        if(getScrollDirection() == ScrollDirection::Vertical){
            mRenderScrollBody->setLogicalWidth(availableLogicalWidth());
        }else{
            mRenderScrollBody->setLogicalHeight(availableLogicalHeight(AvailableLogicalHeightType::ExcludeMarginBorderPadding));
        }
        mRenderScrollBody->setScrollOffset(getScrollOffset().x(), getScrollOffset().y());
        mRenderScrollBody->layoutBody();
     }










}
