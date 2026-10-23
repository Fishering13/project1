/** @file matrix.h
 *  @brief Библиотека матриц. Лабораторная работа 3, вариант 29.
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>

using namespace std;

/** @brief Матрица с отдельным выделением памяти для каждой строки.
 *  @warning Копии используют общую память. Освобождайте её только один раз.
 */
struct Matrix {
    double** data; ///< Указатели на строки.
    int rows;      ///< Число строк.
    int cols;      ///< Число столбцов.
};

/** @brief Создать матрицу, заполненную нулями.
 * @param rows Число строк, больше нуля.
 * @param cols Число столбцов, больше нуля.
 * @return Новая матрица. Память нужно освободить через free_matrix().
 * @throws invalid_argument Размеры меньше или равны нулю.
 * @throws bad_alloc Не хватило памяти. Уже выделенная память освобождается.
 */
Matrix create_matrix(int rows, int cols);

/** @brief Освободить память матрицы. Пустая матрица допустима.
 * @param m Матрица, память которой освобождается.
 * @note Матрица передаётся по значению. Исходные указатели не обнуляются.
 * @warning После вызова нельзя использовать или повторно освобождать копии матрицы.
 */
void free_matrix(Matrix m) noexcept;

/** @brief Сложить матрицы одинакового размера.
 * @param a Первая матрица, не изменяется.
 * @param b Вторая матрица, не изменяется.
 * @return Матрица суммы. Освободить через free_matrix().
 * @throws invalid_argument Матрицы некорректны или их размеры не подходят для операции.
 * @throws bad_alloc Не хватило памяти для результата.
 */
Matrix matrix_add(Matrix a, Matrix b);

/** @brief Перемножить матрицы. Циклы i-k-j последовательно обходят строки.
 * @param a Первая матрица размером M на N.
 * @param b Вторая матрица размером N на K.
 * @return Новая матрица произведения размером M на K.
 * @throws invalid_argument Матрицы некорректны или их размеры не подходят для операции.
 * @throws bad_alloc Не хватило памяти для результата.
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/** @brief Создать матрицу из одномерного массива, записанного по строкам.
 * @param data Непустой указатель на массив из rows*cols чисел double.
 * @param rows Число строк, больше нуля.
 * @param cols Число столбцов, больше нуля.
 * @return Новая матрица с копией данных.
 * @throws invalid_argument Нулевой указатель или размеры меньше либо равны нулю.
 * @throws bad_alloc Не хватило памяти.
 */
Matrix matrix_from_array(const double* data, int rows, int cols);

/** @brief Транспонировать матрицу, не меняя исходную.
 * @param m Исходная корректная матрица.
 * @return Новая матрица: строки и столбцы поменяны местами.
 * @throws invalid_argument Некорректная матрица.
 * @throws bad_alloc Не хватило памяти.
 */
Matrix matrix_transpose(Matrix m);

/** @brief Вывести матрицу с двумя знаками после запятой. Большие матрицы сокращаются.
 * @param m Матрица для вывода. Для некорректной матрицы выводится [Empty matrix].
 * @note Выводятся до 10 строк и 8 столбцов, включая первые и последние.
 */
void print_matrix(Matrix m);

/** @brief Вариант 29: посчитать элементы, модуль которых больше порога.
 * @param m Корректная матрица, не изменяется.
 * @param threshold Конечный порог не меньше нуля, обычно 1e-9.
 * @return Количество элементов, для которых fabs(value) > threshold.
 * @throws invalid_argument Некорректная матрица или недопустимый порог.
 * @throws overflow_error Количество элементов не помещается в int.
 * @note Равные порогу элементы и NaN не учитываются.
 */
int matrix_count_nonzero(Matrix m, double threshold);
#endif
