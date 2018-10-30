#include "LinkedList.hpp"
#include <string>

#define first(p) p.sentinel->next
#define head(p) p.sentinel
#define isHead(p, t) t == head(p)
#define next(p) p->next
#define coefficient(t) t->item.coefficient
#define power(t) t->item.power
#define remove(t) remove_node(t)

typedef List Polynomial;
typedef node* Term;

static inline Term set_coefficient(Term t, double i) {
	t->item.coefficient = i;
	return t;
}

static inline Term set_power(Term t, int i) {
	t->item.power = i;
	return t;
}

Polynomial polynomial(const std::string str);

void destroy(Polynomial p);

Polynomial add(Polynomial a, Polynomial b);

Polynomial sub(Polynomial a, Polynomial b);

Polynomial mul(Polynomial a, Polynomial b);

void print_polynomial(Polynomial p);

bool equals(Polynomial a, Polynomial b);
