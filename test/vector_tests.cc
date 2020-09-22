#include "gtest/gtest.h"

#include "vector.hh"

using namespace Geneous;

TEST(VectorTests, ConstructorTest) {
	// valid fixed size constructor
	Vector<3> {1, 2, 3};

	// invalid: size does not match data size
	ASSERT_DEATH((Vector<2> {1, 2, 3}), ".*");
	// invalid: dynamic size for fixed constructor
	ASSERT_DEATH((Vector<0> {1, 2, 3}), ".*");

	// valid dynamic size constructor
	Vector<0>(3, {1, 2, 3});

	// invalid: size arguments do not match data size
	ASSERT_DEATH((Vector<0>(2, {1, 2, 3})), ".*");

	// valid empty constructors
	Vector<0> a(2);
	Vector<2> b;
	Vector<0> c;
}

TEST(VectorTests, CastTest) {
	Vector<0> a(Vector<3> {1, 2, 3});
	ASSERT_TRUE(a == Vector<0>(3, {1, 2, 3}));

	Vector<2> b(Vector<0>(3, {1, 2, 3}));
	ASSERT_TRUE(b == (Vector<3> {1, 2, 3}));

	ASSERT_DEATH((Vector<3>(Vector<0>(2, {1, 2}))), ".*");
}

TEST(VectorTests, GetValueTest) {
	Vector<3> a {1, 2, 3};
	ASSERT_EQ(a(1), 1);
	ASSERT_EQ(a(2), 2);
	ASSERT_EQ(a(3), 3);
	ASSERT_DEATH(a(0), ".*");
	ASSERT_DEATH(a(4), ".*");

	Vector<0> b(3, {1, 2, 3});
	ASSERT_EQ(b(1), 1);
	ASSERT_EQ(b(2), 2);
	ASSERT_EQ(b(3), 3);
	ASSERT_DEATH(b(0), ".*");
	ASSERT_DEATH(b(4), ".*");
}

TEST(VectorTests, EqualityTest) {
	ASSERT_TRUE((Vector<3> {1, 2, 3}) == (Vector<3> {1, 2, 3}));
	ASSERT_FALSE((Vector<3> {1, 2, 3}) != (Vector<3> {1, 2, 3}));

	ASSERT_FALSE((Vector<3> {1, 2, 3}) == (Vector<3> {4, 5, 6}));
	ASSERT_TRUE((Vector<3> {1, 2, 3}) != (Vector<3> {4, 5, 6}));

	ASSERT_TRUE((Vector<0>(3, {1, 2, 3})) == (Vector<0>(3, {1, 2, 3})));
	ASSERT_FALSE((Vector<0>(3, {1, 2, 3})) != (Vector<0>(3, {1, 2, 3})));

	ASSERT_FALSE((Vector<0>(3, {1, 2, 3})) == (Vector<0>(3, {4, 5, 6})));
	ASSERT_TRUE((Vector<0>(3, {1, 2, 3})) != (Vector<0>(3, {4, 5, 6})));

	ASSERT_TRUE((Vector<3> {1, 2, 3}) == (Vector<0>(3, {1, 2, 3})));
	ASSERT_FALSE((Vector<3> {1, 2, 3}) != (Vector<0>(3, {1, 2, 3})));

	ASSERT_FALSE((Vector<3> {1, 2, 3}) == (Vector<0>(3, {4, 5, 6})));
	ASSERT_TRUE((Vector<3> {1, 2, 3}) != (Vector<0>(3, {4, 5, 6})));

	ASSERT_FALSE((Vector<3> {1, 2, 3}) == (Vector<2> {1, 2}));
	ASSERT_TRUE((Vector<3> {1, 2, 3}) != (Vector<2> {1, 2}));
}

TEST(VectorTests, AssignmentTest) {
	Vector<3> a {1, 2, 3};
	ASSERT_DEATH((a = {1, 2}), ".*");
	a = {4, 5, 6};
	ASSERT_TRUE(a == (Vector<3> {4, 5, 6}));

	Vector<0> b (3, {1, 2, 3});
	ASSERT_DEATH((b = {1, 2}), ".*");
	b = {4, 5, 6};
	ASSERT_TRUE(a == b);

	Vector<3> c = {1, 2, 3};
	ASSERT_TRUE(c == (Vector<3> {1, 2, 3}));
}

TEST(VectorTests, BasicArithmeticTest) {
	Vector<3> a = {1, 2, 3};
	Vector<3> b = {4, 5, 6};

	a += b;
	ASSERT_TRUE(a == (Vector<3> {5, 7, 9}));
	a -= b;
	ASSERT_TRUE(a == (Vector<3> {1, 2, 3}));
	a -= b;
	ASSERT_TRUE(a == (Vector<3> {-3, -3, -3}));

	ASSERT_TRUE((Vector<3> {1, 2, 3}) + (Vector<3> {1, 2, 3}) == (Vector<3> {2, 4, 6}));
	ASSERT_TRUE((Vector<3> {1, 2, 3}) - (Vector<3> {1, 2, 3}) == (Vector<3> {0, 0, 0}));
}
