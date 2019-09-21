#!/usr/bin/env python

#	ct_maxh.py
#	2018-09-21	Markku-Juhani O. Saarinen <mjos@pqshield.com>
#	Copyright (C) 2019, PQShield Ltd. Please see LICENSE.

#	Compute the number of iterations that the constant time sampler requires
#	so that the weight is "h" with probability 1-2^-128 (or other threshold)

import numpy as np
import mpmath as mp

# 	100 decimal digits of precision; more than enough
mp.mp.dps = 100

# base-2 logarithm string

def str_log2(x):
    x = mp.fabs(x)
    return ("2^" + mp.nstr(mp.log(x, 2), 6, strip_zeros=False)).ljust(12)

# precision (number of decimal digits) -- more than enough for fp > 2^-256

def maxh(d, h, alg):

	div = 65536 / d				# PARAMS_RS_DIV
	lim = div * d				# PARAMS_RS_LIM

	#	failure probability threshold
	fp = mp.mpf(2)**(-128)

	#	rejection rate of the uniform sampler part
	r = mp.mpf(lim)/mp.mpf(65536)

	#	initial distribution is P(w=0) = 1, P(w>0) = 0
	wp = np.array([mp.mpf(0)] * (h+1))
	wp[0] = mp.mpf(1);

	for i in range(9999):

		if (wp[h] > 1):
			print alg, "OVERFLOW"
			return -1;

		# end condition; P(w=h) > 1-fp and by implication P(w<h) < fp
		if (wp[h] > mp.mpf(1) - fp):
			break;

		# Bernoulli:
		p = r * mp.mpf(d-min(i,h))/mp.mpf(d)	# step
		q = mp.mpf(1) - p						# no step

		a = wp[0];								# probability convolution
		wp[0] = mp.mpf(0);
		for j in range(h):
			b = wp[j + 1];
			wp[j] += q * a
 			wp[j+1] = p * a
			a = b		
		wp[h] += a								# wp[h] mass does not decrease

	print alg.ljust(20), "\td", d, "\th", h, "\ti", i, "\tf", str_log2(wp[0:h].sum())

	return i


#	parameters

maxh(618,  104, "R5ND_1KEM_0d")
maxh(786,  384, "R5ND_3KEM_0d")
maxh(1018, 428, "R5ND_5KEM_0d")
maxh(586,  182, "R5ND_1PKE_0d")
maxh(852,  212, "R5ND_3PKE_0d")
maxh(1170, 222, "R5ND_5PKE_0d")
maxh(490,  162, "R5ND_1KEM_5d")
maxh(756,  242, "R5ND_3KEM_5d")
maxh(940,  414, "R5ND_5KEM_5d")
maxh(508,  136, "R5ND_1PKE_5d")
maxh(756,  242, "R5ND_3PKE_5d")
maxh(946,  388, "R5ND_5PKE_5d")
maxh(594,  238, "R5N1_1KEM_0d")
maxh(881,  238, "R5N1_3KEM_0d")
maxh(1186, 712, "R5N1_5KEM_0d")
maxh(636,  114, "R5N1_1PKE_0d")
maxh(876,  446, "R5N1_3PKE_0d")
maxh(1217, 462, "R5N1_5PKE_0d")
maxh(372,  178, "R5ND_0KEM_2iot")
maxh(490,  162, "R5ND_1KEM_4longkey")

