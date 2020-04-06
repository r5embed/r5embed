//  xdump.h
//  2020-04-05  Markku-Juhani O. Saarinen <mjos@pqshield.com>
//  Copyright (c) 2020, PQShield Ltd. All rights reserved.

//  byte string checksum for debug traces

#ifndef _XDUMP_H_
#define _XDUMP_H_

#ifdef XDX

#include <stdint.h>
#include <stddef.h>

void xdx_hex(const void *dat, size_t len, const char *lab);
void xdx_chk(const void *dat, size_t len, const char *lab);

#define XDXHEX(dat, len, lab) { xdx_hex(dat, len, lab); }
#define XDXCHK(dat, len, lab) { xdx_chk(dat, len, lab); }

#else

#define XDXHEX(dat, len, lab)				/* NOP */
#define XDXCHK(dat, len, lab)				/* NOP */

#endif										/* XDX */
#endif										/* _XDUMP_H_ */
