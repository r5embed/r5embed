//  kemtv.c
//  Copyright (c) 2019, PQShield Ltd.
//  2019-03-02  Markku-Juhani O. Saarinen <mjos@pqshield.com>

//  Simplified testing for KEM algorithms.

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "api.h"
#include "rng.h"

//  KEM or "PKE" ?
#if defined(CRYPTO_CIPHERTEXTBYTES) && (CRYPTO_CIPHERTEXTBYTES > 1)
#else
// -- we are testing the PKE algorithm as a KEM --
#undef CRYPTO_BYTES
#undef CRYPTO_CIPHERTEXTBYTES
#define CRYPTO_BYTES		   PARAMS_KAPPA_BYTES
#define CRYPTO_CIPHERTEXTBYTES (PARAMS_CT_SIZE + PARAMS_KAPPA_BYTES)
#endif

void print_tv(const uint8_t *dat, size_t len, const char *lab)
{
	uint32_t x;
	size_t i;

	x = 0xDEADBEEF;					 // silly checksum
	for (i = 0; i < len; i++) {
		x += (uint32_t) dat[i];
		x *= 0x01234567;
	}

	printf("%s\t%s\t%08X\t%lu\n",
		CRYPTO_ALGNAME, lab, x, len);
}

int main(int argc, char **argv)
{
	//  test data is here
	uint8_t pk[CRYPTO_PUBLICKEYBYTES];
	uint8_t sk[CRYPTO_SECRETKEYBYTES];
	uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
	uint8_t ss[CRYPTO_BYTES], sr[CRYPTO_BYTES];
    uint8_t seed[48];
	int i;

	//  my simple "test vectors"
	for (i = 0; i < 48; i++)
		seed[i] = i;

	randombytes_init(seed, NULL, 256);

	crypto_kem_keypair(pk, sk);
	crypto_kem_enc(ct, ss, pk);
	crypto_kem_dec(sr, ct, sk);
	
	if (memcmp(ss, sr, CRYPTO_BYTES) != 0)
		printf("%s FAIL! :(\n", CRYPTO_ALGNAME);

    print_tv(pk, CRYPTO_PUBLICKEYBYTES, "pk");
    print_tv(sk, CRYPTO_SECRETKEYBYTES, "sk");
    print_tv(ct, CRYPTO_CIPHERTEXTBYTES, "ct");
    print_tv(ss, CRYPTO_BYTES, "ss");
    print_tv(sr, CRYPTO_BYTES, "sr");

    return 0;
}

