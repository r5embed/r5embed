//  xdump.c
//  2020-04-05  Markku-Juhani O. Saarinen <mjos@pqshield.com>
//  Copyright (c) 2020, PQShield Ltd. All rights reserved.

//  byte string checksum for debug traces

#ifdef XDX
#include <stdio.h>
#include "xdump.h"

void xdx_chk(const void *dat, size_t len, const char *lab)
{
	const uint8_t *v = dat;
	uint32_t x;
	size_t i;
	int ch;

	//  checksum
	x = 0xDEADBEEF;
	for (i = 0; i < len; i++) {
		x += (uint32_t) v[i];
		x *= 0x01234567;
	}

	//  little info
	printf("[XDX] %08X ", x);

	if (lab != NULL)
		printf("%6s ", lab);
	printf("[%5d] ", (int) len);

	for (i = 0; i < 16; i++) {
		if (i < len)
			printf("%02X", v[i]);
		else
			printf("  ");
	}

	printf(" ");

	for (i = 0; i < 16; i++) {
		if (i >= len)
			break;
		ch = v[i];
		if (ch >= 32 && ch < 127)
			putchar(ch);
		else
			putchar('.');
	}
	putchar('\n');
}

void xdx_hex(const void *dat, size_t len, const char *lab)
{
	const uint8_t *v = dat;
	uint32_t x;
	size_t i, j;
	int ch;

	//  checksum
	x = 0xDEADBEEF;
	for (i = 0; i < len; i++) {
		x += (uint32_t) v[i];
		x *= 0x01234567;
	}

	//  little info
	printf("[XDX] %08X ", x);

	if (lab != NULL)
		printf("%6s ", lab);
	printf("[%5d]\n", (int) len);

	for (i = 0; i < len; i += 16) {

		printf("[XHX] %6s %06X ", lab, (unsigned) i);

		for (j = 0; j < 16; j++) {
			if ((j & 3) == 0)
				putchar(' ');
			if (i + j < len)
				printf("%02X", v[i + j]);
			else
				printf("  ");
		}

		putchar(' ');

		for (j = 0; j < 16; j++) {

			if ((j & 3) == 0)
				putchar(' ');

			if (i + j < len) {
				ch = v[i + j];
				if (ch >= 32 && ch < 127)
					putchar(ch);
				else
					putchar('.');
			} else
				break;
		}
		putchar('\n');
	}
}

#endif										/* XDX */
