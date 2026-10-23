#include "matrix.h"
#include <exception>
#include <iostream>
#include <vector>

using namespace std;

/** @brief Own all matrices created during the demonstration. */
struct MatrixStorage {
    vector<Matrix> matrices; ///< Allocations released in reverse order.
    /** @brief Free all registered matrices on normal and exceptional exits. */
    ~MatrixStorage() { for (auto m : matrices) free_matrix(m); }
    /** @brief Register ownership, with cleanup if registration fails.
     * @param m Newly allocated matrix.
     * @return A non-owning alias, valid during this storage's lifetime.
     */
    Matrix own(Matrix m) {
        try { matrices.push_back(m); } catch (...) { free_matrix(m); throw; }
        return m;
    }
};

/** @brief Demonstrate base operations and individual variant 29.
 * @return Zero on success; one on an exception.
 */
int main() {
    try {
        MatrixStorage storage;
        const double a_values[] = {1, 2, 3, 4};
        const double b_values[] = {5, 6, 7, 8};
        Matrix a = storage.own(matrix_from_array(a_values, 2, 2));
        Matrix b = storage.own(matrix_from_array(b_values, 2, 2));
        cout << "Matrix calculator / Laboratory 3 / Variant 29\nA:\n";
        print_matrix(a);
        cout << "B:\n"; print_matrix(b);
        cout << "A + B:\n"; print_matrix(storage.own(matrix_add(a, b)));
        cout << "A * B:\n"; print_matrix(storage.own(matrix_multiply(a, b)));
        cout << "Transpose A:\n"; print_matrix(storage.own(matrix_transpose(a)));
        const double values[] = {0, 1e-10, -2, 3.5, -1e-9, 0, 4, -5, 0};
        Matrix sample = storage.own(matrix_from_array(values, 3, 3));
        cout << "Variant 29: count |value| > threshold\nSample:\n";
        print_matrix(sample);
        cout << "Threshold: 1e-9\nNonzero count: "
                  << matrix_count_nonzero(sample, 1e-9) << "\n";
        try { Matrix bad = matrix_add(a, sample); free_matrix(bad); }
        catch (const exception& error) {
            cout << "Handled size mismatch: " << error.what() << '\n';
        }
    } catch (const exception& error) {
        cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
