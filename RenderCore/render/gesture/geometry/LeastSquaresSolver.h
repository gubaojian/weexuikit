//
// Created by furture on 2018/10/18.
//

#ifndef WEEX_UIKIT_GESTURE_LEASTSQUARESSOLVER_H
#define WEEX_UIKIT_GESTURE_LEASTSQUARESSOLVER_H
#include <vector>
#include <cmath>
#include <cassert>


namespace weexuikit {
    class MatrixVector {
    public:

        MatrixVector(double *values, int offset, int length);

        ~MatrixVector();

        inline double get(int i) const {
            return mElements[i + mOffset];
        }

        inline void set(int i, double value) {
            mElements[i + mOffset] = value;
        }

        double multi(MatrixVector *a);

        inline double norm() {
            return sqrt(this->multi(this));
        }

    private:
        int mOffset;
        int mLength;
        double *mElements;
    };

    class Matrix {
    public:
        Matrix(int rows, int cols);

        ~Matrix();

    public:

        inline double get(int row, int col) {
            return (_elements)[row * _columns + col];
        }

        inline void set(int row, int col, double value) {
            (_elements)[row * _columns + col] = value;
        }

        inline MatrixVector getRow(int row) {
            return MatrixVector(_elements, row * _columns, _columns);
        }


    private:
        int _columns;
        double *_elements;
    };

/// An nth degree polynomial fit to a dataset.
    class PolynomialFit {
    public:
        /// Creates a polynomial fit of the given degree.
        ///
        /// There are n + 1 coefficients in a fit of degree n.
        PolynomialFit(int degree);

        ~PolynomialFit();

    public:
        double *coefficients;
        /// An indicator of the quality of the fit.
        ///
        /// Larger values indicate greater quality.
        double confidence;
    };

/// Uses the least-squares algorithm to fit a polynomial to a set of data.
    class LeastSquaresSolver {

    public:
        LeastSquaresSolver(const std::vector<double> &x, const std::vector<double> &y,
                           const std::vector<double> &w);

        /// Fits a polynomial of the given degree to the data points.
        PolynomialFit *solve(int degree);

    private:
        /// The x-coordinates of each data point.
        std::vector<double> x;

        /// The y-coordinates of each data point.
        std::vector<double> y;

        /// The weight to use for each data point.
        std::vector<double> w;
    };

}

#endif //WEEX_UIKIT_GESTURE_LEASTSQUARESSOLVER_H
