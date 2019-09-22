//	r5_ternvec.c
//	2019-09-21	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (C) 2019, PQShield Ltd. Please see LICENSE.

//	Expand ternary vectors from seed

#include "r5_parameter_sets.h"
#include "r5_ternvec.h"
#include "r5_xof.h"
#include "little_endian.h"

#include <string.h>

#ifndef R5_CT

//	create a sparse ternary vector (faster index type)

void r5_sparse_tern(r5_xof_ctx_t *xof, r5_ternv_t tv)
{
	size_t i;
	uint16_t x;
	uint8_t v[PARAMS_D];

	memset(v, 0, sizeof(v));			// reset table

	for (i = 0; i < PARAMS_H; i++) {
		do {
			do {
				r5_xof_squeeze(xof, &x, sizeof (x));
				x = LITTLE_ENDIAN16(x);
			} while (x >= PARAMS_RS_LIM);
			x /= PARAMS_RS_DIV;
		} while (v[x]);
		v[x] = 1;
		tv[i >> 1][i & 1] = x;			// addition / subtract index
	}
}

#else

//	create a sparse ternary vector (slower constant time version)

void r5_sparse_tern(r5_xof_ctx_t *xof, r5_ternv_t tv)
{
	int h;
	size_t i, j;
	uint16_t x;
	uint64_t a, b, t;

	memset(tv, 0, sizeof(r5_ternv_t));

	//	mark >=d slots as occupied (uniform sampling)
#if (PARAMS_D & 0x3F) != 0
	tv[TVEC_WORDS - 1][0] = (~0llu) << (PARAMS_D & 0x3F);
#endif

	h = -PARAMS_H;							//	dummy rounds once h reaches 0

	for (i = 0; i < PARAMS_HI; i++) {

		r5_xof_squeeze(xof, &x, sizeof (x));
		x = LITTLE_ENDIAN16(x);
		x /= PARAMS_RS_DIV;

		a = 1llu << (x & 0x3F);
		b = 1llu << (x >> 6);

		a &= (((int64_t) h) >> 63);			//	extend sign bit to mask

		for (j = 0; j < TVEC_WORDS; j++) {
			t = (-(b & 1llu)) & a;
			t &= ~tv[j][0];
			tv[j][0] |= t;
			tv[j][1] |= (-((uint64_t) (h & 1))) & t;
			t |= t >> 1;					// t == 0 ? 0 : 1 (faster ?)
			t = (t^(-t)) >> 63;
			h += t;
			b >>= 1;
		}
	}
}

#endif /* R5_ND */

