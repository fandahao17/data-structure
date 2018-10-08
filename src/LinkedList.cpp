#include "LinkedList.hpp"
#include <cstdlib>

node* remove_node(node *p) {
	// remove the node pointed at by p but does not free p.
	p->prev->next = p->next;
	p->next->prev = p->prev;
	p->next = p->prev = nullptr;
	return p;
}

node *add_after(node *dest, node *p) {
	// adds p as the next node of dest, return p.
	p->next = dest->next;
	p->prev = dest;
	dest->next = dest->next->prev = p;
	return p;
}

void init_list(List &l){
	l.sentinel = (node *)malloc(sizeof(node));
	l.sentinel->item = {233};
	l.sentinel->next = l.sentinel->prev = l.sentinel;
	l.size = 0;
}

void destroy_list(List &l){
	clear_list(l);
	free(l.sentinel);
}

void clear_list(List &l) {
	node *p = l.sentinel->next;
	while (p != l.sentinel) {
		node *prev = p;
		p = p->next;
		free(prev);
	}
	l.sentinel->prev = l.sentinel;
	l.sentinel->next = l.sentinel;
	l.size = 0;
}

bool list_empty(List l) {
	return l.size == 0;
}

int get_elem(List l, int i, Item &e) {
	if (i < 0 || i > l.size) {
		return -1;
	}
	node *p = l.sentinel->next;
	while (i--) {
		p = p->next;
	}
	e = p->item;
	return 0;
}

void resort(List l, node *p) {
	node *q = p->prev;
	while (q != l.sentinel && q->freq < p->freq) {
		q = q->prev;
	}
	add_after(q, remove_node(p));
}

int locate_elem(List l, Item e) {
	int i = 0;
	for(node *p = l.sentinel->next; p != l.sentinel; p = p->next, i++) {
		if (p->item.data == e.data) {
			p->freq++;
			resort(l, p);
			return i;
		}
	}
	return -1;
}

int list_insert(List &l, int i, Item e) {
	if (i < 0 || i > l.size) {
		return -1;
	}
	node *p = l.sentinel->next;
	while (i--) {
		p = p->next;
	}
	node *cur = (node *) malloc(sizeof(node));
	(*cur).item = e;
	add_after(p->prev, cur);
	// node cur = {prev, e, p};   What's wrong?
	l.size++;
	return 0;
}
	

int list_delete(List &l, int i, Item &e) {
	if (i < 0 || i > l.size) {
		return -1;
	}
	node *p = l.sentinel->next;
	while (i--) {
		p = p->next;
	}
	e = p->item;
	free(remove_node(p));
	l.size--;
	return 0;
}
