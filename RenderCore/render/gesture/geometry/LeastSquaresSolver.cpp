//
// Created by furture on 2018/10/18.
//

#include "LeastSquaresSolver.h"


namespace weexuikit {
    MatrixVector::MatrixVector(double *values, int offset, int length) {
        this->mElements = values;
        this->mOffset = offset;
        this->mLength = length;
    }

    double MatrixVector::multi(MatrixVector *a) {
        double result = 0.0;
        for (int i = 0; i < mLength; i += 1) {
            result += (this->get(i)) * a->get(i);
        }
        return result;
    }

    MatrixVector::~MatrixVector() {
        this->mElements = nullptr;
        this->mOffset = 0;
        this->mLength = 0;
    }


    Matrix::Matrix(int rows, int cols) {
        _columns = cols;
        _elements = new double[rows * cols]();
    }


    Matrix::~Matrix() {
        if (_elements != nullptr) {
            delete[]  _elements;
            _elements = nullptr;
        }
    }


    PolynomialFit::PolynomialFit(int degree) {
        confidence = 0;
        coefficients = new double[degree + 1]();
    }

    PolynomialFit::~PolynomialFit() {
        if (coefficients != nullptr) {
            delete[]  coefficients;
            coefficients = nullptr;
        }
    }


    LeastSquaresSolver::LeastSquaresSolver(const std::vector<double> &x,
                                           const std::vector<double> &y,
                                           const std::vector<double> &w) {
        assert(x.size() == y.size()),
                assert(y.size() == w.size());
        this->x = x;
        this->y = y;
        this->w = w;
    }


    PolynomialFit *LeastSquaresSolver::solve(int degree) {
        if (degree > x.size()) {
            // Not enough data to fit a curve.
            return nullptr;
        }


        PolynomialFit *result = new PolynomialFit(degree);


        // Shorthands for the purpose of notation equivalence to original C++ code.
        const int m = x.size();
        const int n = degree + 1;


        // Expand the X vector to a matrix A, pre-multiplied by the weights.
        Matrix a = Matrix(n, m);
        for (int h = 0; h < m; h += 1) {
            a.set(0, h, w[h]);
            for (int i = 1; i < n; i += 1)
                a.set(i, h, a.get(i - 1, h) * x[h]);
        }

        // Apply the Gram-Schmidt process to A to obtain its QR decomposition.

        // Orthonormal basis, column-major ordVectorer.
        Matrix q = Matrix(n, m);
        // Upper triangular matrix, row-major order.
        Matrix r = Matrix(n, n);
        for (int j = 0; j < n; j += 1) {
            for (int h = 0; h < m; h += 1) {
                q.set(j, h, a.get(j, h));
            }
            for (int i = 0; i < j; i += 1) {
                MatrixVector qRow = q.getRow(i);
                const double dot = (q.getRow(j).multi(&qRow));
                for (int h = 0; h < m; h += 1) {
                    q.set(j, h, q.get(j, h) - dot * q.get(i, h));
                }
            }
            const double norm = q.getRow(j).norm();
            if (norm < 0.000001) {
                // Vectors are linearly dependent or zero so no solution.
                return nullptr;
            }

            double inverseNorm = 1.0 / norm;
            for (int h = 0; h < m; h += 1)
                q.set(j, h, q.get(j, h) * inverseNorm);
            for (int i = 0; i < n; i += 1) {
                MatrixVector aRow = a.getRow(i);
                r.set(j, i, i < j ? 0.0 : q.getRow(j).multi(&aRow));
            }
        }

        // Solve R B = Qt W Y to find B. This is easy because R is upper triangular.
        // We just work from bottom-right to top-left calculating B's coefficients.
        double *doubleValues = new double[m]();
        MatrixVector wy = MatrixVector(doubleValues, 0, m);

        for (int h = 0; h < m; h += 1) {
            wy.set(h, y[h] * w[h]);
        }

        for (int i = n - 1; i >= 0; i -= 1) {
            MatrixVector matrixVector = q.getRow(i);
            result->coefficients[i] = matrixVector.multi(&wy);
            for (int j = n - 1; j > i; j -= 1)
                result->coefficients[i] -= r.get(i, j) * (result->coefficients[j]);
            result->coefficients[i] /= r.get(i, i);
        }


        // Calculate the coefficient of determination (confidence) as:
        //   1 - (sumSquaredError / sumSquaredTotal)
        // ...where sumSquaredError is the residual sum of squares (variance of the
        // error), and sumSquaredTotal is the total sum of squares (variance of the
        // data) where each has been weighted.
        double yMean = 0.0;
        for (int h = 0; h < m; h += 1)
            yMean += y[h];
        yMean /= m;
        double sumSquaredError = 0.0;
        double sumSquaredTotal = 0.0;
        for (int h = 0; h < m; h += 1) {
            double term = 1.0;
            double err = y[h] - result->coefficients[0];
            for (int i = 1; i < n; i += 1) {
                term *= x[h];
                err -= term * result->coefficients[i];
            }
            sumSquaredError += w[h] * w[h] * err * err;
            double v = y[h] - yMean;
            sumSquaredTotal += w[h] * w[h] * v * v;
        }

        result->confidence =
                sumSquaredTotal <= 0.000001 ? 1.0 : 1.0 - (sumSquaredError / sumSquaredTotal);


        return result;
    }
}