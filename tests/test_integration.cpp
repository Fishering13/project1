#include "arraylib.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
int main() {
    int data[] = {7,3,9,1,5,8,2,6,4};
    constexpr std::size_t n = sizeof(data)/sizeof(data[0]);
    assert(arr_sum(data,n)==45 && arr_max(data,n)==9 && arr_min(data,n)==1);
    double avg = arr_average(data,n);
    assert(avg >= arr_min(data,n) && avg <= arr_max(data,n));
    assert(std::fabs(avg*n-arr_sum(data,n))<1e-9);
    assert(arr_count_positive(data,n)+arr_count_negative(data,n)+arr_count_zero(data,n)==static_cast<int>(n));
    const int sum=arr_sum(data,n);
    std::sort(data,data+n);
    assert(arr_sum(data,n)==sum && std::fabs(arr_average(data,n)-avg)<1e-9);
    int mixed[] = {-2,0,4,-1,3};
    assert(arr_count_positive(mixed,5)+arr_count_negative(mixed,5)+arr_count_zero(mixed,5)==5);
    assert(arr_product(mixed,5)==0);
    std::cout << "[integration] All tests passed\n";
}
