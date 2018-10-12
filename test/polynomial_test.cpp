#include "catch.hpp"
#include "../src/polynomial.hpp"

SCENARIO("Dealing with a Polynomial") {
	WHEN("Init a Polynomial with arg 0.") {
		THEN("It should be a 0 Polynomial.") {
			Polynomial p = polynomial("0");
			print_polynomial(p);
		}
	}

	WHEN("Init a normal Polynomial.") {
		THEN("It should print it properly.") {
			Polynomial p = polynomial("3x^2+x+1");
			print_polynomial(p);
		}
	}

	WHEN("Init a Polynomial with negative coeffient.") {
		THEN("It should print it properly.") {
			Polynomial p = polynomial("-x^7+8x-1");
			print_polynomial(p);
		}
	}

	WHEN("Init a unordered Polynomial with negative coeffient.") {
		THEN("It should sort it properly.") {
			Polynomial p = polynomial("1+7x^3+x+8x^4+x^2");
			print_polynomial(p);
		}
	}

	WHEN("Init a Polynomial with rebundant power.") {
		THEN("It should sort it properly.") {
			Polynomial p = polynomial("-3+7x+2+12x");
			print_polynomial(p);
		}
	}

	/*
	WHEN("Init a Polynomial with negative power.") {
		THEN("It should sort it properly.") {
			Polynomial p = polynomial("-3+7x^(-3)+2+12x^(-2)");
			print_polynomial(p);
		}
	}
	*/

	WHEN("Adding two Polynomials") {
		THEN("It should print it correctly") {
			print_polynomial(add(polynomial("x^3+2x"), polynomial("x^2+1")));
			print_polynomial(polynomial("x^3+x^2+2x+1"));
			print_polynomial(add(polynomial("3x^3+2x^2+x+3"), polynomial("x^2+1")));
			print_polynomial(polynomial("3x^3+3x^2+x+4"));
			print_polynomial(sub(polynomial("3x^3+2x^2+x+3"), polynomial("x^2+1")));
			print_polynomial(polynomial("3x^3+x^2+x+2"));
			print_polynomial(sub(polynomial("x^2+2"), polynomial("x^2+1")));
			print_polynomial(polynomial("0"));
		}
	}

	WHEN("Multiplying two Polynomials.") {
		THEN("It should print it correctly") {
			print_polynomial(mul(polynomial("x^3+2x"), polynomial("3x^2")));
			print_polynomial(mul(polynomial("x^3+2x"), polynomial("3x^2+3x^4+5")));
		}
	}

}
