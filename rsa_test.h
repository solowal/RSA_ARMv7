/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Multiplication/Squaring 512-bit
 */

#ifndef RSA_TEST_H
#define RSA_TEST_H

//#include "mul.h"
//#include "arith.h"


#include "rsa_arith.h"


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



void init_mon(MODEXP_CTX *ctx, UINT32 *r);
void conv_into_mon(UINT32 *r,  UINT32 *a,  MODEXP_CTX *ctx);
void conv_from_mon(UINT32 *r,  UINT32 *a,  MODEXP_CTX *ctx);
void mod_exp_bin(UINT32 *r,  UINT32 *a,  MODEXP_CTX *ctx);
void mod_exp_wdw(UINT32 *r,  UINT32 *a,  MODEXP_CTX *ctx);
void rsa_encrypt(UINT32 *citxt, UINT32 *pltxt, MODEXP_CTX *ctx);
void rsa_decrypt(UINT32 *pltxt, UINT32 *citxt, CRTEXP_CTX *ctx);
void rsa_demo_1024(void);

#endif /* RSA_TEST_H */
