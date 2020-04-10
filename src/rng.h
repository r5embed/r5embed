//  rng.h
//  Copyright (c) 2019, PQShield Ltd. and Koninklijke Philips N.V.

#ifndef _RNG_H_
#define _RNG_H_

//  NIST / SUPERCOP "RNG" Interface

void randombytes_init(unsigned char *entropy_input,
					  unsigned char *personalization_string,
					  int security_strength);

int randombytes(unsigned char *x, unsigned long long xlen);

#endif										/* _RNG_H_ */
