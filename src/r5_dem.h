//	r5_dem.h
//	Copyright (c) 2019, PQShield Ltd. and Koninklijke Philips N.V.

//	Data Encapsulation Mechanism -- Authenticated Encryption

#ifndef _R5_DEM_H_
#define _R5_DEM_H_

#include <stdint.h>
#include <stddef.h>

//	Encrypt and add authentication information

int r5_dem_enc(uint8_t *c, size_t *c_len,
	const uint8_t *m, size_t m_len,
	const uint8_t *key, size_t key_len);

//	Decrypt and verify (nonzero on failure)

int r5_dem_dec(uint8_t *m, size_t *m_len,
	const uint8_t *c, size_t c_len,
	const uint8_t *key, size_t key_len);

#endif /* _R5_DEM_H_ */

