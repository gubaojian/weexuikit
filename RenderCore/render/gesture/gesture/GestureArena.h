//
// Created by furture on 2018/10/11.
//

#ifndef WEEX_UIKIT_GESTURE_GESTUREARENA_H
#define WEEX_UIKIT_GESTURE_GESTUREARENA_H
#include <vector>
#include <cassert>

namespace weexuikit {
    class GestureArenaMember;

    class GestureArena {

    public:
        GestureArena();

        ~GestureArena();

    public:
        std::vector<GestureArenaMember *> *members;
        bool isOpen = true;
        bool isHeld = false;
        bool hasPendingSweep = false;
        /// If a gesture attempts to win while the arena is still open, it becomes the
        /// "eager winner". We look for an eager winner when closing the arena to new
        /// participants, and if there is one, we resolve the arena in its favor at
        /// that time.
        GestureArenaMember *eagerWinner;

    public:
        void add(GestureArenaMember *member) {
            assert(isOpen);
            members->push_back(member);
        }

    };
}


#endif //WEEX_UIKIT_GESTURE_GESTUREARENA_H
