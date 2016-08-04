/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Multiplication/Squaring 512-bit
 */

#include "kara_mul.h"
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>
#include <arm_neon.h>

#define DEBUG 1

#if DEBUG
#include <android/log.h>
#  define  D(x...)  __android_log_print(ANDROID_LOG_INFO,"helloneon",x)
#else
#  define  D(...)  do {} while (0)
#endif

void MUL_1024(uint32_t* r, uint32_t* a, uint32_t* b){
	unsigned int aplus[16];
	unsigned int bplus[16];
	unsigned int rplus[32];
	unsigned int acarry;
	unsigned int bcarry;
	unsigned int rcarry;

	MUL_512(r, a,b);

	//D("0x%x", r[0]);
	//D("0x%x", r[1]);

	MUL_512(&r[32], &a[16], &b[16]);

	acarry = ADD_512(aplus,a,&a[16]);
	bcarry = ADD_512(bplus,b,&b[16]);

	MUL_512(rplus, aplus,bplus);

	rcarry = acarry & bcarry;

	AND_512(bplus,&acarry);
	AND_512(aplus,&bcarry);

	rcarry += ADD_512(&rplus[16],&rplus[16],aplus);
	rcarry += ADD_512(&rplus[16],&rplus[16],bplus);
	/*
	D("%x",aplus[0]);
	D("%x",bplus[0]);
	D("%d",rcarry);
*/
	/*
	int i=0;
	for(i=0;i<32;i++){
		D("0x%x", rplus[i]);
	}
	*/



	rcarry += SUB_1024(rplus,rplus,r);
	rcarry += SUB_1024(rplus,rplus,&r[32]);
	rcarry += ADD_1024(&r[16],&r[16],rplus);

	ADD_512_WORD(&r[48],&rcarry);

}


void MUL_2048(uint32_t* r, uint32_t* a, uint32_t* b){
	unsigned int aplus[32];
	unsigned int bplus[32];
	unsigned int rplus[64];
	unsigned int acarry;
	unsigned int bcarry;
	unsigned int rcarry;

	MUL_1024(r, a,b);

	MUL_1024(&r[64], &a[32], &b[32]);

	acarry = ADD_1024(aplus,a,&a[32]);
	bcarry = ADD_1024(bplus,b,&b[32]);

	MUL_1024(rplus, aplus,bplus);

	rcarry = acarry & bcarry;

	AND_1024(bplus,&acarry);
	AND_1024(aplus,&bcarry);


	rcarry += ADD_1024(&rplus[32],&rplus[32],aplus);
	rcarry += ADD_1024(&rplus[32],&rplus[32],bplus);

	rcarry += SUB_2048(rplus,rplus,r);
	rcarry += SUB_2048(rplus,rplus,&r[64]);
	rcarry += ADD_2048(&r[32],&r[32],rplus);

	ADD_1024_WORD(&r[96],&rcarry);

}
