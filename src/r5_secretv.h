//	r5_secretv.c
//	2019-09-21	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (C) 2019, PQShield Ltd. Please see LICENSE.

#ifndef _R5_SECRETV_H_
#define _R5_SECRETV_H_

#include "r5_parameter_sets.h"

//	type for ternary vector
typedef uint16_t r5_ternv_t[PARAMS_H / 2][2];

//	create n sparse ternary vectors from a seed
void r5_create_secret_vecs(r5_ternv_t sv[],
	const uint8_t seed[PARAMS_KAPPA_BYTES], size_t n);

#endif /* _R5_SECRETV_H_ */

