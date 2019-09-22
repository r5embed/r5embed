//	r5_ringmul.h
//	2019-09-21	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (c) 2019, PQShield Ltd. and Koninklijke Philips N.V.

#ifndef _R5_RINGMUL_H_
#define _R5_RINGMUL_H_

#include "r5_parameter_sets.h"
#include "r5_ternvec.h"

#if (PARAMS_N == PARAMS_D)

// multiplication mod q, result length n
void r5_ringmul_q(modq_t d[PARAMS_D],
	modq_t a[2 * (PARAMS_D + 1)], const r5_ternv_t sv);

// multiplication mod p, result length mu
void r5_ringmul_p(modp_t d[PARAMS_D],
	modp_t a[PARAMS_D + PARAMS_MU + 2], const r5_ternv_t sv);

#endif

#endif /* _R5_RINGMUL_H_ */

