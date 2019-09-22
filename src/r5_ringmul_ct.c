//	r5_ringmul_ct.c
//	Copyright (c) 2019, PQShield Ltd. and Koninklijke Philips N.V.

//	Constant-time ring arithmetic (slow!)

#include "r5_parameter_sets.h"

#if (PARAMS_N == PARAMS_D) && defined(R5_CT)

#include <string.h>
#include "r5_ringmul.h"
#include "r5_xof.h"

// multiplication mod q, result length n

void r5_ringmul_q(modq_t d[PARAMS_D],
	modq_t a[2 * (PARAMS_D + 1)], const r5_ternv_t sv)
{
	size_t i, j, k;
	modq_t addf, subf, w, *b;
	uint64_t t, u;

	//	note: order of coefficients a[1..n] is *NOT* reversed!
	//	"lift" -- multiply by (x - 1)
	a[PARAMS_D] = a[PARAMS_D - 1];
	for (i = PARAMS_D - 1; i >= 1; i--) {
		a[i] = a[i - 1] - a[i];
	}
	a[0] = -a[0];

	//	duplicate at the end
	b = &a[PARAMS_D + 1];
	memcpy(b, a, (PARAMS_D + 1) * sizeof(modq_t));

	//	initialize result
	memset(d, 0, PARAMS_D * sizeof(modq_t));

	a++;								//	adjust for comparison
	for (k = 0; k < TVEC_WORDS; k++) {
		t = sv[k][0] & ~sv[k][1];		//	addition mask
		u = sv[k][0] & sv[k][1];		//	subtraction mask
		for (i = 0; i < 64; i++) {
			addf = -(t & 1);			//	expand lsb
			subf = -(u & 1);
			for (j = 0; j < PARAMS_D; j++) {
				w = b[j];				// no multiplication here!
				w = (addf & w) - (subf & w);
				d[j] += w;
			}
			b--;
			if (b == a)
				break;
			t >>= 1;
			u >>= 1;
		}
	}

	//	"unlift"
	d[0] = -d[0];
	for (i = 1; i < PARAMS_D; i++) {
		d[i] = d[i - 1] - d[i];
	}
}

// multiplication mod p, result length mu

void r5_ringmul_p(modp_t d[PARAMS_MU],
	modp_t a[PARAMS_D + PARAMS_MU + 2], const r5_ternv_t sv)
{
	size_t i, j, k;

	modp_t addf, subf, w, *b;
	uint64_t t, u;

	//	note: order of coefficients p[1..N] is *NOT* reversed!
#if (PARAMS_XE == 0)
	//	without error correction we "lift" -- i.e. multiply by (x - 1)
	a[PARAMS_D] = a[PARAMS_D - 1];
	for (i = PARAMS_D - 1; i >= 1; i--) {
		a[i] = a[i - 1] - a[i];
	}
	a[0] = -a[0];
#else
	a[PARAMS_D] = 0;
	a[PARAMS_D + 1] = a[0];
	a++;								//	don't lift, shift!
#endif
	b = &a[PARAMS_D + 1];
	memcpy(b, a, PARAMS_MU * sizeof(modp_t));

	//	initialize result
	memset(d, 0, (PARAMS_MU) * sizeof(modp_t));

	a++;								//	adjust for comparison
	for (k = 0; k < TVEC_WORDS; k++) {
		t = sv[k][0] & ~sv[k][1];		//	addition mask
		u = sv[k][0] & sv[k][1];		//	subtraction mask
		for (i = 0; i < 64; i++) {
			addf = -(t & 1);			//	expand lsb
			subf = -(u & 1);
			for (j = 0; j < PARAMS_MU; j++) {
				w = b[j];				// no multiplication here!
				w = (addf & w) - (subf & w);
				d[j] += w;
			}
			b--;
			if (b == a)
				break;
			t >>= 1;
			u >>= 1;
		}
	}

#if (PARAMS_XE == 0)
	//	without error correction we "lifted" so we now need to "unlift"
	d[0] = -d[0];
	for (i = 1; i < PARAMS_MU; ++i) {
		d[i] = d[i - 1] - d[i];
	}
#endif
}

#endif
