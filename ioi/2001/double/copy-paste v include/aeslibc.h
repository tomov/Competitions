//tva e in fact .h + .c


/* File: aeslibc.h
 * Copyright (c) 2001, IOI
 * Header file for aeslibc.c
 * GNU C/C++ library for task DOUBLE at IOI2001 Competition
 */

#ifndef __AESLIBC_H
#define __AESLIBC_H

#ifdef __cplusplus
extern "C" {
#endif

#define HEXSTRLEN	( 32 )
#define BLOCKLEN	( 16 )

typedef char HexStr [ HEXSTRLEN+1 ]; /* '0'..'9', 'A'..'F', '\0'-terminated */
typedef unsigned char Block [ BLOCKLEN ];  /* 128 bits */

void hexstr2block ( const HexStr hs, /* out-param */ Block b );
void block2hexstr ( const Block b, /* out-param */ HexStr hs );
void encrypt ( const Block p, const Block k, /* out-param */ Block c );
  /* c = E(p,k) */
void decrypt ( const Block c, const Block k, /* out-param */ Block p );
  /* p = D(c,k) */

#ifdef __cplusplus
}
#endif
#include	<stdio.h>
#include	<ctype.h>
#include	"aeslibc.h"

#define	HEXBITS	( 4 )
#define HEXBASE	( 1 << HEXBITS )

static int toint ( char c )
{
  if ('0' <= c && c <= '9') return c - '0';
  if ('A' <= c && c <= 'F') return c - 'A' + 10;
  if ('a' <= c && c <= 'f') return c - 'a' + 10;
  /* c is not a hexadecimal digit */
  fprintf ( stderr, "'%c' is not a hexadecimal digit\n", c );
  exit ( 201 );
}

void hexstr2block ( const HexStr hs, Block b )
{
  int i; /* to traverse b */
  int j; /* to traverse hs */
  unsigned char h;

  for (i=0; i!=BLOCKLEN; ++i) {
    b [ i ] = 0;
  }

  for (j=0; hs[j]; ++j) {
    h = toint ( hs[j] );
    if (j % 2 == 0) { /* most significant nibble */
      h <<= HEXBITS;
    }
    b [ j / 2 ] |= h;
  }

}

void block2hexstr ( const Block b, HexStr hs )
{
  int i; /* to traverse b */
  char* p = hs; /* to traverse hs */

  for (i=0; i!=BLOCKLEN; ++i) {
    sprintf ( p, "%02X", b[i] );
    p += 2;
  }

  *p = '\0';
}

#include	"rijndael-alg-fst.cpp"

void encrypt ( const Block p, const Block k, Block c )
  /* c = E(p,k) */
{
  u32 ek [ 4*(MAXNR+1) ];
  int nr;

  /* duplicated rijndael calls to equalize speed with Pascal library */
  nr = rijndaelKeySetupEnc ( ek, k, 128 );
  nr = rijndaelKeySetupEnc ( ek, k, 128 );
  rijndaelEncrypt ( ek, nr, p, c );
  rijndaelEncrypt ( ek, nr, p, c );
}

void decrypt ( const Block c, const Block k, Block p )
  /* p = D(c,k) */
{
  u32 ek [ 4*(MAXNR+1) ];
  int nr;

  /* duplicated rijndael calls to equalize speed with Pascal library */
  nr = rijndaelKeySetupDec ( ek, k, 128 );
  nr = rijndaelKeySetupDec ( ek, k, 128 );
  rijndaelDecrypt ( ek, nr, c, p );
  rijndaelDecrypt ( ek, nr, c, p );
}

/* End of file aeslibc.c */


#endif /* __AESLIBC_H */

/* End of file aeslibc.h */
