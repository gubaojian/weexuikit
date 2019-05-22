//
// Created by furture on 2018/10/29.
//

#include "ScrollerView.h"
#include <render/core/rendering/RenderScrollView.h>
#include <render/platform/common/log.h>
#include <render/core/parser/Screen.h>
#include <render/core/parser/StyleParser.h>


namespace weexuikit{



    ScrollerView::ScrollerView(UIContext *context, Node *node) : View(context, node) {

    }
    
    ScrollerView::~ScrollerView(){
       if(mScrollPhysics != nullptr){
           delete  mScrollPhysics;
           mScrollPhysics = nullptr;
       }
       if(mScrollableState != nullptr){
           delete mScrollableState;
           mScrollableState = nullptr;
       }
        if(mScrollPosition != nullptr){
            delete mScrollPosition;
            mScrollPosition = nullptr;
        }
        if(mDragGestureRecognizer != nullptr){
           delete  mDragGestureRecognizer;
           mDragGestureRecognizer = nullptr;
       }
    }

    void ScrollerView::applyDefault(blink::RenderObject *parent) {
        mNode->styles()->insert({Html::Style::STYLE_OVERFLOW, Html::Style::STYLE_OVERFLOW_HIDDEN});
        View::applyDefault(parent);
    }
    
    void ScrollerView::onPointerEvent(weexuikit::PointerEvent &pointerEvent){
        if(pointerEvent.isUpEvent()){
            if(mScrollView->getSliverHeader()->getRefreshState() == blink::RefreshState::RelaseToRefresh){
                mScrollView->getSliverHeader()->setRefreshState(blink::RefreshState::RefreshIng);
                std::shared_ptr<weexuikit::DelayTicker> delayTicker = std::make_shared<weexuikit::DelayTicker>();
                delayTicker->delayTickerCallback = [&](){
                    mScrollView->getSliverHeader()->setRefreshState(blink::RefreshState::PullToRefresh);
                    mScrollView->setScrollOffset(0, 0);
                };
                delayTicker->delayTime = 2500;
                delayTicker->ticker = mContext->getTickerProvider()->createTicker(delayTicker);;
            }
        }
        mScrollPosition->mMinScrollExtent = mScrollView->getMinScrollExtent()/Screen::mDeviceDensity;
        mScrollPosition->mMaxScrollExtent = mScrollView->getMaxScrollExtent()/Screen::mDeviceDensity;
        mScrollPosition->applyViewportDimension(mScrollView->getViewportDimension()/Screen::mDeviceDensity);
        if(pointerEvent.isDownEvent()){
            mDragGestureRecognizer->addPointer(pointerEvent);
        }
    }


    const std::string& ScrollerView::getScrollDirection() {
        return getAttr(Scroller::SCROLL_DIRECTION);
    }
    
    
    blink::RenderObject* ScrollerView::createRenderObject(blink::RenderObject* parent, RefPtr<blink::RenderStyle> renderStyle) {
        mScrollView = new blink::RenderScrollView();
        mScrollView->setStyle(renderStyle);
        mScrollView->setNeedsLayoutAndPrefWidthsRecalc();

        mScrollPhysics = new weexuikit::AlwaysScrollableScrollPhysics(new weexuikit::ClampingScrollPhysics(nullptr));

        mScrollableState = new weexuikit::ScrollableState(mContext->getTickerProvider());
        mScrollPosition = new weexuikit::ScrollPositionWithSingleContext(mScrollPhysics,  mScrollableState);
        mScrollPosition->addListener(this);
        if(getScrollDirection() == Scroller::SCROLL_DIRECTION_HORIZONTAL){
            mScrollView->setScrollDirection(blink::ScrollDirection::Horizontal);
            mDragGestureRecognizer = new  weexuikit::HorizontalDragGestureRecognizer(mContext->getGestureHandlerContext());
            mDragGestureRecognizer->setMaxFlingVelocity(weexuikit::kMaxFlingVelocity/2);
        }else{
            mScrollView->setScrollDirection(blink::ScrollDirection::Vertical);
            mDragGestureRecognizer = new  weexuikit::VerticalDragGestureRecognizer(mContext->getGestureHandlerContext());
        }
        mDragGestureRecognizer->onDown = [&](weexuikit::DragDownDetails details){
            assert(mDrag == nullptr);
            assert(mHold.get() == nullptr);
            mHold = mScrollPosition->hold([&](){
                mHold = nullptr;
            });
        };
        mDragGestureRecognizer->onStart = [&](weexuikit::DragStartDetails details){
            assert(mDrag.get() == nullptr);
            mDrag = mScrollPosition->drag(details, [&](){
                mDrag.reset();
            });
            assert(mDrag.get() != nullptr);
            assert(mHold.get() == nullptr);
            
        };
        mDragGestureRecognizer->onUpdate = [&](const weexuikit::DragUpdateDetails& details){
            // _drag might be null if the drag activity ended and called _disposeDrag.
            assert(mHold.get() == nullptr || mDrag.get() == nullptr);
            if(mDrag.get() != nullptr){
                mDrag->update(details);
            }
            
        };
        
        mDragGestureRecognizer->onEnd = [&](const weexuikit::DragEndDetails& dragEndDetails){
            // _drag might be null if the drag activity ended and called _disposeDrag.
            assert(mHold.get() == nullptr || mDrag.get() == nullptr);
            if(mDrag.get() != nullptr){
                mDrag->end(dragEndDetails);
            }
            assert(mDrag.get() == nullptr);
        };
        mDragGestureRecognizer->onCancel = [&](){
            assert(mHold.get() == nullptr || mDrag.get() == nullptr);
            if(mHold.get() != nullptr){
                mHold->cancel();
            }
            if(mDrag.get() != nullptr){
                mDrag->cancel();
            }
            assert(mHold.get() == nullptr);
            assert(mDrag.get() == nullptr);
        };
        mRenderContainer = mScrollView->getRenderContainer();
        return mScrollView;

    }
    
    void ScrollerView::onListenEvent(){
        if(mScrollPosition != nullptr){
            float pixels = Screen::dpiToDevicePixels(mScrollPosition->pixels());
            if(getScrollDirection() == Scroller::SCROLL_DIRECTION_HORIZONTAL){
                if(std::abs(mScrollView->getScrollOffset().x()) ==  std::abs(pixels)){
                    return;
                }
                mScrollView->setScrollOffset(pixels,  0);
            }else{
                if(std::abs(mScrollView->getScrollOffset().y()) ==  std::abs(pixels)){
                    return;
                }
                mScrollView->setScrollOffset(0,  pixels);
            }
            float offset = Screen::devicePixelsToUnit(pixels);
            std::map<std::string,std::string> params = {
                    {Html::Event::SCROLL_OFFSET, StyleParser::valueToString(-offset)}
            };
            mContext->fireEvent(mNode, Html::Event::SCROLL, params);
            mContext->markNeedsPaint();
        }
    }

}
