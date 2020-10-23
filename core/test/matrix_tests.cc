#include "gtest/gtest.h"
#include "geneous/matrix.hh"

using namespace Geneous;

TEST(MatrixTests, ConstructorTest) {

}

TEST(MatrixTests, CastTest) {

}

TEST(MatrixTests, ValueGetterTest) {

}

TEST(MatrixTests, ValueSetterTest) {

}

TEST(MatrixTests, SetOperatorTest) {
	Matrix<2, 2> m1 {1, 2, 3, 4};
	m1 = {5, 6, 7, 8};
	ASSERT_TRUE(m1 == (Matrix<2, 2> {5, 6, 7, 8}));
	try {
		m1 = {1, 2, 3, 4, 5};
		FAIL();
	} catch(std::invalid_argument ex) {
		SUCCEED();
	}
}

TEST(MatrixTests, EqualityTest) {
	Matrix<2, 2> m1 {1, 2, 3, 4};
	Matrix<0, 0> m2(2, 2, {1, 2, 3, 4});
	ASSERT_TRUE(m1 == m2);
}

TEST(MatrixTests, GetRowTest) {
	Matrix<3, 3> m1 {1, 2, 3, 4, 5, 6, 7, 8, 9};
	ASSERT_TRUE(m1.get_row(1) == (Matrix<1, 3> {1, 2, 3}));
	ASSERT_TRUE(m1.get_row(2) == (Matrix<1, 3> {4, 5, 6}));
	ASSERT_TRUE(m1.get_row(3) == (Matrix<1, 3> {7, 8, 9}));
}

TEST(MatrixTests, GetColumnTest) {
	Matrix<3, 3> m1 {1, 2, 3, 4, 5, 6, 7, 8, 9};
	ASSERT_TRUE(m1.get_column(1) == (Matrix<3, 1> {1, 4, 7}));
	ASSERT_TRUE(m1.get_column(2) == (Matrix<3, 1> {2, 5, 8}));
	ASSERT_TRUE(m1.get_column(3) == (Matrix<3, 1> {3, 6, 9}));
}

TEST(MatrixTests, AddRowTest) {
	// valid
	Matrix<0, 2> m1(1, 2, {1, 2});
	m1.add_row({3, 4});
	ASSERT_TRUE(m1 == (Matrix<2, 2> {1, 2, 3, 4}));
	ASSERT_TRUE(m1 == (Matrix<0, 2>(2, 2, {1, 2, 3, 4})));
	m1.add_row({5, 6});
	ASSERT_TRUE(m1 == (Matrix<3, 2> {1, 2, 3, 4, 5, 6}));
	ASSERT_TRUE(m1 == (Matrix<0, 2>(3, 2, {1, 2, 3, 4, 5, 6})));

	// valid (at index)
	Matrix<0, 2> m2(1, 2, {3, 4});
	m2.add_row({1, 2}, 1);
	ASSERT_TRUE(m2 == (Matrix<2, 2> {1, 2, 3, 4}));
	ASSERT_TRUE(m2 == (Matrix<0, 2>(2, 2, {1, 2, 3, 4})));
	m2.add_row({5, 6}, 2);
	ASSERT_TRUE(m2 == (Matrix<3, 2> {1, 2, 5, 6, 3, 4}));
	ASSERT_TRUE(m2 == (Matrix<0, 2>(3, 2, {1, 2, 5, 6, 3, 4})));

	// invalid (fixed size)
	Matrix<1, 2> m3 {1, 2};
	try {
		m3.add_row({3, 4});
		FAIL();
	} catch(std::invalid_argument ex) {
	
	}

	// invalid (wrong row size)
	Matrix<0, 2> m4(1, 2, {1, 2});
	try {
		m4.add_row({3, 4, 5});
		FAIL();
	} catch(std::invalid_argument ex) {
	
	}
}

