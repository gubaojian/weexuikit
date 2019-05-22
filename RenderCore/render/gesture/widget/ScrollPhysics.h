//
// Created by furture on 2018/10/25.
//

#ifndef WEEX_UIKIT_GESTURE_SCROLLPHYSICS_H
#define WEEX_UIKIT_GESTURE_SCROLLPHYSICS_H

#include <memory>
#include "ScrollMetrics.h"
#include "../physics/Simulation.h"
#include "../physics/SpringSimulation.h"
#include "../gesture/GestureConfig.h"
#include "BouncingScrollSimulation.h"


namespace weexuikit {
/// Determines the physics of a [Scrollable] widget.
///
/// For example, determines how the [Scrollable] will behave when the user
/// reaches the maximum scroll extent or when the user stops scrolling.
///
/// When starting a physics [Simulation], the current scroll position and
/// velocity are used as the initial conditions for the particle in the
/// simulation. The movement of the particle in the simulation is then used to
/// determine the scroll position for the widget.
    class ScrollPhysics {


    public:
        /// Creates an object with the default scroll physics.
        ScrollPhysics(ScrollPhysics *parent);


    public:
        static SpringDescription *kDefaultSpring;
        /// The default accuracy to which scrolling is computed.
        static Tolerance *kDefaultTolerance;

    public:
        /// If non-null, determines the default behavior for each method.
        ///
        /// If a subclass of [ScrollPhysics] does not override a method, that subclass
        /// will inherit an implementation from this base class that defers to
        /// [parent]. This mechanism lets you assemble novel combinations of
        /// [ScrollPhysics] subclasses at runtime.
        ScrollPhysics *mParent;

        /// If [parent] is null then return ancestor, otherwise recursively build a
        /// ScrollPhysics that has [ancestor] as its parent.
        ///
        /// This method is typically used to define [applyTo] methods like:
        /// ```dart
        /// FooScrollPhysics applyTo(ScrollPhysics ancestor) {
        ///   return FooScrollPhysics(parent: buildParent(ancestor));
        /// }
        /// ```
        virtual ScrollPhysics *buildParent(ScrollPhysics *ancestor) {
            if (mParent != nullptr) {
                return mParent;
            }
            if (mParent->applyTo(ancestor) != nullptr) {
                return ancestor;
            }
            return ancestor;
        }

        /// If [parent] is null then return a [ScrollPhysics] with the same
        /// [runtimeType] where the [parent] has been replaced with the [ancestor].
        ///
        /// If this scroll physics object already has a parent, then this method
        /// is applied recursively and ancestor will appear at the end of the
        /// existing chain of parents.
        ///
        /// The returned object will combine some of the behaviors from this
        /// [ScrollPhysics] instance and some of the behaviors from [ancestor].
        ///
        /// See also:
        ///
        ///   * [buildParent], a utility method that's often used to define [applyTo]
        ///     methods for ScrollPhysics subclasses.
        virtual ScrollPhysics *applyTo(ScrollPhysics *ancestor) {
            return new ScrollPhysics(buildParent(ancestor));
        }

        /// Used by [DragScrollActivity] and other user-driven activities to convert
        /// an offset in logical pixels as provided by the [DragUpdateDetails] into a
        /// delta to apply (subtract from the current position) using
        /// [ScrollActivityDelegate.setPixels].
        ///
        /// This is used by some [ScrollPosition] subclasses to apply friction during
        /// overscroll situations.
        ///
        /// This method must not adjust parts of the offset that are entirely within
        /// the bounds described by the given `position`.
        ///
        /// The given `position` is only valid during this method call. Do not keep a
        /// reference to it to use later, as the values may update, may not update, or
        /// may update to reflect an entirely unrelated scrollable.
        virtual double applyPhysicsToUserOffset(ScrollMetrics *position, double offset) {
            if (mParent == nullptr)
                return offset;
            return mParent->applyPhysicsToUserOffset(position, offset);
        }

