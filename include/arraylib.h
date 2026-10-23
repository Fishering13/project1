#ifndef ARRAYLIB_H
#define ARRAYLIB_H
#include <cstddef>

using namespace std;

// Массив a содержит n целых чисел, n > 0. Количество элементов помещается в int.
// Сумма и произведение должны помещаться в int.
// Промежуточные суммы должны помещаться в long long.
#if defined(_WIN32) && !defined(ARRAYLIB_STATIC)
#  if defined(ARRAYLIB_BUILD)
#    define ARRAYLIB_API __declspec(dllexport)
#  else
#    define ARRAYLIB_API __declspec(dllimport)
#  endif
#else
#  define ARRAYLIB_API
#endif
ARRAYLIB_API int arr_sum(const int* a, size_t n);
ARRAYLIB_API int arr_max(const int* a, size_t n);
ARRAYLIB_API int arr_min(const int* a, size_t n);
ARRAYLIB_API double arr_average(const int* a, size_t n);
ARRAYLIB_API int arr_count_positive(const int* a, size_t n);
ARRAYLIB_API int arr_count_negative(const int* a, size_t n);
ARRAYLIB_API int arr_count_zero(const int* a, size_t n);
ARRAYLIB_API int arr_product(const int* a, size_t n);
ARRAYLIB_API double arr_median(const int* a, size_t n);
#endif
