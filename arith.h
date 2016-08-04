#ifndef ARITH_H
#define ARITH_H
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>

unsigned int DIFF_512(uint32_t* c, uint32_t sign);
unsigned int DIFF_1024(uint32_t* c, uint32_t sign);

void ADD_512_WORD(uint32_t* c, uint32_t* word_in); //1024
void ADD_1024_WORD(uint32_t* c, uint32_t* word_in); //2048

void AND_512(uint32_t* c, uint32_t* word_in); //1024
void AND_1024(uint32_t* c, uint32_t* word_in); //2048

unsigned int ADD_512(uint32_t* c, uint32_t* a, uint32_t* b);
unsigned int SUB_512(uint32_t* c, uint32_t* a, uint32_t* b); //c=a-b;

unsigned int ADD_1024(uint32_t* c, uint32_t* a, uint32_t* b);
unsigned int SUB_1024(uint32_t* c, uint32_t* a, uint32_t* b);

unsigned int ADD_2048(uint32_t* c, uint32_t* a, uint32_t* b);
unsigned int SUB_2048(uint32_t* c, uint32_t* a, uint32_t* b); //2048

unsigned int SUB_CDT_512(uint32_t* c, uint32_t* a, uint32_t* b, uint32_t carry);
unsigned int SUB_CDT_1024(uint32_t* c, uint32_t* a, uint32_t* b,
		uint32_t carry);
unsigned int SUB_CDT_2048(uint32_t* c, uint32_t* a, uint32_t* b,
		uint32_t carry);

#endif

