//
//  RenderSliver.hpp
//  core
//
//  Created by furture on 2018/11/19.
//

#ifndef WEEX_UIKIT_RENDER_SLIVER_H
#define WEEX_UIKIT_RENDER_SLIVER_H
#include "RenderBlock.h"
#include "RenderFlexibleBox.h"
#include "RenderSliverHeader.h"
#include <third_party/skia/include/core/SkPictureRecorder.h>

namespace blink {
    
    
    enum class ScrollDirection{
        Vertical,
        Horizontal
    };

    
    class RenderSliver : public RenderBlock {
        
        public:
            RenderSliver();
            ~RenderSliver();
            virtual const char* renderName() const override;

            virtual void layout() override;

            virtual void layoutHeader();
            virtual void layoutSliver()=0;

            virtual void onUpdateScrollDirection(){};
            virtual bool isViewPort() const override { return true; }
        
            void setScrollOffset(float x, float y);
        
            inline FloatPoint getScrollOffset(){
                return mSliverScrollOffset;
            }
        
            void setScrollDirection(ScrollDirection direction){
                if(mScrollDirection != direction){
                    mScrollDirection = direction;
                    onUpdateScrollDirection();
                }
            }
        
            ScrollDirection getScrollDirection(){
                return mScrollDirection;
            }


            int getMinScrollExtent(){
                int extent = mSliverHeader->getScrollOffset();
                if(extent == 0){
                    return extent;
                }
                return extent;
            }

            inline RenderSliverHeader* getSliverHeader(){
                return mSliverHeader;
            }



        private:
            RenderSliverHeader* mSliverHeader;
            FloatPoint mSliverScrollOffset;
            ScrollDirection mScrollDirection;

    };
    
    
    
    
}

#endif /* RenderSliver_hpp */
