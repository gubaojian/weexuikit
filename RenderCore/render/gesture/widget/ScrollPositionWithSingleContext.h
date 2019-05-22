//
// Created by furture on 2018/10/25.
//

#ifndef WEEX_UIKIT_GESTURE_SCROLLPOSITIONWITHSINGLECONTEXT_H
#define WEEX_UIKIT_GESTURE_SCROLLPOSITIONWITHSINGLECONTEXT_H
#include "ScrollPosition.h"
#include "../foundation/StandardExtension.h"
/// A scroll position that manages scroll activities for a single
/// [ScrollContext].
///
/// This class is a concrete subclass of [ScrollPosition] logic that handles a
/// single [ScrollContext], such as a [Scrollable]. An instance of this class
/// manages [ScrollActivity] instances, which change what content is visible in
/// the [Scrollable]'s [Viewport].
///
/// See also:
///
///  * [ScrollPosition], which defines the underlying model for a position
///    within a [Scrollable] but is agnostic as to how that position is
///    changed.
///  * [ScrollView] and its subclasses such as [ListView], which use
///    [ScrollPositionWithSingleContext] to manage their scroll position.
///  * [ScrollController], which can manipulate one or more [ScrollPosition]s,
///    and which uses [ScrollPositionWithSingleContext] as its default class for
///    scroll positions.
/// A scroll position that manages scroll activities for a single
/// [ScrollContext].
///
/// This class is a concrete subclass of [ScrollPosition] logic that handles a
/// single [ScrollContext], such as a [Scrollable]. An instance of this class
/// manages [ScrollActivity] instances, which change what content is visible in
/// the [Scrollable]'s [Viewport].
///
/// See also:
///
///  * [ScrollPosition], which defines the underlying model for a position
///    within a [Scrollable] but is agnostic as to how that position is
///    changed.
///  * [ScrollView] and its subclasses such as [ListView], which use
///    [ScrollPositionWithSingleContext] to manage their scroll position.
///  * [ScrollController], which can manipulate one or more [ScrollPosition]s,
///    and which uses [ScrollPositionWithSingleContext] as its default class for
///    scroll positions.
namespace weexuikit {
    class ScrollPositionWithSingleContext : public ScrollPosition, public ScrollActivityDelegate {


    public:
        /// Create a [ScrollPosition] object that manages its behavior using
        /// [ScrollActivity] objects.
        ///
        /// The `initialPixels` argument can be null, but in that case it is
        /// imperative that the value be set, using [correctPixels], as soon as
        /// [applyNewDimensions] is invoked, before calling the inherited
        /// implementation of that method.
        ///
        /// If [keepScrollOffset] is true (the default), the current scroll offset is
        /// saved with [PageStorage] and restored it if this scroll position's scrollable
        /// is recreated.
        ScrollPositionWithSingleContext(ScrollPhysics *physics, ScrollContext *context,
                                        double initialPixels = 0.0, bool keepScrollOffset = true,
                                        ScrollPosition *oldPosition = nullptr) : ScrollPosition(
                physics, context, keepScrollOffset, oldPosition) {
            mCurrentDrag = nullptr;
            // If oldPosition is not null, the superclass will first call absorb(),
            // which may set _pixels and _activity.
            if (pixels() == 0.0 && initialPixels != 0.0)
                correctPixels(initialPixels);
            if (activity() == nullptr)
                goIdle();
            assert(activity() != nullptr);
        }


        virtual AxisDirection axisDirection() override {
            return context->axisDirection();
        }

        virtual double setPixels(double newPixels) override {
            assert(activity()->isScrolling());
            return ScrollPosition::setPixels(newPixels);
        }


        virtual void absorb(ScrollPosition *other) override {
            ScrollPosition::absorb(other);
            if (!other->isScrollPositionWithSingleContext()) {
                goIdle();
                return;
            }
            activity()->updateDelegate(this);
            ScrollPositionWithSingleContext *typedOther = (ScrollPositionWithSingleContext *) (other);
            mUserScrollDirection = typedOther->mUserScrollDirection;
            assert(mCurrentDrag == nullptr);
            if (typedOther->mCurrentDrag != nullptr) {
                mCurrentDrag = typedOther->mCurrentDrag;
                mCurrentDrag->updateDelegate(this);
                typedOther->mCurrentDrag = nullptr;
            }
        }


        virtual void applyNewDimensions() override {
            ScrollPosition::applyNewDimensions();
            context->setCanDrag(physics->shouldAcceptUserOffset(this));
        }


        virtual void beginActivity(std::shared_ptr<ScrollActivity> newActivity) override {
            mHeldPreviousVelocity = 0.0;
            if (newActivity.get() == nullptr)
                return;
            assert(newActivity->getDelegate() == this);
            ScrollPosition::beginActivity(newActivity);
            if (mCurrentDrag != nullptr) {
                mCurrentDrag->dispose();
                mCurrentDrag = nullptr;
            }
            if (!activity()->isScrolling())
                updateUserScrollDirection(ScrollDirection::idle);
        }


