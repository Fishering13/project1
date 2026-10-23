#include "arraylib.h"
#include <cstddef>
#include <iomanip>
#include <iostream>
using namespace std;
int main() 
{
    int milk[] = {128, 135, 119, 142, 138, 125, 147, 131, 122, 140};
    const size_t n = sizeof(milk) / sizeof(milk[0]);
    cout << "Variant 29: Milk yield\nMilk:";
    for (int value : milk) std::cout << ' ' << value;
    cout << fixed << setprecision(2) << "Count: " << n << "Average: " << arr_average(milk, n) << "Total: " << arr_sum(milk, n) << "Minimum: " << arr_min(milk, n) << "Maximum: " << arr_max(milk, n) << "Median: " << arr_median(milk, n) << '\n';
}
