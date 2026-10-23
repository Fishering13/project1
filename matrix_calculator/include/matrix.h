/** @file matrix.h
 *  @brief Matrix calculator library, laboratory 3, variant 29.
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>

using namespace std;

/** @brief Dynamically allocated matrix with independent rows.
 *  @warning Copies share storage. Free each allocation exactly once.
 */
struct Matrix {
    double** data; ///< Array of row pointers.
    int rows;      ///< Number of rows.
    int cols;      ///< Number of columns.
};

/** @brief Allocate a zero-initialized matrix.
 * @param rows Positive row count.
 * @param cols Positive column count.
 * @return A new owning Matrix.
 * @throws invalid_argument For nonpositive dimensions.
 * @throws bad_alloc If allocation fails; partial storage is freed.
 */
Matrix create_matrix(int rows, int cols);

/** @brief Release all rows and the pointer array; an empty matrix is safe.
 * @param m Matrix whose allocation is released.
 * @note The argument is passed by value: the caller's copy is not reset.
 * @warning Do not use or free aliases after this call.
 */
void free_matrix(Matrix m) noexcept;

/** @brief Add matrices of identical dimensions.
 * @param a Left operand, not modified.
 * @param b Right operand, not modified.
 * @return A newly allocated sum; release with free_matrix().
 * @throws invalid_argument For invalid or incompatible matrices.
 * @throws bad_alloc If result allocation fails.
 */
Matrix matrix_add(Matrix a, Matrix b);

/** @brief Multiply using the i-k-j loop order for sequential row access.
 * @param a Left matrix M by N.
 * @param b Right matrix N by K.
 * @return A newly allocated M by K product.
 * @throws invalid_argument For invalid or incompatible matrices.
 * @throws bad_alloc If result allocation fails.
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/** @brief Construct an independent copy of a row-major flat array.
 * @param data At least rows*cols valid doubles, not null.
 * @param rows Positive row count.
 * @param cols Positive column count.
 * @return A newly allocated matrix.
 * @throws invalid_argument For a null pointer or nonpositive dimensions.
 * @throws bad_alloc If allocation fails.
 */
Matrix matrix_from_array(const double* data, int rows, int cols);

/** @brief Create the transpose, leaving the input unchanged.
 * @param m Valid source matrix.
 * @return A new matrix with swapped dimensions.
 * @throws invalid_argument For invalid input.
 * @throws bad_alloc If allocation fails.
 */
Matrix matrix_transpose(Matrix m);

/** @brief Print a matrix with two decimal places and abbreviated large dimensions.
 * @param m Matrix to print; invalid input prints [Empty matrix].
 * @note At most 10 real rows and 8 real columns are printed, including the ends.
 */
void print_matrix(Matrix m);

/** @brief Variant 29: count elements with absolute value strictly above a threshold.
 * @param m Valid matrix; its contents are not modified.
 * @param threshold Finite nonnegative threshold, usually 1e-9.
 * @return Number of elements satisfying fabs(value) > threshold.
 * @throws invalid_argument For invalid matrix or invalid threshold.
 * @throws overflow_error If the count cannot be represented by int.
 * @note Equality to the threshold is not counted; NaN elements compare false.
 */
int matrix_count_nonzero(Matrix m, double threshold);
#endif
