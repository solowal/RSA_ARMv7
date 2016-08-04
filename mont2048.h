/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Montgomery Reduction 1024-bit
 */

#ifndef MONT2048_H
#define MONT2048_H

#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>

void MM_2048(uint32_t* out, uint32_t* in, uint32_t* m);

#endif /* MONT1024_H */