        virtual void applyUserOffset(double delta) override {
            updateUserScrollDirection(
                    delta > 0.0 ? ScrollDirection::forward : ScrollDirection::reverse);
            setPixels(mPixels - physics->applyPhysicsToUserOffset(this, delta));
        }


        virtual void goIdle() override {
            std::shared_ptr<IdleScrollActivity> idleScrollActivity = std::make_shared<IdleScrollActivity>(
                    this);
            beginActivity(idleScrollActivity);
        }

        /// Start a physics-driven simulation that settles the [pixels] position,
        /// starting at a particular velocity.
        ///
        /// This method defers to [ScrollPhysics.createBallisticSimulation], which
        /// typically provides a bounce simulation when the current position is out of
        /// bounds and a friction simulation when the position is in bounds but has a
        /// non-zero velocity.
        ///
        /// The velocity should be in logical pixels per second.
        virtual void goBallistic(double velocity) override {
            std::shared_ptr<Simulation> simulation(physics->createBallisticSimulation(this, velocity));
            if (simulation.get() != nullptr) {
                std::shared_ptr<BallisticScrollActivity> ballisticScrollActivity = std::make_shared<BallisticScrollActivity>(this, simulation, context->vsync());
                beginActivity(ballisticScrollActivity);
            } else {
                goIdle();
            }
        }

        ScrollDirection userScrollDirection() override {
            return mUserScrollDirection;
        }

        /// Set [userScrollDirection] to the given value.
        ///
        /// If this changes the value, then a [UserScrollNotification] is dispatched.
        void updateUserScrollDirection(ScrollDirection value) {
            if (userScrollDirection() == value) {
                return;
            }
            mUserScrollDirection = value;
            didUpdateScrollDirection(value);
        }

        void animateTo(double to, int64_t duration, Curve &curve) override {
            if (nearEqual(to, pixels(), physics->getTolerance()->distance)) {
                // Skip the animation, go straight to the position as we are already close.
                jumpTo(to);
                return;
            }

            std::shared_ptr<DrivenScrollActivity> activity = std::make_shared<DrivenScrollActivity>(
                    this, pixels(), to, duration, curve, context->vsync());
            beginActivity(activity);
        }


        virtual void jumpTo(double value) override {
            goIdle();
            if (pixels() != value) {
                double oldPixels = pixels();
                forcePixels(value);
                notifyListeners();
                didStartScroll();
                didUpdateScrollPositionBy(pixels() - oldPixels);
                didEndScroll();
            }
            goBallistic(0.0);
        }

        virtual void jumpToWithoutSettling(double value) override {
            goIdle();
            if (pixels() != value) {
                double oldPixels = pixels();
                forcePixels(value);
                notifyListeners();
                didStartScroll();
                didUpdateScrollPositionBy(pixels() - oldPixels);
                didEndScroll();
            }
        }


        virtual std::shared_ptr<ScrollHoldController> hold(VoidCallback holdCancelCallback) override {
            double previousVelocity = activity()->velocity();
            std::shared_ptr<HoldScrollActivity> holdActivity = std::make_shared<HoldScrollActivity>(
                    this, holdCancelCallback);
            beginActivity(holdActivity);
            mHeldPreviousVelocity = previousVelocity;
            return holdActivity;
        }

        virtual std::shared_ptr<Drag> drag(DragStartDetails details, VoidCallback dragCancelCallback) override {
            assert(physics != nullptr);
            std::shared_ptr<ScrollDragController> drag = std::make_shared<ScrollDragController>(
                    this, details, dragCancelCallback,
                    physics->carriedMomentum(mHeldPreviousVelocity),
                    physics->dragStartDistanceMotionThreshold());
            beginActivity(std::make_shared<DragScrollActivity>(this, drag));
            assert(mCurrentDrag.get() == nullptr);
            mCurrentDrag = drag;
            return drag;
        }


        virtual void dispose() override {
            if (mCurrentDrag != nullptr) {
                mCurrentDrag->dispose();
                mCurrentDrag = nullptr;
            }
            ScrollPosition::dispose();
        }


        virtual bool isScrollPositionWithSingleContext() override {
            return false;
        }

    private:
        ScrollDirection mUserScrollDirection = ScrollDirection::idle;
        /// Velocity from a previous activity temporarily held by [hold] to potentially
        /// transfer to a next activity.
        double mHeldPreviousVelocity = 0.0;
        std::shared_ptr<ScrollDragController> mCurrentDrag;
    };
}


#endif //WEEX_UIKIT_GESTURE_SCROLLPOSITIONWITHSINGLECONTEXT_H
