#!/bin/bash

KEM_ND_5D="R5ND_1KEM_5d R5ND_3KEM_5d R5ND_5KEM_5d"
PKE_ND_5D="R5ND_1PKE_5d R5ND_3PKE_5d R5ND_5PKE_5d"

KEM_ND_0D="R5ND_1KEM_0d R5ND_3KEM_0d R5ND_5KEM_0d"
PKE_ND_0D="R5ND_1PKE_0d R5ND_3PKE_0d R5ND_5PKE_0d"

KEM_N1_0D="R5N1_1KEM_0d R5N1_3KEM_0d R5N1_5KEM_0d"
PKE_N1_0D="R5N1_1PKE_0d R5N1_3PKE_0d R5N1_5PKE_0d"

KEM_EXTRA="R5ND_0KEM_2iot R5ND_1KEM_4longkey"

# Command line ?

if [ ! -n "$1" ]
then
	TARGETS="$KEM_ND_5D $PKE_ND_5D $KEM_ND_0D $PKE_ND_0D $KEM_N1_0D $PKE_N1_0D  $KEM_EXTRA"
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

