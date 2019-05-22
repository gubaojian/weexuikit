//
// Created by furture on 2018/10/25.
//

#ifndef WEEX_UIKIT_GESTURE_SPRINGSIMULATION_H
#define WEEX_UIKIT_GESTURE_SPRINGSIMULATION_H
#include "Simulation.h"
#include <cmath>



namespace weexuikit {
/// Structure that describes a spring's constants.
///
/// Used to configure a [SpringSimulation].
    class SpringDescription {


    public:
        /// Creates a spring given the mass, stiffness, and the damping coefficient.
        ///
        /// See [mass], [stiffness], and [damping] for the units of the arguments.
        SpringDescription(double mass, double stiffness, double damping) {
            this->mass = mass;
            this->stiffness = stiffness;
            this->mDamping = damping;
        }

        /// Creates a spring given the mass (m), stiffness (k), and damping ratio (ζ).
        /// The damping ratio is especially useful trying to determining the type of
        /// spring to create. A ratio of 1.0 creates a critically damped spring, > 1.0
        /// creates an overdamped spring and < 1.0 an underdamped one.
        ///
        /// See [mass] and [stiffness] for the units for those arguments. The damping
        /// ratio is unitless.
        static SpringDescription *
        withDampingRatio(double mass, double stiffness, double ratio = 1.0) {
            mass = mass;
            stiffness = stiffness;
            double damping = ratio * 2.0 * std::sqrt(mass * stiffness);
            return new SpringDescription(mass, stiffness, damping);
        }

    public:
        /// The mass of the spring (m). The units are arbitrary, but all springs
        /// within a system should use the same mass units.
        double mass;

        /// The spring constant (k). The units of stiffness are M/T², where M is the
        /// mass unit used for the value of the [mass] property, and T is the time
        /// unit used for driving the [SpringSimulation].
        double stiffness;

        /// The damping coefficient (c).
        ///
        /// Do not confuse the damping _coefficient_ (c) with the damping _ratio_ (ζ).
        /// To create a [SpringDescription] with a damping ratio, use the [new
        /// SpringDescription.withDampingRatio] constructor.
        ///
        /// The units of the damping coefficient are M/T, where M is the mass unit
        /// used for the value of the [mass] property, and T is the time unit used for
        /// driving the [SpringSimulation].
        double mDamping;

    };


/// The kind of spring solution that the [SpringSimulation] is using to simulate the spring.
///
/// See [SpringSimulation.type].
    enum class SpringType {
        /// A spring that does not bounce and returns to its rest position in the
        /// shortest possible time.
                criticallyDamped,

        /// A spring that bounces.
                underDamped,

        /// A spring that does not bounce but takes longer to return to its rest
        /// position than a [criticallyDamped] one.
                overDamped,
    };


    class SpringSolution;

/// A spring simulation.
///
/// Models a particle attached to a spring that follows Hooke's law.
    class SpringSimulation : public Simulation {

    public:
        /// Creates a spring simulation from the provided spring description, start
        /// distance, end distance, and initial velocity.
        ///
        /// The units for the start and end distance arguments are arbitrary, but must
        /// be consistent with the units used for other lengths in the system.
        ///
        /// The units for the velocity are L/T, where L is the aforementioned
        /// arbitrary unit of length, and T is the time unit used for driving the
        /// [SpringSimulation].
        SpringSimulation(SpringDescription *spring, double start, double end, double velocity,
                         Tolerance *tolerance = Tolerance::getDefaultTolerance());

    public:
        double mEndPosition;
        SpringSolution * mSolution;

        /// The kind of spring being simulated, for debugging purposes.
        ///
        /// This is derived from the [SpringDescription] provided to the [new
        /// SpringSimulation] constructor.
        virtual SpringType getType();

        virtual double x(double time) override;


        virtual double dx(double time) override;


        virtual bool isDone(double time) override;

    };


/// A SpringSimulation where the value of [x] is guaranteed to have exactly the
/// end value when the simulation isDone().
    class ScrollSpringSimulation : public SpringSimulation {


    public:
        /// Creates a spring simulation from the provided spring description, start
        /// distance, end distance, and initial velocity.
        ///
        /// See the [new SpringSimulation] constructor on the superclass for a
        /// discussion of the arguments' units.
        ScrollSpringSimulation(SpringDescription *spring, double start, double end, double velocity,
                               Tolerance *tolerance = Tolerance::getDefaultTolerance())
                : SpringSimulation(spring, start, end, velocity, tolerance) {

        }


