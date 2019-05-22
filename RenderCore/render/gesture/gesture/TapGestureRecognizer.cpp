//
// Created by furture on 2018/10/11.
//

#include "TapGestureRecognizer.h"
#include "GestureConfig.h"


namespace weexuikit {
    TapGestureRecognizer::TapGestureRecognizer(GestureHandlerContext *gestureContext)
            : PrimaryPointerGestureRecognizer(
            gestureContext) {
        onTap = nullptr;
        onTapCancel = nullptr;
        onTapDown = nullptr;
        onTapUp = nullptr;
        mHasFinalPosition = false;
        mSentTapDown = false;
        mWonArenaForPrimaryPointer = false;
        mDeadline = kPressTimeout;
    }


    void TapGestureRecognizer::handlePrimaryPointer(const PointerEvent &event) {
        if (event.isUpEvent()) {
            mFinalPosition = event;
            mHasFinalPosition = true;
            _checkUp();
        } else if (event.isCancelEvent()) {
            _reset();
        }
    }

    void TapGestureRecognizer::resolve(GestureDisposition disposition) {
        if (mWonArenaForPrimaryPointer && disposition == GestureDisposition::rejected) {
            // This can happen if the superclass decides the primary pointer
            // exceeded the touch slop, or if the recognizer is disposed.
            if (onTapCancel != nullptr) {
                onTapCancel(mInitialEvent);
            }
            _reset();
        }
        PrimaryPointerGestureRecognizer::resolve(disposition);
    }

    void TapGestureRecognizer::didExceedDeadline() {
        _checkDown();
    }


    void TapGestureRecognizer::acceptGesture(int pointer) {
        PrimaryPointerGestureRecognizer::acceptGesture(pointer);
        if (pointer == mPrimaryPointer) {
            _checkDown();
            mWonArenaForPrimaryPointer = true;
            _checkUp();
        }
    }

    void TapGestureRecognizer::rejectGesture(int pointer) {
        PrimaryPointerGestureRecognizer::rejectGesture(pointer);
        if (pointer == mPrimaryPointer) {
            // Another gesture won the arena.
            assert(state != GestureRecognizerState::possible);
            if (onTapCancel != nullptr) {
                onTapCancel(mInitialEvent);
            }
            _reset();
        }
    }


    void TapGestureRecognizer::_checkDown() {
        if (!mSentTapDown) {
            if (onTapDown != nullptr) {
                onTapDown(mInitialEvent);
            }
            mSentTapDown = true;
        }
    }

    void TapGestureRecognizer::_checkUp() {
        if (mWonArenaForPrimaryPointer && mHasFinalPosition) {
            resolve(GestureDisposition::accepted);
            if (!mWonArenaForPrimaryPointer || !mHasFinalPosition) {
                // It is possible that resolve has just recursively called _checkUp
                // In that case _wonArenaForPrimaryPointer will be false (as _checkUp
                // calls _reset) and we return here to avoid double invocation of the
                // tap callbacks.
                return;
            }

            if (onTapUp != nullptr) {
                onTapUp(mFinalPosition);
            }
            if (onTap != nullptr) {
                onTap(mFinalPosition);
            }
            _reset();
        }
    }


    void TapGestureRecognizer::_reset() {
        mSentTapDown = false;
        mWonArenaForPrimaryPointer = false;
        mHasFinalPosition = false;
    }
}