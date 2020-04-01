//  r5_xof.c
//  2019-03-26  Markku-Juhani O. Saarinen <mjos@pqshield.com>
//  Copyright (c) 2020, PQShield Ltd. All rights reserved.

//  Abstract interface to required FIPS 202 and SP 800-185 features

#include <string.h>

#include "r5_xof.h"
#include "keccakf1600.h"


//  basic functions

void r5_xof_clr(r5_xof_ctx_t * ctx)
{
	size_t i;

	for (i = 0; i < 25; i++) {
		ctx->st[i] = 0;
	}
	ctx->idx = 0;
}

//  incremental input using idx

void r5_xof_in(r5_xof_ctx_t * ctx, const uint8_t * in, size_t len)
{
	size_t i;

	i = ctx->idx;
	if (i > 0) {
		if (i + len < R5_XOF_RATE) {
			memcpy(ctx->buf + i, in, len);
			ctx->idx = i + len;
			return;
		}
		memcpy(ctx->buf + i, in, R5_XOF_RATE - i);
		keccak_xorbytes(ctx->st, ctx->buf, 0, R5_XOF_RATE);
		keccak_f1600(ctx->st);
		i = R5_XOF_RATE - i;
		len -= i;
		in += i;
		ctx->idx = 0;
	}
	while (len >= R5_XOF_RATE) {
		keccak_xorbytes(ctx->st, in, 0, R5_XOF_RATE);
		keccak_f1600(ctx->st);
		len -= R5_XOF_RATE;
		in += R5_XOF_RATE;
	}
	if (len > 0) {
		memcpy(ctx->buf, in, len);
		ctx->idx = len;
	}
}

//  incremental output using idx

void r5_xof_out(r5_xof_ctx_t * ctx, uint8_t * out, size_t len)
{
	size_t i;

	i = R5_XOF_RATE - ctx->idx;
	if (i >= len) {
		memcpy(out, ctx->buf + ctx->idx, len);
		ctx->idx += len;
		return;
	}
	if (i > 0) {
		memcpy(out, ctx->buf + ctx->idx, i);
		out += i;
		len -= i;
		ctx->idx = R5_XOF_RATE;
	}
	while (len >= R5_XOF_RATE) {
		keccak_f1600(ctx->st);
		keccak_extract(ctx->st, out, 0, R5_XOF_RATE);
		len -= R5_XOF_RATE;
		out += R5_XOF_RATE;
	}
	if (len > 0) {
		keccak_f1600(ctx->st);
		keccak_extract(ctx->st, ctx->buf, 0, R5_XOF_RATE);
		memcpy(out, ctx->buf, len);
		ctx->idx = len;
	}
}

//  add a pad byte

void r5_xof_pad(r5_xof_ctx_t * ctx, uint8_t pad)
{
	size_t i = ctx->idx;
	ctx->buf[i] = pad;
	memset(ctx->buf + i + 1, 0x00, R5_XOF_RATE - i - 1);
	ctx->buf[R5_XOF_RATE - 1] |= 0x80;
	keccak_xorbytes(ctx->st, ctx->buf, 0, R5_XOF_RATE);
	ctx->idx = R5_XOF_RATE;
	//  no call to permutation unless output actually requested
}

//  absorb "len" bytes from "in" with padding "pad"

void r5_xof_input(r5_xof_ctx_t * ctx, const void *in, size_t in_len)
{
	r5_xof_clr(ctx);
	r5_xof_in(ctx, in, in_len);
	r5_xof_pad(ctx, 0x1F);
}

//  single-call XOF

void r5_xof(void *out, size_t out_len, const void *in, size_t in_len)
{
	r5_xof_ctx_t ctx;

	r5_xof_clr(&ctx);
	r5_xof_in(&ctx, in, in_len);
	r5_xof_pad(&ctx, 0x1F);
	r5_xof_out(&ctx, out, out_len);
}

//  two-input XOF

void r5_xof_s_input(r5_xof_ctx_t * ctx,
					const void *in, size_t in_len,
					const void *sstr, size_t sstr_len)
{
	const uint8_t cshake_hdr[5] = { 0x01, R5_XOF_RATE, 0x01, 0x00, 0x01 };

	r5_xof_clr(ctx);

	memcpy(ctx->buf, cshake_hdr, 5);
	ctx->buf[5] = 8 * sstr_len;
	memcpy(ctx->buf + 6, sstr, sstr_len);
	memset(ctx->buf + 6 + sstr_len, 0x00, R5_XOF_RATE - 6 - sstr_len);

	keccak_xorbytes(ctx->st, ctx->buf, 0, R5_XOF_RATE);
	keccak_f1600(ctx->st);

	r5_xof_in(ctx, in, in_len);
	r5_xof_pad(ctx, 0x04);
}
