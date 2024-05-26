#include "gtest.h"
#include "FibHeap.h"

TEST(FibHeap, can_create_FibHeap) {
	ASSERT_NO_THROW(FibHeap<double> F);
}

TEST(FibHeap, can_push_element) {
	FibHeap<double> F;
	ASSERT_NO_THROW(F.push(5));
}

TEST(FibHeap, throws_when_do_top_from_empty_heap) {
	FibHeap<double> F;
	ASSERT_ANY_THROW(F.top());
}

TEST(FibHeap, push_element_is_correct) {
	FibHeap<double> F;
	F.push(5);
	EXPECT_EQ(F.top(), 5);
}

TEST(FibHeap, can_pop_element) {
	FibHeap<double> F;
	F.push(3);
	ASSERT_NO_THROW(F.pop());
}

TEST(FibHeap, throws_when_pop_from_empty_heap) {
	FibHeap<double> F;
	ASSERT_ANY_THROW(F.pop());
}

TEST(FibHeap, empty_is_correct) {
	FibHeap<double> F;
	EXPECT_EQ(F.empty(), true);
	F.push(3);
	EXPECT_EQ(F.empty(), false);
}

TEST(FibHeap, pop_decreases_size) {
	FibHeap<double> F;
	for (int i = 0; i < 10; i++) F.push(i);
	for (int i = 0; i < 10; i++) F.pop();
	EXPECT_EQ(F.empty(), true);
}

TEST(FibHeap, smallest_element_always_on_top) {
	FibHeap<double> F;
	F.push(3);
	F.push(8);
	F.push(-1);
	F.push(6);
	F.push(4);
	F.push(12);
	F.push(-2);
	F.push(7);
	double d = F.top();
	for (int i = 0; i < 7; i++) {
		F.pop();
		if (d > F.top()) break;
	}
	EXPECT_EQ(d < F.top(), true);
}
