//  keccakf1600.h
//  2020-04-01  Markku-Juhani O. Saarinen <mjos@pqshield.com>
//  Copyright (c) 2020, PQShield Ltd. All rights reserved.

//  Raw Keccak f-1600 interface. (Derived From public domain sources.)

#ifndef _KECCAKF1600_H_
#define _KECCAKF1600_H_

#include <stdint.h>
#include <stddef.h>

//  permutation
void keccak_f1600(uint64_t * state);

//  extract bytes
void keccak_extract(uint64_t * state,
					uint8_t * data, size_t offset, size_t length);
//  input bytes via xor
void keccak_xorbytes(uint64_t * state, const uint8_t * data,
					 size_t offset, size_t length);

#endif										/* _KECCAKF1600_H_ */
