//  keccakf1600.c
//  2020-04-01  Markku-Juhani O. Saarinen <mjos@pqshield.com>


//  Flag for alternative implementation: keccakf1600_armv7m.S

#if !defined(ARMV7_ASM)

/* Based on the public domain implementation in
 * crypto_hash/keccakc512/simple/ from http://bench.cr.yp.to/supercop.html
 * by Ronny Van Keer
 * and the public domain "TweetFips202" implementation
 * from https://twitter.com/tweetfips202
 * by Gilles Van Assche, Daniel J. Bernstein, and Peter Schwabe */

#include <stdint.h>
#include <stddef.h>

#include <assert.h>
#include "keccakf1600.h"

#define NROUNDS 24
#define ROL64(a, offset) ((a << offset) ^ (a >> (64-offset)))

//  little endian helpers

static inline uint64_t le_get64(const uint8_t * x)
{
	return ((uint64_t) x[0]) | (((uint64_t) x[1]) << 8)
		| (((uint64_t) x[2]) << 16) | (((uint64_t) x[3]) << 24)
		| (((uint64_t) x[4]) << 32) | (((uint64_t) x[5]) << 40)
		| (((uint64_t) x[6]) << 48) | (((uint64_t) x[7]) << 56);
}

static inline void le_put64(uint8_t * x, uint64_t u)
{
	x[0] = u;
	x[1] = u >> 8;
	x[2] = u >> 16;
	x[3] = u >> 24;
	x[4] = u >> 32;
	x[5] = u >> 40;
	x[6] = u >> 48;
	x[7] = u >> 56;
}

void keccak_extract(uint64_t * state, uint8_t * data, size_t offset,
					size_t length)
{
	size_t i;

	(void) offset;							//  kill warning

	for (i = 0; i < length / 8; i++) {
		le_put64(data + 8 * i, state[i]);
	}
}

void keccak_xorbytes(uint64_t * state, const uint8_t * data, size_t offset,
					 size_t length)
{
	size_t i;

	(void) offset;							//  kill warning

	for (i = 0; i < length / 8; ++i) {
		state[i] ^= le_get64(data + 8 * i);
	}
}

//  Keccak-f1600 permutation

