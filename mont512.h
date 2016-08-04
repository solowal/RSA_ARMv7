/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Montgomery Reduction 512-bit
 */

#ifndef MONT_H
#define MONT_H
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>


void MM_512(uint32_t* out, uint32_t* in, uint32_t* m);

#endif /* MONT_H */
