//  r5_xof.h
//  2019-03-26  Markku-Juhani O. Saarinen <mjos@pqshield.com>
//  Copyright (c) 2020, PQShield Ltd. All rights reserved.

//  Abstract interface to required FIPS 202 and SP 800-185 features

#ifndef _R5_XOF_H_
#define _R5_XOF_H_

#include "r5_parameter_sets.h"

//  -- Keccak-based functionality --

#define SHAKE128_RATE 168
#define SHAKE256_RATE 136

#if (PARAMS_KAPPA_BYTES > 16)
#define R5_XOF_RATE SHAKE256_RATE
#else
#define R5_XOF_RATE SHAKE128_RATE
#endif

typedef struct {
	uint64_t st[25];
	uint8_t buf[R5_XOF_RATE];
	size_t idx;
} r5_xof_ctx_t;

// In Round5 SHAKE is used for everything, so hash = xof
#define r5_hash r5_xof

//  Common interface

void r5_xof(void *out, const size_t out_len,
			const void *in, const size_t in_len);


void r5_xof_input(r5_xof_ctx_t * ctx, const void *in, size_t in_len);

void r5_xof_s_input(r5_xof_ctx_t * ctx,
					const void *in, size_t in_len,
					const void *sstr, size_t sstr_len);


//  basic interface
void r5_xof_clr(r5_xof_ctx_t * ctx);
void r5_xof_in(r5_xof_ctx_t * ctx, const uint8_t * in, size_t in_len);
void r5_xof_pad(r5_xof_ctx_t * ctx, uint8_t pad);
void r5_xof_out(r5_xof_ctx_t * ctx, uint8_t * out, size_t out_len);

#endif										/* _R5_XOF_H_ */
