#	Makefile
#	2020-04-01	Markku-Juhani O. Saarinen <mjos@pqshield.com>
#   Copyright (c) 2020, PQShield Ltd.  All rights reserved.

#	export all variables to sub-makefiles
export				

BIN		= xtest
#CSRC	= $(wildcard src/*.c)
#SSRC	= $(wildcard src/*.S)
#CSRC	+= test/mynistrng.c test/aesenc-1kt.c test/mygenkat_kem.c
CSRC	= src/keccakf1600.c src/r5_xof.c test/test_tuplehash.c
OBJS	= $(CSRC:.c=.o) $(SSRC:.S=.o)
CC		= gcc
CFLAGS	?= -g -Wall -Wshadow -fsanitize=address,undefined -O2
CFLAGS	+= -Inist -Isrc -DR5ND_1CCA_5d -DXDBX
LIBS    =

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS) $(LIBS)

%.o:	%.[cS]
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJS) $(BIN) *~ src/*~ test/*~ *.req *.rsp
#	cd subdir && $(MAKE) clean

