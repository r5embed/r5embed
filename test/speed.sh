#!/bin/bash

#	speed.sh
#	2020-01-24	Markku-Juhani O. Saarinen <mjos@pqshield.com>
#	Simple speed test script. Also generates "small" test vectors.

CPA_ND_5D="R5ND_1CPA_5d R5ND_3CPA_5d R5ND_5CPA_5d"
CCA_ND_5D="R5ND_1CCA_5d R5ND_3CCA_5d R5ND_5CCA_5d"
CPA_ND_0D="R5ND_1CPA_0d R5ND_3CPA_0d R5ND_5CPA_0d"
CCA_ND_0D="R5ND_1CCA_0d R5ND_3CCA_0d R5ND_5CCA_0d"
CPA_N1_0D="R5N1_1CPA_0d R5N1_3CPA_0d R5N1_5CPA_0d"
CCA_N1_0D="R5N1_1CCA_0d R5N1_3CCA_0d R5N1_5CCA_0d"
CPA_EXTRA="R5ND_0CPA_2iot R5ND_1CPA_4longkey" 

# Command line ?

if [ ! -n "$1" ]
then
	TARGETS="$CPA_ND_5D $CCA_ND_5D $CPA_ND_0D $CCA_ND_0D $CPA_N1_0D $CCA_N1_0D $CPA_EXTRA"
else
	TARGETS=$@
fi

# compile and test

CC=gcc
R5_SRC=src
CFLAGS="-Wall -march=native -Ofast -DNDEBUG"
LIBS=""
TEST_MAIN=test/speed.c
RNG_SRC=test/myfastrng.c
MYDIR=`pwd`
WORKD=`mktemp -d /tmp/r5test.XXXXXXXXXX`

for targ in $TARGETS
do
	mkdir -p $WORKD/$targ
	
	cd $MYDIR
	$CC $CFLAGS -o $WORKD/$targ/speed -D$targ -Inist -I$R5_SRC \
		$TEST_MAIN $RNG_SRC $R5_SRC/*.c $LIBS
	$WORKD/$targ/speed
done

rm -rf $WORKD

