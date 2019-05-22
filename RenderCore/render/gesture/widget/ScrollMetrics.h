//
// Created by furture on 2018/10/23.
//

#ifndef WEEX_UIKIT_GESTURE_SCROLLMETRICS_H
#define WEEX_UIKIT_GESTURE_SCROLLMETRICS_H

#include <algorithm>
#include "../foundation/BasicTypes.h"

namespace weexuikit {
/// A description of a [Scrollable]'s contents, useful for modeling the state
/// of its viewport.
///
/// This class defines a current position, [pixels], and a range of values
/// considered "in bounds" for that position. The range has a minimum value at
/// [minScrollExtent] and a maximum value at [maxScrollExtent] (inclusive). The
/// viewport scrolls in the direction and axis described by [axisDirection]
/// and [axis].
///
/// The [outOfRange] getter will return true if [pixels] is outside this defined
/// range. The [atEdge] getter will return true if the [pixels] position equals
/// either the [minScrollExtent] or the [maxScrollExtent].
///
/// The dimensions of the viewport in the given [axis] are described by
/// [viewportDimension].
///
/// The above values are also exposed in terms of [extentBefore],
/// [extentInside], and [extentAfter], which may be more useful for use cases
/// such as scroll bars; for example, see [Scrollbar].
///
/// See also:
///
///  * [FixedScrollMetrics], which is an immutable object that implements this
///    interface.
    class ScrollMetrics {


    public:
        /// The minimum in-range value for [pixels].
        ///
        /// The actual [pixels] value might be [outOfRange].
        ///
        /// This value can be negative infinity, if the scroll is unbounded.
        virtual double minScrollExtent()=0;

        /// The maximum in-range value for [pixels].
        ///
        /// The actual [pixels] value might be [outOfRange].
        ///
        /// This value can be infinity, if the scroll is unbounded.
        virtual double maxScrollExtent()=0;

        /// The current scroll position, in logical pixels along the [axisDirection].
        virtual double pixels()=0;

        /// The extent of the viewport along the [axisDirection].
        virtual double viewportDimension()=0;

        /// The direction in which the scroll view scrolls.
        virtual AxisDirection axisDirection()=0;

        /// The axis in which the scroll view scrolls.
        virtual Axis axis() {
            return axisDirectionToAxis(axisDirection());
        }

        /// Whether the [pixels] value is outside the [minScrollExtent] and
        /// [maxScrollExtent].
        virtual bool outOfRange() {
            return pixels() < minScrollExtent() || pixels() > maxScrollExtent();
        }

        /// Whether the [pixels] value is exactly at the [minScrollExtent] or the
        /// [maxScrollExtent].
        virtual bool atEdge() {
            return pixels() == minScrollExtent() || pixels() == maxScrollExtent();
        }

        /// The quantity of content conceptually "above" the currently visible content
        /// of the viewport in the scrollable. This is the content above the content
        /// described by [extentInside].
        virtual double extentBefore() {
            return std::max(pixels() - minScrollExtent(), 0.0);
        }

        /// The quantity of visible content.
        ///
        /// If [extentBefore] and [extentAfter] are non-zero, then this is typically
        /// the height of the viewport. It could be less if there is less content
        /// visible than the size of the viewport.
        virtual double extentInside() {
            return std::min(pixels(), maxScrollExtent()) -
                   std::max(pixels(), minScrollExtent()) +
                   std::min(viewportDimension(), maxScrollExtent() - minScrollExtent());
        }

        /// The quantity of content conceptually "below" the currently visible content
        /// of the viewport in the scrollable. This is the content below the content
        /// described by [extentInside].
        virtual double extentAfter() {
            return std::max(maxScrollExtent() - pixels(), 0.0);
        }
    };


/// An immutable snapshot of values associated with a [Scrollable] viewport.
///
/// For details, see [ScrollMetrics], which defines this object's interfaces.
    class FixedScrollMetrics : public ScrollMetrics {

    public:
        /// Creates an immutable snapshot of values associated with a [Scrollable] viewport.
        FixedScrollMetrics(double minScrollExtent, double maxScrollExtent, double pixels,
                           double viewportDimension, AxisDirection axisDirection) {
            this->mMinScrollExtent = minScrollExtent;
            this->mMaxScrollExtent = maxScrollExtent;
            this->mPixels = pixels;
            this->mViewportDimension = viewportDimension;
            this->mAxisDirection = axisDirection;
        }


    public:
        double mMinScrollExtent;
        double mMaxScrollExtent;
        double mPixels;
        double mViewportDimension;
        AxisDirection mAxisDirection;


    public:

        virtual double minScrollExtent() override {
            return mMinScrollExtent;
        }

        virtual double maxScrollExtent() override {
            return mMaxScrollExtent;
        }

        virtual double pixels() override {
            return mPixels;
        }

        virtual double viewportDimension() override {
            return mViewportDimension;
        }

        virtual AxisDirection axisDirection() override {
            return mAxisDirection;
        }
    };
}

#endif //WEEX_UIKIT_GESTURE_SCROLLMETRICS_H
