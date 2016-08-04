/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Multiplication/Squaring 512-bit
 */

#include "kara_sqr.h"
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>
#include <arm_neon.h>
#include <android/log.h>
#  define  D(x...)  __android_log_print(ANDROID_LOG_INFO,"helloneon",x)

void SQR_1024(uint32_t* r, uint32_t* a) {
	unsigned int adiff[16] __attribute__ ((aligned(16)));
	unsigned int rdiff[32] __attribute__ ((aligned(16)));
	unsigned int asign;
	unsigned int rcarry;

	int i = 0;

	asign = SUB_512(adiff, &a[16], a);

	DIFF_512(adiff, asign);

	SQR_512(rdiff, adiff);

	SQR_512(r, a);
	SQR_512(&r[32], &a[16]);

	rcarry = SUB_1024(rdiff, r, rdiff);
	rcarry += ADD_1024(rdiff, rdiff, &r[32]);
	rcarry += ADD_1024(&r[16], &r[16], rdiff);

	ADD_512_WORD(&r[48], &rcarry);

}

void SQR_2048(uint32_t* r, uint32_t* a) {
	unsigned int adiff[32] __attribute__ ((aligned(16)));
	unsigned int rdiff[64] __attribute__ ((aligned(16)));
	unsigned int asign;
	unsigned int rcarry;

	int i = 0;

	asign = SUB_1024(adiff, &a[32], a);

	DIFF_1024(adiff, asign);

	SQR_1024(rdiff, adiff);

	SQR_1024(r, a);
	SQR_1024(&r[64], &a[32]);

	rcarry = SUB_2048(rdiff, r, rdiff);
	rcarry += ADD_2048(rdiff, rdiff, &r[64]);
	rcarry += ADD_2048(&r[32], &r[32], rdiff);

	ADD_1024_WORD(&r[96], &rcarry);

}
