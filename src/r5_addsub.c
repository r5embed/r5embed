//	r5_addsub.c
//	Copyright (c) 2019, PQShield Ltd.

//	Addition-subtraction loops. The right number of of combined elements
//	depends on the register file structure of the target -- ARM allows
//	basically any register to be used as a pointer, which is a benefit.

#include "r5_parameter_sets.h"
#include "r5_addsub.h"

#ifndef ARMV7_ASM
#ifndef __AVX2__

//	Basic generic C versions

void r5_modq_addsub_d(modq_t *dst,
	const modq_t *p_add, const modq_t *p_sub)
{
	size_t i;

	for (i = 0; i < PARAMS_D; i++) {
		dst[i] += p_add[i] - p_sub[i];
	}
}

void r5_modq_addsub3_d(modq_t *dst,
	const modq_t *p_add1, const modq_t *p_sub1,
	const modq_t *p_add2, const modq_t *p_sub2,
	const modq_t *p_add3, const modq_t *p_sub3)
{
	size_t i;

	for (i = 0; i < PARAMS_D; i++) {
		dst[i] += p_add1[i] - p_sub1[i]
				+ p_add2[i] - p_sub2[i]
				+ p_add3[i] - p_sub3[i];
	}
}

#endif /* !__AVX2__ */

void r5_modq_addsub_perm_nbar_d(modq_t *dst, const uint16_t *perm,
	const modq_t *p_add, const modq_t *p_sub)
{
	size_t i, j, k;

	i = 0;
	for (j = 0; j < PARAMS_D; j++) {
		k = perm[j];
		dst[i] += p_add[k] - p_sub[k];
		i += PARAMS_N_BAR;
	}
}

void r5_modq_addsub3_perm_nbar_d(modq_t *dst, const uint16_t *perm,
	const modq_t *p_add1, const modq_t *p_sub1,
	const modq_t *p_add2, const modq_t *p_sub2,
	const modq_t *p_add3, const modq_t *p_sub3)
{
	size_t i, j, k;

	i = 0;
	for (j = 0; j < PARAMS_D; j++) {
		k = perm[j];
		dst[i] += p_add1[k] - p_sub1[k]
				+ p_add2[k] - p_sub2[k]
				+ p_add3[k] - p_sub3[k];
		i += PARAMS_N_BAR;
	}
}

void r5_modp_addsub_mu(modp_t *dst,
	const modp_t *p_add, const modp_t *p_sub)
{
	size_t i;

	for (i = 0; i < PARAMS_MU; i++) {
		dst[i] += p_add[i] - p_sub[i];
	}
}

#endif /* !ARMV7_ASM */
