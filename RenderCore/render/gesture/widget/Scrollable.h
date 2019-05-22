//
// Created by furture on 2018/10/26.
//

#ifndef WEEX_UIKIT_GESTURE_SCROLLABLE_H
#define WEEX_UIKIT_GESTURE_SCROLLABLE_H
#include <memory>
#include "Drag.h"
#include "ScrollActivity.h"
#include "ScrollPosition.h"
#include "ScrollableState.h"
#include "ScrollPositionWithSingleContext.h"


namespace weexuikit {

    class Scrollable {

        public:
            Scrollable(TickerProvider* tickerProvider) {
                mPhysics = new AlwaysScrollableScrollPhysics(new ClampingScrollPhysics(nullptr));
                mScrollableState = new ScrollableState(tickerProvider);
                mPosition = new ScrollPositionWithSingleContext(mPhysics,  mScrollableState);
                mTickerProvider = tickerProvider;
            }

        private:
            std::shared_ptr<Drag> mDrag;
            std::shared_ptr<ScrollHoldController> mHold;
            ScrollPhysics *mPhysics;
            ScrollableState* mScrollableState;
            ScrollPosition *mPosition;
            TickerProvider* mTickerProvider;
            

        public:
            /// The manager for this [Scrollable] widget's viewport position.
            ///
            /// To control what kind of [ScrollPosition] is created for a [Scrollable],
            /// provide it with custom [ScrollController] that creates the appropriate
            /// [ScrollPosition] in its [ScrollController.createScrollPosition] method.
            ScrollPosition *getPosition() {
                return mPosition;
            }

        public:
            void handleDragDown(DragDownDetails details) {
                assert(mDrag == nullptr);
                assert(mHold == nullptr);
                mHold = mPosition->hold([&]() {
                    this->disposeHold();
                });
            }

            void handleDragStart(DragStartDetails details) {
                // It's possible for _hold to become null between _handleDragDown and
                // _handleDragStart, for example if some user code calls jumpTo or otherwise
                // triggers a new activity to begin.
                assert(mDrag.get() == nullptr);
                mDrag = mPosition->drag(details, [&]() {
                    this->disposeDrag();
                });
                assert(mDrag.get() != nullptr);
                assert(mHold.get() == nullptr);
            }

            void handleDragUpdate(DragUpdateDetails details) {
                // _drag might be null if the drag activity ended and called _disposeDrag.
                assert(mHold.get() == nullptr || mDrag.get() == nullptr);
                if (mDrag.get()) {
                    mDrag->update(details);
                }
            }

            void handleDragEnd(DragEndDetails details) {
                // _drag might be null if the drag activity ended and called _disposeDrag.
                assert(mHold.get() == nullptr || mDrag.get() == nullptr);
                if (mDrag.get()) {
                    mDrag->end(details);
                }
                assert(mDrag.get() == nullptr);
            }

            void handleDragCancel() {
                // _hold might be null if the drag started.
                // _drag might be null if the drag activity ended and called _disposeDrag.
                assert(mHold.get() == nullptr || mDrag.get() == nullptr);
                if (mHold.get() != nullptr) {
                    mHold->cancel();
                }
                if (mDrag.get()) {
                    mDrag->cancel();
                }
                assert(mHold.get() == nullptr);
                assert(mDrag.get() == nullptr);
            }

            void disposeHold() {
                mHold = nullptr;
            }

            void disposeDrag() {
                mDrag = nullptr;
            }
    };

}


#endif //WEEX_UIKIT_GESTURE_SCROLLABLE_H
