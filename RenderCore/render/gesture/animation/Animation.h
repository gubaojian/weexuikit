//
// Created by furture on 2018/10/23.
//

#ifndef WEEX_UIKIT_GESTURE_ANIMATION_H
#define WEEX_UIKIT_GESTURE_ANIMATION_H
#include "../foundation/Listenable.h"
#include <vector>
#include <cassert>
#include <algorithm>
#include <functional>


namespace weexuikit{

    /// The status of an animation
    enum class AnimationStatus {
        /// The animation is stopped at the beginning
                dismissed,

        /// The animation is running from beginning to end
                forward,

        /// The animation is running backwards, from end to beginning
                reverse,

        /// The animation is stopped at the end
                completed,
    };

    /// Signature for listeners attached using [Animation.addStatusListener].
    class AnimationStatusListener {
        public:
            void onAnimationStatus(const AnimationStatus status){

            }
    };


    /// An animation with a value of type `T`.
    ///
    /// An animation consists of a value (of type `T`) together with a status. The
    /// status indicates whether the animation is conceptually running from
    /// beginning to end or from the end back to the beginning, although the actual
    /// value of the animation might not change monotonically (e.g., if the
    /// animation uses a curve that bounces).
    ///
    /// Animations also let other objects listen for changes to either their value
    /// or their status. These callbacks are called during the "animation" phase of
    /// the pipeline, just prior to rebuilding widgets.
    ///
    /// To create a new animation that you can run forward and backward, consider
    /// using [AnimationController].
    class Animation {

        public:

        /// Calls listener every time the status of the animation changes.
        ///
        /// Listeners can be removed with [removeStatusListener].
        virtual void addStatusListener(AnimationStatusListener* listener){

        }

        /// Stops calling the listener every time the status of the animation changes.
        ///
        /// Listeners can be added with [addStatusListener].
        virtual void removeStatusListener(AnimationStatusListener* listener){

        }


        /// The current status of this animation.
        virtual AnimationStatus status()=0;

        /// Whether this animation is stopped at the beginning.
        bool isDismissed() {
            return status() == AnimationStatus::dismissed;
        }
        /// Whether this animation is stopped at the end.
        bool isCompleted(){
            return status() == AnimationStatus::completed;
        }

    };



    class ListenerMixin {
        // This class is intended to be used as a mixin, and should not be
        // extended directly.
    public:

        virtual void didRegisterListener(){

        }

        virtual void didUnregisterListener(){

        }
    };


    /// A mixin that helps listen to another object only when this object has registered listeners.
    class AnimationLazyListenerMixin : public ListenerMixin {
            // This class is intended to be used as a mixin, and should not be
            // extended directly.
       public:
            int mListenerCounter = 0;


            virtual void didRegisterListener() override{
                assert(mListenerCounter >= 0);
                if (mListenerCounter == 0)
                    didStartListening();
                mListenerCounter += 1;
            }

            virtual void didUnregisterListener() override{
                assert(mListenerCounter >= 1);
                mListenerCounter -= 1;
                if (mListenerCounter == 0)
                    didStopListening();
            }


            /// Whether there are any listeners.
            bool isListening() {
                    return mListenerCounter > 0;
            }

            /// Called when the number of listeners changes from zero to one.
          public:
            virtual void didStartListening(){

            }

            /// Called when the number of listeners changes from one to zero.
            virtual void didStopListening(){

            }

    };



    /// A mixin that replaces the didRegisterListener/didUnregisterListener contract
    /// with a dispose contract.
    class AnimationEagerListenerMixin : public ListenerMixin {
            // This class is intended to be used as a mixin, and should not be
            // extended directly.
         public:
            virtual void didRegisterListener()override{ }


            virtual void didUnregisterListener() override{ }

            /// Release the resources used by this object. The object is no longer usable
            /// after this method is called.
            virtual void dispose() {}
    };



    /// A mixin that implements the [addListener]/[removeListener] protocol and notifies
    /// all the registered listeners when [notifyListeners] is called.
    class AnimationLocalListenersMixin : public  ListenerMixin, public Listenable {
            // This class is intended to be used as a mixin, and should not be
            // extended directly.
         public:

           std::vector<ListenVoidCallback*> mListeners;

            /// Calls the listener every time the value of the animation changes.
            ///
            /// Listeners can be removed with [removeListener].
            virtual void addListener(ListenVoidCallback* listener){
                didRegisterListener();
                mListeners.push_back(listener);
            }

            /// Stop calling the listener every time the value of the animation changes.
            ///
            /// Listeners can be added with [addListener].
            virtual void removeListener(ListenVoidCallback* listener){
                std::remove(mListeners.begin(), mListeners.end(), listener);
                didUnregisterListener();
            }

            /// Calls all the listeners.
            ///
            /// If listeners are added or removed during this function, the modifications
            /// will not change which listeners are called during this iteration.
            void notifyListeners() {
                std::vector<ListenVoidCallback*> localListeners = mListeners;
                for (ListenVoidCallback* listener : localListeners) {
                    listener->onListenEvent();
                }
            }
    };


    /// A mixin that implements the addStatusListener/removeStatusListener protocol
    /// and notifies all the registered listeners when notifyStatusListeners is
    /// called.
    class AnimationLocalStatusListenersMixin : public ListenerMixin {

            // This class is intended to be used as a mixin, and should not be
            // extended directly.
    public:
           std::vector<AnimationStatusListener*> mStatusListeners;

            /// Calls listener every time the status of the animation changes.
            ///
            /// Listeners can be removed with [removeStatusListener].
            void addStatusListener(AnimationStatusListener* listener) {
                didRegisterListener();
                mStatusListeners.push_back(listener);
            }

            /// Stops calling the listener every time the status of the animation changes.
            ///
            /// Listeners can be added with [addStatusListener].
            void removeStatusListener(AnimationStatusListener* listener) {
                std::remove(mStatusListeners.begin(), mStatusListeners.end(), listener);
                didUnregisterListener();
            }

            /// Calls all the status listeners.
            ///
            /// If listeners are added or removed during this function, the modifications
            /// will not change which listeners are called during this iteration.
            void notifyStatusListeners(const AnimationStatus status) {
                std::vector<AnimationStatusListener*> localListeners = mStatusListeners;
                for (AnimationStatusListener* listener : localListeners) {
                    listener->onAnimationStatus(status);
                }
            }
    };
}

#endif //WEEX_UIKIT_GESTURE_ANIMATION_H
