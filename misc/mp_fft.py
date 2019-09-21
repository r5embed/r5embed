#!/usr/bin/env python

#   mp_fft.py
#   2018-08-25  Markku-Juhani O. Saarinen <mjos@iki.fi>

#   high-precision convolutions with FFT. Original adopted via apfft from
#   https://jakevdp.github.io/blog/2013/08/28/understanding-the-fft/

import numpy as np
import mpmath as mp

mp_real = np.vectorize(mp.re)

# FFT and inverse FFT using mpmath

def mp_fft(v, inv_fft=False):

    n = v.shape[0]
    if n == 1:
        return v

    if np.log2(n) % 1 > 0:
        raise ValueError("size of b must be a power of 2")

    # inverse op changes this sign, and scaling at the end
    s_pi = mp.pi * mp.mpc(1j)
    if not inv_fft:
        s_pi = -s_pi

    m = np.array([ [mp.mpc(1), mp.mpc(1)], [mp.mpc(1), mp.mpc(-1)] ])
    m = m.dot(v.reshape((2, -1)))

    # build-up each level of the recursive calculation all at once
    while m.shape[0] < n:
        m_even = m[:, :m.shape[1] / 2]
        m_odd = m[:, m.shape[1] / 2:]
        l = m.shape[0]
        w = mp.exp(s_pi / mp.mpf(l));
        a = np.empty(l, dtype=mp.mpc)
        x = mp.mpc(1)
        for i in range(l - 1):
            a[i] = x;
            x *= w
        a[l - 1] = x
        a = a[:, None]
        m = np.vstack([m_even + a * m_odd,
                       m_even - a * m_odd])

    # scale the result if inverse
    if inv_fft:
        m /= mp.mpf(n)

    return m.ravel()

# convolution on arrays with FFT

def mp_conv(x, y):
    xy = mp_fft(x, False) * mp_fft(y, False)
    xy = mp_fft(xy, True)
    return mp_real(xy)


# -- test code --

# equivalent exhaustive method for testing

def mp_conv2(x, y):
    l = x.shape[0]
    r = np.array([mp.mpf(0)] * l)
    for i in range(l):
        for j in range(l):
            r[(i + j) % l] += x[i] * y[j]
    return mp_real(r)

# a vector of random numbers, scaled to sum up to 1

def mp_rand_dist(l):
    v = np.array([mp.rand() for i in range(l)])
    return v / v.sum()

# returns a very small number if fft works

def test_fft():
    n = 2**10
    a = mp_rand_dist(n)
    b = mp_rand_dist(n)
    c = mp_conv(a, b)
    d = mp_conv2(a, b)
    eps = 0
    for i in range(n):
        eps = max(eps, mp.fabs(c[i] - d[i]))
    return eps

# run the test
mp.mp.dps = 100
print test_fft()

