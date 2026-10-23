#include "matrix.h"
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <vector>

using namespace std;

/** @brief Основа тестов: освобождает матрицы даже при провале проверки. */
class MatrixTest : public ::testing::Test {
protected:
    vector<Matrix> allocations; ///< Созданные в тесте матрицы.
    /** @brief Освободить все матрицы после теста. */
    void TearDown() override { for (auto m : allocations) free_matrix(m); }
    /** @brief Добавить матрицу в список для освобождения памяти.
     * @param m Новая матрица.
     * @return Копия указателей. Память освобождается после теста.
     */
    Matrix own(Matrix m) {
        try { allocations.push_back(m); } catch (...) { free_matrix(m); throw; }
        return m;
    }
    /** @brief Создать матрицу из заданных значений и добавить в список.
     * @param values Элементы, записанные по строкам.
     * @param rows Число строк.
     * @param cols Число столбцов.
     * @return Копия указателей на созданную матрицу.
     */
    Matrix from(initializer_list<double> values, int rows, int cols) {
        return own(matrix_from_array(values.begin(), rows, cols));
    }
};

TEST_F(MatrixTest, CreateZeroInitialized) {
    auto a = own(create_matrix(3, 4));
    EXPECT_EQ(a.rows,3); EXPECT_EQ(a.cols,4);
    for(int i=0;i<3;++i) for(int j=0;j<4;++j) EXPECT_DOUBLE_EQ(a.data[i][j],0);
}
TEST_F(MatrixTest, MinimumSize) { auto a=own(create_matrix(1,1)); EXPECT_DOUBLE_EQ(a.data[0][0],0); }
TEST_F(MatrixTest, InvalidDimensions) {
    EXPECT_THROW(create_matrix(0,3),invalid_argument);
    EXPECT_THROW(create_matrix(3,-1),invalid_argument);
}
TEST_F(MatrixTest, FromArrayDeepCopy) {
    double values[]={1,2,3,4,5,6}; auto a=own(matrix_from_array(values,2,3));
    values[0]=99; EXPECT_DOUBLE_EQ(a.data[0][0],1); EXPECT_DOUBLE_EQ(a.data[1][2],6);
}
TEST_F(MatrixTest, FromArrayNull) { EXPECT_THROW(matrix_from_array(nullptr,2,2),invalid_argument); }
TEST_F(MatrixTest, Addition) {
    auto a=from({1,2,3,4},2,2), b=from({5,6,7,8},2,2);
    auto c=own(matrix_add(a,b));
    EXPECT_DOUBLE_EQ(c.data[0][0],6); EXPECT_DOUBLE_EQ(c.data[0][1],8);
    EXPECT_DOUBLE_EQ(c.data[1][0],10); EXPECT_DOUBLE_EQ(c.data[1][1],12);
    EXPECT_DOUBLE_EQ(a.data[0][0],1);
}
TEST_F(MatrixTest, AdditionFractionalRectangular) {
    auto a=from({1.5,-2,0,4,5,6},2,3), b=from({-1.5,2,3,0,-5,1},2,3);
    auto c=own(matrix_add(a,b)); EXPECT_EQ(c.cols,3);
    EXPECT_DOUBLE_EQ(c.data[0][0],0); EXPECT_DOUBLE_EQ(c.data[1][2],7);
}
TEST_F(MatrixTest, AdditionMismatch) {
    auto a=own(create_matrix(2,2)), b=own(create_matrix(2,3));
    EXPECT_THROW(matrix_add(a,b),invalid_argument);
}
TEST_F(MatrixTest, Multiply) {
    auto a=from({1,2,3,4},2,2), b=from({5,6,7,8},2,2), c=own(matrix_multiply(a,b));
    EXPECT_DOUBLE_EQ(c.data[0][0],19); EXPECT_DOUBLE_EQ(c.data[0][1],22);
    EXPECT_DOUBLE_EQ(c.data[1][0],43); EXPECT_DOUBLE_EQ(c.data[1][1],50);
}
TEST_F(MatrixTest, MultiplyRectangular) {
    auto a=from({1,2,3,4,5,6},2,3), b=from({7,8,9,10,11,12},3,2);
    auto c=own(matrix_multiply(a,b)); EXPECT_EQ(c.rows,2); EXPECT_EQ(c.cols,2);
    EXPECT_DOUBLE_EQ(c.data[0][0],58); EXPECT_DOUBLE_EQ(c.data[1][1],154);
}
TEST_F(MatrixTest, RowTimesColumn) {
    auto a=from({1,2,3},1,3), b=from({4,5,6},3,1), c=own(matrix_multiply(a,b));
    EXPECT_EQ(c.rows,1); EXPECT_EQ(c.cols,1); EXPECT_DOUBLE_EQ(c.data[0][0],32);
}
TEST_F(MatrixTest, MultiplyMismatch) {
    auto a=own(create_matrix(2,3)), b=own(create_matrix(2,2));
    EXPECT_THROW(matrix_multiply(a,b),invalid_argument);
}
TEST_F(MatrixTest, TransposeTwice) {
    auto a=from({1,2,3,4,5,6},2,3), t=own(matrix_transpose(a)), tt=own(matrix_transpose(t));
    EXPECT_EQ(t.rows,3); EXPECT_EQ(t.cols,2); EXPECT_DOUBLE_EQ(t.data[2][1],6);
    for(int i=0;i<2;++i) for(int j=0;j<3;++j) EXPECT_DOUBLE_EQ(tt.data[i][j],a.data[i][j]);
}
TEST_F(MatrixTest, NonzeroZeros) { auto a=own(create_matrix(2,3)); EXPECT_EQ(matrix_count_nonzero(a,0),0); }
TEST_F(MatrixTest, NonzeroSignedValues) {
    auto a=from({0,1e-10,-2,3.5,-1e-9,0,4,-5,0},3,3);
    EXPECT_EQ(matrix_count_nonzero(a,1e-9),4);
    EXPECT_EQ(matrix_count_nonzero(a,0),6);
    EXPECT_DOUBLE_EQ(a.data[0][2],-2);
}
TEST_F(MatrixTest, NonzeroStrictThreshold) {
    auto a=from({-2,-1,0,1,2,3},2,3); EXPECT_EQ(matrix_count_nonzero(a,2),1);
}
TEST_F(MatrixTest, NonzeroNegativeCountsByMagnitude) {
    auto a=from({-5,-3,-1},1,3); EXPECT_EQ(matrix_count_nonzero(a,2),2);
}
TEST_F(MatrixTest, NonzeroInvalidThreshold) {
    auto a=own(create_matrix(1,1));
    EXPECT_THROW(matrix_count_nonzero(a,-1),invalid_argument);
    EXPECT_THROW(matrix_count_nonzero(a,numeric_limits<double>::infinity()),invalid_argument);
    EXPECT_THROW(matrix_count_nonzero(a,numeric_limits<double>::quiet_NaN()),invalid_argument);
}
TEST_F(MatrixTest, InvalidMatrixRejected) {
    Matrix empty{nullptr,0,0}; auto a=own(create_matrix(1,1));
    EXPECT_THROW(matrix_add(a,empty),invalid_argument);
    EXPECT_THROW(matrix_multiply(empty,a),invalid_argument);
    EXPECT_THROW(matrix_transpose(empty),invalid_argument);
    EXPECT_THROW(matrix_count_nonzero(empty,0),invalid_argument);
}
TEST_F(MatrixTest, NullRowRejected) {
    double* rows[]={nullptr}; Matrix a{rows,1,1};
    EXPECT_THROW(matrix_count_nonzero(a,0),invalid_argument);
}
TEST_F(MatrixTest, EmptyFreeRepeatedSafe) {
    Matrix empty{nullptr,0,0};
    EXPECT_NO_THROW(free_matrix(empty));
    EXPECT_NO_THROW(free_matrix(empty));
}
TEST_F(MatrixTest, IntegrationIdentityPreservesCount) {
    auto a=from({0,-2,3,0},2,2), identity=from({1,0,0,1},2,2);
    auto result=own(matrix_multiply(a,identity));
    EXPECT_EQ(matrix_count_nonzero(result,1e-9),matrix_count_nonzero(a,1e-9));
    for(int i=0;i<2;++i) for(int j=0;j<2;++j) EXPECT_DOUBLE_EQ(result.data[i][j],a.data[i][j]);
}
TEST_F(MatrixTest, PrintLargeIncludesLastRowAndColumn) {
    auto a=own(create_matrix(15,12)); a.data[14][11]=987.25;
    ostringstream output; auto* original=cout.rdbuf(output.rdbuf());
    print_matrix(a); cout.rdbuf(original);
    EXPECT_NE(output.str().find("987.25"),string::npos);
    EXPECT_NE(output.str().find("Matrix 15x12"),string::npos);
}
