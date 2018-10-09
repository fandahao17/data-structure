#include "catch.hpp"
#include "../src/polynomial.hpp"

SCENARIO("Dealing with a Polynomial") {
	WHEN("Init a Polynomial with arg 0.") {
		THEN("It should be a 0 Polynomial.") {
			Polynomial p = init("0");
			print_polynomial(p);
		}
	}

	WHEN("Init a normal Polynomial.") {
		THEN("It should print it properly.") {
			Polynomial p = init("3x^2+x+1");
			print_polynomial(p);
		}
	}

	WHEN("Init a Polynomial with negative coeffient.") {
		THEN("It should print it properly.") {
			Polynomial p = init("-x^7+8x-1");
			print_polynomial(p);
		}
	}

	WHEN("Init a unordered Polynomial with negative coeffient.") {
		THEN("It should sort it properly.") {
			Polynomial p = init("1+7x^3+x+8x^4+x^2");
			print_polynomial(p);
		}
	}

	WHEN("Init a Polynomial with rebundant power.") {
		THEN("It should sort it properly.") {
			Polynomial p = init("-3+7x+2+12x");
			print_polynomial(p);
		}
	}

	/*
	WHEN("Init a Polynomial with negative power.") {
		THEN("It should sort it properly.") {
			Polynomial p = init("-3+7x^(-3)+2+12x^(-2)");
			print_polynomial(p);
		}
	}
	*/

	WHEN("Adding two Polynomials") {
		THEN("It should print it correctly") {
			print_polynomial(add(init("x^3+2x"), init("x^2+1")));
			print_polynomial(init("x^3+x^2+2x+1"));
			print_polynomial(add(init("3x^3+2x^2+x+3"), init("x^2+1")));
			print_polynomial(init("3x^3+3x^2+x+4"));
			print_polynomial(sub(init("3x^3+2x^2+x+3"), init("x^2+1")));
			print_polynomial(init("3x^3+x^2+x+2"));
		}
	}

	WHEN("Multiplying two Polynomials.") {
		THEN("It should print it correctly") {
			print_polynomial(mul(init("x^3+2x"), init("3x^2")));
			print_polynomial(mul(init("x^3+2x"), init("3x^2+3x^4+5")));
		}
	}

}
