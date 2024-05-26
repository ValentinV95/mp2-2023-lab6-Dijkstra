#include <sstream>
#include <gtest.h>
#include "matrix.h"

TEST(SquareMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(SquareMatrix<int> m(5));
}

TEST(SquareMatrix, throws_when_create_matrix_with_zero_size)
{
	ASSERT_ANY_THROW(SquareMatrix<int> m(0));
}

TEST(SquareMatrix, can_copy_matrix)
{
	SquareMatrix<int> m(5);
	ASSERT_NO_THROW(SquareMatrix<int> m1(m));
}

TEST(SquareMatrix, can_assign_matrix)
{
	SquareMatrix<int> m(20);
	SquareMatrix<int> m1(20);
	ASSERT_NO_THROW(m = m1);
}

TEST(SquareMatrix, copied_matrix_has_its_own_memory)
{
	SquareMatrix<int> m1(20);
	m1.pos(1, 0) = 42;
	SquareMatrix<int> m2(m1);
	m1.pos(2, 0) = 47;
	EXPECT_NE(m1.pos(2,0), m2.pos(2,0));
}

TEST(SquareMatrix, assigned_matrix_has_its_own_memory)
{
	SquareMatrix<int> m1(20);
	SquareMatrix<int> m2(20);
	m2 = m1;
	m1.pos(1, 0) = 42;
	m1.pos(2, 0) = 47;
	EXPECT_NE(m1.pos(2, 0), m2.pos(2, 0));
}

TEST(SquareMatrix, can_get_size)
{
	SquareMatrix<int> m(3);
	EXPECT_EQ(3, m.size());
}

TEST(SquareMatrix, can_set_and_get_element)
{
	SquareMatrix<int> m(2);
	m.pos(0,0) = 7;
	EXPECT_EQ(7, m.pos(0,0));
}

TEST(SquareMatrix, operators_shr_and_shl_dont_change_values)
{
	SquareMatrix<int> m1(2), m2(2);
	std::stringstream ss;
	m1.pos(0, 0) = 1; m1.pos(0, 1) = 2;
	m1.pos(1, 0) = 3; m1.pos(1, 1) = 4;

	ss << m1;
	ss >> m2;
	
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			ASSERT_EQ(m1.pos(i, j), m2.pos(i, j));
}

TEST(SquareMatrix, operator_shr_handles_invalid_input)
{
	SquareMatrix<int> m(2);
	std::stringstream ss;
	ss << "1 2 a 3";
	ASSERT_ANY_THROW(ss >> m);
}