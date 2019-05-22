//
// Created by furture on 2018/10/16.
//

#ifndef WEEX_UIKIT_GESTURE_GESTURECONFIG_H
#define WEEX_UIKIT_GESTURE_GESTURECONFIG_H


namespace weexuikit {
/// The time that must elapse before a tap gesture sends onTapDown, if there's
/// any doubt that the gesture is a tap.
    const int64_t kPressTimeout = 100;

/// Maximum length of time between a tap down and a tap up for the gesture to be
/// considered a tap. (Currently not honored by the TapGestureRecognizer.)
// uses this.
    const int64_t kHoverTapTimeout = 150;

/// Maximum distance between the down and up pointers for a tap. (Currently not
/// honored by the [TapGestureRecognizer]; [PrimaryPointerGestureRecognizer],
/// which TapGestureRecognizer inherits from, uses [kTouchSlop].)
    const double kHoverTapSlop = 20.0; // Logical pixels

/// The time before a long press gesture attempts to win.
    const int64_t kLongPressTimeout = 500;

/// The distance a touch has to travel for the framework to be confident that
/// the gesture is a scroll gesture, or, inversely, the maximum distance that a
/// touch can travel before the framework becomes confident that it is not a
/// tap.
// This value was empirically derived. We started at 8.0 and increased it to
// 18.0 after getting complaints that it was too difficult to hit targets.
    const double kTouchSlop = 18.0; // Logical pixels

/// The distance a touch has to travel for the framework to be confident that
/// the gesture is a paging gesture. (Currently not used, because paging uses a
/// regular drag gesture, which uses kTouchSlop.)
// paging, which use this constant.
    const double kPagingTouchSlop = kTouchSlop * 2.0; // Logical pixels

/// The distance a touch has to travel for the framework to be confident that
/// the gesture is a panning gesture.
    const double kPanSlop = kTouchSlop * 2.0; // Logical pixels


/// The distance a touch has to travel for the framework to be confident that
/// the gesture is a scale gesture.
    const double kScaleSlop = kTouchSlop; // Logical pixels

/// The minimum velocity for a touch to consider that touch to trigger a fling
/// gesture.
    const double kMinFlingVelocity = 50.0; // Logical pixels / second
// const Velocity kMinFlingVelocity = const Velocity(pixelsPerSecond: 50.0);

/// Drag gesture fling velocities are clipped to this value.
    const double kMaxFlingVelocity = 6000.0; // Logical pixels / second

}
#endif //WEEX_UIKIT_GESTURE_GESTURECONFIG_H
