#include "arraylib.h"
#include <iostream>

int main() {
    int data[] = {-5, 0, 3, 3, 8, -2};
    const std::size_t n = sizeof(data) / sizeof(data[0]);
    std::cout << "Array:";
    for (int value : data) std::cout << ' ' << value;
    std::cout << "\nSum: " << arr_sum(data, n)
              << "\nMax: " << arr_max(data, n)
              << "\nMin: " << arr_min(data, n)
              << "\nAverage: " << arr_average(data, n)
              << "\nPositive: " << arr_count_positive(data, n)
              << "\nNegative: " << arr_count_negative(data, n)
              << "\nZero: " << arr_count_zero(data, n)
              << "\nProduct: " << arr_product(data, n)
              << "\nMedian: " << arr_median(data, n) << '\n';
}
