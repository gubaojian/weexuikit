//
// Created by furture on 2018/10/29.
//

#ifndef WEEX_UIKIT_RENDERSCROLLVIEW_H
#define WEEX_UIKIT_RENDERSCROLLVIEW_H
#include "RenderSliver.h"
#include "RenderFlexibleBox.h"
#include "RenderSliverBody.h"

namespace blink {

    class RenderScrollView : public RenderSliver {


        public:
            RenderScrollView();
            ~RenderScrollView();
            virtual const char* renderName() const override;
            virtual void layoutSliver() override;
            virtual void onUpdateScrollDirection() override;
        
            RenderFlexibleBox* getRenderContainer(){
                return mRenderScrollBody;
            }
        
            int getMaxScrollExtent(){
                if(getScrollDirection() == ScrollDirection::Vertical){
                    return (getRenderContainer()->pixelSnappedHeight() - pixelSnappedHeight());
                }else{
                    return (getRenderContainer()->pixelSnappedWidth() - pixelSnappedWidth());
                }
            }
        
            int getViewportDimension(){
                if(getScrollDirection() == ScrollDirection::Vertical){
                    return pixelSnappedHeight();
                }else{
                    return pixelSnappedWidth();
                }
            }
        


        private:
           RenderSliverBody* mRenderScrollBody;
    };

}



#endif //WEEX_UIKIT_RENDERSCROLLVIEW_H
