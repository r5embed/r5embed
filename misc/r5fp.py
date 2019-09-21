#!/usr/bin/env python

#   r5fp.py
#   2018-08-25  Markku-Juhani O. Saarinen <mjos@iki.fi>

#   Error estimates for Round5 via convolutions.

import sys
import numpy as np
import mpmath as mp

from mp_fft import mp_conv

#   Recap of Round5
#   ---------------
#
#   q > p > t  are powers of 2
#   Rq = ring with coefficients mod q
#   Rp = ring with coefficients mod p
#
#   KeyGen
#
#       A = Uniform in Zq
#       S = Secret distribution
#       B = A * S mod Rq, rounded to Zp
#
#   Encrypt
#
#       R = Secret distribution
#       U = A * R mod Rq, rounded to Zp
#       X = B * R mod Rp
#
#   Decrypt
#
#       Y = U * S mod Rp
#
#   Let X' be X rounded to Zt
#   Decryption is a success if (X'*(q/p) - Y) rounded to Z2 is zero.
#
#   let eqp,eqp' = error introduced by q->p rounding
#            ept = error introduced by p->t rounding
#
#   X' = (A * S + eqp ) * R = A * R * S + eqp * R + ept
#   Y' = (A * R + eqp') * S = A * R * S + eqp' * S
#   (X' - Y') = eqp * R - eqp' * S + ept0

# precision (number of decimal digits) -- more than enough for fp > 2^-256
mp.mp.dps = 100

# epsilon in probability computations
prq_eps = mp.mpf(2)**(-300)

# just a (very precise) zero vector

def mp_zeros(l):
    return np.array([mp.mpf(0)] * l)

# base-2 logarithm string

def str_log2(x):
    x = mp.fabs(x)
    if x <= prq_eps:
        return "0".ljust(12)
    return ("2^" + mp.nstr(mp.log(x, 2), 6, strip_zeros=False)).ljust(12)

# gives variance, 1-sum = eps, and sum over "failure" range, as a string

def str_var(v):
    l = len(v)
    var = mp.mpf(0)
    eps = 1.0
    for i in range (-l/2,l/2):
        var += v[i] * (i * i)
        eps -= v[i]
    if mp.fabs(eps) > prq_eps:
        return "!!! eps=" + str_log2(eps)
        exit()

    return mp.nstr(var).ljust(12)

# gives variance, 1-sum = eps, and sum over "failure" range, as a string

def str_stats(v):
    l = len(v)
    return ("var=" + str_var(v) +
            "bfp=" + str_log2(v[(l/4):(3*l/4)].sum()))

# creates a distribution from list [h1, h2, .. ]. If only one [h], ternary.

def prq_h_distr(q, n, h):
    r = mp_zeros(q)
    r[0] = mp.mpf(n - np.asarray(h).sum()) / n
    i = 0
    for x in h:
        i += 1
        r[i] = mp.mpf(0.5) * x / n
        r[q - i] = mp.mpf(0.5) * x / n
    return r

# negate a distribution

def prq_neg(q, a):
    r = mp_zeros(q)
    r[0] = a[0]
    for i in range(1, q):
        r[q - i] = a[i]
    return r

# multiply two distributions mod q (convolution)

def prq_mul(q, a, b):
    r = mp_zeros(q)
    for i in range(q):
        if a[i] > prq_eps:
            for j in range(q):
                if b[j] > prq_eps:
                    r[(i * j) % q] += a[i] * b[j]
    return r

# add two distributions mod q (convolution)

def prq_add2(q, a, b):
    r = mp_zeros(q)
    for i in range(q):
        if a[i] > prq_eps:
            for j in range(q):
                r[(i + j) % q] += a[i] * b[j]
    return r

# add two distributions mod q (convolution)

def prq_add(q, a, b):
    if len(a) != q or len(b) != q:
        raise ValueError("input vector length must be q")
    if np.log2(q) % 1 > 0:
        return prq_add2(q, a, b)    # can't use FFT, use O(n^2) method
    else:
        return mp_conv(a, b)        # power-of 2, use FFT

