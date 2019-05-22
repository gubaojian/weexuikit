//
// Created by furture on 2018/10/11.
//

#ifndef WEEX_UIKIT_GESTURE_ONESEQUENCEGESTURERECOGNIZER_H
#define WEEX_UIKIT_GESTURE_ONESEQUENCEGESTURERECOGNIZER_H
#include "GestureRecognizer.h"
#include "GestureArenaEntry.h"
#include "GestureArenaTeam.h"
#include <map>
#include <set>

/// Base class for gesture recognizers that can only recognize one
/// gesture at a time. For example, a single [TapGestureRecognizer]
/// can never recognize two taps happening simultaneously, even if
/// multiple pointers are placed on the same widget.
///
/// This is in contrast to, for instance, [MultiTapGestureRecognizer],
/// which manages each pointer independently and can consider multiple
/// simultaneous touches to each result in a separate tap.
namespace weexuikit {


    class OneSequenceGestureRecognizer : public GestureRecognizer, public PointerRoute {


    public:
        OneSequenceGestureRecognizer(GestureHandlerContext *gestureContext);

        ~OneSequenceGestureRecognizer();

    private:
        std::map<int, GestureArenaEntry *> *mEntries;
        std::set<int> *mTrackedPointers;
        GestureArenaTeam *mTeam;

    public:
        virtual void handleEvent(const PointerEvent &event) = 0;

        /// Called when the number of pointers this recognizer is tracking changes from one to zero.
        ///
        /// The given pointer ID is the ID of the last pointer this recognizer was
        /// tracking.
        virtual void didStopTrackingLastPointer(int pointer) = 0;


        /// Resolves this recognizer's participation in each gesture arena with the
        /// given disposition.
        virtual void resolve(GestureDisposition disposition);

        virtual void dispose();


        void route(const PointerEvent &event) override final;

        /// The team that this recognizer belongs to, if any.
        ///
        /// If [team] is null, this recognizer competes directly in the
        /// [GestureArenaManager] to recognize a sequence of pointer events as a
        /// gesture. If [team] is non-null, this recognizer competes in the arena in
        /// a group with other recognizers on the same team.
        ///
        /// A recognizer can be assigned to a team only when it is not participating
        /// in the arena. For example, a common time to assign a recognizer to a team
        /// is shortly after creating the recognizer.
        GestureArenaTeam *gestureArenaTeam() {
            return mTeam;
        }

        void setTeam(GestureArenaTeam *value) {
            assert(value != nullptr);
            assert(mEntries->size() == 0);
            assert(mTrackedPointers->size() == 0);
            assert(mTeam == nullptr);
            mTeam = value;
        }

        GestureArenaEntry *_addPointerToArena(int pointer);


        /// Causes events related to the given pointer ID to be routed to this recognizer.
        ///
        /// The pointer events are delivered to [handleEvent].
        ///
        /// Use [stopTrackingPointer] to remove the route added by this function.
        void startTrackingPointer(int pointer);

        /// Stops events related to the given pointer ID from being routed to this recognizer.
        ///
        /// If this function reduces the number of tracked pointers to zero, it will
        /// call [didStopTrackingLastPointer] synchronously.
        ///
        /// Use [startTrackingPointer] to add the routes in the first place.
        void stopTrackingPointer(int pointer);

        /// Stops tracking the pointer associated with the given event if the event is
        /// a [PointerUpEvent] or a [PointerCancelEvent] event.
        void stopTrackingIfPointerNoLongerDown(PointerEvent event);


        virtual void acceptGesture(int pointer) override {}

        virtual void rejectGesture(int pointer) override {}
    };

}

#endif //WEEX_UIKIT_GESTURE_ONESEQUENCEGESTURERECOGNIZER_H
