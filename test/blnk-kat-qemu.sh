#!/bin/bash

#	Simple (quick) KAT/Correctness testing script.

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
	TARGETS="$KEM_ND_5D $PKE_ND_5D $KEM_ND_0D $PKE_ND_0D $KEM_N1_0D $PKE_N1_0D $KEM_EXTRA"
else
	TARGETS=$@
fi

# if multiple arguments given, lauch them in parallel (fill all cores)

targs=( $TARGETS )
ntarg=${#targs[@]}

if [ $ntarg \> 1 ]
then
	for x in `seq 1 $ntarg`
	do
		$0 ${targs[$x - 1]} &
		pids[${x}]=$!
	done

	for pid in ${pids[@]}
	do
        wait $pid
	done
	echo "finished."
	exit
fi

# compile and test

#CC=gcc
#CC=clang
CC=arm-linux-gnueabihf-gcc 
#CC=aarch64-linux-gnu-gcc
#CC=mips-linux-gnu-gcc
#CC=powerpc-linux-gnu-gcc

R5_SRC=src
CFLAGS="-march=armv7-a -DARMV7_ASM -DNDEBUG -DBLNK2 -Wall -Ofast -static"
#CFLAGS="-Wall -Wextra -Wshadow -Ofast -static -DBLNK2"
LIBS=""
KEM_MAIN=test/mygenkat_kem.c
PKE_MAIN=test/mygenkat_pke.c
RNG_SRC=test/myfastrng.c
GOOD_KAT=test/good.blnk.kat
MYDIR=`pwd`

WORKD=`mktemp -d /tmp/r5test.XXXXXXXXXX`

for targ in $TARGETS
do
	rm -rf $WORKD/$targ
	mkdir -p $WORKD/$targ
	
	if [ "${targ:6:3}" = "KEM" ]
	then
		TEST_MAIN=$KEM_MAIN
	else
		TEST_MAIN=$PKE_MAIN
	fi

	kat1=`grep $targ $GOOD_KAT`
	kat1=${kat1:0:64}

	cd $MYDIR
	$CC $CFLAGS -o $WORKD/$targ/genkat -D$targ -Inist -I$R5_SRC \
		$TEST_MAIN $RNG_SRC $R5_SRC/*.c $R5_SRC/*.S $LIBS

	cd $WORKD/$targ
	./genkat
	cd ..

	kat2=`sha256sum $targ/*.rsp`
	kat2=${kat2:0:64}

	if [ "$kat1" = "$kat2" ]
	then
		echo $targ "OK"
	else
		echo "I want :" $kat1
		echo "I have :" $kat2
		echo $targ "FAIL"
	fi
done

rm -rf $WORKD

