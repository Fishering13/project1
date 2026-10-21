#include "matrix.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
/** @brief Check dimensions, row array and individual row pointers.
 * @param m Matrix to inspect.
 * @return True when the matrix structure is usable.
 */
bool valid(Matrix m) noexcept {
    if (!m.data || m.rows <= 0 || m.cols <= 0) return false;
    for (int i = 0; i < m.rows; ++i) if (!m.data[i]) return false;
    return true;
}
/** @brief Reject invalid matrix structures.
 * @param m Matrix to validate.
 * @throws std::invalid_argument For invalid input.
 */
void require_valid(Matrix m) {
    if (!valid(m)) throw std::invalid_argument("Invalid matrix");
}
}

Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0)
        throw std::invalid_argument("Matrix dimensions must be positive");
    Matrix result{new double*[rows]{}, rows, cols};
    try {
        for (int i = 0; i < rows; ++i) result.data[i] = new double[cols]{};
    } catch (...) {
        free_matrix(result);
        throw;
    }
    return result;
}

void free_matrix(Matrix m) noexcept {
    if (!m.data) return;
    for (int i = 0; i < m.rows; ++i) delete[] m.data[i];
    delete[] m.data;
}

Matrix matrix_add(Matrix a, Matrix b) {
    require_valid(a);
    require_valid(b);
    if (a.rows != b.rows || a.cols != b.cols)
        throw std::invalid_argument("Addition requires equal dimensions");
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; ++i)
        for (int j = 0; j < a.cols; ++j)
            result.data[i][j] = a.data[i][j] + b.data[i][j];
    return result;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    require_valid(a);
    require_valid(b);
    if (a.cols != b.rows)
        throw std::invalid_argument("Multiplication requires a.cols == b.rows");
    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; ++i)
        for (int k = 0; k < a.cols; ++k) {
            const double value = a.data[i][k];
            for (int j = 0; j < b.cols; ++j)
                result.data[i][j] += value * b.data[k][j];
        }
    return result;
}

Matrix matrix_from_array(const double* data, int rows, int cols) {
    if (!data) throw std::invalid_argument("Array must not be null");
    Matrix result = create_matrix(rows, cols);
    const double* next = data;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) result.data[i][j] = *next++;
    return result;
}

Matrix matrix_transpose(Matrix m) {
    require_valid(m);
    Matrix result = create_matrix(m.cols, m.rows);
    for (int i = 0; i < m.rows; ++i)
        for (int j = 0; j < m.cols; ++j) result.data[j][i] = m.data[i][j];
    return result;
}

int matrix_count_nonzero(Matrix m, double threshold) {
    require_valid(m);
    if (!std::isfinite(threshold) || threshold < 0.0)
        throw std::invalid_argument("Threshold must be finite and nonnegative");
    int count = 0;
    for (int i = 0; i < m.rows; ++i)
        for (int j = 0; j < m.cols; ++j)
            if (std::fabs(m.data[i][j]) > threshold) {
                if (count == std::numeric_limits<int>::max())
                    throw std::overflow_error("Count exceeds int range");
                ++count;
            }
    return count;
}

void print_matrix(Matrix m) {
    if (!valid(m)) { std::cout << "[Empty matrix]\n"; return; }
    const auto flags = std::cout.flags();
    const auto precision = std::cout.precision();
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < m.rows; ++i) {
        if (m.rows > 10 && i == 5) { std::cout << "[...]\n"; i = m.rows - 5; }
        std::cout << '[';
        for (int j = 0; j < m.cols; ++j) {
            if (m.cols > 8 && j == 4) { std::cout << " ..."; j = m.cols - 4; }
            std::cout << ' ' << std::setw(8) << m.data[i][j];
        }
        std::cout << " ]\n";
    }
    if (m.rows > 10 || m.cols > 8)
        std::cout << "Matrix " << m.rows << 'x' << m.cols << " (abbreviated)\n";
    std::cout.flags(flags);
    std::cout.precision(precision);
}
