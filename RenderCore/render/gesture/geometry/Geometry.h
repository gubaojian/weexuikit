//
// Created by furture on 2018/10/18.
//

#ifndef WEEX_UIKIT_GESTURE_GEOMETRY_H
#define WEEX_UIKIT_GESTURE_GEOMETRY_H


#include <cmath>

namespace weexuikit {

    class Offset {

    public:
        Offset() : dx(0), dy(0) {};

        Offset(double x, double y) : dx(x), dy(y) {};

        inline double distance() {
            return sqrt(dx * dx + dy * dy);
        };

        inline double distanceSquared() {
            return dx * dx + dy * dy;
        }


        inline bool isZero() {
            return dx == 0 && dy == 0;
        }

        /// Binary subtraction operator.
        ///
        /// Returns an offset whose [dx] value is the left-hand-side operand's [dx]
        /// minus the right-hand-side operand's [dx] and whose [dy] value is the
        /// left-hand-side operand's [dy] minus the right-hand-side operand's [dy].

        inline Offset operator-(const Offset &other) {
            return Offset(dx - other.dx, dy - other.dy);
        }


        /// Multiplication operator.
        ///
        /// Returns an offset whose coordinates are the coordinates of the
        /// left-hand-side operand (an Offset) multiplied by the scalar
        /// right-hand-side operand (a double).
        ///
        /// See also [scale].
        inline Offset operator*(double operand) {
            return Offset(dx * operand, dy * operand);
        }


        /// Division operator.
        ///
        /// Returns an offset whose coordinates are the coordinates of the
        /// left-hand-side operand (an Offset) divided by the scalar right-hand-side
        /// operand (a double).
        ///
        /// See also [scale].
        inline Offset operator/(double operand) {
            return Offset(dx / operand, dy / operand);
        }


        inline Offset &operator+=(const Offset &other) {
            dx += other.dx;
            dy += other.dy;
            return *this;
        }

        /// Binary addition operator.
        ///
        /// Returns an offset whose [dx] value is the sum of the [dx] values of the
        /// two operands, and whose [dy] value is the sum of the [dy] values of the
        /// two operands.
        ///
        /// See also [translate].
        inline Offset operator+(const Offset &other) {
            return Offset(dx + other.dx, dy + other.dy);
        }

    public:
        double dx;
        double dy;
    };

    inline Offset makeOffset(double dx, double dy) {
        return Offset(dx, dy);
    }

    inline Offset makeZero() {
        return Offset(0, 0);
    }

}
#endif //WEEX_UIKIT_GESTURE_GEOMETRY_H_H