void keccak_f1600(uint64_t state[25])
{
	//  round constants

	const uint64_t rc[NROUNDS] = {
		0x0000000000000001, 0x0000000000008082, 0x800000000000808A,
		0x8000000080008000, 0x000000000000808B, 0x0000000080000001,
		0x8000000080008081, 0x8000000000008009, 0x000000000000008A,
		0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
		0x000000008000808B, 0x800000000000008B, 0x8000000000008089,
		0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
		0x000000000000800A, 0x800000008000000A, 0x8000000080008081,
		0x8000000000008080, 0x0000000080000001, 0x8000000080008008
	};

	int round;

	uint64_t Aba, Abe, Abi, Abo, Abu;
	uint64_t Aga, Age, Agi, Ago, Agu;
	uint64_t Aka, Ake, Aki, Ako, Aku;
	uint64_t Ama, Ame, Ami, Amo, Amu;
	uint64_t Asa, Ase, Asi, Aso, Asu;
	uint64_t BCa, BCe, BCi, BCo, BCu;
	uint64_t Da, De, Di, Do, Du;
	uint64_t Eba, Ebe, Ebi, Ebo, Ebu;
	uint64_t Ega, Ege, Egi, Ego, Egu;
	uint64_t Eka, Eke, Eki, Eko, Eku;
	uint64_t Ema, Eme, Emi, Emo, Emu;
	uint64_t Esa, Ese, Esi, Eso, Esu;

	//copyFromState(A, state)
	Aba = state[0];
	Abe = state[1];
	Abi = state[2];
	Abo = state[3];
	Abu = state[4];
	Aga = state[5];
	Age = state[6];
	Agi = state[7];
	Ago = state[8];
	Agu = state[9];
	Aka = state[10];
	Ake = state[11];
	Aki = state[12];
	Ako = state[13];
	Aku = state[14];
	Ama = state[15];
	Ame = state[16];
	Ami = state[17];
	Amo = state[18];
	Amu = state[19];
	Asa = state[20];
	Ase = state[21];
	Asi = state[22];
	Aso = state[23];
	Asu = state[24];

	for (round = 0; round < NROUNDS; round += 2) {

		//    prepareTheta
		BCa = Aba ^ Aga ^ Aka ^ Ama ^ Asa;
		BCe = Abe ^ Age ^ Ake ^ Ame ^ Ase;
		BCi = Abi ^ Agi ^ Aki ^ Ami ^ Asi;
		BCo = Abo ^ Ago ^ Ako ^ Amo ^ Aso;
		BCu = Abu ^ Agu ^ Aku ^ Amu ^ Asu;

		//thetaRhoPiChiIotaPrepareTheta(round  , A, E)
		Da = BCu ^ ROL64(BCe, 1);
		De = BCa ^ ROL64(BCi, 1);
		Di = BCe ^ ROL64(BCo, 1);
		Do = BCi ^ ROL64(BCu, 1);
		Du = BCo ^ ROL64(BCa, 1);

		Aba ^= Da;
		BCa = Aba;
		Age ^= De;
		BCe = ROL64(Age, 44);
		Aki ^= Di;
		BCi = ROL64(Aki, 43);
		Amo ^= Do;
		BCo = ROL64(Amo, 21);
		Asu ^= Du;
		BCu = ROL64(Asu, 14);
		Eba = BCa ^ ((~BCe) & BCi);
		Eba ^= (uint64_t) rc[round];
		Ebe = BCe ^ ((~BCi) & BCo);
		Ebi = BCi ^ ((~BCo) & BCu);
		Ebo = BCo ^ ((~BCu) & BCa);
		Ebu = BCu ^ ((~BCa) & BCe);

		Abo ^= Do;
		BCa = ROL64(Abo, 28);
		Agu ^= Du;
		BCe = ROL64(Agu, 20);
		Aka ^= Da;
		BCi = ROL64(Aka, 3);
		Ame ^= De;
		BCo = ROL64(Ame, 45);
		Asi ^= Di;
		BCu = ROL64(Asi, 61);
		Ega = BCa ^ ((~BCe) & BCi);
		Ege = BCe ^ ((~BCi) & BCo);
		Egi = BCi ^ ((~BCo) & BCu);
		Ego = BCo ^ ((~BCu) & BCa);
		Egu = BCu ^ ((~BCa) & BCe);

		Abe ^= De;
		BCa = ROL64(Abe, 1);
		Agi ^= Di;
		BCe = ROL64(Agi, 6);
		Ako ^= Do;
		BCi = ROL64(Ako, 25);
		Amu ^= Du;
		BCo = ROL64(Amu, 8);
		Asa ^= Da;
		BCu = ROL64(Asa, 18);
		Eka = BCa ^ ((~BCe) & BCi);
		Eke = BCe ^ ((~BCi) & BCo);
		Eki = BCi ^ ((~BCo) & BCu);
		Eko = BCo ^ ((~BCu) & BCa);
		Eku = BCu ^ ((~BCa) & BCe);

		Abu ^= Du;
		BCa = ROL64(Abu, 27);
		Aga ^= Da;
		BCe = ROL64(Aga, 36);
		Ake ^= De;
		BCi = ROL64(Ake, 10);
		Ami ^= Di;
		BCo = ROL64(Ami, 15);
		Aso ^= Do;
		BCu = ROL64(Aso, 56);
		Ema = BCa ^ ((~BCe) & BCi);
		Eme = BCe ^ ((~BCi) & BCo);
		Emi = BCi ^ ((~BCo) & BCu);
		Emo = BCo ^ ((~BCu) & BCa);
		Emu = BCu ^ ((~BCa) & BCe);

		Abi ^= Di;
		BCa = ROL64(Abi, 62);
		Ago ^= Do;
		BCe = ROL64(Ago, 55);
		Aku ^= Du;
		BCi = ROL64(Aku, 39);
		Ama ^= Da;
		BCo = ROL64(Ama, 41);
		Ase ^= De;
		BCu = ROL64(Ase, 2);
		Esa = BCa ^ ((~BCe) & BCi);
		Ese = BCe ^ ((~BCi) & BCo);
		Esi = BCi ^ ((~BCo) & BCu);
		Eso = BCo ^ ((~BCu) & BCa);
		Esu = BCu ^ ((~BCa) & BCe);

		//    prepareTheta
		BCa = Eba ^ Ega ^ Eka ^ Ema ^ Esa;
		BCe = Ebe ^ Ege ^ Eke ^ Eme ^ Ese;
		BCi = Ebi ^ Egi ^ Eki ^ Emi ^ Esi;
		BCo = Ebo ^ Ego ^ Eko ^ Emo ^ Eso;
		BCu = Ebu ^ Egu ^ Eku ^ Emu ^ Esu;

		//thetaRhoPiChiIotaPrepareTheta(round+1, E, A)
		Da = BCu ^ ROL64(BCe, 1);
		De = BCa ^ ROL64(BCi, 1);
		Di = BCe ^ ROL64(BCo, 1);
		Do = BCi ^ ROL64(BCu, 1);
		Du = BCo ^ ROL64(BCa, 1);

		Eba ^= Da;
		BCa = Eba;
		Ege ^= De;
		BCe = ROL64(Ege, 44);
		Eki ^= Di;
		BCi = ROL64(Eki, 43);
		Emo ^= Do;
		BCo = ROL64(Emo, 21);
		Esu ^= Du;
		BCu = ROL64(Esu, 14);
		Aba = BCa ^ ((~BCe) & BCi);
		Aba ^= (uint64_t) rc[round + 1];
		Abe = BCe ^ ((~BCi) & BCo);
		Abi = BCi ^ ((~BCo) & BCu);
		Abo = BCo ^ ((~BCu) & BCa);
		Abu = BCu ^ ((~BCa) & BCe);

		Ebo ^= Do;
		BCa = ROL64(Ebo, 28);
		Egu ^= Du;
		BCe = ROL64(Egu, 20);
		Eka ^= Da;
		BCi = ROL64(Eka, 3);
		Eme ^= De;
		BCo = ROL64(Eme, 45);
		Esi ^= Di;
		BCu = ROL64(Esi, 61);
		Aga = BCa ^ ((~BCe) & BCi);
		Age = BCe ^ ((~BCi) & BCo);
		Agi = BCi ^ ((~BCo) & BCu);
		Ago = BCo ^ ((~BCu) & BCa);
		Agu = BCu ^ ((~BCa) & BCe);

		Ebe ^= De;
		BCa = ROL64(Ebe, 1);
		Egi ^= Di;
		BCe = ROL64(Egi, 6);
		Eko ^= Do;
		BCi = ROL64(Eko, 25);
		Emu ^= Du;
		BCo = ROL64(Emu, 8);
		Esa ^= Da;
		BCu = ROL64(Esa, 18);
		Aka = BCa ^ ((~BCe) & BCi);
		Ake = BCe ^ ((~BCi) & BCo);
		Aki = BCi ^ ((~BCo) & BCu);
		Ako = BCo ^ ((~BCu) & BCa);
		Aku = BCu ^ ((~BCa) & BCe);

		Ebu ^= Du;
		BCa = ROL64(Ebu, 27);
		Ega ^= Da;
		BCe = ROL64(Ega, 36);
		Eke ^= De;
		BCi = ROL64(Eke, 10);
		Emi ^= Di;
		BCo = ROL64(Emi, 15);
		Eso ^= Do;
		BCu = ROL64(Eso, 56);
		Ama = BCa ^ ((~BCe) & BCi);
		Ame = BCe ^ ((~BCi) & BCo);
		Ami = BCi ^ ((~BCo) & BCu);
		Amo = BCo ^ ((~BCu) & BCa);
		Amu = BCu ^ ((~BCa) & BCe);

		Ebi ^= Di;
		BCa = ROL64(Ebi, 62);
		Ego ^= Do;
		BCe = ROL64(Ego, 55);
		Eku ^= Du;
		BCi = ROL64(Eku, 39);
		Ema ^= Da;
		BCo = ROL64(Ema, 41);
		Ese ^= De;
		BCu = ROL64(Ese, 2);
		Asa = BCa ^ ((~BCe) & BCi);
		Ase = BCe ^ ((~BCi) & BCo);
		Asi = BCi ^ ((~BCo) & BCu);
		Aso = BCo ^ ((~BCu) & BCa);
		Asu = BCu ^ ((~BCa) & BCe);
	}

	//copyToState(state, A)
	state[0] = Aba;
	state[1] = Abe;
	state[2] = Abi;
	state[3] = Abo;
	state[4] = Abu;
	state[5] = Aga;
	state[6] = Age;
	state[7] = Agi;
	state[8] = Ago;
	state[9] = Agu;
	state[10] = Aka;
	state[11] = Ake;
	state[12] = Aki;
	state[13] = Ako;
	state[14] = Aku;
	state[15] = Ama;
	state[16] = Ame;
	state[17] = Ami;
	state[18] = Amo;
	state[19] = Amu;
	state[20] = Asa;
	state[21] = Ase;
	state[22] = Asi;
	state[23] = Aso;
	state[24] = Asu;
}

#endif										/* !ARMV7_ASM */