        /// Whether the scrollable should let the user adjust the scroll offset, for
        /// example by dragging.
        ///
        /// By default, the user can manipulate the scroll offset if, and only if,
        /// there is actually content outside the viewport to reveal.
        ///
        /// The given `position` is only valid during this method call. Do not keep a
        /// reference to it to use later, as the values may update, may not update, or
        /// may update to reflect an entirely unrelated scrollable.
        virtual bool shouldAcceptUserOffset(ScrollMetrics *position) {
            if (mParent == nullptr)
                return position->pixels() != 0 ||
                       position->minScrollExtent() != position->maxScrollExtent();
            return mParent->shouldAcceptUserOffset(position);
        }

        /// Determines the overscroll by applying the boundary conditions.
        ///
        /// Called by [ScrollPosition.applyBoundaryConditions], which is called by
        /// [ScrollPosition.setPixels] just before the [ScrollPosition.pixels] value
        /// is updated, to determine how much of the offset is to be clamped off and
        /// sent to [ScrollPosition.didOverscrollBy].
        ///
        /// The `value` argument is guaranteed to not equal the [ScrollMetrics.pixels]
        /// of the `position` argument when this is called.
        ///
        /// It is possible for this method to be called when the `position` describes
        /// an already-out-of-bounds position. In that case, the boundary conditions
        /// should usually only prevent a further increase in the extent to which the
        /// position is out of bounds, allowing a decrease to be applied successfully,
        /// so that (for instance) an animation can smoothly snap an out of bounds
        /// position to the bounds. See [BallisticScrollActivity].
        ///
        /// This method must not clamp parts of the offset that are entirely within
        /// the bounds described by the given `position`.
        ///
        /// The given `position` is only valid during this method call. Do not keep a
        /// reference to it to use later, as the values may update, may not update, or
        /// may update to reflect an entirely unrelated scrollable.
        ///
        /// ## Examples
        ///
        /// [BouncingScrollPhysics] returns zero. In other words, it allows scrolling
        /// past the boundary unhindered.
        ///
        /// [ClampingScrollPhysics] returns the amount by which the value is beyond
        /// the position or the boundary, whichever is furthest from the content. In
        /// other words, it disallows scrolling past the boundary, but allows
        /// scrolling back from being overscrolled, if for some reason the position
        /// ends up overscrolled.
        virtual double applyBoundaryConditions(ScrollMetrics *position, double value) {
            if (mParent == nullptr)
                return 0.0;
            return mParent->applyBoundaryConditions(position, value);
        }

        /// Returns a simulation for ballistic scrolling starting from the given
        /// position with the given velocity.
        ///
        /// This is used by [ScrollPositionWithSingleContext] in the
        /// [ScrollPositionWithSingleContext.goBallistic] method. If the result
        /// is non-null, [ScrollPositionWithSingleContext] will begin a
        /// [BallisticScrollActivity] with the returned value. Otherwise, it will
        /// begin an idle activity instead.
        ///
        /// The given `position` is only valid during this method call. Do not keep a
        /// reference to it to use later, as the values may update, may not update, or
        /// may update to reflect an entirely unrelated scrollable.
        virtual Simulation* createBallisticSimulation(ScrollMetrics *position, double velocity) {
            if (mParent == nullptr)
                return nullptr;
            return mParent->createBallisticSimulation(position, velocity);
        }

        /// The spring to use for ballistic simulations.
        SpringDescription *spring() {
            if (mParent != nullptr) {
                return mParent->spring();
            }
            return kDefaultSpring;
        }


        /// The tolerance to use for ballistic simulations.
        Tolerance *getTolerance() {
            if (mParent) {
                return mParent->getTolerance();
            }
            return kDefaultTolerance;
        }

        /// The minimum distance an input pointer drag must have moved to
        /// to be considered a scroll fling gesture.
        ///
        /// This value is typically compared with the distance traveled along the
        /// scrolling axis.
        ///
        /// See also:
        ///
        ///  * [VelocityTracker.getVelocityEstimate], which computes the velocity
        ///    of a press-drag-release gesture.
        double minFlingDistance() {
            if (mParent) {
                return minFlingDistance();
            }
            return kTouchSlop;
        }

