#include "gtest/gtest.h"

#include "matrix.hh"

using namespace Geneous;

TEST(MatrixTests, ConstructorTest) {
	// valid fixed size constructor
	Matrix<2, 2> {1, 2, 3, 4};

	// invalid: size does not match data size
	ASSERT_DEATH((Matrix<1, 2> {1, 2, 3, 4}), ".*");
	// invalid: dynamic size for fixed size constructor
	ASSERT_DEATH((Matrix<0, 0> {1, 2, 3, 4}), ".*");

	// valid dynamic size constructor
	Matrix<0, 0>(2, 2, {1, 2, 3, 4});

	// invalid: size arguments do not match data size
	ASSERT_DEATH((Matrix<0, 0>(2, 2, {1, 2, 3})), ".*");

	// valid empty constructors
	Matrix<0, 0> a(2, 2);
	Matrix<2, 2> b;
	Matrix<0, 0> c;
}

TEST(MatrixTests, GetTransposeTest) {
	Matrix<2, 2> a {1, 2, 3, 4};
	ASSERT_TRUE(a.get_transpose() == (Matrix<2, 2> {1, 3, 2, 4}));
	
	Matrix<3, 1> b {1, 2, 3};
	ASSERT_TRUE(b.get_transpose() == (Matrix<1, 3> {1, 2, 3}));

	Matrix<0, 0> c(2, 3, {1, 2, 3, 4, 5, 6});
	ASSERT_TRUE(c.get_transpose() == (Matrix<3, 2> {1, 4, 2, 5, 3, 6}));
}

TEST(MatrixTests, CastTests) {
	Matrix<0, 0> a(Matrix<2, 2> {1, 2, 3, 4});
	ASSERT_TRUE(a == (Matrix<0, 0>(2, 2, {1, 2, 3, 4})));

	Matrix<2, 2> b(Matrix<0, 0>(2, 2, {1, 2, 3, 4}));
	ASSERT_TRUE(b == (Matrix<2, 2> {1, 2, 3, 4}));

	ASSERT_DEATH((Matrix<2, 2>(Matrix<0, 0>(3, 1, {1, 2, 3, 4}))), ".*");
}

TEST(MatrixTests, GetValueTest) {
	Matrix<2, 2> a {1, 2, 3, 4};
	ASSERT_EQ(a(1, 1), 1);
	ASSERT_EQ(a(1, 2), 2);
	ASSERT_EQ(a(2, 1), 3);
	ASSERT_EQ(a(2, 2), 4);
	ASSERT_DEATH(a(0, 0), ".*");
	ASSERT_DEATH(a(3, 1), ".*");
	ASSERT_DEATH(a(1, 3), ".*");
	
	Matrix<0, 0> b(2, 2, {1, 2, 3, 4});
	ASSERT_EQ(b(1, 1), 1);
	ASSERT_EQ(b(1, 2), 2);
	ASSERT_EQ(b(2, 1), 3);
	ASSERT_EQ(b(2, 2), 4);
	ASSERT_DEATH(b(0, 0), ".*");
	ASSERT_DEATH(b(3, 1), ".*");
	ASSERT_DEATH(b(1, 3), ".*");
}

TEST(MatrixTests, EqualityTest) {
	ASSERT_TRUE((Matrix<2, 2> {1, 2, 3, 4}) == (Matrix<2, 2> {1, 2, 3, 4}));
	ASSERT_FALSE((Matrix<2, 2> {1, 2, 3, 4}) != (Matrix<2, 2> {1, 2, 3, 4}));

	ASSERT_FALSE((Matrix<2, 2> {1, 2, 3, 4}) == (Matrix<2, 2> {5, 6, 7, 8}));
	ASSERT_TRUE((Matrix<2, 2> {1, 2, 3, 4}) != (Matrix<2, 2> {5, 6, 7, 8}));
	
	ASSERT_TRUE((Matrix<2, 2> {1, 2, 3, 4}) == (Matrix<0, 0>(2, 2, {1, 2, 3, 4})));
	ASSERT_FALSE((Matrix<2, 2> {1, 2, 3, 4}) != (Matrix<0, 0>(2, 2, {1, 2, 3, 4})));
	
	ASSERT_FALSE((Matrix<2, 1> {1, 2}) == (Matrix<2, 2> {1, 2, 3, 4}));
	ASSERT_TRUE((Matrix<2, 1> {1, 2}) != (Matrix<2, 2> {1, 2, 3, 4}));
}

TEST(MatrixTests, AssignmentTest) {
	Matrix<2, 2> a {1, 2, 3, 4};
	ASSERT_DEATH((a = {1, 2}), ".*");
	a = {5, 6, 7, 8};
	ASSERT_TRUE(a == (Matrix<2, 2> {5, 6, 7, 8}));

	Matrix<0, 0> b(2, 2, {1, 2, 3, 4});
	ASSERT_DEATH((b = {1, 2}), ".*");
	b = {5, 6, 7, 8};
	ASSERT_TRUE(a == b);

	Matrix<2, 2> c = {1, 2, 3, 4};
	ASSERT_TRUE(c == (Matrix<2, 2> {1, 2, 3, 4}));
}

TEST(MatrixTests, BasicArithmeticTest) {
	Matrix<2, 2> a = {1, 2, 3, 4};
	Matrix<2, 2> b = {5, 6, 7, 8};
	a += b;
	ASSERT_TRUE(a == (Matrix<2, 2> {6, 8, 10, 12}));
	a -= b;
	ASSERT_TRUE(a == (Matrix<2, 2> {1, 2, 3, 4}));
	a -= b;
	ASSERT_TRUE(a == (Matrix<2, 2> {-4, -4, -4, -4}));

	ASSERT_TRUE((Matrix<2, 2> {1, 2, 3, 4}) + (Matrix<2, 2> {1, 2, 3, 4}) == (Matrix<2, 2> {2, 4, 6, 8}));
	ASSERT_TRUE((Matrix<2, 2> {1, 2, 3, 4}) - (Matrix<2, 2> {1, 2, 3, 4}) == (Matrix<2, 2> {0, 0, 0, 0}));

	Matrix<2, 2> c {1, 2, 3, 4};
	c *= 2;
	ASSERT_TRUE(c == (Matrix<2, 2> {2, 4, 6, 8}));
	ASSERT_TRUE((Matrix<2, 2> {1, 2, 3, 4}) * 2 == (Matrix<2, 2> {2, 4, 6, 8}));
}

TEST(MatrixTests, MatrixMultiplicationTest) {
	{
		Matrix<2, 2> a {2, 0, 0, 2};
		Matrix<2, 1> b {1, 1};
		ASSERT_TRUE(a * b == (Matrix<2, 1> {2, 2}));
	}
	{
		Matrix<0, 0> a(2, 2, {2, 0, 0, 2});
		Matrix<2, 1> b {1, 1};
		ASSERT_TRUE(a * b == (Matrix<0, 1>(2, 1, {2, 2})));
	}
}