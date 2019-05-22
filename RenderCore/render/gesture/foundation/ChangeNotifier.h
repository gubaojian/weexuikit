//
// Created by furture on 2018/10/25.
//

#ifndef WEEX_UIKIT_GESTURE_CHANGENOTIFIE_H
#define WEEX_UIKIT_GESTURE_CHANGENOTIFIE_H
#include <vector>
#include <algorithm>
#include "Listenable.h"

namespace weexuikit{


    /// A class that can be extended or mixed in that provides a change notification
    /// API using [VoidCallback] for notifications.
    ///
    /// [ChangeNotifier] is optimized for small numbers (one or two) of listeners.
    /// It is O(N) for adding and removing listeners and O(N²) for dispatching
    /// notifications (where N is the number of listeners).
    ///
    /// See also:
    ///
    ///  * [ValueNotifier], which is a [ChangeNotifier] that wraps a single value.
    class ChangeNotifier : public Listenable {

    public:
        ChangeNotifier(){};
        ~ChangeNotifier(){
            mListeners.clear();
            mListeners.shrink_to_fit();
        }

    public:
        std::vector<ListenVoidCallback*> mListeners;

    public:
        /// Whether any listeners are currently registered.
        ///
        /// Clients should not depend on this value for their behavior, because having
        /// one listener's logic change when another listener happens to start or stop
        /// listening will lead to extremely hard-to-track bugs. Subclasses might use
        /// this information to determine whether to do any work when there are no
        /// listeners, however; for example, resuming a [Stream] when a listener is
        /// added and pausing it when a listener is removed.
        ///
        /// Typically this is used by overriding [addListener], checking if
        /// [hasListeners] is false before calling `super.addListener()`, and if so,
        /// starting whatever work is needed to determine when to call
        /// [notifyListeners]; and similarly, by overriding [removeListener], checking
        /// if [hasListeners] is false after calling `super.removeListener()`, and if
        /// so, stopping that same work.
        bool hasListeners() {
            return mListeners.size() > 0;
        }

        /// Register a closure to be called when the object changes.
        ///
        /// This method must not be called after [dispose] has been called.
        virtual void addListener(ListenVoidCallback* listener) override{
            mListeners.push_back(listener);
        }

        /// Remove a previously registered closure from the list of closures that are
        /// notified when the object changes.
        ///
        /// If the given listener is not registered, the call is ignored.
        ///
        /// This method must not be called after [dispose] has been called.
        ///
        /// If a listener had been added twice, and is removed once during an
        /// iteration (i.e. in response to a notification), it will still be called
        /// again. If, on the other hand, it is removed as many times as it was
        /// registered, then it will no longer be called. This odd behavior is the
        /// result of the [ChangeNotifier] not being able to determine which listener
        /// is being removed, since they are identical, and therefore conservatively
        /// still calling all the listeners when it knows that any are still
        /// registered.
        ///
        /// This surprising behavior can be unexpectedly observed when registering a
        /// listener on two separate objects which are both forwarding all
        /// registrations to a common upstream object.
        virtual void removeListener(ListenVoidCallback* listener) override{
            std::remove(mListeners.begin(), mListeners.end(), listener);
        }

        /// Discards any resources used by the object. After this is called, the
        /// object is not in a usable state and should be discarded (calls to
        /// [addListener] and [removeListener] will throw after the object is
        /// disposed).
        ///
        /// This method should only be called by the object's owner.



        /// Call all the registered listeners.
        ///
        /// Call this method whenever the object changes, to notify any clients the
        /// object may have. Listeners that are added during this iteration will not
        /// be visited. Listeners that are removed during this iteration will not be
        /// visited after they are removed.
        ///
        /// Exceptions thrown by listeners will be caught and reported using
        /// [FlutterError.reportError].
        ///
        /// This method must not be called after [dispose] has been called.
        ///
        /// Surprising behavior can result when reentrantly removing a listener (i.e.
        /// in response to a notification) that has been registered multiple times.
        /// See the discussion at [removeListener].
        virtual void notifyListeners() {
            if (mListeners.size() > 0) {
                for (ListenVoidCallback* listener : mListeners) {
                    listener->onListenEvent();
                }
            }
        }

    };



/// A [ChangeNotifier] that holds a single value.
///
/// When [value] is replaced, this class notifies its listeners.
    template <typename  T > class ValueNotifier : public ChangeNotifier{

    public:
        /// Creates a [ChangeNotifier] that wraps this value.
        ValueNotifier(T value){
            mValue = value;
        };

    public:
        T mValue;

    public:
        /// The current value stored in this notifier.
        ///
        /// When the value is replaced, this class notifies its listeners.

        T value(){
            return mValue;
        }

        void setValue(T newValue) {
            if (mValue == newValue)
                return;
            mValue = newValue;
            notifyListeners();
        }

    };

}



#endif //WEEX_UIKIT_GESTURE_CHANGENOTIFIE_H
