//
// Created by furture on 2019/1/4.
//

#include <render/gesture/physics/SpringSimulation.h>
#include <render/platform/transforms/ScaleTransformOperation.h>
#include <render/platform/transforms/TransformationMatrix.h>
#include <render/core/rendering/RenderBox.h>


#include "AnimationView.h"
namespace weexuikit {

    AnimationView::AnimationView(UIContext *context, weexuikit::Node *node) : View(context,node) {

    }


    void AnimationView::attachRenderObject(blink::RenderObject *parent, int index) {
        PassRefPtr<blink::RenderStyle> renderStyle = blink::RenderStyle::clone(mRenderObject->style());
        blink::TransformOperations from;
        PassRefPtr<blink::ScaleTransformOperation> transform = blink::ScaleTransformOperation::create(
                2,
                2,
                blink::TransformOperation::OperationType::Scale);
        from.operations().append(transform);

        blink::TransformOperations to;
        PassRefPtr<blink::ScaleTransformOperation> toTransform = blink::ScaleTransformOperation::create(
                0.5,
                0.5,
                blink::TransformOperation::OperationType::Scale);
        //to.operations().append(toTransform);


        //from = from.blend(to, 0.5);
        from = to.blend(from, 0.25);
        //from.blend(from, 0.5);

        renderStyle->setTransform(from);



        mRenderObject->setStyle(renderStyle);
        //((blink::RenderBox*)mRenderObject)->transform()->scale(10);
        markWidgetNeedLayout();


        View::attachRenderObject(parent, index);







        /**
        LOGE("Weex", "Weex AnimationView:: start");
        animationTicker = std::make_shared<AnimationTicker>();
        AnimationView* weakSelf = this;
        animationTicker->onAnimation  = [weakSelf](float process){
            LOGE("Weex", "Weex AnimationView::onListenEvent %f ", process);
            int width = 400 + 1000*process;
            weakSelf->mRenderObject->style()->setWidth({width, blink::LengthType::Fixed});
            weakSelf->mRenderObject->setStyle(weakSelf->mRenderObject->style());
            weakSelf->markWidgetNeedLayout();
        };
        animationTicker->duration = 5000;
        Ticker*  ticker = mContext->getTickerProvider()->createTicker(animationTicker);
        animationTicker->ticker = ticker;
        ticker->start();
         */




        //animationController = AnimationController::sharePtrAnimationController(1, 1000,
                                                                             //  mContext->getTickerProvider(),
                                                                              // AnimationBehavior::normal);
        //animationController->addListener(this);
        //animationController->animateTo(1000, 1000);
    }


    void AnimationView::onListenEvent() {
        //LOGE("Weex", "Weex AnimationView::onListenEvent %d ", animationController->value());
        //int width = 1000*animationController->value();
        //mRenderObject->style()->setWidth({width, blink::LengthType::Fixed});
    }
}
