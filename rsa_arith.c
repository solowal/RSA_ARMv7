/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Multiplication/Squaring 512-bit
 */

#include "rsa_arith.h"
#include <android/log.h>
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>
#include <arm_neon.h>



void mod_mul(UINT32* out, UINT32* in1, UINT32* in2, UINT32* n, UINT32 n_,
		UINT32 LEN) {
	UINT32 tmp[2 * LEN];
	int i;
	if (LEN == 16) {
		MUL_512(tmp, in1, in2);
		MM_512(out, tmp, n);
	} else if (LEN == 32) {
		MUL_1024(tmp, in1, in2);

		MM_1024(out, tmp, n);

	} else if (LEN == 64) {
		MUL_2048(tmp, in1, in2);
		MM_2048(out, tmp, n);
	}
}

void mod_sqr(UINT32* out, UINT32* in1, UINT32* n, UINT32 n_, UINT32 LEN) {
	UINT32 tmp[2 * LEN];

	if (LEN == 16) {
		SQR_512(tmp, in1);
		MM_512(out, tmp, n);
	} else if (LEN == 32) {
		SQR_1024(tmp, in1);
		MM_1024(out, tmp, n);
	} else if (LEN == 64) {
		SQR_2048(tmp, in1);
		MM_2048(out, tmp, n);
	}
}

void int_red_rps(UINT32* out, UINT32* in1, UINT32* n, UINT32 n_, UINT32 LEN) {
	if (LEN == 16) {
		MM_512(out, in1, n);
	} else if (LEN == 32) {
		MM_1024(out, in1, n);
	} else if (LEN == 64) {
		MM_2048(out, in1, n);
	}
}
//int_red_rps(r, a, n, n0_, len);

unsigned int int_add(UINT32* out, UINT32* in1, UINT32* n, UINT32 LEN) {
	if (LEN == 16) {
		return ADD_512(out, in1, n);
	} else if (LEN == 32) {
		return ADD_1024(out, in1, n);
	} else if (LEN == 64) {
		return ADD_2048(out, in1, n);
	}
}

unsigned int int_sub(UINT32* out, UINT32* in1, UINT32* n, UINT32 LEN) {
	if (LEN == 16) {
		return SUB_512(out, in1, n);
	} else if (LEN == 32) {
		return SUB_1024(out, in1, n);
	} else if (LEN == 64) {
		return SUB_2048(out, in1, n);
	}
}

//carry -= int_sub_cdt(r, r, n, carry, len);

unsigned int int_sub_cdt(UINT32* out, UINT32* in1, UINT32* n, UINT32 carry,
		UINT32 LEN) {
	if (LEN == 16) {
		return SUB_CDT_512(out, in1, n, carry);
	} else if (LEN == 32) {
		return SUB_CDT_1024(out, in1, n, carry);
	} else if (LEN == 64) {
		return SUB_CDT_2048(out, in1, n, carry);
	}
}

void int_cpy(UINT32 *r, UINT32 *a, int len) {
	int i;

	for (i = len - 1; i >= 0; i--)
		r[i] = a[i];
}

void int_set(UINT32 *r, UINT32 a, int len) {
	int i;

	for (i = len - 1; i > 0; i--)
		r[i] = 0;
	r[0] = a;
}

int int_cmp(UINT32 *a, UINT32 *b, int len) {
	int i;

	for (i = len - 1; i >= 0; i--) {
		if (a[i] > b[i])
			return 1;
		if (a[i] < b[i])
			return -1;
	}
	return 0;  // a equals b
}

void m_variable_set(UINT32* out, UINT32* in, UINT32 n_, UINT32 LEN) {
	//LEN 16->512-bit / 32->1024-bit
	out[0] = n_;
	out[1] = n_;
	out[2] = 1;
	out[3] = 1;

	int i = 4;
	int j = 0;

	int k = LEN / 8;

	//m 1  5  2  6  3  7  4  8
	for (j = 0; j < k; j++) {
		out[i + 0 + j * 8] = in[0 + j * 8];
		out[i + 1 + j * 8] = in[4 + j * 8];
		out[i + 2 + j * 8] = in[1 + j * 8];
		out[i + 3 + j * 8] = in[5 + j * 8];
		out[i + 4 + j * 8] = in[2 + j * 8];
		out[i + 5 + j * 8] = in[6 + j * 8];
		out[i + 6 + j * 8] = in[3 + j * 8];
		out[i + 7 + j * 8] = in[7 + j * 8];
	}
	i = 4 + LEN;
	//m 1  2  3  4  5  6  7  8
	for (j = 0; j < k; j++) {
		out[i + 0 + j * 8] = in[0 + j * 8];
		out[i + 1 + j * 8] = in[1 + j * 8];
		out[i + 2 + j * 8] = in[2 + j * 8];
		out[i + 3 + j * 8] = in[3 + j * 8];
		out[i + 4 + j * 8] = in[4 + j * 8];
		out[i + 5 + j * 8] = in[5 + j * 8];
		out[i + 6 + j * 8] = in[6 + j * 8];
		out[i + 7 + j * 8] = in[7 + j * 8];
	}
	//0,0,0,0,0,0,0,0
	i = 4 + LEN + LEN;
	for (j = 0; j < k; j++) {
		out[i + 0 + j * 8] = 0;
		out[i + 1 + j * 8] = 0;
		out[i + 2 + j * 8] = 0;
		out[i + 3 + j * 8] = 0;
		out[i + 4 + j * 8] = 0;
		out[i + 5 + j * 8] = 0;
		out[i + 6 + j * 8] = 0;
		out[i + 7 + j * 8] = 0;
	}

}
