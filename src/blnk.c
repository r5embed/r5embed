//	blnk.c
//	2019-02-20	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (C) 2019, PQShield Ltd. Please see LICENSE.

//	The BLNK2 core.

#ifdef BLNK2

#include <string.h>

#include "blnk.h"

//	Clear state

void blnk_clr(blnk_t *ctx, size_t rate, uint8_t rounds)
{
	memset(ctx->st, 0, BLNK_BLOCK);
	ctx->pos = 0;
	ctx->rate = rate;
	ctx->rounds = rounds;
}

//	End a data element (compulsory between different domain types)

void blnk_fin(blnk_t *ctx, blnk_dom_t dom)
{
	const uint8_t pad[1] = { 0x01 };

	blnk_put(ctx, dom, pad, 1);				// padding bit
	if ((dom & BLNK_FULL) == 0) {			// not a full-state input domain?
		ctx->st[ctx->rate - 1] ^= 0x80;		// flip last bit before capacity
	}

	BLNK_PI(&ctx->st, dom | BLNK_LAST, ctx->rounds);	// finalize
	ctx->pos = 0;
}

//	Absorb data

void blnk_put(blnk_t *ctx, blnk_dom_t dom, const void *in, size_t len)
{
	size_t j, rate;

	//	full state-absorption ?
	rate = dom & BLNK_FULL ? BLNK_BLOCK : ctx->rate;

	for (j = 0; j < len; j++) {
		if (ctx->pos >= rate) {
			BLNK_PI(&ctx->st, dom, ctx->rounds);
			ctx->pos = 0;
		}
		ctx->st[ctx->pos++] ^= ((const uint8_t *) in)[j];
	}
}

//	Squeeze data

void blnk_get(blnk_t *ctx, blnk_dom_t dom, void *out, size_t len)
{
	size_t j;

	for (j = 0; j < len; j++) {
		if (ctx->pos >= ctx->rate) {
			BLNK_PI(&ctx->st, dom, ctx->rounds);
			ctx->pos = 0;
		}
		((uint8_t *) out)[j] = ctx->st[ctx->pos++];
	}
}

//	Encrypt data

void blnk_enc(blnk_t *ctx, blnk_dom_t dom,
	void *out, const void *in, size_t len)
{
	size_t j;

	for (j = 0; j < len; j++) {
		if (ctx->pos >= ctx->rate) {
			BLNK_PI(&ctx->st, dom, ctx->rounds);
			ctx->pos = 0;
		}
		ctx->st[ctx->pos] ^= ((const uint8_t *) in)[j];
		((uint8_t *) out)[j] = ctx->st[ctx->pos++];
	}
}

//	Decrypt data

void blnk_dec(blnk_t *ctx, blnk_dom_t dom,
	void *out, const void *in, size_t len)
{
	size_t j;
	uint8_t t;

	for (j = 0; j < len; j++) {
		if (ctx->pos >= ctx->rate) {
			BLNK_PI(&ctx->st, dom, ctx->rounds);
			ctx->pos = 0;
		}
		t = ((const uint8_t *) in)[j];
		((uint8_t *) out)[j] = ctx->st[ctx->pos] ^ t;
		ctx->st[ctx->pos++] = t;
	}
}

// Compare to output (0 == equal)

int blnk_cmp(blnk_t *ctx, blnk_dom_t dom, const void *in, size_t len)
{
	size_t j;
	uint8_t d;

	d = 0;
	for (j = 0; j < len; j++) {
		if (ctx->pos >= ctx->rate) {
			BLNK_PI(&ctx->st, dom, ctx->rounds);
			ctx->pos = 0;
		}
		d |= ((const uint8_t *) in)[j] ^ ctx->st[ctx->pos++];
	}

	return d != 0;
}

#endif /* BLNK2 */
