#include "arraylib.h"
#include <algorithm>
#include <vector>
#include <climits>

int arr_sum(const int* a, std::size_t n) {
    long long result = 0;
    for (std::size_t i = 0; i < n; ++i) result += a[i];
    return static_cast<int>(result);
}
int arr_max(const int* a, std::size_t n) {
    int result = a[0];
    for (std::size_t i = 1; i < n; ++i) if (a[i] > result) result = a[i];
    return result;
}
int arr_min(const int* a, std::size_t n) {
    int result = a[0];
    for (std::size_t i = 1; i < n; ++i) if (a[i] < result) result = a[i];
    return result;
}
double arr_average(const int* a, std::size_t n) {
    double result = 0.0;
    for (std::size_t i = 0; i < n; ++i) result += a[i];
    return result / static_cast<double>(n);
}
int arr_count_positive(const int* a, std::size_t n) {
    int result = 0;
    for (std::size_t i = 0; i < n; ++i) if (a[i] > 0) ++result;
    return result;
}
int arr_count_negative(const int* a, std::size_t n) {
    int result = 0;
    for (std::size_t i = 0; i < n; ++i) if (a[i] < 0) ++result;
    return result;
}
int arr_count_zero(const int* a, std::size_t n) {
    int result = 0;
    for (std::size_t i = 0; i < n; ++i) if (a[i] == 0) ++result;
    return result;
}
int arr_product(const int* a, std::size_t n) {
    // A zero makes the mathematical product zero, even with large other factors.
    if (arr_count_zero(a, n) != 0) return 0;
    // Compute sign separately so INT_MIN * -1 * -1 has no signed overflow.
    bool negative = false;
    unsigned int magnitude = 1;
    for (std::size_t i = 0; i < n; ++i) {
        if (a[i] < 0) negative = !negative;
        const unsigned int factor = a[i] < 0
            ? 0u - static_cast<unsigned int>(a[i]) : static_cast<unsigned int>(a[i]);
        magnitude *= factor;
    }
    if (!negative) return static_cast<int>(magnitude);
    if (magnitude == static_cast<unsigned int>(INT_MAX) + 1u) return INT_MIN;
    return -static_cast<int>(magnitude);
}
double arr_median(const int* a, std::size_t n) {
    std::vector<int> copy(a, a + n);
    std::sort(copy.begin(), copy.end());
    if (n % 2 != 0) return copy[n / 2];
    return (static_cast<double>(copy[n / 2 - 1]) + copy[n / 2]) / 2.0;
}
