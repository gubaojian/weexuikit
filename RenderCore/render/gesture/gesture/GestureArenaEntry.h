//
// Created by furture on 2018/10/11.
//

#ifndef WEEX_UIKIT_GESTURE_GESTUREARENAENTRY_H
#define WEEX_UIKIT_GESTURE_GESTUREARENAENTRY_H
#include "GestureArenaMember.h"

namespace weexuikit {
    class GestureArenaManager;


/// Whether the gesture was accepted or rejected.
    enum class GestureDisposition {
        /// This gesture was accepted as the interpretation of the user's input.
                accepted,

        /// This gesture was rejected as the interpretation of the user's input.
                rejected,
    };

    class GestureArenaEntry {

    public:
        GestureArenaEntry(GestureArenaManager *arena, int pointer, GestureArenaMember *member) {
            mArena = arena;
            mPointer = pointer;
            mMember = member;
        };

        /// Call this member to claim victory (with accepted) or admit defeat (with rejected).
        ///
        /// It's fine to attempt to resolve a gesture recognizer for an arena that is
        /// already resolved.
        virtual void resolve(GestureDisposition disposition);

    private:
        GestureArenaManager *mArena;
        int mPointer;
        GestureArenaMember *mMember;
    };
}


#endif //WEEX_UIKIT_GESTURE_GESTUREARENAENTRY_H
