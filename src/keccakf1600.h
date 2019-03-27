//  keccakf1600.h
//  Raw Keccak f-1600 interface. (Derived From public domain sources.)

#ifndef _KECCAKF1600_H_
#define _KECCAKF1600_H_

#include <stdint.h>
#include <stddef.h>

void KeccakF1600_StateExtractBytes(uint64_t *state,
    uint8_t *data, size_t offset, size_t length);
void KeccakF1600_StateXORBytes(uint64_t *state,
    const uint8_t *data, size_t offset, size_t length);
void KeccakF1600_StatePermute(uint64_t * state);

#endif /* _KECCAKF1600_H_ */

