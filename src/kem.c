//	kem.c
//	Copyright (c) 2019, PQShield Ltd. and Koninklijke Philips N.V.

//	Implementation of NIST KEM API

#include "r5_parameter_sets.h"

#ifndef ROUND5_CCA_PKE

//	This is the normal CPA KEM interface

#include <string.h>

#include "nist_kem.h"
#include "r5_cpa_pke.h"
#include "r5_xof.h"
#include "rng.h"

// CPA-KEM KeyGen()

int crypto_kem_keypair(uint8_t *pk, uint8_t *sk)
{
	return r5_cpa_pke_keygen(pk, sk);
}

// CPA-KEM Encaps()

int crypto_kem_enc(uint8_t *ct, uint8_t *k, const uint8_t *pk)
{
	uint8_t hash_input[PARAMS_KAPPA_BYTES + PARAMS_CT_SIZE];

	uint8_t m[PARAMS_KAPPA_BYTES];
	uint8_t rho[PARAMS_KAPPA_BYTES];

	/* Generate a random m and rho */
	randombytes(m, PARAMS_KAPPA_BYTES);
	randombytes(rho, PARAMS_KAPPA_BYTES);

	r5_cpa_pke_encrypt(ct, pk, m, rho);

	/* k = H(m, ct) */
	memcpy(hash_input, m, PARAMS_KAPPA_BYTES);
	memcpy(hash_input + PARAMS_KAPPA_BYTES, ct, PARAMS_CT_SIZE);
	r5_xof(k, PARAMS_KAPPA_BYTES, hash_input,
		PARAMS_KAPPA_BYTES + PARAMS_CT_SIZE);

	return 0;
}

// CPA-KEM Decaps()

int crypto_kem_dec(uint8_t *k, const uint8_t *ct, const uint8_t *sk)
{
	uint8_t hash_input[PARAMS_KAPPA_BYTES + PARAMS_CT_SIZE];
	uint8_t m[PARAMS_KAPPA_BYTES];

	/* Decrypt m */
	r5_cpa_pke_decrypt(m, sk, ct);

	/* k = H(m, ct) */
	memcpy(hash_input, m, PARAMS_KAPPA_BYTES);
	memcpy(hash_input + PARAMS_KAPPA_BYTES, ct, PARAMS_CT_SIZE);
	r5_xof(k, PARAMS_KAPPA_BYTES, hash_input,
		PARAMS_KAPPA_BYTES + PARAMS_CT_SIZE);

	return 0;
}

#else

//	We also provide an alternative KEM interface for CCA parameter sets

#include "nist_kem.h"
#include "r5_cca_kem.h"

int crypto_kem_keypair(uint8_t *pk, uint8_t *sk)
{
	return r5_cca_kem_keygen(pk, sk);
}

int crypto_kem_enc(uint8_t *ct, uint8_t *k, const uint8_t *pk)
{
	return r5_cca_kem_encapsulate(ct, k, pk);
}

int crypto_kem_dec(uint8_t *k, const uint8_t *ct, const uint8_t *sk)
{
	return r5_cca_kem_decapsulate(k, ct, sk);
}

#endif /* !defined ROUND5_CCA_PKE */

