// A doubly linked list with a sentinel node.
#ifndef LINKEDLIST_H
#define LINKEDLIST_H 

typedef struct Item{
	double coefficient; 
	int power;
} Item;

struct node;
typedef struct node{
	node *prev;
	Item item; 
	node *next;
} node;

typedef struct List {
	node *sentinel;
	int size;	
} List;

void init_list(List &l);

void destroy_list(List &l);

void clear_list(List &l);

bool list_empty(List l);

int get_elem(List l, int i, Item &e);

// returns the index of the first occurence of Item e.
int locate_elem(List l, Item e);

int list_insert(List &l, int i, Item e);

int list_delete(List &l, int i, Item &e);

node *add_after(node *dest, node *p);

node* remove_node(node *p);
#endif /* ifndef LINKED */
