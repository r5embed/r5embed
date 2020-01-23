//	aesenc.h
//	2019-10-23	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (c) 2019, PQShield Ltd. All rights reserved.

#ifndef _AESENC_H_
#define _AESENC_H_

#include <stdint.h>
#include <stddef.h>

#define AES128_ROUNDS 10
#define AES192_ROUNDS 12
#define AES256_ROUNDS 14

#define AES128_RK_WORDS (4 * (AES128_ROUNDS + 1))
#define AES192_RK_WORDS (4 * (AES192_ROUNDS + 1))
#define AES256_RK_WORDS (4 * (AES256_ROUNDS + 1))

//	set key
void aes128_set_key(uint32_t rk[44], const uint8_t key[16]);
void aes192_set_key(uint32_t rk[52], const uint8_t key[24]);
void aes256_set_key(uint32_t rk[60], const uint8_t key[32]);

// encrypt a block
void aes_enc_rounds(uint8_t ct[16], const uint8_t pt[16],
					const uint32_t rk[], int nr);

#define aes128_enc_block(ct, pt, rk) aes_enc_rounds(ct, pt, rk, AES128_ROUNDS);
#define aes192_enc_block(ct, pt, rk) aes_enc_rounds(ct, pt, rk, AES192_ROUNDS);
#define aes256_enc_block(ct, pt, rk) aes_enc_rounds(ct, pt, rk, AES256_ROUNDS);

#endif							/* _AESENC_H_ */
