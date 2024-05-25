#include "gtest.h"
#include "BinHeap.h"

TEST(BinHeap, can_create_BinHeap) {
	ASSERT_NO_THROW(BinHeap<double> B);
}

TEST(BinHeap, can_push_element) {
	BinHeap<double> B;
	ASSERT_NO_THROW(B.push(5));
}

TEST(BinHeap, throws_when_do_top_from_empty_heap) {
	BinHeap<double> B;
	ASSERT_ANY_THROW(B.top());
}

TEST(BinHeap, push_element_is_correct) {
	BinHeap<double> B;
	B.push(5);
	EXPECT_EQ(B.top(), 5);
}

TEST(BinHeap, can_pop_element) {
	BinHeap<double> B;
	B.push(3);
	ASSERT_NO_THROW(B.pop());
}

TEST(BinHeap, throws_when_pop_from_empty_heap) {
	BinHeap<double> B;
	ASSERT_ANY_THROW(B.pop());
}

TEST(BinHeap, empty_is_correct) {
	BinHeap<double> B;
	EXPECT_EQ(B.empty(), true);
	B.push(3);
	EXPECT_EQ(B.empty(), false);
}

TEST(BinHeap, pop_decreases_size) {
	BinHeap<double> B;
	for (int i = 0; i < 10; i++) B.push(i);
	for (int i = 0; i < 10; i++) B.pop();
	EXPECT_EQ(B.empty(), true);
}

TEST(BinHeap, smallest_element_always_on_top) {
	BinHeap<double> B;
	B.push(3);
	B.push(8);
	B.push(-1);
	B.push(6);
	B.push(4);
	B.push(12);
	B.push(-2);
	B.push(7);
	double d = B.top();
	for (int i = 0; i < 7; i++) {
		B.pop();
		if (d > B.top()) break;
	}
	EXPECT_EQ(d < B.top(), true);
}