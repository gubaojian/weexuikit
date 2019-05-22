//
// Created by furture on 2018/10/23.
//

#ifndef WEEX_UIKIT_GESTURE_LISTENABLE_H
#define WEEX_UIKIT_GESTURE_LISTENABLE_H
#include <functional>

namespace weexuikit {

    class ListenVoidCallback {

    public:
        virtual void onListenEvent() {

        }
    };

    class Listenable {

    public:
        /// Register a closure to be called when the object notifies its listeners.
        virtual void addListener(ListenVoidCallback *listener) {};

        /// Remove a previously registered closure from the list of closures that the
        /// object notifies.
        virtual void removeListener(ListenVoidCallback *listener) {};
    };

// An interface for subclasses of [Listenable] that expose a [value].
///
/// This interface is implemented by [ValueNotifier<T>] and [Animation<T>], and
/// allows other APIs to accept either of those implementations interchangeably.
    template<typename T>
    class ValueListenable {
    public:
        virtual T value()=0;
    };
}

#endif //WEEX_UIKIT_GESTURE_LISTENABLE_H
