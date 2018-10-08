#include "catch.hpp"
#include "../src/list_sq.hpp"

SCENARIO("lists can be inserted.", "[insert]") {
	GIVEN("A initilized list") {
		List l;
		init_list(l);

		WHEN("insert 20 elements") {
			for (int i = 0; i < 20; ++i) {
				INFO(i << "succeeded");
				list_insert(l, i, i);
			}
			THEN("size should expand 2 times.") {
				REQUIRE(l.size == 40);
				REQUIRE( l.data[10] == 10);
			}
		}
	}
}
