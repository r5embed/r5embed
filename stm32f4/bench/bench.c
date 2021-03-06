//	bench.c
//	2019-03-10	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (c) 2019, PQShield Ltd. All rights reserved.

//	Benchmark code. Helped by OpenCM3 examples and PQM4.

#include <stdio.h>
#include <string.h>

#include "main.h"
#include "api.h"
#include "rng.h"

//	timeout, three seconds
#ifndef BENCH_TIMEOUT
#define BENCH_TIMEOUT (3 * 24000000)
#endif

//	test data is here
static uint8_t pk[CRYPTO_PUBLICKEYBYTES];
static uint8_t sk[CRYPTO_SECRETKEYBYTES];
static uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
static uint8_t ss[CRYPTO_BYTES], sr[CRYPTO_BYTES];

//	rng seed
static uint8_t seed[48];

//	simple test vectors

void print_tv(const uint8_t *dat, size_t len, const char *lab)
{
	char buf[80];
	uint32_t x;
	size_t i;

	x = 0xDEADBEEF;						// silly checksum
	for (i = 0; i < len; i++) {
		x += (uint32_t) dat[i];
		x *= 0x01234567;
	}

	snprintf(buf, sizeof(buf), "%s\ttv %08X\t%s\t#%u\n",
		CRYPTO_ALGNAME, (unsigned) x, lab, (unsigned) len);
	my_print(buf);
}

//	print a line of "data"

void print_data(char *label, int res)
{
	char buf[80];

	snprintf(buf, sizeof(buf), "%s\t%s\t#%d\n", CRYPTO_ALGNAME, label, res);
	my_print(buf);
}

//	this stack probe both checks and fills the stack
//	it's hacky but I don't think that there is a "standard" way of doing this
//	(If you get 70000, just run it again.)

#ifndef STACK_MAX
#define STACK_MAX 70000
#endif
#ifndef STACK_FILL
#define STACK_FILL 0xD3
#endif

volatile uint8_t *sp;

static size_t stack_probe()
{
	register size_t used;
	volatile uint8_t sb;

	sp = &sb - STACK_MAX;
	for (used = STACK_MAX; used > 0; used--) {
		if (*sp != STACK_FILL)
			break;
		sp++;
	}
	while (sp < &sb) {
		*sp = STACK_FILL;
		sp++;
	}

	return used;
}


int test_stack()
{
	int i;
	static size_t kg, en, de;

	//	my simple "test vectors"

	for (i = 0; i < 48; i++)
		seed[i] = i;

	randombytes_init(seed, NULL, 256);

	//	test vectors and stack usage

	kg = stack_probe();
	crypto_kem_keypair(pk, sk);
	kg = stack_probe();
	crypto_kem_enc(ct, ss, pk);
	en = stack_probe();
	crypto_kem_dec(sr, ct, sk);
	de = stack_probe();

	print_data("stack bytes\tKG", kg);
	print_data("stack bytes\tEnc", en);
	print_data("stack bytes\tDec", de);

	print_tv(pk, CRYPTO_PUBLICKEYBYTES, "pk");
	print_tv(sk, CRYPTO_SECRETKEYBYTES, "sk");

	print_tv(ct, CRYPTO_CIPHERTEXTBYTES, "ct");
	print_tv(ss, CRYPTO_BYTES, "ss");
	print_tv(sr, CRYPTO_BYTES, "sr");

	return 0;
}

#include "keccakf1600.h"

//	speed benchmark

int test_speed()
{
	int i;
	uint64_t n, beg, kg, en, de;
	uint64_t t0, t1, t2, t3;

	// Keccak
	uint64_t st[25];

	for (i = 0; i < 25; i++) {
		st[i] = i;
	}

	// banner
	my_print("\t\t\t\t\t#");
	my_print(CRYPTO_ALGNAME);
	my_print("\n");

	// time permutation speed

	n = 0;
	t0 = get_cycles();
	do {

		for (i = 0; i < 100; i++) {
			keccak_f1600(st);
			keccak_f1600(st);
			keccak_f1600(st);
			keccak_f1600(st);
			keccak_f1600(st);
			n += 5;
		}
		t1 = get_cycles() - t0;
	} while (t1 < BENCH_TIMEOUT);

	print_data("permutation\tperm ", t1 / n);

	n = 0;
	kg = 0;
	en = 0;
	de = 0;

	beg = get_cycles();
	do {

		t0 = get_cycles();
		crypto_kem_keypair(pk, sk);
		t1 = get_cycles();
		crypto_kem_enc(ct, ss, pk);
		t2 = get_cycles();
		crypto_kem_dec(sr, ct, sk);
		t3 = get_cycles();

		// check correctness always
		if (memcmp(ss, sr, CRYPTO_BYTES) != 0)
			return -666;

		kg += t1 - t0;
		en += t2 - t1;
		de += t3 - t2;
		n++;

	} while ((t3 - beg) < BENCH_TIMEOUT);

	// scale to kilocycles in case of overflow
	n *= 1000;
	print_data("kilo cycles\tKG ", kg / n);
	print_data("kilo cycles\tEnc", en / n);
	print_data("kilo cycles\tDec", de / n);
	print_data("kilo cycles\tKEX", (kg + en + de) / n);

/*
	print_data("PK\t", CRYPTO_PUBLICKEYBYTES);
	print_data("SK\t", CRYPTO_SECRETKEYBYTES);
	print_data("CT\t", CRYPTO_CIPHERTEXTBYTES);
	print_data("SS\t", CRYPTO_BYTES);
	print_data("Xfr\t", CRYPTO_PUBLICKEYBYTES + CRYPTO_CIPHERTEXTBYTES);
*/

	return 0;
}

