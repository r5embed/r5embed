//	r5_secretv.c
//	2019-09-21	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (C) 2019, PQShield Ltd. Please see LICENSE.

//	Expand ternary vectors from seed

#include "r5_parameter_sets.h"
#include "r5_secretv.h"
#include "r5_xof.h"
#include "little_endian.h"

#include <string.h>

//	create n sparse ternary vectors from a seed

void r5_create_secret_vecs(r5_ternv_t sv[],
	const uint8_t seed[PARAMS_KAPPA_BYTES], size_t n)
{
	size_t i, j;
	uint16_t x;
	uint8_t v[PARAMS_D];

	r5_xof_ctx_t xof;

	r5_xof_input(&xof, seed, PARAMS_KAPPA_BYTES);

	for (j = 0; j < n; j++) {
		memset(v, 0, sizeof(v));		// reset table
		for (i = 0; i < PARAMS_H; i++) {
			do {
				do {
					r5_xof_squeeze(&xof, &x, sizeof (x));
					x = LITTLE_ENDIAN16(x);
				} while (x >= PARAMS_RS_LIM);
				x /= PARAMS_RS_DIV;
			} while (v[x]);
			v[x] = 1;
			sv[j][i >> 1][i & 1] = x; // addition / subtract index
		}
	}
}

