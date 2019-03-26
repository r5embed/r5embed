//	r5_xof.h
//	2019-03-26	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (c) 2019, PQShield Ltd.

//	Abstract interface to an extensible output function ("XOF") type hash.
//	Allows only one "input", but you can call "squeeze" many times.


#ifndef _R5_XOF_H_
#define _R5_XOF_H_

#include "r5_parameter_sets.h"


#ifndef BLNK2

// -- Keccak-based functionality --

#include "keccakf1600.h"

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

#else

// -- SNEIK-based functionality --

#include "blnk.h"
typedef blnk_t r5_xof_ctx_t;

#endif /* !BLNK2 */

void r5_xof(void *out, const size_t out_len,
	const void *in, const size_t in_len);

void r5_xof_input(r5_xof_ctx_t *ctx,
	const void *in, size_t in_len);

void r5_xof_s_input(r5_xof_ctx_t *ctx,
	const void *in, size_t in_len,
	const void *sstr, size_t sstr_len);

void r5_xof_squeeze(r5_xof_ctx_t *ctx,
	void *out, size_t out_len);

#endif /* _R5_XOF_H_ */

