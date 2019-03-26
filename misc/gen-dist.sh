#!/bin/bash

KEM_ND_5D="R5ND_1KEM_5d R5ND_3KEM_5d R5ND_5KEM_5d"
PKE_ND_5D="R5ND_1PKE_5d R5ND_3PKE_5d R5ND_5PKE_5d"

KEM_N1_0D="R5N1_1KEM_0d R5N1_3KEM_0d R5N1_5KEM_0d"
PKE_N1_0D="R5N1_1PKE_0d R5N1_3PKE_0d R5N1_5PKE_0d"

KEM_ND_0D="R5ND_1KEM_0d R5ND_3KEM_0d R5ND_5KEM_0d"
PKE_ND_0D="R5ND_1PKE_0d R5ND_3PKE_0d R5ND_5PKE_0d"

KEM_EXTRA="R5ND_0KEM_2iot R5ND_1KEM_4longkey" 

# Command line ?

if [ ! -n "$1" ]
then
	TARGETS="$KEM_ND_5D $PKE_ND_5D $KEM_N1_0D $PKE_N1_0D $KEM_ND_0D $PKE_ND_0D $KEM_EXTRA"
else
	TARGETS=$@
fi

# compile and test

CC=gcc
R5_SRC=src
CFLAGS="-Wall -O"
LIBS="-lkeccak -lcrypto"
TEST_MAIN=misc/gen_api_h.c
RNG_SRC=test/myfastrng.c
MYDIR=`pwd`
NIST_RNG="nist/rng.c nist/rng.h"

WORKD=`mktemp -d /tmp/r5test.XXXXXXXXXX`

for targ in $TARGETS
do
	mkdir -p $WORKD/$targ

	if [ "${targ:6:3}" = "KEM" ]
	then
		OUT_DIR=Implementation/kem/$targ
		PROTO=misc/kem_proto.h
		NIST_GEN=nist/PQCgenKAT_kem.c
	else
		OUT_DIR=Implementation/encrypt/$targ
		PROTO=misc/encrypt_proto.h
		NIST_GEN=nist/PQCgenKAT_encrypt.c
	fi

	mkdir -p $OUT_DIR
	cp -r src/* $OUT_DIR
    cp -r $NIST_GEN $OUT_DIR
	cp -r $NIST_RNG $OUT_DIR
	echo "#define" $targ > $OUT_DIR/round5_variant_setting.h

	gcc $CFLAGS -o $WORKD/$targ/api -D$targ -Inist -I$R5_SRC \
		$TEST_MAIN $RNG_SRC $R5_SRC/*.c $LIBS
	$WORKD/$targ/api | tee $OUT_DIR/api.h
	cat $PROTO >> $OUT_DIR/api.h
done

rm -rf $WORKD

