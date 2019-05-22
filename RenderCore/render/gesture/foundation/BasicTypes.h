//
// Created by furture on 2018/10/23.
//

#ifndef WEEX_UIKIT_GESTURE_BASICTYPES_H
#define WEEX_UIKIT_GESTURE_BASICTYPES_H


#include <cassert>

namespace weexuikit {

/// The two cardinal directions in two dimensions.
///
/// The axis is always relative to the current coordinate space. This means, for
/// example, that a [horizontal] axis might actually be diagonally from top
/// right to bottom left, due to some local [Transform] applied to the scene.
///
/// See also:
///
///  * [AxisDirection], which is a directional version of this enum (with values
///    light left and right, rather than just horizontal).
///  * [TextDirection], which disambiguates between left-to-right horizontal
///    content and right-to-left horizontal content.
    enum class Axis {
        /// Left and right.
        ///
        /// See also:
        ///
        ///  * [TextDirection], which disambiguates between left-to-right horizontal
        ///    content and right-to-left horizontal content.
                horizontal,

        /// Up and down.
                vertical,
    };

/// A direction along either the horizontal or vertical [Axis].
    enum class AxisDirection {
        /// Zero is at the bottom and positive values are above it: ⇈
        ///
        /// Alphabetical content with a [GrowthDirection.forward] would have the A at
        /// the bottom and the Z at the top. This is an unusual configuration.
                up,

        /// Zero is on the left and positive values are to the right of it: ⇉
        ///
        /// Alphabetical content with a [GrowthDirection.forward] would have the A on
        /// the left and the Z on the right. This is the ordinary reading order for a
        /// horizontal set of tabs in an English application, for example.
                right,

        /// Zero is at the top and positive values are below it: ⇊
        ///
        /// Alphabetical content with a [GrowthDirection.forward] would have the A at
        /// the top and the Z at the bottom. This is the ordinary reading order for a
        /// vertical list.
                down,

        /// Zero is to the right and positive values are to the left of it: ⇇
        ///
        /// Alphabetical content with a [GrowthDirection.forward] would have the A at
        /// the right and the Z at the left. This is the ordinary reading order for a
        /// horizontal set of tabs in a Hebrew application, for example.
                left,
    };


/// Returns the [Axis] that contains the given [AxisDirection].
///
/// Specifically, returns [Axis.vertical] for [AxisDirection.up] and
/// [AxisDirection.down] and returns [Axis.horizontal] for [AxisDirection.left]
/// and [AxisDirection.right].
    inline static Axis axisDirectionToAxis(AxisDirection axisDirection) {
        switch (axisDirection) {
            case AxisDirection::up:
            case AxisDirection::down:
                return Axis::vertical;
            case AxisDirection::left:
            case AxisDirection::right:
                return Axis::horizontal;
        }
        return Axis::vertical;
    }


/// Returns whether travelling along the given axis direction visits coordinates
/// along that axis in numerically decreasing order.
///
/// Specifically, returns true for [AxisDirection.up] and [AxisDirection.left]
/// and false for [AxisDirection.down] and [AxisDirection.right].
    inline bool axisDirectionIsReversed(AxisDirection axisDirection) {
        switch (axisDirection) {
            case AxisDirection::up:
            case AxisDirection::left:
                return true;
            case AxisDirection::down:
            case AxisDirection::right:
                return false;
        }
        return true;
    }

    inline double math_sign(double sign) {
        if (sign < 0) {
            return -1;
        }
        if (sign > 0) {
            return 1;
        }
        return sign;
    }


/// Linearly interpolate between two numbers.
    inline double lerpDouble(double a, double b, double t) {
        return a + (b - a) * t;
    }

/// Whether two doubles are within a given distance of each other.
///
/// The `epsilon` argument must be positive and not null.
/// The `a` and `b` arguments may be null. A null value is only considered
/// near-equal to another null value.
    inline bool nearEqual(double a, double b, double epsilon) {
        assert(epsilon >= 0.0);
        return ((a > (b - epsilon)) && (a < (b + epsilon))) || a == b;
    }

/// Whether a double is within a given distance of zero.
///
/// The epsilon argument must be positive.
    inline bool nearZero(double a, double epsilon) {
        return nearEqual(a, 0.0, epsilon);
    }

}

#endif //WEEX_UIKIT_GESTURE_BASICTYPES_H
