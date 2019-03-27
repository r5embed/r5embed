//  sneik_param.h
//  2019-02-19  Markku-Juhani O. Saarinen <mjos@pqshield.com>
//  Copyright (C) 2019, PQShield Ltd. Please see LICENSE.

//  This file provides parametrizations for the SNEIK family.

#ifndef _SNEIK_PARAM_H_
#define _SNEIK_PARAM_H_

#include <stdint.h>
#include "api.h"

// Compression function prototype
void sneik_f512(void *state, uint8_t dom, uint8_t rounds);

// Parameters (sizes are in bytes)
#define BLNK_BLOCK 64
#define BLNK_PI(x, dom, rounds) sneik_f512(x, dom, rounds)

// == SNEIKEN AEADs ==

#ifdef CRYPTO_KEYBYTES

#define SNEIKEN_RATE (BLNK_BLOCK - CRYPTO_KEYBYTES)

//	number of rounds
#if (CRYPTO_KEYBYTES == 16)
#define SNEIKEN_ROUNDS 6
#elif (CRYPTO_KEYBYTES == 24)
#define SNEIKEN_ROUNDS 7
#elif (CRYPTO_KEYBYTES == 32)
#define SNEIKEN_ROUNDS 8
#else
#error "Could not determine security level."
#endif

#endif	/* CRYPTO_KEYBYTES */

//  == SNEIKHA Cryptographic Hashes ==

#if defined(CRYPTO_BYTES) && !defined(PARAMS_KAPPA_BYTES)
#define SNEIKHA_RATE (BLNK_BLOCK - CRYPTO_BYTES)

#if (CRYPTO_BYTES == 16)
#define SNEIKHA_ROUNDS 4
#elif (CRYPTO_BYTES == 32)
#define SNEIKHA_ROUNDS 8
#elif (CRYPTO_BYTES == 48)
#define SNEIKHA_ROUNDS 8
#else
#error "Could not determine security level."
#endif

#endif	/* CRYPTO_BYTES */

//	== SNEIGEN Entropy distribution function ==

#ifdef PARAMS_KAPPA_BYTES

#define SNEIGEN_RATE (BLNK_BLOCK - PARAMS_KAPPA_BYTES)

#if (PARAMS_KAPPA_BYTES == 16)
#define SNEIGEN_ROUNDS 4
#elif (PARAMS_KAPPA_BYTES == 24)
#define SNEIGEN_ROUNDS 5
#elif (PARAMS_KAPPA_BYTES == 32)
#define SNEIGEN_ROUNDS 6
#else
#error "Could not determine security level."
#endif

#endif /* PARAMS_KAPPA_BYTES */

#endif	/* _SNEIK_PARAM_H_ */

