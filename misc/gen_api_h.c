//	gen_api_h.c
//	Copyright (c) 2019, PQShield Ltd.
//	2019-03-02	Markku-Juhani O. Saarinen <mjos@pqshield.com>

//	Quick and dirty generation of api.h files with actual constants.

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "api.h"

// KEM or PKE ?
#if defined(CRYPTO_CIPHERTEXTBYTES) && (CRYPTO_CIPHERTEXTBYTES > 0)
#define KEM_TEST
#else
#define PKE_TEST
#endif

int main(int argc, char **argv)
{
	printf("#define CRYPTO_SECRETKEYBYTES %d\n", CRYPTO_SECRETKEYBYTES);
	printf("#define CRYPTO_PUBLICKEYBYTES %d\n", CRYPTO_PUBLICKEYBYTES);
	printf("#define CRYPTO_BYTES %d\n", CRYPTO_BYTES);

#ifdef KEM_TEST
	printf("#define CRYPTO_CIPHERTEXTBYTES %d\n", CRYPTO_CIPHERTEXTBYTES);
#endif
	printf("#define CRYPTO_ALGNAME \"%s\"\n\n", CRYPTO_ALGNAME);

	return 0;
}


