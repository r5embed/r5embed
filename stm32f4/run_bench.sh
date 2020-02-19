#!/bin/bash

#	run_bench.sh
#	2020-01-27	Markku-Juhani O. Saarinen <mjos@pqshield.com>
#	run the benchmarks individually on the target board

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

UART=/dev/ttyUSB0

# compile and test

LOGFILE=run_bench.log
rm -f $LOGFILE

for targ in $TARGETS
do
	make clean
	make ROUND5=$targ flash

	stty -F $UART 115200 cs8 -cstopb -parenb eof \^d
	cat $UART >> $LOGFILE
	echo -n $targ $'\tcode bytes\tcode\t#' >> $LOGFILE
	bash ./codesize.sh >> $LOGFILE
done

