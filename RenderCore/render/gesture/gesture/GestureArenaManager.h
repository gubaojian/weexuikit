//
// Created by furture on 2018/10/11.
//

#ifndef WEEX_UIKIT_GESTURE_GESTUREARENAMANAGER_H
#define WEEX_UIKIT_GESTURE_GESTUREARENAMANAGER_H
#include "GestureArena.h"
#include "GestureArenaMember.h"
#include "GestureArenaEntry.h"
#include <map>
#include <algorithm>


namespace weexuikit {

    class GestureArenaManager {


    private:
        std::map<int, GestureArena *> mArenas;

    public:
        /// Adds a new member (e.g., gesture recognizer) to the arena.
        GestureArenaEntry *add(int pointer, GestureArenaMember *member);


        /// Prevents new members from entering the arena.
        ///
        /// Called after the framework has finished dispatching the pointer down event.
        void close(int pointer);

        /// Forces resolution of the arena, giving the win to the first member.
        ///
        /// Sweep is typically after all the other processing for a [PointerUpEvent]
        /// have taken place. It ensures that multiple passive gestures do not cause a
        /// stalemate that prevents the user from interacting with the app.
        ///
        /// Recognizers that wish to delay resolving an arena past [PointerUpEvent]
        /// should call [hold] to delay sweep until [release] is called.
        ///
        /// See also:
        ///
        ///  * [hold]
        ///  * [release]
        void sweep(int pointer);


        /// Prevents the arena from being swept.
        ///
        /// Typically, a winner is chosen in an arena after all the other
        /// [PointerUpEvent] processing by [sweep]. If a recognizer wishes to delay
        /// resolving an arena past [PointerUpEvent], the recognizer can [hold] the
        /// arena open using this function. To release such a hold and let the arena
        /// resolve, call [release].
        ///
        /// See also:
        ///
        ///  * [sweep]
        ///  * [release]
        void hold(int pointer);


        /// Releases a hold, allowing the arena to be swept.
        ///
        /// If a sweep was attempted on a held arena, the sweep will be done
        /// on release.
        ///
        /// See also:
        ///
        ///  * [sweep]
        ///  * [hold]
        void release(int pointer);


        /// Reject or accept a gesture recognizer.
        ///
        /// This is called by calling [GestureArenaEntry.resolve] on the object returned from [add].
        void _resolve(int pointer, GestureArenaMember *member, GestureDisposition disposition);

        void _tryToResolveArena(int pointer, GestureArena *state);

        void _resolveByDefault(int pointer, GestureArena *state);

        void _resolveInFavorOf(int pointer, GestureArena *state, GestureArenaMember *member);
    };
}


#endif //WEEX_UIKIT_GESTURE_GESTUREARENAMANAGER_H
