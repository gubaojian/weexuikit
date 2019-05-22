//
// Created by furture on 2019/3/6.
//

#ifndef WEEX_UIKIT_RENDERSLIDER_H
#define WEEX_UIKIT_RENDERSLIDER_H
#include "RenderBlock.h"

namespace blink {

    class RenderSlider : public RenderBlock {

         public:
            RenderSlider();
            ~RenderSlider();
            virtual const char* renderName() const override;
            virtual void layout() override;

         public:
             virtual void paintChildren(PaintInfo&, const LayoutPoint&,Vector<RenderBox*>& layers) override;


         public:
            float  getCurrentOffset(){
                return mOffsetValue;
            }
            int getCurrentIndex(){
                return mCurrentIndex;
            }
            void setCurrentOffset(float offset);
            void setCurrentIndex(int index);

         public:
             void onOffsetTransformUpdatepdate();

         private:
             blink::RenderBlock* getLeftItem();
             blink::RenderBlock* getCurrentItem();
             blink::RenderBlock* getRightItem();


         private:
              int   mCurrentIndex;
              float mOffsetValue;
    };
}


#endif //WEEX_UIKIT_RENDERSLIDER_H
