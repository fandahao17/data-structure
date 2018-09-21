#include <iostream>
#include <cstdio>
#ifndef DBG_H
#define DBG_H 
#define debug_v(NAME, VAR) std::cout << "[" << __FILE__ << " " \
	<< __func__ << "(" << __LINE__ << ")" << "] "  << NAME << " = " << VAR << std::endl
#define debug(M, ...) fprintf(stdout, "DEBUG %s:%d %s: " M" \n",\
        __FILE__, __LINE__,__func__, ##__VA_ARGS__)
#endif /* ifndef DBG_H  */
