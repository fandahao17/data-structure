#include "LinkedList.hpp"
#include <string>

typedef List Polynomial;

Polynomial init(std::string str);

void destroy(Polynomial p);

Polynomial add(Polynomial a, Polynomial b);

Polynomial sub(Polynomial a, Polynomial b);

Polynomial mul(Polynomial a, Polynomial b);

void print_polynomial(Polynomial p);
