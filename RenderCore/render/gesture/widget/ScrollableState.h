//
// Created by furture on 2018/10/28.
//

#ifndef WEEX_UIKIT_GESTURE_SCROLLABLESTATE_H
#define WEEX_UIKIT_GESTURE_SCROLLABLESTATE_H
#include "ScrollContext.h"

namespace weexuikit {
    class ScrollableState : public ScrollContext {


    public:
        ScrollableState(TickerProvider* tickerProvider) {
            mTickerProvider = tickerProvider;
        }

    public:


        /// A [TickerProvider] to use when animating the scroll position.
        virtual TickerProvider *vsync() {
            return mTickerProvider;
        }

        /// The direction in which the widget scrolls.
        virtual AxisDirection axisDirection() {
            return AxisDirection::down;
        }

        /// Whether the contents of the widget should ignore [PointerEvent] inputs.
        ///
        /// Setting this value to true prevents the use from interacting with the
        /// contents of the widget with pointer events. The widget itself is still
        /// interactive.
        ///
        /// For example, if the scroll position is being driven by an animation, it
        /// might be appropriate to set this value to ignore pointer events to
        /// prevent the user from accidentally interacting with the contents of the
        /// widget as it animates. The user will still be able to touch the widget,
        /// potentially stopping the animation.
        virtual void setIgnorePointer(bool value) {

        }

        /// Whether the user can drag the widget, for example to initiate a scroll.
        virtual void setCanDrag(bool value) {

        }
    private:
        TickerProvider *mTickerProvider;
    };
}


#endif //WEEX_UIKIT_GESTURE_SCROLLABLESTATE_H