# add a sum of m independent variables with same distribution to r

def prq_summ(q, r, a, m, verbose=False):

    t = 0
    u = 1

    # scalar multiplication
    while True:

        if (m & 1) == 1:
            r = prq_add(q, r, a)
            t += u
            if verbose:
                print "summ() add " + str(t).rjust(3) + ": " + str_stats(r)

        m >>= 1
        if m == 0:
            break
        a = prq_add(q, a, a)
        u = u + u
        if verbose:
            print "summ() dbl " + str(u).rjust(3) + ": var=" + str_var(a)

    return r

# error that corresponds to q->a->b rounding

def prq_rnderr(q, a, b):
    r = mp_zeros(q)

    for i in range(q):

        j = (i + ((q/a) >> 1)) % q      # round q->a
        j /= (q/a)
        j = (j + ((a/b) >> 1)) % a      # round a->b
        j /= (a/b)
        j *= (a/b)                      # round b->a
        j *= (q/a)                      # round a->q

        r[(q + i - j) % q] += 1.0 / q
    return r

# round (shorten) q->p

def prq_round(q, p, a):
    r = mp_zeros(p)
    for i in range(q):
        j = (i + ((q/p) >> 1)) % q
        j /= (q/p)
        r[j] += a[i]
    return r

# prettyprint ranges

def prq_print(v):
    q = len(v)
    first = -q/2
    prev = v[first + q]
    for j in range(-q/2 + 1, q/2 + 1):
        i = j
        if i < 0:
            i += q
        if j == q/2 or mp.fabs(v[i] - prev) > prq_eps:
            if prev > prq_eps:
                if first == j - 1:
                    s = str(first).center(16)
                else:
                    s = str(first).rjust(6) +  " .. " + str(j - 1).ljust(6)
                print s + "Pr: " + str_log2(prev) + mp.nstr(prev, 30)
            prev = v[i]
            first = j
    print


# failure probability computation

def round5_fp(d, n, h, q, p, t, f, mu, B, add_coeff=False, verbose=False):

    zerq = mp_zeros(q)                  # distribution Pr(X=0) = 1
    zerq[0] = mp.mpf(1)

    eqp = prq_rnderr(q, q, p)           # error from q->p rounding
    if verbose:
        print "q->p rounding".ljust(16) + str_stats(eqp)
        prq_print(eqp)

    dif = mp_zeros(q)                   # coefficient difference distribution
    dif[0] = mp.mpf(1)

    scale = 0
    for w in h:                         # w = weight of +-scale
        scale += 1
        if add_coeff:
            w = 2 * w                   # closer to 2 * w - 1 if h ~= w/2
        if verbose:
            print "w" + str(scale), "=", w

        s = mp_zeros(q)                 # get a secret distribution
        s[scale] = mp.mpf(0.5)
        s[-scale] = mp.mpf(0.5)
        es = prq_mul(q, s, eqp)         # secret * error
        if verbose:
            print "secret * error".ljust(16) + str_stats(es)
#            prq_print(es)

        dif = prq_summ(q, dif, es, w, verbose)  # es distribution added w times
        if verbose:
            print ("h" + str(scale) + " dif").ljust(16) + str_stats(dif)

    dif = prq_add(q, dif, dif)          # two of these, eqp * R and eqp * S
    if verbose:
        print "eqp*R + eqp'*S".ljust(16) + str_stats(dif)

    ept = prq_rnderr(q, p, t)           # error from p->t rounding
    if verbose:
        print "p->t rounding".ljust(16) + str_var(ept)

    dif = prq_add(q, dif, ept)
    if verbose:
        print "rounded p->t".ljust(16) + str_stats(dif)

    # Decryption failure ranges for case when parameter B>1
    up_fail = (q + (1<<B)) // (1<<(B+1))
    down_fail = (q * ((1<<(B+1)) - 1) + (1<<B)) // (1<<(B+1))

    bfp = dif[up_fail:down_fail].sum();

    if verbose:
        print "per bit failure probability:", str_log2(bfp)
        print bfp

    ffp = mp.mpf(0);
    for j in range(f + 1, mu + 1):
        ffp += (mp.binomial(mu, j) * mp.power(bfp, j) *
                mp.power(mp.mpf(1) - bfp, (mu - j)))

    if verbose:
        print "more than", f, "errors in", mu, "bits:", str_log2(ffp)
        print ffp

    return float(mp.log(ffp, 2))


