//
// Created by furture on 2018/10/18.
//

#include "VelocityTracker.h"

namespace weexuikit {
    VelocityTracker::VelocityTracker() {
        mSamples = new PointAtTime *[mHistorySize]();
    }

    VelocityTracker::~VelocityTracker() {
        if (mSamples) {
            for (int i = 0; i < mHistorySize; i++) {
                PointAtTime *pointAtTime = mSamples[i];
                if (pointAtTime != nullptr) {
                    delete pointAtTime;
                }
                mSamples[i] = nullptr;
            }
            delete[]  mSamples;
            mSamples = nullptr;
        }
    }


    void VelocityTracker::addPosition(int64_t time, Offset position) {
        mIndex += 1;
        if (mIndex == mHistorySize)
            mIndex = 0;
        PointAtTime *pointAtTime = mSamples[mIndex];
        if (pointAtTime == nullptr) {
            pointAtTime = new PointAtTime();
            mSamples[mIndex] = pointAtTime;
        }
        pointAtTime->time = time;
        pointAtTime->point = position;
    }

    VelocityEstimate *VelocityTracker::getVelocityEstimate() {
        std::vector<double> x;
        std::vector<double> y;
        std::vector<double> w;
        std::vector<double> time;
        int sampleCount = 0;
        int index = mIndex;

        PointAtTime *newestSample = mSamples[index];
        if (newestSample == nullptr)
            return nullptr;

        PointAtTime *previousSample = newestSample;
        PointAtTime *oldestSample = newestSample;

        // Starting with the most recent PointAtTime sample, iterate backwards while
        // the samples represent continuous motion.
        do {
            PointAtTime *sample = mSamples[index];
            if (sample == nullptr)
                break;

            double age = (newestSample->time - sample->time);
            double delta = std::abs(sample->time - previousSample->time);
            previousSample = sample;
            if (age > mHorizonMilliseconds || delta > mAssumePointerMoveStoppedMilliseconds)
                break;

            oldestSample = sample;
            Offset position = sample->point;
            x.push_back(position.dx);
            y.push_back(position.dy);
            w.push_back(1.0);
            time.push_back(-age);
            index = (index == 0 ? mHistorySize : index) - 1;

            sampleCount += 1;
        } while (sampleCount < mHistorySize);

        if (sampleCount >= mMinSampleSize) {
            LeastSquaresSolver xSolver = LeastSquaresSolver(time, x, w);
            PolynomialFit *xFit = xSolver.solve(2);

            if (xFit != nullptr) {
                std::unique_ptr<PolynomialFit> xFitRef(xFit);
                LeastSquaresSolver ySolver = LeastSquaresSolver(time, y, w);
                PolynomialFit *yFit = ySolver.solve(2);
                if (yFit != nullptr) {
                    std::unique_ptr<PolynomialFit> yFitRef(yFit);
                    Offset pixelsPerSecond = {xFit->coefficients[1] * 1000,
                                              yFit->coefficients[1] * 1000};

                    double confidence = xFit->confidence * yFit->confidence;
                    int64_t duration = newestSample->time - oldestSample->time;
                    Offset offset = newestSample->point - oldestSample->point;
                    return new VelocityEstimate{pixelsPerSecond, confidence, duration, offset};
                }
            }
        }

        Offset pixelsPerSecond = {0, 0};
        double confidence = 1.0;
        int64_t duration = newestSample->time - oldestSample->time;
        Offset offset = newestSample->point - oldestSample->point;

        // We're unable to make a velocity estimate but we did have at least one
        // valid pointer position.
        return new VelocityEstimate{pixelsPerSecond, confidence, duration, offset};
    }

    Velocity VelocityTracker::getVelocity() {
        VelocityEstimate *estimate = getVelocityEstimate();
        Offset pixelsPerSecond;
        if (estimate == nullptr) {
            return Velocity{pixelsPerSecond};
        }
        pixelsPerSecond = estimate->pixelsPerSecond;
        delete estimate;
        return Velocity{pixelsPerSecond};
    }
}