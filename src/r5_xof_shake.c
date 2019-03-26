//	r5_xof_shake.c
//	2019-03-26	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (c) 2019, PQShield Ltd.

#ifndef BLNK2

#include "r5_xof.h"

#include <assert.h>
#include <string.h>

static void keccak_absorb(r5_xof_ctx_t *ctx,
	const uint8_t *in, size_t len, uint8_t pad)
{
	while (len >= R5_XOF_RATE) {
		KeccakF1600_StateXORBytes(ctx->st, in, 0, R5_XOF_RATE);
		KeccakF1600_StatePermute(ctx->st);
		len -= R5_XOF_RATE;
		in += R5_XOF_RATE;
	}
	memcpy(ctx->buf, in, len);
	ctx->buf[len] = pad;
	memset(ctx->buf + len + 1, 0x00, R5_XOF_RATE - len - 1);
	ctx->buf[R5_XOF_RATE - 1] |= 0x80;

	KeccakF1600_StateXORBytes(ctx->st, ctx->buf, 0, R5_XOF_RATE);
}

void r5_xof_input(r5_xof_ctx_t *ctx,
	const void *in, size_t in_len)
{
	memset(ctx->st, 0x00, 200);
	keccak_absorb(ctx, in, in_len, 0x1F);
	ctx->idx = R5_XOF_RATE;
}

void r5_xof_squeeze(r5_xof_ctx_t *ctx,
	void *out, size_t out_len)
{
	size_t i, j;
	i = ctx->idx;
	for (j = 0; j < out_len; j++) {
		if (i >= R5_XOF_RATE) {
			KeccakF1600_StatePermute(ctx->st);
			KeccakF1600_StateExtractBytes(ctx->st, ctx->buf, 0, R5_XOF_RATE);
			i = 0;
		}
		((uint8_t *) out)[j] = ctx->buf[i++];
	}
	ctx->idx = i;
}

void r5_xof(void *out, size_t out_len,
	const void *in, size_t in_len)
{
	r5_xof_ctx_t ctx;

	r5_xof_input(&ctx, in, in_len);
	r5_xof_squeeze(&ctx, out, out_len);
}


void r5_xof_s_input(r5_xof_ctx_t *ctx,
	const void *in, size_t in_len,
	const void *sstr, size_t sstr_len)
{
	const uint8_t cshake_hdr[5] = { 0x01, R5_XOF_RATE, 0x01, 0x00, 0x01 };

	assert(sstr_len < 32);

	memset(ctx->st, 0, 200);
	memcpy(ctx->buf, cshake_hdr, 5);
	ctx->buf[5] = 8 * sstr_len;
	memcpy(ctx->buf + 6, sstr, sstr_len);
	memset(ctx->buf + 6 + sstr_len, 0x00, R5_XOF_RATE - 6 - sstr_len);

	KeccakF1600_StateXORBytes(ctx->st, ctx->buf, 0, R5_XOF_RATE);
	KeccakF1600_StatePermute(ctx->st);

	keccak_absorb(ctx, in, in_len, 0x04);

	ctx->idx = R5_XOF_RATE;
}

#endif /* !BLNK2 */
