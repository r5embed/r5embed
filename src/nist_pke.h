//	nist_pke.h
//	Copyright (c) 2019, PQShield Ltd. and Koninklijke Philips N.V.

//	The NIST API for Public Key Encryption

#ifndef _NIST_PKE_H_
#define _NIST_PKE_H_

int crypto_encrypt_keypair(unsigned char *pk, unsigned char *sk);

int crypto_encrypt(unsigned char *c, unsigned long long *clen,
	const unsigned char *m, unsigned long long mlen,
	const unsigned char *pk);

int crypto_encrypt_open(unsigned char *m, unsigned long long *mlen,
	const unsigned char *c, unsigned long long clen,
	const unsigned char *sk);

#endif /* _NIST_PKE_H_ */
