//	main.h
//	2019-03-10	Markku-Juhani O. Saarinen <mjos@pqshield.com>

#ifndef _MAIN_H_

#include <stdint.h>

//	return total number of ticks
uint64_t get_cycles();

//	print to uart2
void my_print(const char *str);

#endif /* _MAIN_H_ */

