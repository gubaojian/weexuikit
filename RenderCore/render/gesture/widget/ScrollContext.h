//
// Created by furture on 2018/10/25.
//

#ifndef WEEX_UIKIT_GESTURE_SCROLLCONTEXT_H
#define WEEX_UIKIT_GESTURE_SCROLLCONTEXT_H

#include "../foundation/BasicTypes.h"
#include "../foundation/TickerProvider.h"


namespace weexuikit {
/// An interface that [Scrollable] widgets implement in order to use
/// [ScrollPosition].
///
/// See also:
///
///  * [ScrollableState], which is the most common implementation of this
///    interface.
///  * [ScrollPosition], which uses this interface to communicate with the
///    scrollable widget.
    class ScrollContext {


    public:

        /// A [TickerProvider] to use when animating the scroll position.
        virtual TickerProvider *vsync()=0;

        /// The direction in which the widget scrolls.
        virtual AxisDirection axisDirection()=0;

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
        virtual void setIgnorePointer(bool value)=0;

        /// Whether the user can drag the widget, for example to initiate a scroll.
        virtual void setCanDrag(bool value)=0;

        /// Set the [SemanticsAction]s that should be expose to the semantics tree.
        //virtual void setSemanticsActions(Set<SemanticsAction> actions);
    };
}


#endif //WEEX_UIKIT_GESTURE_SCROLLCONTEXT_H
