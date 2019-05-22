//
// Created by furture on 2018/10/11.
//

#ifndef WEEX_UIKIT_GESTURE_GESTUREARENAMEMBER_H
#define WEEX_UIKIT_GESTURE_GESTUREARENAMEMBER_H


namespace weexuikit {
/// Represents an object participating in an arena.
///
/// Receives callbacks from the GestureArena to notify the object when it wins
/// or loses a gesture negotiation. Exactly one of [acceptGesture] or
/// [rejectGesture] will be called for each arena this member was added to,
/// regardless of what caused the arena to be resolved. For example, if a
/// member resolves the arena itself, that member still receives an
/// [acceptGesture] callback.

    class GestureArenaMember {

        public:
            /// Called when this member wins the arena for the given pointer id.
            virtual void acceptGesture(int pointer) = 0;

            /// Called when this member loses the arena for the given pointer id.
            virtual void rejectGesture(int pointer) = 0;
    };
}


#endif //WEEX_UIKIT_GESTURE_GESTUREARENAMEMBER_H
