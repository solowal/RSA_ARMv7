/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Multiplication/Squaring 512-bit
 */

#ifndef KARA_MUL_H
#define KARA_MUL_H

#include "mul.h"
#include "arith.h"

#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>

void MUL_1024(uint32_t* r, uint32_t* a, uint32_t* b);
void MUL_2048(uint32_t* r, uint32_t* a, uint32_t* b);

#endif /* KARA_MUL_H */
