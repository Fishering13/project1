#include "arraylib.h"
#include <cstddef>
#include <iomanip>
#include <iostream>

int main() {
    int scores[] = {72, 85, 91, 64, 78, 88, 95, 69, 84, 76};
    const std::size_t n = sizeof(scores) / sizeof(scores[0]);
    int at_least_80 = 0;
    for (std::size_t i = 0; i < n; ++i) {
        if (scores[i] >= 80) ++at_least_80;
    }
    std::cout << "Variant 02: Test scores\nScores:";
    for (int score : scores) std::cout << ' ' << score;
    std::cout << std::fixed << std::setprecision(2)
              << "\nCount: " << n
              << "\nAverage: " << arr_average(scores, n)
              << "\nMaximum: " << arr_max(scores, n)
              << "\nMinimum: " << arr_min(scores, n)
              << "\nScores >= 80: " << at_least_80
              << "\nMedian: " << arr_median(scores, n) << '\n';
}
