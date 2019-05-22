//
// Created by furture on 2018/10/23.
//

#ifndef WEEX_UIKIT_GESTURE_TOLERANCE_H
#define WEEX_UIKIT_GESTURE_TOLERANCE_H


namespace weexuikit {
/// Structure that specifies maximum allowable magnitudes for distances,
/// durations, and velocity differences to be considered equal.
    class Tolerance {
    public:
        /// Creates a [Tolerance] object. By default, the distance, time, and velocity
        /// tolerances are all ±0.001; the constructor arguments override this.
        Tolerance();

        Tolerance(double distance, double time, double velocity);

        static Tolerance *getDefaultTolerance();

    public:
        static constexpr double _epsilonDefault = 1e-3;

    private:
        /// A default tolerance of 0.001 for all three values.
        static Tolerance *defaultTolerance;

    public:
        /// The magnitude of the maximum distance between two points for them to be
        /// considered within tolerance.
        ///
        /// The units for the distance tolerance must be the same as the units used
        /// for the distances that are to be compared to this tolerance.
        double distance;

        /// The magnitude of the maximum duration between two times for them to be
        /// considered within tolerance.
        ///
        /// The units for the time tolerance must be the same as the units used
        /// for the times that are to be compared to this tolerance.
        double time;

        /// The magnitude of the maximum difference between two velocities for them to
        /// be considered within tolerance.
        ///
        /// The units for the velocity tolerance must be the same as the units used
        /// for the velocities that are to be compared to this tolerance.
        double velocity;

    };
}


#endif //WEEX_UIKIT_GESTURE_TOLERANCE_H
