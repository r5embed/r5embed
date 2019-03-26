//	r5_dem.h
//	Copyright (c) 2019, PQShield Ltd. and Koninklijke Philips N.V.

#ifndef _R5_DEM_H_
#define _R5_DEM_H_

#include <stdint.h>
#include <stddef.h>


/**
 * Applies a DEM to the given message using the specified key.
 *
 * @param[out] c	  the encapsulated message
 * @param[out] c_len the length of the encapsulated message (`m_len` + 16 bytes)
 * @param[in]  key	  the key to use for the encapsulation
 * @param[in]  key_len the length of the key
 * @param[in]  m	  the message to encapsulate
 * @param[in]  m_len  the length of the message
 * @return __0__ in case of success
 */

int round5_dem(uint8_t *c, size_t *c_len,
				const uint8_t *key, size_t key_len,
				const uint8_t *m, size_t m_len);

/**
 * Inverses the application of a DEM to a message.
 *
 * @param[out] m	   the original message
 * @param[out] m_len   the length of the decapsulated message (`c2_len` - 16)
 * @param[in]  key	   the key to use for the encapsulation
 * @param[in]  key_len the length of the key
 * @param[in]  c	   the encapsulated message
 * @param[in]  c_len  the length of the encapsulated message
 * @return __0__ in case of success
 */

int round5_dem_inverse(uint8_t *m, size_t *m_len,
						const uint8_t *key, size_t key_len,
						const uint8_t *c, size_t c_len);

#endif /* _R5_DEM_H_ */
