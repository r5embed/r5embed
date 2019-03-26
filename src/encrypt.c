//	encrypt.c
//	Copyright (c) 2019, PQShield Ltd. and Koninklijke Philips N.V.

//	Implementation of NIST Encryption API

#include "r5_parameter_sets.h"

#ifdef ROUND5_CCA_PKE

#include <string.h>

#include "nist_pke.h"
#include "r5_cca_kem.h"
#include "r5_dem.h"

int crypto_encrypt_keypair(unsigned char *pk, unsigned char *sk)
{
	return r5_cca_kem_keygen(pk, sk);
}

int crypto_encrypt(unsigned char *ct, unsigned long long *ct_len,
	const unsigned char *m, const unsigned long long m_len,
	const unsigned char *pk)
{
	unsigned char c1[PARAMS_CT_SIZE + PARAMS_KAPPA_BYTES];
	unsigned char k[PARAMS_KAPPA_BYTES];
	size_t c2_len;

	/* Determine c1 and k */
	r5_cca_kem_encapsulate(c1, k, pk);

	/* Copy c1 into first part of ct */
	memcpy(ct, c1, sizeof(c1));

	/* Apply DEM to get second part of ct */
	if (round5_dem(ct + sizeof(c1), &c2_len, k, PARAMS_KAPPA_BYTES, m, m_len))
		return -1;

	*ct_len = sizeof(c1) + c2_len;

	return 0;
}

int crypto_encrypt_open(unsigned char *m, unsigned long long *m_len,
	const unsigned char *ct, unsigned long long ct_len,
	const unsigned char *sk)
{
	unsigned char k[PARAMS_KAPPA_BYTES];
	size_t m2_len;

	/* Check length, should be at least c1_len + 16 (for the DEM tag) */
	if (ct_len < (PARAMS_CT_SIZE + PARAMS_KAPPA_BYTES + 16))
		return -1;

	/* Determine k */
	r5_cca_kem_decapsulate(k, ct, sk);

	/* Apply DEM-inverse to get m */
	if (round5_dem_inverse(m, &m2_len, k, PARAMS_KAPPA_BYTES,
			&ct[PARAMS_CT_SIZE + PARAMS_KAPPA_BYTES],
			ct_len - (PARAMS_CT_SIZE + PARAMS_KAPPA_BYTES)))
		return -1;

	/* OK */
	*m_len = (unsigned long long) m2_len;

	return 0;
}

#endif /* ROUND5_CCA_PKE */

