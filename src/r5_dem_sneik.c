//	r5_dem_sneik.c
//	2019-03-26	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (c) 2019, PQShield Ltd.

#ifdef BLNK2
#include "r5_parameter_sets.h"
#ifdef ROUND5_CCA_PKE
#include "blnk.h"

//	rate is set by secret size
#define SNEIKEN_RATE (BLNK_BLOCK - PARAMS_KAPPA_BYTES)

//	parameter definitions
#define CRYPTO_KEYBYTES PARAMS_KAPPA_BYTES
#define CRYPTO_NPUBBYTES 0
#define CRYPTO_ABYTES 16

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

//	The SNEIKEN AEAD as a DEM (Data Encapsulation Mechanism): "Encrypt"

int round5_dem(uint8_t *c, size_t *c_len,
	const uint8_t *key, size_t key_len,
	const uint8_t *m, size_t m_len)
{
	const uint8_t id[6] = { 'a', 'e',	//	Parameter set
		SNEIKEN_RATE, CRYPTO_KEYBYTES, CRYPTO_NPUBBYTES, CRYPTO_ABYTES };

	blnk_t	ctx;						//	Local state

	//	Clear state, set parameters
	blnk_clr(&ctx, SNEIKEN_RATE, SNEIKEN_ROUNDS);

	//	Key block: id | k | iv
	blnk_put(&ctx, BLNK_KEYF, id, sizeof(id));
	blnk_put(&ctx, BLNK_KEYF, key, key_len);
	//	blnk_put(&ctx, BLNK_KEYF, npub, CRYPTO_NPUBBYTES);
	blnk_fin(&ctx, BLNK_KEYF);

	//	Associated Data (full state)
	//	blnk_put(&ctx, BLNK_ADF, ad, (size_t) adlen);
	blnk_fin(&ctx, BLNK_ADF);			//	(No AD but still do a permutation)

	// Encrypt Message (this version doesn't handle overlap)
	blnk_enc(&ctx, BLNK_PTCT, c, m, m_len);
	blnk_fin(&ctx, BLNK_PTCT);

	//	Get MAC
	blnk_get(&ctx, BLNK_HASH, c + m_len, CRYPTO_ABYTES);

	//	blnk_fin(&ctx, BLNK_HASH);		//	Required for MAC-and-Continue

	*c_len = m_len + CRYPTO_ABYTES;		//	Store length

	return 0;							//	Success.
}


//	The SNEIKEN AEAD as a DEM (Data Encapsulation Mechanism): "Decrypt"

int round5_dem_inverse(uint8_t *m, size_t *m_len,
	const uint8_t *key, size_t key_len,
	const uint8_t *c, size_t c_len)
{
	const uint8_t id[6] = { 'a', 'e',	//	Parameter set
		SNEIKEN_RATE, CRYPTO_KEYBYTES, CRYPTO_NPUBBYTES, CRYPTO_ABYTES };
	blnk_t	ctx;						//	Local state

	if (c_len < CRYPTO_ABYTES)
		return -1;
	c_len -= CRYPTO_ABYTES;				//	c_len now holds m_len
	*m_len = c_len;

	//	Clear state, set parameters
	blnk_clr(&ctx, SNEIKEN_RATE, SNEIKEN_ROUNDS);

	//	Key block: id | k | iv
	blnk_put(&ctx, BLNK_KEYF, id, sizeof(id));
	blnk_put(&ctx, BLNK_KEYF, key, key_len);
	//	blnk_put(&ctx, BLNK_KEYF, npub, CRYPTO_NPUBBYTES);
	blnk_fin(&ctx, BLNK_KEYF);

	//	Associated Data (full state)
	//	blnk_put(&ctx, BLNK_ADF, ad, (size_t) adlen);
	blnk_fin(&ctx, BLNK_ADF);			//	(No AD but still do a permutation)

	//	Decrypt Message (can't handle overlap)
	blnk_dec(&ctx, BLNK_PTCT, m, c, c_len);
	blnk_fin(&ctx, BLNK_PTCT);

	//	Compare MAC
	if (blnk_cmp(&ctx, BLNK_HASH, c + c_len, CRYPTO_ABYTES) != 0)
		return -1;						//	Authentication failure

	//	blnk_fin(&ctx, BLNK_HASH);		//	Required for MAC-and-Continue

	return 0;							//	Success.
}

#endif /* ROUND5_CCA_PKE */
#endif /* BLNK2 */

