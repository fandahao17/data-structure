#include "list_sq.hpp"
#include <cstdlib>
#include <cstring>

using namespace std;
void init_list(List &l) {
	l.data = static_cast<int *>(calloc(DEFAULT_SIZE, sizeof(int)));
	l.length = 0;
	l.size = DEFAULT_SIZE;
}

void destroy_list(List &l) {
	free(l.data);
	l.length = l.size = 0;
}

// a helper function.
void resize_list(List &l, int size) {
	l.data = static_cast<int *>(realloc(l.data, size * sizeof(int)));
	l.size = size;
}

void clear_list(List &l) {
	l.length = 0;
	resize_list(l, DEFAULT_SIZE);
}

bool list_empty(List l) {
	return l.length == 0;
}

int get_elem(List l, int i, int &e) {
	if (i >= l.length || i < 0) {
		return -1;
	}
	e = l.data[i];
	return 0;
}

int locate_elem(List l, int e, bool (*cmp)(int a, int b)) {
	for (int i = 0; i < l.length; ++i) {
		if (cmp(e, l.data[i])) {
			return i;
		}
	}
	return -1;
}

int list_insert(List &l, int i, int e) {
	if (i < 0 || i > l.length) {
		return -1;
	}
	for (int j = l.length; j > i; --j) {
		l.data[j] = l.data[j-1];
	}
	l.data[i] = e;
	l.length++;
	if (l.length >= l.size) {
		resize_list(l, l.length * RESIZE_RATE);
	}
	return 0;
}

int list_delete(List &l, int i, int &e) {
	if (i < 0 || i > l.length) {
		return -1;
	}
	e = l.data[i];
	for (int j = l.length; j > i; --j) {
		l.data[j-1] = l.data[j];
	}
	l.length--;
	if (l.length <= l.size / SHRINK_LINE) {
		int size = l.length / RESIZE_RATE;
		resize_list(l, size < DEFAULT_SIZE ? DEFAULT_SIZE : size);
	}
	return 0;
}

/* --------ABSTRACTION BARRIER------------ */

List list_union(List la, List lb) {
	List lc;
	init_list(lc);
	int l1 = la.length, l2 =lb.length;
	int v1, v2, ia = 0;
	int ib = 0, ic = 0;
	while (ia <= l1 - 1 && ib <= l2 - 1) {
		get_elem(la, ia, v1);
		get_elem(lb, ib, v2);
		if (v1 > v2) {
			while (v1 > v2 && ib++ < l2 -1) {
				get_elem(lb, ib , v2);
			}
		} else {
			while (v1 < v2 && ia++ < l1 -1) {
				get_elem(la, ia , v1);
			}
		}
		if (v1 == v2) {
			list_insert(lc, ic++, v1);
			ia++;
			ib++;
		}
	}
	return lc;
}