        virtual double x(double time) override {
            return isDone(time) ? mEndPosition : SpringSimulation::x(time);
        }
    };


    class SpringSolution {

    public:
        static SpringSolution *
        makeSpringSolution(SpringDescription *spring, double initialPosition,
                           double initialVelocity);

        virtual double x(double time)=0;

        virtual double dx(double time)=0;

        virtual SpringType getType()=0;
    };

    class CriticalSolution : public SpringSolution {

    public:
        static CriticalSolution *
        makeCriticalSolution(SpringDescription *spring, double distance, double velocity) {
            double r = -spring->mDamping / (2.0 * spring->mass);
            double c1 = distance;
            double c2 = velocity / (r * distance);
            return new CriticalSolution(r, c1, c2);
        }

    public:
        CriticalSolution(double r, double c1, double c2) {
            mR = r,
            mC1 = c1,
            mC2 = c2;
        }

    public:
        double mR;
        double mC1;
        double mC2;


        virtual double x(double time) override {
            return (mC1 + mC2 * time) * std::pow(M_E, mR * time);
        }


        virtual double dx(double time) override {
            double power = std::pow(M_E, mR * time);
            return mR * (mC1 + mC2 * time) * power + mC2 * power;
        }


        virtual SpringType getType() override {
            return SpringType::criticallyDamped;
        }
    };

    class OverdampedSolution : public SpringSolution {

    public:
        static OverdampedSolution *
        makeOverdampedSolution(SpringDescription *spring, double distance, double velocity) {
            double cmk = spring->mDamping * spring->mDamping - 4 * spring->mass * spring->stiffness;
            double r1 = (-spring->mDamping - std::sqrt(cmk)) / (2.0 * spring->mass);
            double r2 = (-spring->mDamping + std::sqrt(cmk)) / (2.0 * spring->mass);
            double c2 = (velocity - r1 * distance) / (r2 - r1);
            double c1 = distance - c2;
            return new OverdampedSolution(r1, r2, c1, c2);
        }

    public:
        OverdampedSolution(double r1, double r2, double c1, double c2) {
            mR1 = r1,
            mR2 = r2,
            mC1 = c1,
            mC2 = c2;
        }

    public:
        double mR1;
        double mR2;
        double mC1;
        double mC2;


        virtual double x(double time) override {
            return mC1 * std::pow(M_E, mR1 * time) +
                   mC2 * std::pow(M_E, mR2 * time);
        }


        virtual double dx(double time) override {
            return mC1 * mR1 * std::pow(M_E, mR1 * time) +
                   mC2 * mR2 * std::pow(M_E, mR2 * time);
        }

        virtual SpringType getType() override {
            return SpringType::overDamped;
        }
    };

    class UnderdampedSolution : public SpringSolution {

    public:
        static UnderdampedSolution* makeUnderdampedSolution(SpringDescription *spring, double distance, double velocity) {
            double w = std::sqrt(4.0 * spring->mass * spring->stiffness -
                                 spring->mDamping * spring->mDamping) / (2.0 * spring->mass);
            double r = -(spring->mDamping / 2.0 * spring->mass);
            double c1 = distance;
            double c2 = (velocity - r * distance) / w;
            return new UnderdampedSolution(w, r, c1, c2);
        }

        UnderdampedSolution(double w, double r, double c1, double c2) {
            mW = w;
            mR = r;
            mC1 = c1;
            mC2 = c2;
        }

    public:
        double mW;
        double mR;
        double mC1;
        double mC2;


        virtual double x(double time) override {
            return std::pow(M_E, mR * time) *
                   (mC1 * std::cos(mW * time) + mC2 * std::sin(mW * time));
        }


        virtual double dx(double time) override {
            double power = std::pow(M_E, mR * time);
            double cosine = std::cos(mW * time);
            double sine = std::sin(mW * time);
            return power * (mC2 * mW * cosine - mC1 * mW * sine) +
                   mR * power * (mC2 * sine + mC1 * cosine);
        }

        virtual SpringType getType() override {
            return SpringType::underDamped;
        }
    };

}




#endif //WEEX_UIKIT_GESTURE_SPRINGSIMULATION_H
