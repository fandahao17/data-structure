#include "gtest/gtest.h"
#include "../src/list_sq.hpp"

namespace {
TEST(TestSQ, TestClear) {
	List l;
	init_list(l);
	
	for (int i = 0; i < 15; ++i) {
		list_insert(l, i, i);
	}
	
	EXPECT_EQ(l.length, 15);
	EXPECT_EQ(l.size, 2 * DEFAULT_SIZE);
	clear_list(l);
	EXPECT_EQ(l.length, 0);
	EXPECT_EQ(l.size, DEFAULT_SIZE);
	destroy_list(l);
}
	//Create a list, then insert 100 elems,then destroy it.
TEST(TestSQ, TestInit) {
	List l;
	init_list(l);
	ASSERT_NE(l.data, nullptr);
	destroy_list(l);
}

TEST(TestSQ, TestInsert) {
	List l;
	init_list(l);
	for (int i = 0; i < 20; ++i) {
		list_insert(l, i, i);
	}
	EXPECT_EQ(l.size, 40);
	EXPECT_EQ(l.length, 20);
	EXPECT_EQ(l.data[10], 10);
	int v = list_insert(l, -1, 200);
	EXPECT_EQ(v, -1);
	v = list_insert(l, 10, 200);
	EXPECT_EQ(v, 0);
	v = list_insert(l, 49, 200);
	EXPECT_EQ(v, -1);
	v = list_insert(l, 0, 200);
	EXPECT_EQ(v, 0);
	EXPECT_EQ(l.data[0], 200);
	for (int i = 1; i < 11; ++i) {
		EXPECT_EQ(l.data[i], i - 1);
	}
	EXPECT_EQ(l.data[11], 200);
	for (int i = 12; i < l.length; ++i) {
		EXPECT_EQ(l.data[i], i - 2);
	}
	destroy_list(l);
}

TEST(TestSQ, TestDelete) {
	List l;
	init_list(l);
	for (int i = 0; i < 20; ++i) {
		list_insert(l, i, i);
	}
	int elem;
	EXPECT_EQ(list_delete(l, 19, elem), 0);
	EXPECT_EQ(elem, 19);
	EXPECT_EQ(list_delete(l, -1, elem), -1);
	EXPECT_EQ(list_delete(l, 200, elem), -1);
	for (int i = 18; i >= 0; --i) {
		EXPECT_EQ(l.data[i], i);
		list_delete(l, i, elem);
	}
	EXPECT_EQ(l.length, 0);
	EXPECT_EQ(l.size, 10);
	destroy_list(l);
}
	

TEST(TestSQ, TestEmptyGet) {
	List l;
	init_list(l);
	EXPECT_TRUE(list_empty(l));
	for (int i = 0; i < 100; ++i) {
		list_insert(l, i, i);
	}
	EXPECT_FALSE(list_empty(l));
	int elem;
	EXPECT_EQ(get_elem(l, 49, elem), 0);
	EXPECT_EQ(elem, 49);
	EXPECT_EQ(get_elem(l, -1, elem), -1);
	EXPECT_EQ(get_elem(l, 200, elem), -1);
}

bool greater_than(int a, int b) { return a < b; }
TEST(TestSQ, TestLocate) {
	List l;
	init_list(l);
	for (int i = 0; i < 100; ++i) {
		list_insert(l, i, i);
	}
	EXPECT_EQ(locate_elem(l, 49, greater_than), 50);
	EXPECT_EQ(locate_elem(l, 100, greater_than), -1);
	}
TEST(TestUnion, NoUnion) {
	List la, lb, lc;
	init_list(la);
	init_list(lb);
	int la_items[] = {0, 2, 4, 6, 8};
	int lb_items[] = {1, 3, 5, 7, 9};
	for (int i = 0; i < 5; ++i) {
		list_insert(la, i, la_items[i]);
		list_insert(lb, i, lb_items[i]);
	}
	lc = list_union(la, lb);
	EXPECT_EQ(lc.length, 0);
}
TEST(TestUnion, SameList) {
	List la, lb, lc;
	init_list(la);
	init_list(lb);
	int la_items[] = {0, 2, 4, 6, 8};
	int lb_items[] = {0, 2, 4, 6, 8};
	for (int i = 0; i < 5; ++i) {
		list_insert(la, i, la_items[i]);
		list_insert(lb, i, lb_items[i]);
	}
	lc = list_union(la, lb);
	EXPECT_EQ(lc.length, 5);
	for (int i = 0; i < 5; ++i) {
		int v = 0;
		get_elem(lc, i, v);
		EXPECT_EQ(v, la_items[i]);
	}
}
TEST(TestUnion, EmptyList) {
	List la, lb, lc;
	init_list(la);
	init_list(lb);
	int la_items[] = {0, 2, 4, 6, 8};
	for (int i = 0; i < 5; ++i) {
		list_insert(la, i, la_items[i]);
	}
	lc = list_union(la, lb);
	EXPECT_EQ(lc.length, 0);
}
TEST(TestUnion, NormalCase) {
	List la, lb, lc;
	init_list(la);
	init_list(lb);
	int la_items[] = {0, 2, 4, 6, 8};
	int lb_items[] = {1,2,  3, 5, 6, 8, 13};
	int lc_items[] = {2, 6, 8};
	for (int i = 0; i < 5; ++i) {
		list_insert(la, i, la_items[i]);
	}
	for (int i = 0; i < 7; ++i) {
		list_insert(lb, i, lb_items[i]);
	}
	lc = list_union(la, lb);
	for (int i = 0; i < 3; ++i) {
		int v = 0;
		get_elem(lc, i, v);
		EXPECT_EQ(v, lc_items[i]);
	}
}
TEST(TestUnion, LastEqual) {
	List la, lb, lc;
	init_list(la);
	init_list(lb);
	int la_items[] = {0, 2, 4, 6, 8};
	int lb_items[] = {-1, 1,2,  3, 5, 7, 8};
	int lc_items[] = {2, 8};
	for (int i = 0; i < 5; ++i) {
		list_insert(la, i, la_items[i]);
	}
	for (int i = 0; i < 7; ++i) {
		list_insert(lb, i, lb_items[i]);
	}
	lc = list_union(la, lb);
	for (int i = 0; i < 2; ++i) {
		int v = 0;
		get_elem(lc, i, v);
		EXPECT_EQ(v, lc_items[i]);
	}
}
}
