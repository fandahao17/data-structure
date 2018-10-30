#include "polynomial.hpp"
#include <cctype>
#include <iostream>
#include <cmath>
#include <sstream>

static int size(Polynomial p) {
	int i = 0;
	for(Term t = first(p); t != head(p); t = next(t)) {
		i++;
	}
	return i;
}

static Polynomial filtered_poly (Polynomial p) {
	Term t = first(p);
	while (!(isHead(p, t))) {
		Term n = next(t);
		if (coefficient(t) == 0 && power(t) != 0) {
			remove(t);
		}
		t = n;
	}
	return p;
}

static void insert_term_at(Polynomial p, Term dest, Term src) {
	if (!(isHead(p, dest)) && power(dest) == power(src)) {
		set_coefficient(dest, coefficient(dest) + coefficient(src));
		src = dest;
	} else {
		add_after(dest->prev, src);
	}
}

static Term term(double coefficient, int power) {
	Term t = (Term) malloc(sizeof(node));
	set_coefficient(t, coefficient);
	set_power(t, power);
	return t;
}

Polynomial poly_insert(Polynomial p, Item new_item) {
	Term new_term = term(new_item.coefficient, new_item.power);
	Term t = first(p);
	while (t != head(p) && power(t) > power(new_term)) {
		t = next(t);
	}
	insert_term_at(p, t, new_term);
	return filtered_poly(p);
}

Polynomial polynomial(const std::string str) {
	Polynomial p;
	init_list(p);
	if (str.empty()) {
		return p;
	} 
	std::stringstream s;
	if(str.at(0) != '-') {
		s << "+" << str;
	}else {
		s << str;
	}
	
	while (s.peek() != EOF) {
		double coefficient = 1;
		int power = 0;
		char sign;
		s >> sign;
		if (s.peek() != 'x') {
			s >> coefficient;
		}
		coefficient *= (sign == '+' ? 1 : -1);
		if (!s || s.peek() != 'x') {
			poly_insert(p, {coefficient, power});
			continue;
		}
		power = 1;
		s.ignore(1);
		if (!s || s.peek() != '^') {
			poly_insert(p, {coefficient, power});
			continue;
		}
		s.ignore(1);
		s >> power;
		poly_insert(p, {coefficient, power});
	}
	return p;
}

Polynomial real_add(Polynomial a, Polynomial b, int is_add) {
	Term pa = first(a), pb = first(b);
	Polynomial result = polynomial("");
	while (pa != head(a) && pb != head(b)) {
		if (power(pa) > power(pb)) {
			while (pa != head(a) && power(pa) > power(pb)) {
				double c = coefficient(pa);
				int p = power(pa);
				insert_term_at(result, head(result), term(c, p));
				pa = next(pa);
			}
		} else {
			while (pb != head(b) && power(pb) > power(pa)) {
				double c = coefficient(pb);
				int p = power(pb);
				insert_term_at(result, head(result), term(c, p));
				pb = next(pb);
			}
		}
		if (pa != head(a) && pb != head(b) && power(pa) == power(pb)) {
			double c = coefficient(pa) + coefficient(pb)*is_add;
			int p = power(pb);
			insert_term_at(result, head(result), term(c, p));
			pa = next(pa);
			pb = next(pb);
		}
	}
	while (pa != head(a)) {
		double c = coefficient(pa);
		int	p = power(pa);
		insert_term_at(result, head(result), term(c, p));
		pa = next(pa);
	}
	while (pb != head(b)) {
		double c = coefficient(pb) * is_add;
		int	p = power(pb);
		insert_term_at(result, head(result), term(c, p));
		pb = next(pb);
	}
	return filtered_poly(result);
}

Polynomial add(Polynomial a, Polynomial b) {
	return real_add(a, b, 1);
}

Polynomial sub(Polynomial a, Polynomial b) {
	return real_add(a, b, -1);
}

Polynomial one_mul_n(Item e, Polynomial b) {
	double c = e.coefficient;
	int	p = e.power;
	node *pb = b.sentinel->next;
	Polynomial result = polynomial("");
	while (pb != b.sentinel) {
		double bc = pb->item.coefficient;
		int	bp = pb->item.power;
		poly_insert(result, {bc * c, bp + p});
		pb = pb->next;
	}
	return result;
}

Polynomial mul(Polynomial a, Polynomial b) {
	Polynomial result = polynomial("");
	Term p = first(a);
	while (p != head(a)) {
		result = add(result, one_mul_n(p->item, b));
		p = next(p);
	}
	return result;
}

std::string make_term(node *p) {
	double c = coefficient(p);
	std::ostringstream out;
    out.precision(1);
    out << std::fixed << c;
	int	po = power(p);
	if (po == 0) {
		return out.str();
	}
	std::string c_part = (fabs(c) ==1 ? (c > 0 ? "" : "-")
		   							: out.str());
	std::string p_part;
	if (po != 1) {
		p_part = "^" + std::to_string(po);
		if (po < 0) {
			p_part = "(" + p_part +")";
		}
	}
	return c_part + "x" + p_part;
}

void print_polynomial(Polynomial p) {
	Term q = first(p);
	std::cout << make_term(q);
	q = next(q);
	while (q != head(p)) {
		if (q->item.coefficient >= 0) {
			std::cout << "+";
		}
		std::cout << make_term(q);
		q = next(q);
	}
	std::cout << std::endl;
}

bool equals(Polynomial a, Polynomial b) {
	if (size(a) != size(b)) {
		return false;
	}
	Term ta = first(a), tb = first(b);
	while (ta != head(a)) {
		if (coefficient(ta) != coefficient(tb) || power(ta) != power(tb)) {
			return false;
		}
		ta = next(ta);
		tb = next(tb);
	}
	return true;
}
