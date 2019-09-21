#!/usr/bin/env python

#  r5fp_run.py
#  2018-08-25  Markku-Juhani O. Saarinen <mjos@iki.fi>

from r5fp import round5_fp, round5_fp_fast

f = 0
fp_computer = round5_fp_fast
verbose = False


#print "\n\nR5ND_1KEM:"
#print fp_computer(522, 522, [208], 2**14, 2**8, 2**4, f, 128+91, 1, True, verbose)

#print "\n\nR5ND_3KEM:"
#print fp_computer(756, 756, [242], 2**15, 2**8, 2**4, f, 192+103, 1, True, verbose)

#print "\n\nR5ND_5KEM:"
#print fp_computer(1018, 1018, [254], 2**15, 2**8, 2**4, f, 256+121, 1, True, verbose)

#print "\n\nR5ND_1PKE:"
#print fp_computer(546, 546, [158], 2**16, 2**8, 2**4, f, 128+91, 1, True, verbose)

#print "\n\nR5ND_3PKE:"
#print fp_computer(786,  786, [204], 2**16, 2**8, 2**6, f, 192+103, 1, True, verbose)

#print "\n\nR5ND_5PKE:"
#print fp_computer(1108, 1108, [198], 2**16, 2**8, 2**5, f, 256+121, 1, True, verbose)


#print "\n\nR2ND_1KEM:"
#print fp_computer(618,618,[104],2**11,2**8,2**4, f, 128+91, 1, True, verbose)

#print "\n\nR2ND_3KEM:"
#print fp_computer(786,786,[384],2**13,2**9,2**4, f, 192+103, 1, True, verbose)

#print "\n\nR2ND_5KEM:"
#print fp_computer(1018,1018,[428],2**14,2**9,2**4, f, 256+121, 1, True, verbose)

#print "\n\nR2ND_1PKE:"
#print fp_computer(586,586,[182],2**13,2**9,2**4, f, 128+91, 1, True, verbose)

#print "\n\nR2ND_3PKE:"
#print fp_computer(852,852,[212],2**12,2**9,2**5, f, 192+103, 1, True, verbose)

#print "\n\nR2ND_5PKE:"
#print fp_computer(1090,1090,[480],2**16,2**10,2**3, f, 256+121, 1, True, verbose)


f = 5
print "\n\nR5ND+_1KEM:"
print fp_computer(490,490,[162],2**10,2**7,2**3, f, 128+205, 1, False, verbose)

print "\n\nR5ND+_3KEM:"
print fp_computer(756,756,[242],2**12,2**8,2**2, f, 192+231, 1, False, verbose)

print "\n\nR5ND+_5KEM:"
print fp_computer(940,940,[414],2**12,2**8,2**2, f, 256+234, 1, False, verbose)

print "\n\nR5ND+_1PKE:"
print fp_computer(508,508,[136],2**10,2**7,2**4, f, 128+205, 1, False, verbose)

print "\n\nR5ND+_3PKE:"
print fp_computer(756,756,[242],2**12,2**8,2**3, f, 192+231, 1, False, verbose)

print "\n\nR5ND+_5PKE:"
print fp_computer(940,940,[414],2**12,2**8,2**3, f, 256+234, 1, False, verbose)


#print "\n\nR5T_1KEM:"
#print fp_computer(635, 1, [266], 2**15, 2**11, 2**10, 0, 32, 4, False, verbose)

#print "\n\nR5T_3KEM:"
#print fp_computer(929, 1, [268], 2**14, 2**11, 2**10, 0, 48, 4, False, verbose)

#print "\n\nR5T_5KEM:"
#print fp_computer(1186, 1, [712], 2**14, 2**12, 2**7, 0, 64, 4, False, verbose)

#print "\n\nR5T_1PKE:"
#print fp_computer(694, 1, [152], 2**13, 2**11, 2**10, 0, 32, 4, False, verbose)

#print "\n\nR5T_3PKE:"
#print fp_computer(932, 1, [540], 2**14, 2**12, 2**9, 0, 48, 4, False, verbose)

#print "\n\nR5T_5PKE:"
#print fp_computer(1198, 1, [574], 2**14, 2**12, 2**10, 0, 64, 4, False, verbose)
