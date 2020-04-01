//  myfastrng.c
//  2019-03-02  Markku-Juhani O. Saarinen <mjos@pqshield.com>
//  Copyright (c) 2019, PQShield Ltd.

//  Fast "random-looking number" generator for performance testing.

#include <string.h>
#include <stdint.h>
#include "rng.h"

static uint64_t rng_a = 0xCAFEBABEDEADBEEF, rng_b = 0x0123456789ABCDEF;

void randombytes_init(unsigned char *entropy_input,
					  unsigned char *personalization_string,
					  int security_strength)
{
	size_t i;
	uint8_t t;

	(void) security_strength;

	rng_a = 0xCAFEBABEDEADBEEF;

	for (i = 0; i < 48; i++) {
		rng_a = (rng_a >> 11) | (rng_a << 53);
		t = entropy_input[i];
		if (personalization_string != NULL)
			t ^= personalization_string[i];
		rng_a += t;
	}

	rng_b = 0x0123456789ABCDEF;
}

int randombytes(unsigned char *x, unsigned long long xlen)
{
	size_t i;

	for (i = 0; i < xlen; i++) {

		// xor three parts together to make it more nonlinear in Zn
		x[i] = (rng_a >> 56) ^ (rng_a >> 32) ^ rng_a;

		rng_b += rng_a;						// two Fibonacci steps
		rng_a += rng_b;
	}

	return 0;
}
