//	r5_cca_kem.h
//	Copyright (c) 2019, PQShield Ltd. and Koninklijke Philips N.V.
//	Markku-Juhani O. Saarinen, Koninklijke Philips N.V.

#ifndef _R5_CCA_KEM_H_
#define _R5_CCA_KEM_H_

#include <stdint.h>

/**
 * Generates a CCA KEM key pair. Uses the parameters as specified.
 *
 * @param[out] pk	  public key
 * @param[out] sk	  secret key
 * @return __0__ in case of success
 */
int r5_cca_kem_keygen(uint8_t *pk, uint8_t *sk);

/**
 * CCA KEM encapsulate. Uses the parameters as specified.
 *
 * @param[out] ct	  key encapsulation message (<b>important:</b> the size of `ct` is `ct_size` + `kappa_bytes`!)
 * @param[out] k	  shared secret
 * @param[in]  pk	  public key with which the message is encapsulated
 * @return __0__ in case of success
 */
int r5_cca_kem_encapsulate(uint8_t *ct, uint8_t *k, const uint8_t *pk);

/**
 * CCA KEM de-capsulate. Uses the parameters as specified.
 *
 * @param[out] k	  shared secret
 * @param[in]  ct	  key encapsulation message (<b>important:</b> the size of `ct` is `ct_size` + `kappa_bytes`!)
 * @param[in]  sk	  secret key with which the message is to be de-capsulated (<b>important:</b> the size of `sk` is `sk_size` + `kappa_bytes` + `pk_size`!)
 * @return __0__ in case of success
 */
int r5_cca_kem_decapsulate(uint8_t *k, const uint8_t *ct, const uint8_t *sk);

#endif /* R5_CCA_KEM_H */
