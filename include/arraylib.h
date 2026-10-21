#ifndef ARRAYLIB_H
#define ARRAYLIB_H
#include <cstddef>

// Preconditions: a points to n valid ints; n > 0; counts fit int.
// For sum/product, integer intermediate results must be representable in int.
#if defined(_WIN32) && !defined(ARRAYLIB_STATIC)
#  if defined(ARRAYLIB_BUILD)
#    define ARRAYLIB_API __declspec(dllexport)
#  else
#    define ARRAYLIB_API __declspec(dllimport)
#  endif
#else
#  define ARRAYLIB_API
#endif
ARRAYLIB_API int arr_sum(const int* a, std::size_t n);
ARRAYLIB_API int arr_max(const int* a, std::size_t n);
ARRAYLIB_API int arr_min(const int* a, std::size_t n);
ARRAYLIB_API double arr_average(const int* a, std::size_t n);
ARRAYLIB_API int arr_count_positive(const int* a, std::size_t n);
ARRAYLIB_API int arr_count_negative(const int* a, std::size_t n);
ARRAYLIB_API int arr_count_zero(const int* a, std::size_t n);
ARRAYLIB_API int arr_product(const int* a, std::size_t n);
ARRAYLIB_API double arr_median(const int* a, std::size_t n);
#endif
