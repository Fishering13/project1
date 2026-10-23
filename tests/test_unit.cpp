#include "arraylib.h"
#include <cassert>
#include <cmath>
#include <climits>
#include <iostream>

using namespace std;
bool close(double a, double b) { return fabs(a-b) < 1e-9; }
int main() {
    int a[] = {-5, 0, 3, 3, 8, -2};
    assert(arr_sum(a,6)==7); assert(arr_min(a,6)==-5); assert(arr_max(a,6)==8);
    assert(arr_count_positive(a,6)==3); assert(arr_count_negative(a,6)==2);
    assert(arr_count_zero(a,6)==1); assert(arr_product(a,6)==0);
    assert(close(arr_average(a,6),7.0/6.0));
    int one[] = {-7};
    assert(arr_sum(one,1)==-7 && arr_min(one,1)==-7 && arr_max(one,1)==-7);
    assert(arr_product(one,1)==-7 && arr_count_negative(one,1)==1);
    assert(arr_count_positive(one,1)==0 && arr_count_zero(one,1)==0);
    assert(close(arr_average(one,1),-7));
    int zeros[] = {0,0,0};
    assert(arr_sum(zeros,3)==0 && arr_product(zeros,3)==0);
    assert(arr_count_zero(zeros,3)==3 && arr_max(zeros,3)==0 && arr_min(zeros,3)==0);
    int p[] = {1,2,3,4}; assert(arr_product(p,4)==24);
    int neg[] = {-3,-1,-2};
    assert(arr_sum(neg,3)==-6 && arr_product(neg,3)==-6);
    assert(arr_min(neg,3)==-3 && arr_max(neg,3)==-1);
    int extremes[] = {INT_MAX,INT_MAX};
    assert(close(arr_average(extremes,2),INT_MAX));
    int zero_product[] = {INT_MAX,INT_MAX,0}; assert(arr_product(zero_product,3)==0);
    int even[] = {7,1,9,3};
    const int saved[] = {7,1,9,3};
    assert(close(arr_median(even,4),5));
    for (size_t i=0;i<4;++i) assert(even[i]==saved[i]);
    int odd[] = {5,1,3}; assert(close(arr_median(odd,3),3));
    assert(close(arr_median(one,1),-7));
    assert(close(arr_median(zeros,3),0));
    assert(close(arr_median(extremes,2),INT_MAX));
    int limits[] = {INT_MIN,INT_MAX}; assert(close(arr_median(limits,2),-0.5));
    assert(close(arr_median(neg,3),-2));
    int cancellation[] = {INT_MAX,1,-1}; assert(arr_sum(cancellation,3)==INT_MAX);
    int product_limits[] = {INT_MIN,-1,-1}; assert(arr_product(product_limits,3)==INT_MIN);
    cout << "[unit] All tests passed\n";
}
