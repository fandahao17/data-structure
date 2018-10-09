#include "polynomial.hpp"
#include <iostream>
#include <cctype>

Polynomial poly_insert(Polynomial &p, Item new_item) {
	node *q = p.sentinel;
	int i = 0;
	while (q->next != p.sentinel && q->next->item.power>new_item.power) {
		q = q->next;
		i++;
	}
	if (q->next->item.power == new_item.power) {
		q->next->item.coefficient += new_item.coefficient;
	} else {
		list_insert(p, i, new_item);
	}
	if (q->next->item.coefficient == 0) {
		remove_node(q->next);
	}
	return p;
}

Polynomial init(const std::string str) {
	Polynomial p;
	init_list(p);
	std::string new_str = str;
	if(str.at(0) != '-') {
		new_str.insert(0, "+");
	}
	
	decltype(new_str.length()) pos = 0;
	while (pos != new_str.length()) {
		char sign = 0;
		sign = new_str.at(pos++);
		int coeffient = (new_str.at(pos) == 'x' ? 1 : 0), power = 0;
		while (pos != new_str.length() && isnumber(new_str.at(pos))) {
			coeffient = coeffient * 10 + new_str.at(pos++) - '0';
		}
		coeffient *= (sign == '+' ? 1 : -1);
		// Very ugly!
		if (pos != new_str.length() && new_str.at(pos) == 'x') {
			pos += 1;
			if (pos != new_str.length() && new_str.at(pos) == '^') {
				pos += 1;
				while (pos != new_str.length()&& isnumber(new_str.at(pos))){
					power = power * 10 + new_str.at(pos++) - '0';
				}
			} else {
				power = 1;
			}
		}
		poly_insert(p, {coeffient, power});
	}
	return p;
}

Polynomial real_add(Polynomial a, Polynomial b, int is_add) {
	node *pa = a.sentinel->next, *pb = b.sentinel->next;
	Polynomial result = init("0");
	while (pa != a.sentinel && pb != b.sentinel) {
		if (pa->item.power >= pb->item.power) {
			while (pa != a.sentinel && pa->item.power >= pb->item.power) {
				// TODO : add float support
				int c = pa->item.coefficient, p = pa->item.power;
				// TODO : Don't use poly_insert
				poly_insert(result, {c, p});
				pa = pa->next;
			}
		} else {
			while (pb != b.sentinel && pb->item.power >= pa->item.power) {
				int c = pb->item.coefficient * is_add, p = pb->item.power;
				poly_insert(result, {c, p});
				pb = pb->next;
			}
		}
	}
	while (pa != a.sentinel) {
		int c = pa->item.coefficient, p = pa->item.power;
		poly_insert(result, {c, p});
		pa = pa->next;
	}
	while (pb != b.sentinel) {
		int c = pb->item.coefficient * is_add, p = pb->item.power;
		poly_insert(result, {c, p});
		pb = pb->next;
	}
	return result;
}

Polynomial add(Polynomial a, Polynomial b) {
	return real_add(a, b, 1);
}

Polynomial sub(Polynomial a, Polynomial b) {
	return real_add(a, b, -1);
}

Polynomial one_mul_n(Item e, Polynomial b) {
	int c = e.coefficient, p = e.power;
	node *pb = b.sentinel->next;
	Polynomial result = init("0");
	while (pb != b.sentinel) {
		int bc = pb->item.coefficient, bp = pb->item.power;
		poly_insert(result, {bc * c, bp + p});
		pb = pb->next;
	}
	return result;
}

Polynomial mul(Polynomial a, Polynomial b) {
	Polynomial result = init("0");
	node *p = a.sentinel->next;
	while (p != a.sentinel) {
		result = add(result, one_mul_n(p->item, b));
		p = p->next;
	}
	return result;
}

std::string make_term(node *p) {
	int c = p->item.coefficient, po = p->item.power;
	if (po == 0) {
		return std::to_string(c);
	}
	std::string c_part = (abs(c) ==1 ? (c > 0 ? "" : "-")
		   							: std::to_string(c));
	std::string p_part = "";
	if (po != 1) {
		p_part = "^" + std::to_string(po);
		if (po < 0) {
			p_part = "(" + p_part +")";
		}
	}
	return c_part + "x" + p_part;
}

void print_polynomial(Polynomial p) {
	node *q = p.sentinel->next;
	std::cout << make_term(q);
	q = q->next;
	while (q != p.sentinel) {
		if (q->item.coefficient >= 0) {
			std::cout << "+";
		}
		std::cout << make_term(q);
		q = q->next;
	}
	std::cout << std::endl;
}
