//
// Created by furture on 2018/10/11.
//

#ifndef WEEX_UIKIT_GESTURE_TAPGESTURERECOGNIZER_H
#define WEEX_UIKIT_GESTURE_TAPGESTURERECOGNIZER_H

#include "PrimaryPointerGestureRecognizer.h"
#include <functional>

namespace weexuikit {
    using GestureTapDownCallback = std::function<void(const PointerEvent &)>;
    using GestureTapUpCallback = std::function<void(const PointerEvent &)>;
    using GestureTapCallback = std::function<void(const PointerEvent &)>;
    using GestureTapCancelCallback = std::function<void(const PointerEvent &)>;

    class TapGestureRecognizer : public PrimaryPointerGestureRecognizer {

    public:
        TapGestureRecognizer(GestureHandlerContext *gestureContext);

    public:
        void handlePrimaryPointer(const PointerEvent &event) override;

        void resolve(GestureDisposition disposition) override;

        virtual void didExceedDeadline() override;

        virtual void acceptGesture(int pointer) override;

        virtual void rejectGesture(int pointer) override;


        void _checkDown();

        void _checkUp();

        void _reset();

    public:
        /// A pointer that might cause a tap has contacted the screen at a particular
        /// location.
        ///
        /// This triggers before the gesture has won the arena, after a short timeout
        /// ([deadline]).
        ///
        /// If the gesture doesn't win the arena, [onTapCancel] is called next.
        /// Otherwise, [onTapUp] is called next.
        ///
        /// See also:
        ///
        ///  * [GestureDetector.onTapDown], which exposes this callback.
        GestureTapDownCallback onTapDown;

        /// A pointer that will trigger a tap has stopped contacting the screen at a
        /// particular location.
        ///
        /// This triggers once the gesture has won the arena, immediately before
        /// [onTap].
        ///
        /// If the gesture doesn't win the arena, [onTapCancel] is called instead.
        ///
        GestureTapUpCallback onTapUp;


        /// A tap has occurred.
        ///
        /// This triggers once the gesture has won the arena, immediately after
        /// [onTapUp].
        ///
        /// If the gesture doesn't win the arena, [onTapCancel] is called instead.
        ///
        GestureTapCallback onTap;

        /// The pointer that previously triggered [onTapDown] will not end up causing
        /// a tap.
        ///
        /// This triggers if the gesture loses the arena.
        ///
        /// If the gesture wins the arena, [onTapUp] and [onTap] are called instead.
        ///
        /// See also:
        ///
        ///  * [GestureDetector.onTapCancel], which exposes this callback.
        GestureTapCancelCallback onTapCancel;


    private:
        bool mSentTapDown = false;
        bool mWonArenaForPrimaryPointer = false;
        PointerEvent mFinalPosition;
        bool mHasFinalPosition;
    };
}


#endif //WEEX_UIKIT_GESTURE_TAPGESTURERECOGNIZER_H
