/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Multiplication/Squaring 512-bit
 */

#ifndef KARA_SQR_H
#define KARA_SQR_H

#include "sqr.h"
#include "arith.h"

#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>

void SQR_1024(uint32_t* r, uint32_t* a);
void SQR_2048(uint32_t* r, uint32_t* a);

#endif /* KARA_MUL_H */