TEST(MatrixTests, RemoveRowTest) {
	// valid (to zero size)
	Matrix<0, 2> m1(1, 2, {1, 2});
	m1.remove_row(1);
	ASSERT_TRUE(m1 == (Matrix<0, 2>(0, 0)));

	// valid
	Matrix<0, 2> m2(3, 2, {1, 2, 3, 4, 5, 6});
	m2.remove_row(2);
	ASSERT_TRUE(m2 == (Matrix<2, 2> {1, 2, 5, 6}));
	m2.remove_row(1);
	ASSERT_TRUE(m2 == (Matrix<1, 2> {5, 6}));

	// invalid (fixed size)
	Matrix<2, 2> m3 {1, 2, 3, 4};
	try {
		m3.remove_row(1);
		FAIL();
	} catch(std::invalid_argument ex) {
		SUCCEED();
	}
}

TEST(MatrixTests, AddColumnTest) {
	// valid
	Matrix<2, 0> m1(2, 1, {1, 2});
	m1.add_column({3, 4});
	ASSERT_TRUE(m1 == (Matrix<2, 2> {1, 3, 2, 4}));
	m1.add_column({5, 6}, 2);
	ASSERT_TRUE(m1 == (Matrix<2, 3> {1, 5, 3, 2, 6, 4}));

	// invalid (fixed size)
	Matrix<2, 1> m2 {1, 2};
	try {
		m2.add_column({3, 4});
		FAIL();
	} catch(std::invalid_argument ex) {
	
	}

	// invalid (wrong column size)
	try {
		m1.add_column({1, 2, 3});
		FAIL();
	} catch(std::invalid_argument ex) {
	
	}
}

TEST(MatrixTests, RemoveColumnTest) {
	// valid
	Matrix<2, 0> m1(2, 1, {1, 2});
	m1.remove_column(1);
	ASSERT_TRUE(m1 == (Matrix<2, 0>(0, 0)));

	// valid
	Matrix<2, 0> m2(2, 3, {1, 2, 3, 4, 5, 6});
	m2.remove_column(2);
	ASSERT_TRUE(m2 == (Matrix<2, 2> {1, 3, 4, 6}));
	m2.remove_column(1);
	ASSERT_TRUE(m2 == (Matrix<2, 1> {3, 6}));

	// invalid (fixed size)
	Matrix<2, 2> m3 {1, 2, 3, 4};
	try {
		m3.remove_column(1);
		FAIL();
	} catch(std::invalid_argument ex) {
	
	}
}

TEST(MatrixTests, ScaleTest) {
	Matrix<2, 2> m1 {1, 2, 3, 4};
	m1 *= 2;
	ASSERT_TRUE(m1 == (Matrix<2, 2> {2, 4, 6, 8}));
	m1 *= -1;
	ASSERT_TRUE(m1 == (Matrix<2, 2> {-2, -4, -6, -8}));
}

TEST(MatrixTests, AdditionTest) {
	Matrix<2, 2> m1 {1, 2, 3, 4};
	Matrix<0, 0> m2(2, 2, {5, 6, 7, 8});
	Matrix<2, 2> m3 = m1 + m2;
	ASSERT_TRUE(m3 == (Matrix<0, 0>(2, 2, {6, 8, 10, 12})));
	
	Matrix<1, 2> m4 {1, 2};
	try {
		m3 + m4;
		FAIL();
	} catch(std::invalid_argument ex) {
		SUCCEED();
	}
}

TEST(MatrixTests, SubtractionTest) {
	Matrix<2, 2> m1 {1, 2, 3, 4};
	Matrix<0, 0> m2(2, 2, {5, 6, 7, 8});
	Matrix<2, 2> m3 = m1 - m2;
	ASSERT_TRUE(m3 == (Matrix<0, 0>(2, 2, {-4, -4, -4, -4})));
	
	Matrix<1, 2> m4 {1, 2};
	try {
		m3 - m4;
		FAIL();
	} catch(std::invalid_argument ex) {
	
	}
}

TEST(MatrixTests, MultiplicationTest) {
	Matrix<2, 2> m1 {1, 2, 3, 4};
	Matrix<0, 0> m2(2, 2, {2, 0, 0, 2});
	ASSERT_TRUE(m1 * m2 == (Matrix<0, 0>(2, 2, {2, 4, 6, 8})));

	try {
		Matrix<2, 1> m3 {1, 2};
		m3 * m1;
		FAIL();
	} catch(std::invalid_argument ex) {

	}
}