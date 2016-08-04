/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Multiplication 512-bit
 */

#ifndef MUL_H
#define MUL_H
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>

void MUL_512(uint32_t* c, uint32_t* a,uint32_t* b);

#endif /* MUL_H */
