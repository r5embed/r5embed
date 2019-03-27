//  r5_dem_aesgcm.c
//  Copyright (c) 2019, PQShield Ltd. and Koninklijke Philips N.V.

#ifndef BLNK2
#include "r5_parameter_sets.h"
#ifdef ROUND5_CCA_PKE

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "r5_dem.h"
#include "r5_xof.h"
#include "aesgcm.h"

//  Encrypt and add authentication information

int r5_dem_enc(uint8_t *c, size_t *c_len,
    const uint8_t *m, size_t m_len,
    const uint8_t *key, size_t key_len)
{
    uint8_t final_key_iv[32 + 12];
    const uint8_t * const iv = final_key_iv + key_len;

    assert(key_len == 16 || key_len == 24 || key_len == 32);

    //  process the input key to get a key/iv pair
    r5_xof(final_key_iv, (size_t) (key_len + 12), key, key_len);

    //  set ciphertext size
    *c_len = m_len + 16;

    switch (key_len) {
        case 16:
            aes128_enc_gcm(c, m, m_len, final_key_iv, iv);
            break;

        case 24:
            aes192_enc_gcm(c, m, m_len, final_key_iv, iv);
            break;

        case 32:
            aes256_enc_gcm(c, m, m_len, final_key_iv, iv);
            break;

        default:
            return -1;
    }

    return 0;
}

//  Decrypt and verify (nonzero on failure)

int r5_dem_dec(uint8_t *m, size_t *m_len,
    const uint8_t *c, size_t c_len,
    const uint8_t *key, size_t key_len)
{
    uint8_t final_key_iv[32 + 12];
    const uint8_t * const iv = final_key_iv + key_len;

    assert(key_len == 16 || key_len == 24 || key_len == 32);

    if (c_len < 16)
        return -1;
    *m_len = c_len - 16;

    //  process the input key to get a key/iv pair
    r5_xof(final_key_iv, (size_t) (key_len + 12), key, key_len);

    switch (key_len) {
        case 16:
            if (aes128_dec_vfy_gcm(m, c, c_len, final_key_iv, iv))
                return -1;
            break;

        case 24:
            if (aes192_dec_vfy_gcm(m, c, c_len, final_key_iv, iv))
                return -1;
            break;

        case 32:
            if (aes256_dec_vfy_gcm(m, c, c_len, final_key_iv, iv))
                return -1;
            break;
    }

    return 0;
}

#endif /* ROUND5_CCA_PKE */
#endif /* !BLNK2 */
