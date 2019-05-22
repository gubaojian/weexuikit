//
//  RenderSliver.cpp
//  core
//
//  Created by furture on 2018/11/19.
//

#include "RenderSliver.h"
#include "RenderText.h"

namespace blink {

    
    RenderSliver::RenderSliver(){
        mSliverScrollOffset.setX(0);
        mSliverScrollOffset.setY(0);
        mScrollDirection = ScrollDirection::Vertical;
        mSliverHeader = new RenderSliverHeader();
        addChild(mSliverHeader);//may be rewrite layout will be better.
    }
    
    RenderSliver::~RenderSliver(){
    
    }
    
    const char* RenderSliver::renderName() const{
         return "RenderSliver";
    }
    
    
    void RenderSliver::layout(){
        ASSERT(needsLayout());
        simplifiedLayout();
        updateLogicalWidth();
        updateLogicalHeight();

        layoutHeader();
        layoutSliver();
        
        m_overflow.clear();
        addVisualEffectOverflow();
        updateLayerTransformAfterLayout();
        clearNeedsLayout();
    }
    
    void RenderSliver::layoutHeader(){
        mSliverHeader->refreshHeaderLayout();
    }

    void RenderSliver::setScrollOffset(float x, float y) {
        if(mScrollDirection == ScrollDirection::Vertical){
            if(y == mSliverScrollOffset.y()){
                return;
            }
            if(y < 0){
                y = std::min(y, mSliverHeader->getScrollOffset());
            }
            mSliverScrollOffset.setY(-y);
        }else{
            if(x == mSliverScrollOffset.x()){
                return;
            }
            if(x < 0){
                x = std::min(x, mSliverHeader->getScrollOffset());
            }
            mSliverScrollOffset.setX(-x);
        }
        layoutSliver();
    }
   
    
    
}