        /// The minimum velocity for an input pointer drag to be considered a
        /// scroll fling.
        ///
        /// This value is typically compared with the magnitude of fling gesture's
        /// velocity along the scrolling axis.
        ///
        /// See also:
        ///
        ///  * [VelocityTracker.getVelocityEstimate], which computes the velocity
        ///    of a press-drag-release gesture.
        virtual double minFlingVelocity() {
            if (mParent) {
                return mParent->minFlingVelocity();
            }
            return kMinFlingVelocity;
        }

        /// Scroll fling velocity magnitudes will be clamped to this value.
        double maxFlingVelocity() {
            if (mParent) {
                return mParent->maxFlingVelocity();
            }
            return kMaxFlingVelocity;
        }

        /// Returns the velocity carried on repeated flings.
        ///
        /// The function is applied to the existing scroll velocity when another
        /// scroll drag is applied in the same direction.
        ///
        /// By default, physics for platforms other than iOS doesn't carry momentum.
        virtual double carriedMomentum(double existingVelocity) {
            if (mParent == nullptr)
                return 0.0;
            return mParent->carriedMomentum(existingVelocity);
        }

        /// The minimum amount of pixel distance drags must move by to start motion
        /// the first time or after each time the drag motion stopped.
        ///
        /// If null, no minimum threshold is enforced.
        virtual double dragStartDistanceMotionThreshold() {
            if (mParent != nullptr) {
                mParent->dragStartDistanceMotionThreshold();
            }
            return 0;
        }

        /// Whether a viewport is allowed to change its scroll position implicitly in
        /// responds to a call to [RenderObject.showOnScreen].
        ///
        /// [RenderObject.showOnScreen] is for example used to bring a text field
        /// fully on screen after it has received focus. This property controls
        /// whether the viewport associated with this object is allowed to change the
        /// scroll position to fulfill such a request.
        bool allowImplicitScrolling() {
            return true;
        }
    };

/// Scroll physics for environments that allow the scroll offset to go beyond
/// the bounds of the content, but then bounce the content back to the edge of
/// those bounds.
///
/// This is the behavior typically seen on iOS.
///
/// See also:
///
///  * [ScrollConfiguration], which uses this to provide the default
///    scroll behavior on iOS.
///  * [ClampingScrollPhysics], which is the analogous physics for Android's
///    clamping behavior.
    class BouncingScrollPhysics : public ScrollPhysics {

    public:
        /// Creates scroll physics that bounce back from the edge.
        BouncingScrollPhysics(ScrollPhysics *parent) : ScrollPhysics(parent) {

        }

        virtual BouncingScrollPhysics *applyTo(ScrollPhysics *ancestor) override {
            return new BouncingScrollPhysics(buildParent(ancestor));
        }

        /// The multiple applied to overscroll to make it appear that scrolling past
        /// the edge of the scrollable contents is harder than scrolling the list.
        /// This is done by reducing the ratio of the scroll effect output vs the
        /// scroll gesture input.
        ///
        /// This factor starts at 0.52 and progressively becomes harder to overscroll
        /// as more of the area past the edge is dragged in (represented by an increasing
        /// `overscrollFraction` which starts at 0 when there is no overscroll).
        double frictionFactor(double overscrollFraction) {
            return 0.52 * std::pow(1 - overscrollFraction, 2);
        }


        virtual double applyPhysicsToUserOffset(ScrollMetrics *position, double offset) override {
            assert(offset != 0.0);
            assert(position->minScrollExtent() <= position->maxScrollExtent());

            if (!position->outOfRange())
                return offset;

            double overscrollPastStart = std::max(position->minScrollExtent() - position->pixels(),
                                                  0.0);
            double overscrollPastEnd = std::max(position->pixels() - position->maxScrollExtent(),
                                                0.0);
            double overscrollPast = std::max(overscrollPastStart, overscrollPastEnd);
            bool easing = (overscrollPastStart > 0.0 && offset < 0.0)
                          || (overscrollPastEnd > 0.0 && offset > 0.0);

            double friction = easing // Apply less resistance when easing the overscroll vs tensioning.
                              ? frictionFactor(
                            (overscrollPast - std::abs(offset) / position->viewportDimension()))
                              : frictionFactor(overscrollPast / position->viewportDimension());
            double direction = math_sign(offset);

            return direction * _applyFriction(overscrollPast, std::abs(offset), friction);
        }

