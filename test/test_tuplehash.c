//  test_tuplehash.c
//  2020-04-01  Markku-Juhani O. Saarinen <mjos@pqshield.com>
//  Copyright (c) 2020, PQShield Ltd. All rights reserved.

#include <stdio.h>
#include <string.h>

#include "r5_xof.h"
#include "keccakf1600.h"

void r5_xof_enc_right(r5_xof_ctx_t * ctx, size_t x)
{
	int i;
	uint8_t buf[9];

	i = 8;
	do {
		buf[--i] = x & 0xFF;
		x >>= 8;
	}
	while (x > 0);
	buf[8] = 8 - i;

	r5_xof_in(ctx, buf + i, 9 - i);
}

void r5_xof_enc_left(r5_xof_ctx_t * ctx, size_t x)
{
	int i;
	uint8_t buf[9];

	i = 8;
	do {
		buf[i--] = x & 0xFF;
		x >>= 8;
	}
	while (x > 0);
	buf[i] = 8 - i;
	r5_xof_in(ctx, buf + i, 9 - i);
}

void r5_xof_enc_dat(r5_xof_ctx_t * ctx, const uint8_t * dat, size_t len)
{
	r5_xof_enc_left(ctx, 8 * len);
	r5_xof_in(ctx, dat, len);
}

void r5_xof_enc_str(r5_xof_ctx_t * ctx, const char *s)
{
	int l;

	l = strlen(s);
	r5_xof_enc_left(ctx, 8 * l);
	r5_xof_in(ctx, (uint8_t *) s, l);
}

void r5_xof_perm(r5_xof_ctx_t * ctx)
{
	size_t i = ctx->idx;
	memset(ctx->buf + i, 0x00, R5_XOF_RATE - i);
	keccak_xorbytes(ctx->st, ctx->buf, 0, R5_XOF_RATE);
	keccak_f1600(ctx->st);
	ctx->idx = 0;
}

int main(int argc, char **argv)
{
	const uint8_t b1[3] = { 0x00, 0x01, 0x02 };
	const uint8_t b2[6] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15 };

	uint8_t buf[32];

	r5_xof_ctx_t ctx;

	r5_xof_clr(&ctx);
	r5_xof_enc_left(&ctx, R5_XOF_RATE);
	r5_xof_enc_str(&ctx, "TupleHash");
	r5_xof_enc_str(&ctx, "");				//  S
	r5_xof_perm(&ctx);


	keccak_extract(ctx.st, ctx.buf, 0, R5_XOF_RATE);

	r5_xof_enc_dat(&ctx, b1, 3);
	r5_xof_enc_dat(&ctx, b2, 6);
	r5_xof_enc_right(&ctx, 0);				//  output length
	r5_xof_pad(&ctx, 0x04);

	r5_xof_out(&ctx, buf, 32);

	printf("result =");
	for (size_t i = 0; i < 32; i++)
		printf(" %02X", buf[i]);
	printf("\n");

	return 0;
}
