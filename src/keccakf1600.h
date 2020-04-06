//  keccakf1600.h
//  2020-04-01  Markku-Juhani O. Saarinen <mjos@pqshield.com>
//  Copyright (c) 2020, PQShield Ltd. All rights reserved.

//  Raw Keccak f-1600 interface. (Derived From public domain sources.)

#ifndef _KECCAKF1600_H_
#define _KECCAKF1600_H_

#ifndef ARMV7_ASM

#include <stdint.h>
#include <stddef.h>

//  keccakf1600.c prototypes

//  permutation
void keccak_f1600(uint64_t * state);

//  extract bytes
void keccak_extract(uint64_t * state, uint8_t * data, size_t length);

//  input bytes via xor
void keccak_xorbytes(uint64_t * state, const uint8_t * data, size_t length);

#else										/* !ARMV7_ASM */

//  keccakf1600_armv7.S prototypes

void KeccakF1600_StateExtractBytes(void *state, uint8_t * data,
								   unsigned int offset, unsigned int length);

void KeccakF1600_StateXORBytes(void *state, const uint8_t * data,
							   unsigned int offset, unsigned int length);

void KeccakF1600_StatePermute(void *state);

//  wrappers

#define keccak_extract(state, data, rate) \
	{ KeccakF1600_StateExtractBytes(state, data, 0, rate); }

#define keccak_xorbytes(state, data, rate) \
	{ KeccakF1600_StateXORBytes(state, data, 0, rate); }

#define keccak_f1600(state) \
	{ KeccakF1600_StatePermute(state); }

#endif										/* ARMV7_ASM */

#endif										/* _KECCAKF1600_H_ */