        static double _applyFriction(double extentOutside, double absDelta, double gamma) {
            assert(absDelta > 0);
            double total = 0.0;
            if (extentOutside > 0) {
                double deltaToLimit = extentOutside / gamma;
                if (absDelta < deltaToLimit)
                    return absDelta * gamma;
                total += extentOutside;
                absDelta -= deltaToLimit;
            }
            return total + absDelta;
        }


        virtual double applyBoundaryConditions(ScrollMetrics *position, double value) override {
            return 0.0;
        }

        virtual Simulation *
        createBallisticSimulation(ScrollMetrics *positionMetrics, double velocity) override {
            Tolerance *tolerance = this->getTolerance();
            if (std::abs(velocity) >= tolerance->velocity || positionMetrics->outOfRange()) {
                double position = positionMetrics->pixels();
                double _velocity = velocity * 0.91;
                double leadingExtent = positionMetrics->minScrollExtent();
                double trailingExtent = positionMetrics->maxScrollExtent();
                SpringDescription *springDesc = spring();
                return new BouncingScrollSimulation(position, _velocity, leadingExtent,
                                                    trailingExtent, springDesc, tolerance);
            }
            return nullptr;
        }

        // The ballistic simulation here decelerates more slowly than the one for
        // ClampingScrollPhysics so we require a more deliberate input gesture
        // to trigger a fling.
        virtual double minFlingVelocity() override {
            return kMinFlingVelocity * 2.0;
        }

        // Methodology:
        // 1- Use https://github.com/flutter/scroll_overlay to test with Flutter and
        //    platform scroll views superimposed.
        // 2- Record incoming speed and make rapid flings in the test app.
        // 3- If the scrollables stopped overlapping at any moment, adjust the desired
        //    output value of this function at that input speed.
        // 4- Feed new input/output set into a power curve fitter. Change function
        //    and repeat from 2.
        // 5- Repeat from 2 with medium and slow flings.
        /// Momentum build-up function that mimics iOS's scroll speed increase with repeated flings.
        ///
        /// The velocity of the last fling is not an important factor. Existing speed
        /// and (related) time since last fling are factors for the velocity transfer
        /// calculations.
        virtual double carriedMomentum(double existingVelocity) override {
            return math_sign(existingVelocity) *
                   std::min(0.000816 * std::pow(std::abs(existingVelocity), 1.967), 40000.0);
        }

        // Eyeballed from observation to counter the effect of an unintended scroll
        // from the natural motion of lifting the finger after a scroll.
        virtual double dragStartDistanceMotionThreshold() override {
            return 3.5;
        }
    };

/// Scroll physics for environments that prevent the scroll offset from reaching
/// beyond the bounds of the content.
///
/// This is the behavior typically seen on Android.
///
/// See also:
///
///  * [ScrollConfiguration], which uses this to provide the default
///    scroll behavior on Android.
///  * [BouncingScrollPhysics], which is the analogous physics for iOS' bouncing
///    behavior.
///  * [GlowingOverscrollIndicator], which is used by [ScrollConfiguration] to
///    provide the glowing effect that is usually found with this clamping effect
///    on Android. When using a [MaterialApp], the [GlowingOverscrollIndicator]'s
///    glow color is specified to use [ThemeData.accentColor].
    class ClampingScrollPhysics : public ScrollPhysics {

    public:
        /// Creates scroll physics that prevent the scroll offset from exceeding the
        /// bounds of the content..
        ClampingScrollPhysics(ScrollPhysics *parent) : ScrollPhysics(parent) {

        }