'''
    Idea for "comb" convolutions is similar to polynomial multiplications:

         2**n-1           n-1
    X * ( SUM x^i ) = X * PROD  (x^(2**i) + 1)
          i=0             i=0

    Followed by a centering and mirroring etc.

    Algorithm is entirely additive so smaller mantissa precision is required.
'''

# comb length n, "scaling" d

def conv_comb(v, n, d):
    l = len(v)
    i = 1
    while i < n:
        v += np.roll(v, (d * i) % l)
        i <<= 1
    return v / n

# q->p rounding error multiplied with with +-i distribution

def conv_comb_qp(v, q, p, d):
    v = conv_comb(v, q / p, d);

    # center, mirror it
    v += np.roll(v, d)
    v = np.roll(v, q - (((d * (q / p)) / 2) % q))
    return v / 2

# p->t rounding

def conv_comb_pt(v, q, p, t):
    v = conv_comb(v, q / t, 1)
    # p->t via q->p just puts it at an angle
    v = np.roll(v, q - (((q / t) + (q / p)) / 2))
    return v

def round5_fp_fast(d, n, h, q, p, t, f, mu, B, add_coeff=False, verbose=False):

#   dif = mp_zeros(q)                   # full precision
#   dif[0] = mp.mpf(1.0)

    dif = np.zeros(q)                   # double precision approximation
    dif[0] = 1.0

    scale = 0
    for w in h:                         # w = weight of +-scale
        scale += 1
        if add_coeff:
            w = 2 * w                   # closer to 2 * w - 1 if h ~= w/2
        w *= 2                          # double it here; can use floats
        if verbose:
            print "\nw" + str(scale), "=", w

        for i in range(w):
            dif = conv_comb_qp(dif, q, p, scale)
            if verbose:
                sys.stdout.write('.')
                sys.stdout.flush()
    if verbose:
        print "done"

    # convert to mpf if we were double
    dif = np.array([mp.mpf(dif[i]) for i in range(len(dif))])
    dif /= dif.sum()                    # normalize, just in case

    if verbose:
        print "eqp*R + eqp'*S".ljust(16) + str_stats(dif)

    dif = conv_comb_pt(dif, q, p, t)
    if verbose:
        print "rounded p->t".ljust(16) + str_stats(dif)

    # Decryption failure ranges for case when parameter B>1
    up_fail = (q + (1<<B)) // (1<<(B+1))
    down_fail = (q*( (1<<(B+1)) - 1) + (1<<B)) // (1<<(B+1))

    bfp = dif[up_fail:down_fail].sum();

    if verbose:
        print "per bit failure probability:", str_log2(bfp)
        print bfp

    ffp = mp.mpf(0);
    for j in range(f + 1, mu + 1):
        ffp += (mp.binomial(mu, j) * mp.power(bfp, j) *
                mp.power(mp.mpf(1) - bfp, (mu - j)))

    if verbose:
        print "more than", f, "errors in", mu, "bits:", str_log2(ffp)
        print ffp

    return float(mp.log(ffp, 2))

'''
# my testing parameters

print "\n\nR5ND_EXPR:"
print round5_fp_fast(100, 100, [48, 12, 2], 2**12, 2**6, 2**4, 0, 96, 1, False, True)
print round5_fp(100, 100, [48, 12, 2], 2**12, 2**6, 2**4, 0, 96, 1, False, True)

print "R5ND_PILE:"
print round5_fp(100, 100, [50], 2**12, 2**6, 2**4, 0, 96, 1, True, True)
'''


