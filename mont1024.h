/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Montgomery Reduction 1024-bit
 */

#ifndef MONT1024_H
#define MONT1024_H

#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>

void MM_1024(uint32_t* out, uint32_t* in, uint32_t* m);

#endif /* MONT1024_H */
