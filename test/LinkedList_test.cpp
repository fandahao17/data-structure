#include "catch.hpp"
#include "../src/LinkedList.hpp"

SCENARIO("A linked list should be inserted and deleted at ant place.") {
	GIVEN("An initilized list.") {
		List l;
		init_list(l);
		Item elems[] = {{1}, {2}, {3}, {4}};
		int result[] = {3, 4, 1, 2};
		list_insert(l, 0, elems[0]);
		list_insert(l, 1, elems[1]);
		list_insert(l, 0, elems[2]);
		list_insert(l, 1, elems[3]);

		WHEN("insert elems into the list.") {

			THEN("size is 4, list is {3, 4, 1, 2}") {
				REQUIRE(l.size == 4);
				int i = 0;
				for(node *p = l.sentinel->next; p != l.sentinel; p = p->next) {
					CHECK(p->item.data == result[i++]);
				}
			}
		}

		AND_WHEN("delete elems from the list.") {
			THEN("it returns the right elem."){
				Item elem;
				list_delete(l, 0, elem);
				CHECK(elem.data == result[0]);
				list_delete(l, 2, elem);
				CHECK(elem.data == result[3]);
				list_delete(l, 1, elem);
				CHECK(elem.data == result[2]);
			}
		}

		clear_list(l);
		list_insert(l, 0, elems[0]);
		list_insert(l, 1, elems[1]);
		list_insert(l, 0, elems[2]);
		list_insert(l, 1, elems[3]);
		AND_WHEN("locate elems of the list.") {
			int i = 0;
			for(node *p = l.sentinel->next; p != l.sentinel; p = p->next) {
				CHECK(p->item.data == result[i++]);
			}
			for (int i = 0; i < 4; ++i) {
				Item e = {result[i]};
				CHECK(locate_elem(l, e) == i);
			}
			Item e = {result[3]};
			locate_elem(l, e);
			CHECK(locate_elem(l, e) == 0);
			e = {result[1]};
			CHECK(locate_elem(l, e) == 2);
			locate_elem(l, e);
			locate_elem(l, e);
			CHECK(locate_elem(l, e) == 0);
			e = {10};
			CHECK(locate_elem(l, e) == -1);
		}
		AND_WHEN("gets elems of the list.") {
			THEN("it returns the right elem.") {
				Item e;
				get_elem(l, 0, e);
				CHECK(e.data == result[0]);
				get_elem(l, 1, e);
				CHECK(e.data == result[1]);
				CHECK(get_elem(l, 5, e) == -1);
			}
		}
	}
}
