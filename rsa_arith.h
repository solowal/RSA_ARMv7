/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Multiplication/Squaring 512-bit
 */

#ifndef RSA_ARITH_H
#define RSA_ARITH_H

//#include "mul.h"
//#include "arith.h"

#include "kara_mul.h"
#include "kara_sqr.h"
#include "mont512.h"
#include "mont1024.h"
#include "mul.h"
#include "sqr.h"




#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>




// The header file inttypes.h is part of the ANSI C99 standard and contains
// definitions for fixed-width integer types such as int16_t, int32_t, or
// int64_t.  However, if inttypes.h is not available (e.g. MS Visual C), we
// have to define these types ourselves.  The following code does this.


#include <inttypes.h>

typedef int8_t   INT8;
typedef uint8_t  UINT8;
typedef int16_t  INT16;
typedef uint16_t UINT16;
typedef int32_t  INT32;
typedef uint32_t UINT32;
typedef int64_t  INT64;
typedef uint64_t UINT64;


// context for modular exponentiation

typedef struct modexp_ctx
{
   UINT32 *n;         // modulus N (product of primes P, Q)
  int nlen;                // number of 32-bit words N consists of
   UINT32 *e;         // exponent E
  int elen;                // number of 32-bit words E consists of
   UINT32 *r;         // Montgomery radix R = 2^2n mod N for operand conv
  UINT32 n0_;              // ant n0_ = -N[0]^-1 mod 2^32 for Montg red
} MODEXP_CTX;

// context for CRT-based modular exponentiation

typedef struct crtexp_ctx
{
   UINT32 *n;         // modulus N (product of primes P, Q)
  int nlen;                // number of 32-bit words N consists of
   UINT32 *r;         // Montgomery radix R = 2^2n mod N for operand conv
  UINT32 n0_;              // ant n0_ = -N[0]^-1 mod 2^32 for Montg red
   UINT32 *yp;        // ant YP = Q^(P-1) mod N for CRT computation
   UINT32 *yq;        // ant YQ = P^(Q-1) mod N for CRT computation
   MODEXP_CTX *pctx;  // exponentiation context for prime P
   MODEXP_CTX *qctx;  // exponentiation context for prime Q
} CRTEXP_CTX;

// function prototypes
void mod_mul(UINT32* out, UINT32* in1, UINT32* in2, UINT32* n, UINT32 n_,
		UINT32 LEN);
void mod_sqr(UINT32* out, UINT32* in1, UINT32* n, UINT32 n_, UINT32 LEN);
void int_red_rps(UINT32* out, UINT32* in1, UINT32* n, UINT32 n_, UINT32 LEN);
unsigned int int_add(UINT32* out, UINT32* in1, UINT32* n, UINT32 LEN);
unsigned int  int_sub(UINT32* out, UINT32* in1, UINT32* n, UINT32 LEN);
unsigned int int_sub_cdt(UINT32* out, UINT32* in1, UINT32* n, UINT32 carry,
		UINT32 LEN);
void int_cpy(UINT32 *r, UINT32 *a, int len);
void int_set(UINT32 *r, UINT32 a, int len);
int int_cmp(UINT32 *a, UINT32 *b, int len);
void m_variable_set(UINT32* out, UINT32* in, UINT32 n_, UINT32 LEN) ;

#endif /* RSA_ARITH_H */
