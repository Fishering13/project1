#include <cstddef>
#include <algorithm>
#include <vector>

using namespace std;

int arr_sum(const int* a, size_t n) {
    int result = 0;
    for (size_t i = 0; i < n; ++i) result += a[i];
    return result;
}
int arr_max(const int* a, size_t n) {
    int result = a[0];
    for (size_t i = 1; i < n; ++i) if (a[i] > result) result = a[i];
    return result;
}
int arr_min(const int* a, size_t n) {
    int result = a[0];
    for (size_t i = 1; i < n; ++i) if (a[i] < result) result = a[i];
    return result;
}
double arr_average(const int* a, size_t n) {
    double result = 0.0;
    for (size_t i = 0; i < n; ++i) result += a[i];
    return result / static_cast<double>(n);
}
int arr_count_positive(const int* a, size_t n) {
    int result = 0;
    for (size_t i = 0; i < n; ++i) if (a[i] > 0) ++result;
    return result;
}
int arr_count_negative(const int* a, size_t n) {
    int result = 0;
    for (size_t i = 0; i < n; ++i) if (a[i] < 0) ++result;
    return result;
}
int arr_count_zero(const int* a, size_t n) {
    int result = 0;
    for (size_t i = 0; i < n; ++i) if (a[i] == 0) ++result;
    return result;
}
int arr_product(const int* a, size_t n) {
    // Если есть ноль, произведение равно нулю.
    if (arr_count_zero(a, n) != 0) return 0;
    int result = 1;
    for (size_t i = 0; i < n; ++i) result *= a[i];
    return result;
}
double arr_median(const int* a, size_t n) {
    vector<int> copy(a, a + n);
    sort(copy.begin(), copy.end());
    if (n % 2 != 0) return copy[n / 2];
    return (static_cast<double>(copy[n / 2 - 1]) + copy[n / 2]) / 2.0;
}
#include <iostream>


int main() {
    int data[] = {-5, 0, 3, 3, 8, -2};
    const size_t n = sizeof(data) / sizeof(data[0]);
    cout << "Array:";
    for (int value : data) cout << ' ' << value;
    cout << "\nSum: " << arr_sum(data, n)
              << "\nMax: " << arr_max(data, n)
              << "\nMin: " << arr_min(data, n)
              << "\nAverage: " << arr_average(data, n)
              << "\nPositive: " << arr_count_positive(data, n)
              << "\nNegative: " << arr_count_negative(data, n)
              << "\nZero: " << arr_count_zero(data, n)
              << "\nProduct: " << arr_product(data, n)
              << "\nMedian: " << arr_median(data, n) << '\n';
}
