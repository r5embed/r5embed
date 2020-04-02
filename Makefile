#	Makefile
#	2020-04-01	Markku-Juhani O. Saarinen <mjos@pqshield.com>
#   Copyright (c) 2020, PQShield Ltd.  All rights reserved.

#	export all variables to sub-makefiles
export				

BIN		= xtest
CSRC	= $(wildcard src/*.c)
SSRC	= $(wildcard src/*.S)
CSRC	+= test/mynistrng.c test/aesenc-1kt.c test/mygenkat_kem.c
OBJS	= $(CSRC:.c=.o) $(SSRC:.S=.o)
CC		= gcc
CFLAGS	?= -g -Wall -Wshadow -fsanitize=address,undefined -O2
CFLAGS	+= -Inist -Isrc -DR5ND_1CPA_5d
LIBS    =

default:
	@echo "Dummy makefile. Use ./test/testkat.sh to run a self-test."

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS) $(LIBS)

%.o:	%.[cS]
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJS) $(BIN) *~ src/*~ test/*~ *.req *.rsp

