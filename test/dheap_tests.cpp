#include "gtest.h"
#include "dheap.h"

TEST(dheap, can_create_dheap) {
	ASSERT_NO_THROW(DHeap<double> D);
}

TEST(dheap, can_push_element) {
	DHeap<double> D;
	ASSERT_NO_THROW(D.push(5));
}

TEST(dheap, throws_when_do_top_from_empty_heap) {
	DHeap<double> D;
	ASSERT_ANY_THROW(D.top());
}

TEST(dheap, push_element_is_correct) {
	DHeap<double> D;
	D.push(5);
	EXPECT_EQ(D.top(), 5);
}

TEST(dheap, can_pop_element) {
	DHeap<double> D;
	D.push(3);
	ASSERT_NO_THROW(D.pop());
}

TEST(dheap, throws_when_pop_from_empty_heap) {
	DHeap<double> D;
	ASSERT_ANY_THROW(D.pop());
}

TEST(dheap, empty_is_correct) {
	DHeap<double> D;
	EXPECT_EQ(D.empty(), true);
	D.push(3);
	EXPECT_EQ(D.empty(), false);
}

TEST(dheap, pop_decreases_size) {
	DHeap<double> D;
	for (int i = 0; i < 10; i++) D.push(i);
	for (int i = 0; i < 10; i++) D.pop();
	EXPECT_EQ(D.empty(), true);
}

TEST(dheap, smallest_element_always_on_top) {
	DHeap<double> D;
	D.push(3);
	D.push(8);
	D.push(-1);
	D.push(6);
	D.push(4);
	D.push(12);
	D.push(-2);
	D.push(7);
	double d = D.top();
	for (int i = 0; i < 7; i++) {
		D.pop();
		if (d > D.top()) break;
	}
	EXPECT_EQ(d < D.top(), true);
}