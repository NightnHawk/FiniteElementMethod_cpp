//
// Created by grzeg on 17.12.2023.
//

#ifndef FEM_MATRIX_H
#define FEM_MATRIX_H


#include <iostream>
#include <vector>

template <class T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    Matrix(size_t numRows, size_t numCols, const T &initialValue = T())
        : rows(numRows), cols(numCols), data(numRows, std::vector<T>(numCols, initialValue)) {}

    [[nodiscard]] size_t numRows() const {
        return rows;
    }

    [[nodiscard]] size_t numCols() const {
        return cols;
    }

    T& operator()(size_t row, size_t col) {
        return data[row][col];
    }

    void print() const {
        for(size_t i = 0; i < rows; i++) {
            for(size_t j = 0; j < cols; j++) {
                std::cout << std::to_string(data[i][j]) << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::vector<T>> getSubMatrix(size_t excludeRow, size_t excludeCol) const {
        std::vector<std::vector<T>> subMat;
        subMat.reserve(rows - 1);

        for (size_t i = 0; i < rows; ++i) {
            if (i == excludeRow) continue;
            std::vector<T> row;
            row.reserve(cols - 1);
            for (size_t j = 0; j < cols; ++j) {
                if (j != excludeCol) {
                    row.push_back(data[i][j]);
                }
            }
            subMat.push_back(row);
        }

        return subMat;
    }

    std::vector<T> getRow(size_t index) const {
        return data[index];
    }

    template<typename U = T, typename std::enable_if<std::is_same<U, float>::value || std::is_same<U, double>::value, int>::type = 0>
    T determinant() const {
        if (rows != cols) {
            throw std::runtime_error("Determinant is only defined for square matrices.");
        }

        if (rows == 1) {
            return data[0][0];
        } else {
            T det = static_cast<T>(0);
            int sign = 1;

            for (size_t i = 0; i < cols; ++i) {
                Matrix<T> subMat(rows - 1, cols - 1);
                for (size_t j = 1; j < rows; ++j) {
                    size_t colIdx = 0;
                    for (size_t k = 0; k < cols; ++k) {
                        if (k != i) {
                            subMat(j - 1, colIdx) = data[j][k];
                            ++colIdx;
                        }
                    }
                }
                det += static_cast<T>(sign) * data[0][i] * subMat.determinant();
                sign = -sign;
            }

            return det;
        }
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        if(rows != other.rows or cols != other.cols) {
            std::string error_message = "Matrices must have the same dimensions for addition. dim(A) = (" +
                    std::to_string(rows) + ", " + std::to_string(cols) + ") != dim(B) = (" +
                    std::to_string(other.rows) + ", " + std::to_string(other.cols) + ")";
            throw std::invalid_argument(error_message);
        }

        Matrix<T> result(rows, cols);
        for(size_t i = 0; i < rows; i++)
            for(size_t j = 0; j < cols; j++)
                result(i, j) = data[i][j] + other.data[i][j];

        return result;
    }

    Matrix<T> operator-(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            std::string error_message = "Matrices must have the same dimensions for subtraction. dim(A) = (" +
                    std::to_string(rows) + ", " + std::to_string(cols) + ") != dim(B) = (" +
                    std::to_string(other.rows) + ", " + std::to_string(other.cols) + ")";
            throw std::invalid_argument(error_message);
        }

        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result(i, j) = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator*(const T& scalar) const {
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] * scalar;
            }
        }

        return result;
    }

    std::vector<T> operator*(const std::vector<T> &vec) const {
        if (cols != vec.size()) {
            std::string error_message = "Matrix columns must match vector size for multiplication. dim(A) = (" +
                    std::to_string(rows) + ", " + std::to_string(cols) + ") + dim(B) = (" +
                    std::to_string(vec.size()) + ")";
            throw std::invalid_argument(error_message);
        }
        std::vector<T> result(rows, 0);

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result[i] += data[i][j] * vec[j];
            }
        }

        return result;
    }

    static Matrix<T> outerProduct(const std::vector<T> &vec1, const std::vector<T> &vec2) {
        size_t rows = vec1.size();
        size_t cols = vec2.size();

        Matrix<T> result(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = vec1[i] * vec2[j];
            }
        }

        return result;
    }

    static T dotProduct(const std::vector<T>& vec1, const std::vector<T>& vec2) {
        if (vec1.size() != vec2.size()) {
            std::string error_message = "Vectors must have the same size for dot product. dim(A) = (" +
                    std::to_string(vec1.size()) + ") != dim(B) = (" + std::to_string(vec2.size()) + ")";
            throw std::invalid_argument(error_message);
        }

        T result = static_cast<T>(0);

        for (size_t i = 0; i < vec1.size(); ++i) {
            result += vec1[i] * vec2[i];
        }

        return result;
    }

    std::vector<T> flatten() {
        std::vector<T> flattened;
        for(const auto& row: this->data) {
            flattened.insert(flattened.end(), row.begin(), row.end());
        }
        return flattened;
    }

    static std::vector<T> vecMultiplyScalar(std::vector<double> vec, T scalar) {
        std::vector<T> result(vec.size());
        for(size_t i = 0; i < vec.size(); i++) {
            result[i] = vec[i] * scalar;
        }
        return result;
    }

    static std::vector<T> sumVec(std::vector<T> vec1, std::vector<T> vec2) {
        if(vec1.size() != vec2.size()) {
            std::string error_message = "Vectors must have the same size for summation. dim(A) = (" +
            std::to_string(vec1.size()) + ") != dim(B) = (" + std::to_string(vec2.size()) + ")";
            throw std::invalid_argument(error_message);
        }
        std::vector<T> result(vec1.size());
        for(size_t i = 0; i < vec1.size(); i++) {
            result[i] = vec1[i] + vec2[i];
        }
        return result;
    }

    static std::vector<T> solveEquations(Matrix<T> &inputMatrix) {
        int n = inputMatrix.numRows();

        for(int i = 0; i < n; i++) {
            T divisor = inputMatrix(i, i);
            for(int j = i; j < n + 1; j++) {
                inputMatrix(i, j) /= divisor;
            }

            for(int k = 0; k < n; k++) {
                if(k != i) {
                    T factor = inputMatrix(k, i);
                    for(int j = i; j < n + 1; j++) {
                        inputMatrix(k, j) -= factor * inputMatrix(i, j);
                    }
                }
            }
        }

        std::vector<T> solution;
        for(int i = 0; i < n; i++) {
            solution.push_back(inputMatrix(i, n));
        }

        return solution;
    }

    static std::vector<T> gaussJordan(Matrix<T> &inputMatrix) {
        auto matrix = inputMatrix.data;
        int n = matrix.size();

        for (int i = 0; i < n; i++) {
            // Find pivot row
            int pivot = i;
            for (int j = i + 1; j < n; j++) {
                if (abs(matrix[j][i]) > abs(matrix[pivot][i])) {
                    pivot = j;
                }
            }

            if (abs(matrix[pivot][i]) < 1e-10) {
                // Matrix is singular or nearly singular
                continue;
            }

            // Swap rows
            swap(matrix[i], matrix[pivot]);

            // Make the diagonal element 1
            double divisor = matrix[i][i];
            for (int j = i; j < n + 1; j++) {
                matrix[i][j] /= divisor;
            }

            // Eliminate other elements
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    double factor = matrix[j][i];
                    for (int k = i; k < n + 1; k++) {
                        matrix[j][k] -= factor * matrix[i][k];
                    }
                }
            }
        }
        // Extract solution
        std::vector<double> solution;
        for (int i = 0; i < n; ++i) {
            solution.push_back(matrix[i][n]);
        }

        return solution;
    }

    void full(T value) {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++)
                data[i][j] = value;
        }
    }
};

#endif //FEM_MATRIX_H
