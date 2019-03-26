#!/bin/bash

MYDIR=`pwd`
for targ in Implementation/*/*
do
	cd $targ
	gcc -o genkat *.c -lcrypto
	./genkat
	sha256sum *.rsp
	cd $MYDIR
done