        virtual ClampingScrollPhysics *applyTo(ScrollPhysics *ancestor) override {
            return new ClampingScrollPhysics(buildParent(ancestor));
        }


        virtual double applyBoundaryConditions(ScrollMetrics *position, double value) override {
            if (value < position->pixels() &&
                position->pixels() <= position->minScrollExtent()) // underscroll
                return value - position->pixels();
            if (position->maxScrollExtent() <= position->pixels() &&
                position->pixels() < value) // overscroll
                return value - position->pixels();
            if (value < position->minScrollExtent() &&
                position->minScrollExtent() < position->pixels()) // hit top edge
                return value - position->minScrollExtent();
            if (position->pixels() < position->maxScrollExtent() &&
                position->maxScrollExtent() < value) // hit bottom edge
                return value - position->maxScrollExtent();
            return 0.0;
        }


        virtual Simulation* createBallisticSimulation(ScrollMetrics *position, double velocity) override {
            Tolerance *tolerance = this->getTolerance();
            if (position->outOfRange()) {
                double end;
                if (position->pixels() > position->maxScrollExtent())
                    end = position->maxScrollExtent();
                if (position->pixels() < position->minScrollExtent())
                    end = position->minScrollExtent();
                return new ScrollSpringSimulation(spring(), position->pixels(), end,
                                                  std::min(0.0, velocity), tolerance);
            }
            if (std::abs(velocity) < tolerance->velocity)
                return nullptr;
            if (velocity > 0.0 && position->pixels() >= position->maxScrollExtent())
                return nullptr;
            if (velocity < 0.0 && position->pixels() <= position->minScrollExtent())
                return nullptr;
            double friction = 0.015;
            return new ClampingScrollSimulation(position->pixels(), velocity, friction, tolerance);
        }
    };

/// Scroll physics that always lets the user scroll.
///
/// On Android, overscrolls will be clamped by default and result in an
/// overscroll glow. On iOS, overscrolls will load a spring that will return
/// the scroll view to its normal range when released.
///
/// See also:
///
///  * [ScrollPhysics], which can be used instead of this class when the default
///    behavior is desired instead.
///  * [BouncingScrollPhysics], which provides the bouncing overscroll behavior
///    found on iOS.
///  * [ClampingScrollPhysics], which provides the clamping overscroll behavior
///    found on Android.
    class AlwaysScrollableScrollPhysics : public ScrollPhysics {


    public:
        /// Creates scroll physics that always lets the user scroll.
        AlwaysScrollableScrollPhysics(ScrollPhysics *parent) : ScrollPhysics(parent) {
        }

        virtual AlwaysScrollableScrollPhysics *applyTo(ScrollPhysics *ancestor) override {
            return new AlwaysScrollableScrollPhysics(buildParent(ancestor));
        }

        virtual bool shouldAcceptUserOffset(ScrollMetrics *position) override {
            return true;
        }
    };

/// Scroll physics that does not allow the user to scroll.
///
/// See also:
///
///  * [ScrollPhysics], which can be used instead of this class when the default
///    behavior is desired instead.
///  * [BouncingScrollPhysics], which provides the bouncing overscroll behavior
///    found on iOS.
///  * [ClampingScrollPhysics], which provides the clamping overscroll behavior
///    found on Android.
    class NeverScrollableScrollPhysics : public ScrollPhysics {


    public:
        /// Creates scroll physics that does not let the user scroll.
        NeverScrollableScrollPhysics(ScrollPhysics *parent) : ScrollPhysics(parent) {
        }

        virtual NeverScrollableScrollPhysics *applyTo(ScrollPhysics *ancestor) override {
            return new NeverScrollableScrollPhysics(buildParent(ancestor));
        }

        virtual bool shouldAcceptUserOffset(ScrollMetrics *position) override {
            return false;
        }

        virtual bool allowImplicitScrolling() {
            return false;
        }
    };

}



#endif //WEEX_UIKIT_GESTURE_SCROLLPHYSICS_H
