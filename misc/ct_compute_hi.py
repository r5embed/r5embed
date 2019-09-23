#!/usr/bin/env python

#	ct_compute_hi.py
#	2018-09-21	Markku-Juhani O. Saarinen <mjos@pqshield.com>
#	Copyright (C) 2019, PQShield Ltd. Please see LICENSE.

#	Compute the number of iterations that the constant time sampler requires
#	so that the weight is "h" with probability 1-2^-128 (or other threshold)

import numpy as np
import mpmath as mp

# precision (in decimal digits) -- 100 is more than enough for fp > 2^-256

mp.mp.dps = 100

# base-2 logarithm string

def str_log2(x):
	x = mp.fabs(x)
	return ("2^" + mp.nstr(mp.log(x, 2), 6, strip_zeros=False)).ljust(12)

# given dimension d and weight h, determine number of "passes" required

def compute_hi(d, h, alg):

	# failure probability threshold 2^-128
	fp = mp.mpf(2)**(-128)

	# rejection rate of the uniform sampler part
	div = 65536 / d								# PARAMS_RS_DIV
	lim = div * d								# PARAMS_RS_LIM
	r = mp.mpf(lim)/mp.mpf(65536)

	#  bp[w] is the "Bernoulli" transition probabililiy from weight w to w+1
	bp = np.array([r * mp.mpf(d-i)/mp.mpf(d) for i in range(h)])

	# initial distribution is Pr(w=0) = 1, Pr(w>0) = 0
	wp = np.array([mp.mpf(0)] * (h+1))			# wp[i] = Pr(w=i)
	wp[0] = mp.mpf(1);

	# i is the number of passes
	for i in range(9999):

		# end condition; Pr(w=h) > 1-fp or equivalently Pr(w<h or w>h) < fp
		if (wp[h] > mp.mpf(1) - fp):
			break;

		# redistribute probability mass; can be done in place
		a = wp[0];
		wp[0] = mp.mpf(0);
		for j in range(h):
			b = wp[j + 1];
			wp[j] += (mp.mpf(1) - bp[j]) * a	# w unchanged probability
			wp[j + 1] = bp[j] * a				# w++ probability
			a = b
		wp[h] += b								# wp[h] mass does not decrease

	# verbose information
	print alg.ljust(20) + "d=" + str(d).ljust(6) + "h=" + str(h).ljust(6),
	print "hi=" + str(i).ljust(6) + "fp=" + str_log2(wp[0:h].sum())

	return i


#	parameters

compute_hi(618,	 104, "R5ND_1KEM_0d")
compute_hi(786,	 384, "R5ND_3KEM_0d")
compute_hi(1018, 428, "R5ND_5KEM_0d")
compute_hi(586,	 182, "R5ND_1PKE_0d")
compute_hi(852,	 212, "R5ND_3PKE_0d")
compute_hi(1170, 222, "R5ND_5PKE_0d")
compute_hi(490,	 162, "R5ND_1KEM_5d")
compute_hi(756,	 242, "R5ND_3KEM_5d")
compute_hi(940,	 414, "R5ND_5KEM_5d")
compute_hi(508,	 136, "R5ND_1PKE_5d")
compute_hi(756,	 242, "R5ND_3PKE_5d")
compute_hi(946,	 388, "R5ND_5PKE_5d")
compute_hi(594,	 238, "R5N1_1KEM_0d")
compute_hi(881,	 238, "R5N1_3KEM_0d")
compute_hi(1186, 712, "R5N1_5KEM_0d")
compute_hi(636,	 114, "R5N1_1PKE_0d")
compute_hi(876,	 446, "R5N1_3PKE_0d")
compute_hi(1217, 462, "R5N1_5PKE_0d")
compute_hi(372,	 178, "R5ND_0KEM_2iot")
compute_hi(490,	 162, "R5ND_1KEM_4longkey")

