/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Squaring 512-bit
 */

#ifndef SQR_H
#define SQR_H
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>


void SQR_512(uint32_t* c, uint32_t* a);

#endif /* SQR_H */
