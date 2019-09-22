//	r5_ternveh.c
//	2019-09-21	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (C) 2019, PQShield Ltd. Please see LICENSE.

#ifndef _R5_TERNVEC_H_
#define _R5_TERNVEC_H_

#include "r5_parameter_sets.h"
#include "r5_xof.h"

//	currently constant time support only for ring variants
#if defined(R5_CT) && (PARAMS_N == 1)
#warning "Disabling R5_CT for non-ring variant."
#undef R5_CT
#endif

//	set the ternary vector type (also used for matrices)
#ifdef R5_CT
//	slow constant-time type
#define TVEC_WORDS DIV_CEIL(PARAMS_D, 64)
typedef uint64_t r5_ternv_t[TVEC_WORDS][2];
#else
//	fast index type
typedef uint16_t r5_ternv_t[PARAMS_H / 2][2];
#endif

//	create a sparse ternary vector
void r5_sparse_tern(r5_xof_ctx_t *xof, r5_ternv_t tv);

#endif /* _R5_TERNVEC_H_ */

