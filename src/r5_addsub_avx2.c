//  r5_addsub_avx2.c
//  Copyright (c) 2019, PQShield Ltd.

//  Addition-subtraction loops.  Some basic AVX2 optimizations.

#include "r5_parameter_sets.h"
#include "r5_addsub.h"

#ifdef __AVX2__
#include <immintrin.h>

void r5_modq_addsub_d(modq_t *dst,
    const modq_t *p_add, const modq_t *p_sub)
{
    size_t i;

    __m256i t, u;
    for (i = 0; i < PARAMS_D - 15; i += 16) {
        t = _mm256_loadu_si256((__m256i *) &p_add[i]);
        u = _mm256_loadu_si256((__m256i *) &p_sub[i]);
        t = _mm256_sub_epi16(t, u);
        u = _mm256_loadu_si256((__m256i *) &dst[i]);
        t = _mm256_add_epi16(t, u);
        _mm256_storeu_si256((__m256i *) &dst[i], t);
    }

    for (; i < PARAMS_D; i++) {
        dst[i] += p_add[i] - p_sub[i];
    }
}

void r5_modq_addsub3_d(modq_t *dst,
    const modq_t *p_add1, const modq_t *p_sub1,
    const modq_t *p_add2, const modq_t *p_sub2,
    const modq_t *p_add3, const modq_t *p_sub3)
{
    size_t i;

    __m256i t, u;
    for (i = 0; i < PARAMS_D - 15; i += 16) {
        t = _mm256_loadu_si256((__m256i *) &dst[i]);
        u = _mm256_loadu_si256((__m256i *) &p_add1[i]);
        t = _mm256_add_epi16(t, u);
        u = _mm256_loadu_si256((__m256i *) &p_sub1[i]);
        t = _mm256_sub_epi16(t, u);
        u = _mm256_loadu_si256((__m256i *) &p_add2[i]);
        t = _mm256_add_epi16(t, u);
        u = _mm256_loadu_si256((__m256i *) &p_sub2[i]);
        t = _mm256_sub_epi16(t, u);
        u = _mm256_loadu_si256((__m256i *) &p_add3[i]);
        t = _mm256_add_epi16(t, u);
        u = _mm256_loadu_si256((__m256i *) &p_sub3[i]);
        t = _mm256_sub_epi16(t, u);
        _mm256_storeu_si256((__m256i *) &dst[i], t);
    }

    for (; i < PARAMS_D; i++) {
        dst[i] += p_add1[i] - p_sub1[i]
                + p_add2[i] - p_sub2[i]
                + p_add3[i] - p_sub3[i];
    }
}

#endif
