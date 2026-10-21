#include "arraylib.h"
#include <cstddef>
#include <iomanip>
#include <iostream>

int main() {
    int milk[] = {128, 135, 119, 142, 138, 125, 147, 131, 122, 140};
    const std::size_t n = sizeof(milk) / sizeof(milk[0]);
    std::cout << "Variant 29: Milk yield\nMilk:";
    for (int value : milk) std::cout << ' ' << value;
    std::cout << std::fixed << std::setprecision(2)
              << "\nCount: " << n
              << "\nAverage: " << arr_average(milk, n)
              << "\nTotal: " << arr_sum(milk, n)
              << "\nMinimum: " << arr_min(milk, n)
              << "\nMaximum: " << arr_max(milk, n)
              << "\nMedian: " << arr_median(milk, n) << '\n';
}
