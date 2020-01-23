#!/bin/bash

#	Simple (quick) KAT/Correctness testing script.

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
#	TARGETS="$CPA_ND_5D $CPA_ND_0D $CPA_N1_0D $CPA_EXTRA"
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

CC=gcc
R5_SRC=src
CFLAGS="-march=native -Wall -Wextra -Wshadow -fsanitize=address,undefined -O2"
LIBS=""
TEST_MAIN=test/mygenkat_kem.c
RNG_SRC="test/mynistrng.c test/aesenc-1kt.c"
GOOD_KAT=test/good.kat
MYDIR=`pwd`

WORKD=`mktemp -d /tmp/r5test.XXXXXXXXXX`

for targ in $TARGETS
do
	rm -rf $WORKD/$targ
	mkdir -p $WORKD/$targ
	
	kat1=`grep $targ $GOOD_KAT`
	kat1=${kat1:0:64}

	cd $MYDIR
	$CC $CFLAGS -o $WORKD/$targ/genkat -D$targ -Inist -I$R5_SRC \
		$TEST_MAIN $RNG_SRC $R5_SRC/*.c $LIBS

	cd $WORKD/$targ
	./genkat
	cd ..

#	echo $WORKD/$targ

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

