#ifndef LIST_SQ
#define LIST_SQ

#define DEFAULT_SIZE 10
#define RESIZE_RATE 2
#define SHRINK_LINE 4
typedef struct List {
	int *data;
	int length;
	int size;
} List;

void init_list(List &l);

void destroy_list(List &l);

void clear_list(List &l);

bool list_empty(List l);

int get_elem(List l, int i, int &e);

int locate_elem(List l, int e, bool (*cmp)(int, int));

int list_insert(List &l, int i, int e);

int list_delete(List &l, int i, int &e);

List list_union(List la, List lb);
#endif /* ifndef LIST_EQ */
