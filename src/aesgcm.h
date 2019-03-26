//	aesgcm.h
//	Copyright (c) 2019, PQShield Ltd.

//	2019-03-04	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Simple GCM functionality. No support of associated data.

#ifndef _AESGCM_H_
#define _AESGCM_H_

#include <stdint.h>
#include <stddef.h>

#define AES128_ROUNDS 10
#define AES192_ROUNDS 12
#define AES256_ROUNDS 14

#define AES128_RK_WORDS (4 * (AES128_ROUNDS + 1))
#define AES192_RK_WORDS (4 * (AES192_ROUNDS + 1))
#define AES256_RK_WORDS (4 * (AES256_ROUNDS + 1))

//	Key expansion

void aes128_set_key(uint32_t rk[AES128_RK_WORDS], const uint8_t key[16]);
void aes192_set_key(uint32_t rk[AES192_RK_WORDS], const uint8_t key[24]);
void aes256_set_key(uint32_t rk[AES256_RK_WORDS], const uint8_t key[32]);

void aes_enc_rounds(uint8_t ct[16], const uint8_t pt[16],
	const uint32_t rk[], int nr);

//	Single-block operation prototypes for convenience.

#define aes128_enc_block(ct, pt, rk) aes_enc_rounds(ct, pt, rk, AES128_ROUNDS);
#define aes192_enc_block(ct, pt, rk) aes_enc_rounds(ct, pt, rk, AES192_ROUNDS);
#define aes256_enc_block(ct, pt, rk) aes_enc_rounds(ct, pt, rk, AES256_ROUNDS);

//	AES-GCM. ciphertext is always 16 bytes larger than plaintext.
//	The decrypt/verify routines return nonzero on failure.

void aes128_enc_gcm(uint8_t *c, const uint8_t *m, size_t mlen,
	const uint8_t *key, const uint8_t iv[12]);
int aes128_dec_vfy_gcm(uint8_t *m, const uint8_t *c, size_t clen,
	const uint8_t *key, const uint8_t iv[12]);

void aes192_enc_gcm(uint8_t *c, const uint8_t *m, size_t mlen,
	const uint8_t *key, const uint8_t iv[12]);
int aes192_dec_vfy_gcm(uint8_t *m, const uint8_t *c, size_t clen,
	const uint8_t *key, const uint8_t iv[12]);

void aes256_enc_gcm(uint8_t *c, const uint8_t *m, size_t mlen,
	const uint8_t *key, const uint8_t iv[12]);
int aes256_dec_vfy_gcm(uint8_t *m, const uint8_t *c, size_t clen,
	const uint8_t *key, const uint8_t iv[12]);

#endif /* _AESGCM_H_ */
