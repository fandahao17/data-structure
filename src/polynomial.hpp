#include "LinkedList.hpp"
#include <string>

typedef List Polynomial;
typedef node* Term;

static inline int get_coefficient(Term t) {
	return t->item.coefficient;
}

static inline int get_power(Term t) {
	return t->item.power;
}

static inline Term set_coefficient(Term t, int i) {
	t->item.coefficient = i;
	return t;
}

static inline Term set_power(Term t, int i) {
	t->item.power = i;
	return t;
}

static inline Term next(Term t) {
	return t->next;
}

static inline Term first(Polynomial p) {
	return p.sentinel->next;
}

Polynomial polynomial(const std::string str);

void destroy(Polynomial p);

Polynomial add(Polynomial a, Polynomial b);

Polynomial sub(Polynomial a, Polynomial b);

Polynomial mul(Polynomial a, Polynomial b);

void print_polynomial(Polynomial p);

bool equals(Polynomial a, Polynomial b);
