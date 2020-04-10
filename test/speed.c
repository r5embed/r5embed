//  speed.c
//  2019-03-02  Markku-Juhani O. Saarinen <mjos@pqshield.com>
//  Copyright (c) 2019, PQShield Ltd. All rights reserved.

//  Simplified speed testing for KEM and PKE algorithms.

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <inttypes.h>
#include <sys/time.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "api.h"
#include "rng.h"

// for __rdtsc()
#ifdef __x86_64__
#include <x86intrin.h>
#define GET_CYCLES __rdtsc()
#else
#define GET_CYCLES 0
#endif

#ifndef XBENCH_REPS
#define XBENCH_REPS 100
#endif

// timeout in seconds

#ifndef XBENCH_TIMEOUT
#define XBENCH_TIMEOUT 2.0
#endif

#ifndef CRYPTO_ALGNAME
#define CRYPTO_ALGNAME "UNKNOWN ALGORITHM"
#endif

#ifndef MY_MSG_SIZE
#define MY_MSG_SIZE 48
#endif

// gives roughly 2 microsecond precision on my system

static double clk_now()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) != 0) {
		perror("gettimeofday()");
		exit(-1);
	}
	return ((double) tv.tv_sec) + 1E-6 * ((double) tv.tv_usec);
}

void dump_tv(const uint8_t * dat, size_t len, const char *lab)
{
	uint32_t x;
	size_t i;

	x = 0xDEADBEEF;

	for (i = 0; i < len; i++) {
		x += (uint32_t) dat[i];
		x *= 0x01234567;
	}

	printf("%s tv %08X  %s\t%6u\n", CRYPTO_ALGNAME, x, lab, (unsigned) len);
}

int main(int argc, char **argv)
{
	uint8_t seed[48];
	int i, fails;
	uint64_t n, clk1, clk2;
	double tim1, tim2;
	uint8_t *pk[XBENCH_REPS], *sk[XBENCH_REPS], *ct[XBENCH_REPS],
		*ss[XBENCH_REPS], *sr[XBENCH_REPS];

	// allocate multiple of everything

	for (i = 0; i < XBENCH_REPS; i++) {
		pk[i] = (uint8_t *) malloc(CRYPTO_PUBLICKEYBYTES);
		sk[i] = (uint8_t *) malloc(CRYPTO_SECRETKEYBYTES);
		ct[i] = (uint8_t *) malloc(CRYPTO_CIPHERTEXTBYTES);
		ss[i] = (uint8_t *) malloc(CRYPTO_BYTES);
		sr[i] = (uint8_t *) malloc(CRYPTO_BYTES);
		memset(ss[i], 0x55, CRYPTO_BYTES);
		memset(sr[i], 0xAA, CRYPTO_BYTES);
	}

	// init random

	for (i = 0; i < 48; i++)
		seed[i] = i;
	randombytes_init(seed, NULL, 256);

	crypto_kem_keypair(pk[0], sk[0]);
	crypto_kem_enc(ct[0], ss[0], pk[0]);
	crypto_kem_dec(sr[0], ct[0], sk[0]);

	dump_tv(pk[0], CRYPTO_PUBLICKEYBYTES, "pk");
	dump_tv(sk[0], CRYPTO_SECRETKEYBYTES, "sk");
	dump_tv(ct[0], CRYPTO_CIPHERTEXTBYTES, "ct");
	dump_tv(ss[0], CRYPTO_BYTES, "ss");
	dump_tv(sr[0], CRYPTO_BYTES, "sr");

	fails = 0;

	//  test for correctness and benchmark the whole thing

	n = 0;
	fails = 0;
	tim1 = clk_now();
	clk2 = 0;
	do {
		clk1 = GET_CYCLES;
		for (i = 0; i < XBENCH_REPS; i++) {

			if (crypto_kem_keypair(pk[i], sk[i]) ||
				crypto_kem_enc(ct[i], ss[i], pk[i]) ||
				crypto_kem_dec(sr[i], ct[i], sk[i]) ||
				memcmp(ss[i], sr[i], CRYPTO_BYTES) != 0) {
				// failed!
				fails++;
			}
		}
		clk2 += GET_CYCLES - clk1;
		tim2 = clk_now() - tim1;
		n += XBENCH_REPS;

	} while (tim2 < XBENCH_TIMEOUT);

	printf("Tot %12" PRIu64 " clk %12.9f sec\t[%s]\n",
		   clk2 / n, tim2 / n, CRYPTO_ALGNAME);

	if (fails > 0) {
		printf("test failed %d/%d times [%s]\n",
			   (int) fails, (int) n, CRYPTO_ALGNAME);
	}
	// time keygen

	n = 0;
	tim1 = clk_now();
	clk2 = 0;
	do {
		clk1 = GET_CYCLES;
		for (i = 0; i < XBENCH_REPS; i++) {
			crypto_kem_keypair(pk[i], sk[i]);
		}
		clk2 += GET_CYCLES - clk1;
		tim2 = clk_now() - tim1;
		n += XBENCH_REPS;
	} while (tim2 < XBENCH_TIMEOUT);

	printf("KG  %12" PRIu64 " clk %12.9f sec\t[%s]\n",
		   clk2 / n, tim2 / n, CRYPTO_ALGNAME);

	//  time encaps

	n = 0;
	tim1 = clk_now();
	clk2 = 0;
	do {
		clk1 = GET_CYCLES;
		for (i = 0; i < XBENCH_REPS; i++) {
			crypto_kem_enc(ct[i], ss[i], pk[i]);
		}
		clk2 += GET_CYCLES - clk1;
		tim2 = clk_now() - tim1;
		n += XBENCH_REPS;
	} while (tim2 < XBENCH_TIMEOUT);

	printf("Enc %12" PRIu64 " clk %12.9f sec\t[%s]\n",
		   clk2 / n, tim2 / n, CRYPTO_ALGNAME);

	//  time decaps

	n = 0;
	tim1 = clk_now();
	clk2 = 0;
	do {
		clk1 = GET_CYCLES;
		for (i = 0; i < XBENCH_REPS; i++) {
			crypto_kem_dec(ss[i], ct[i], sk[i]);
		}
		clk2 += GET_CYCLES - clk1;
		tim2 = clk_now() - tim1;
		n += XBENCH_REPS;
	} while (tim2 < XBENCH_TIMEOUT);

	printf("Dec %12" PRIu64 " clk %12.9f sec\t[%s]\n",
		   clk2 / n, tim2 / n, CRYPTO_ALGNAME);

	// free all

	for (i = 0; i < XBENCH_REPS; i++) {
		free(pk[i]);
		free(sk[i]);
		free(ct[i]);
		free(ss[i]);
		free(sr[i]);
	}

	return 0;
}
