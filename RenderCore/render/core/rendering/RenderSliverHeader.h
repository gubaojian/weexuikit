//
// Created by furture on 2019/1/8.
//

#ifndef WEEX_UIKIT_REFRESHHEADER_H
#define WEEX_UIKIT_REFRESHHEADER_H
#include "RenderFlexibleBox.h"


namespace blink{


    enum class RefreshState{
        DisableRefresh,
        PullToRefresh,
        RelaseToRefresh,
        RefreshIng
    };

    class RenderSliverHeader : public RenderFlexibleBox {

        public:
            RenderSliverHeader();
            virtual ~RenderSliverHeader();

        public:
           void refreshHeaderLayout();

        public:
            RefreshState getRefreshState(){
                return mHeaderState;
            }

            void setRefreshState(RefreshState state){
                mHeaderState =  state;
            }

            void setSliverScrollerOffset(LayoutPoint sliverScrollOffset){
                mSliverScrollOffset = sliverScrollOffset;
            }

            void setPullDistance(LayoutUnit pullDistance);

            LayoutUnit getPullDistance();

            float getScrollOffset();


        private:
            RefreshState mHeaderState;
            LayoutUnit mPullDistance;
            LayoutPoint mSliverScrollOffset;
    };
}



#endif //WEEX_UIKIT_RENDERREFRESHHEADER_H
