/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Multiplication/Squaring 512-bit
 */

#include "rsa_test.h"
#include "rsa_arith.h"
#include <android/log.h>
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>
#include <arm_neon.h>

//////////////////////////////////////////////////////////////////////////////
////////////////////// OPERANDS FOR 1024-BIT RSA EXAMPLE /////////////////////
//////////////////////////////////////////////////////////////////////////////

#define DEBUG 1

#if DEBUG
#include <android/log.h>
#  define  D(x...)  __android_log_print(ANDROID_LOG_INFO,"helloneon",x)
#else
#  define  D(...)  do {} while (0)
#endif

UINT32 n_inv = 0x8E565CA5;

// 1024-bit RSA modulus N
UINT32 n1024[32] = { 0x9965D4D3, 0xCAA2D776, 0xD1114101, 0x0A51B091, 0x73D434E2,
		0xD99E9853, 0x37155A38, 0x13823C67, 0x97BD3556, 0xC8F07514, 0xA029E0BF,
		0xE2746854, 0x55E1F417, 0xA4668A26, 0xCCBB1415, 0x636D795E, 0x0DA422D7,
		0x58E0362E, 0xC5D7B078, 0xE11EB8AC, 0x79CE0746, 0xA99729C8, 0x36E3CB29,
		0xA328F602, 0x292E4304, 0x1DCA1678, 0xDD86CFAB, 0xE6EEAEED, 0xA65FC463,
		0x262846F6, 0xE192B408, 0xC830E8AB };

// Montgomery radix R = 2^2n mod N
UINT32 r1024[32] = { 0xC50B1E5A, 0x96DE039D, 0x6DECCB92, 0x91E29DD8, 0x3437FCB2,
		0xE5B4546D, 0xBD131CD0, 0xF3670BC3, 0x602DA9DA, 0x5343297B, 0x15E8FE80,
		0xA15CC6D3, 0xA38B21FE, 0x48A4D7EB, 0xB38609E5, 0x7ED5E07E, 0x55ABCB6F,
		0x96959475, 0x47DA5122, 0x89DF0CBE, 0x8D577CCD, 0x1D72AEE9, 0x59D0D2F,
		0x5B3626C7, 0xBF626F29, 0x48562E4A, 0x1A0BFDEA, 0xF2AFAA4, 0x77097C0C,
		0xED90A015, 0xDB631662, 0x49A544B6 };

// public exponent E for encryption / signature verification
UINT32 e1024[32] = { 0x00010001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000 };

// private exponent D for decryption / signature generation
UINT32 d1024[32] = { 0x8AD8F271, 0x3EF382BB, 0x3ED66F29, 0xDC7F7962, 0x18FA33DE,
		0x660CB143, 0xA2C93481, 0x7B55DC08, 0x88BE2321, 0x755F311F, 0xA0B02CB3,
		0x0A490FA5, 0x3044288F, 0xDE1B587D, 0xA31F3808, 0x2C4AE16C, 0x1183B20E,
		0x071E5AE2, 0x1ED00D6E, 0x60D9D602, 0x97B7526F, 0x400A04DF, 0x90392575,
		0x64EC2A22, 0xF49A2ABB, 0xFD37493C, 0x8BAAD745, 0x0DCDCD5B, 0x029949C5,
		0xCFE0B885, 0xCAAAEA66, 0x4E85B09D };

// prime decomposition P, Q of N
UINT32 p1024[16] = { 0x0EC5A8C5, 0xB31E8567, 0xC3FBCC90, 0x71A32B18, 0x101A2CC4,
		0x58BF5DEF, 0xF9B437B9, 0x888B60C8, 0xBAC3643B, 0x70D44028, 0xACCB7372,
		0xB39C6D36, 0x197BE331, 0x65F81B88, 0x350F35EA, 0xE95CA97E };
UINT32 q1024[16] = { 0x2B7470B7, 0xE07A2A6F, 0x5D8620D9, 0x16F49CC2, 0x8CFB9C97,
		0x25D3FB46, 0xA88EA743, 0x87B96B28, 0x3F82D9C5, 0xE3725D72, 0x6961D6C4,
		0x6E6B5F0E, 0x52040612, 0x3A1654B8, 0x6B5B35D3, 0xDB9C79FF };

// Montgomery radix for P and Q
UINT32 rp1024[16] = { 0xA9EED4E6, 0xA0466FB6, 0x19C968E1, 0x09F66963,
		0xB9190D50, 0x3173C434, 0x8C7ECE36, 0x48D12FE9, 0x23A85905, 0x69DEB1A3,
		0xFBBEFC81, 0xBF736273, 0x3E92B6E8, 0xC56E4910, 0x0E66ED1B, 0xD738043B };
UINT32 rq1024[16] = { 0xF4884E12, 0x8C20EDD1, 0xCE41F8DC, 0x1EDDFE1C,
		0x02C4AD67, 0x930E26FA, 0x83E62EA4, 0xADE3A92D, 0xCE7C6D4E, 0x67405920,
		0xAA526AEC, 0x6D9A1737, 0x56BE990D, 0xA9A2D52F, 0xA2C00C75, 0xB31494F9 };

// CRT exponents DP = D mod (P-1) and DQ = D mod (Q-1)
UINT32 dp1024[16] = { 0x9A35C57D, 0xF02D8FE5, 0x4E8B97D1, 0x9C860DC8,
		0xBF960FD2, 0xF7215EFD, 0x65E1AAAE, 0x82210805, 0xCA66CE54, 0x4C3C5262,
		0xB5F01B00, 0x30EECC66, 0x56375B2F, 0xEB8D145D, 0x3F18189E, 0x5804C24D };
UINT32 dq1024[16] = { 0xA9F19D91, 0x244E04E5, 0x177A5335, 0x56AFCC8B,
		0x7B90876B, 0x73FCEAA0, 0x61FC00A7, 0x8AF68FC2, 0x7A6AABA4, 0xA569030A,
		0x5C72750F, 0xD79ACA64, 0xF9B2D726, 0xF7731B81, 0x4E5B38F5, 0xC6071B9B };

// CRT constants YP = Q^(P-1) mod N and YQ = P^(Q-1) mod N
// both YP and YQ have to be in the Montgomery domain of N
UINT32 yp1024[32] = { 0x4AE16619, 0xB5290A9E, 0x9ADF4D12, 0x356B180E,
		0x031C6B00, 0xA6AD14CB, 0x1B6931D8, 0x1B16F3BA, 0x9745DAA8, 0x38427BAE,
		0x0F1BE9A3, 0x019E127F, 0xB7921F3F, 0xA9726125, 0xB8E6F337, 0x2F55DB68,
		0xBDAFC061, 0xC50512C3, 0x1A3D9B23, 0x050B6D9C, 0x9ACEC359, 0xEDB1AF4A,
		0x7A66D1C0, 0xDD5F0253, 0x2DE56A80, 0x1FC895F1, 0xDD441B00, 0x177B5574,
		0x6AEE4D38, 0xF49E1CD1, 0x62E0BB40, 0x77971E7B };
UINT32 yq1024[32] = { 0xB51E99E7, 0x4AD6F561, 0x6520B2ED, 0xCA94E7F1,
		0xFCE394FF, 0x5952EB34, 0xE496CE27, 0xE4E90C45, 0x68BA2557, 0xC7BD8451,
		0xF0E4165C, 0xFE61ED80, 0x486DE0C0, 0x568D9EDA, 0x47190CC8, 0xD0AA2497,
		0x42503F9E, 0x3AFAED3C, 0xE5C264DC, 0xFAF49263, 0x65313CA6, 0x124E50B5,
		0x85992E3F, 0x22A0FDAC, 0xD21A957F, 0xE0376A0E, 0x22BBE4FF, 0xE884AA8B,
		0x9511B2C7, 0x0B61E32E, 0x9D1F44BF, 0x8868E184 };

void rsa_demo_1024(void) {
	int i;
	// context for 1024-bit public-key exponentiation

	// plaintext, ciphertext for 1024-bit RSA example
	UINT32 pltxt[32] = { 0x1234567, 0x89ABDCEF, 0x1234567, 0x89ABDCEF,
			0x1234567, 0x89ABDCEF, 0x1234567, 0x89ABDCEF, 0x1234567, 0x89ABDCEF,
			0x1234567, 0x89ABDCEF, 0x1234567, 0x89ABDCEF, 0x1234567, 0x89ABDCEF,
			0x1234567, 0x89ABDCEF, 0x1234567, 0x89ABDCEF, 0x1234567, 0x89ABDCEF,
			0x1234567, 0x89ABDCEF, 0x1234567, 0x89ABDCEF, 0x1234567, 0x89ABDCEF,
			0x1234567, 0x89ABDCEF, 0x1234567, 0x89ABDCEF };
	UINT32 citxt[32];

	UINT32 n_tmp[3 * 32 + 4];
	m_variable_set(n_tmp, n1024, n_inv, 32);

	MODEXP_CTX pub1024_ctx = { &(n_tmp[0]), 32, &(e1024[0]), 1, &(r1024[0]),
			0x8E565CA5 };

	// encrypt the plaintext
	rsa_encrypt(citxt, pltxt, &pub1024_ctx);
	//print_words("ciphertext: 0x", citxt, 32);

	UINT32 n_tmp2[3 * 16 + 4];
	m_variable_set(n_tmp2, p1024, 0x3A0869F3, 16);

	MODEXP_CTX p1024_ctx = { &(n_tmp2[0]), 16, &(dp1024[0]), 16, &(rp1024[0]),
			0x3A0869F3 };

	UINT32 n_tmp3[3 * 16 + 4];
	m_variable_set(n_tmp3, q1024, 0x863A92F9, 16);

	MODEXP_CTX q1024_ctx = { &(n_tmp3[0]), 16, &(dq1024[0]), 16, &(rq1024[0]),
			0x863A92F9 };

	UINT32 n_tmp4[3 * 32 + 4];
	m_variable_set(n_tmp4, n1024, 0x8E565CA5, 32);

	CRTEXP_CTX prv1024_ctx = // context for private-key operations
			{ &(n_tmp4[0]), 32, &(r1024[0]), 0x8E565CA5, &(yp1024[0]),
					&(yq1024[0]), &p1024_ctx, &q1024_ctx };

	// decrypt the ciphertext
	rsa_decrypt(pltxt, citxt, &prv1024_ctx);
	//print_words("plaintext : 0x", pltxt, 32);
}

void conv_into_mon(UINT32 *r, UINT32 *a, MODEXP_CTX *ctx) {
	int len = ctx->nlen;
	//UINT32 tmp[2 * len];

	mod_mul(r, a, ctx->r, ctx->n, 0, len);
}

void conv_from_mon(UINT32 *r, UINT32 *a, MODEXP_CTX *ctx) {
	int len = ctx->nlen;
	UINT32 one[len], tmp[2 * len];

	int_set(one, 1, len);
	mod_mul(r, a, one, ctx->n, 0, len);
}

void mod_exp_bin(UINT32 *r, UINT32 *a, MODEXP_CTX *ctx) {
	int i = ctx->elen - 1, len = ctx->nlen;
	UINT32 *n = ctx->n, *n0_ = &(ctx->n0_);
	UINT32 mask = 0x80000000U;
	UINT32 tmp[2 * len];

	// find the leading "1" in exponent E
	while (((ctx->e[i] & mask) == 0) && (mask > 0))
		mask >>= 1;
	if (mask == 0) {
		int_set(r, 1, len);
		return;
	}

	// we start from the second-most significant bit of E
	mask >>= 1;
	int_cpy(r, a, len);

	// binary exponentiation method (square-and-multiply)
	for (i = i; i >= 0; i--) {
		for (mask = mask; mask > 0; mask >>= 1) {
			mod_sqr(r, r, n, 0, len);
			if (ctx->e[i] & mask)
				mod_mul(r, r, a, n, 0, len);
		}
		mask = 0x80000000U;
	}
}

void rsa_encrypt(UINT32 *citxt, UINT32 *pltxt, MODEXP_CTX *ctx) {
	int len = ctx->nlen;
	UINT32 plmon[len];  // plaintext in Montgomery domain
	UINT32 rdx[len];    // array for the Montgomery radix

	// convert plaintext into Montgomery domain
	conv_into_mon(plmon, pltxt, ctx);

	// perform the actual exponentiation

	mod_exp_bin(citxt, plmon, ctx);

	// convert result from Montgomery domain
	conv_from_mon(citxt, citxt, ctx);
	/*
	 int i;
	 for (i = 0; i < 32; i++) {
	 D("0x%X", citxt[i]);
	 }
	 */
}

/////////////////////////////////////////////
void init_table(UINT32 *t, UINT32 *a, MODEXP_CTX *ctx) {
	int i, len = ctx->nlen;
	//UINT32 *n = ctx->n, *n0_ = &(ctx->n0_);
	UINT32 *n = ctx->n, *n0_ = &(ctx->n0_);
	UINT32 *tptr[16];  // array of 16 pointers to the 16 entries of the table
	UINT32 *tmp = t;   // we use the first 2*len words for the product/square

	for (i = 0; i < 16; i++)
		tptr[i] = &(t[len * i]);

	// calculate t[2] = A^2 mod N, t[4] = A^4 Mod N, t[8] = A^8 mod N
	mod_sqr(tptr[2], a, n, *n0_, len);
	mod_sqr(tptr[4], tptr[2], n, *n0_, len);
	mod_sqr(tptr[8], tptr[4], n, *n0_, len);

	// calculate table entries t[3], t[5] to t[8], and t[9] to t[15]
	mod_mul(tptr[3], tptr[2], a, n, *n0_, len);
	for (i = 5; i <= 7; i++)
		mod_mul(tptr[i], tptr[i - 1], a, n, *n0_, len);
	for (i = 9; i <= 15; i++)
		mod_mul(tptr[i], tptr[i - 1], a, n, *n0_, len);

	// t[0] = 1 (i.e. 2^n - N in Montgomery domain)
	int_set(tptr[1], 0, len);

	int_sub(tptr[0], tptr[1], &n[4+len], len);

	// t[1] = A
	int_cpy(tptr[1], a, len);
}

void mod_exp_wdw(UINT32 *r, UINT32 *a, MODEXP_CTX *ctx) {
	int i, idx, shift_dist, len = ctx->nlen;
	UINT32 *n = ctx->n, *n0_ = &(ctx->n0_);
	UINT32 eword, mask;
	UINT32 tmp[2 * len], table[16][len];

	// initialize the 16 entries of the look-up table
	init_table(&(table[0][0]), a, ctx);

	// set r to 1 (i.e. 2^n - N in Montgomery domain)
	int_cpy(r, table[0], len);

	// highly-regular 4-bit window method
	for (i = ctx->elen - 1; i >= 0; i--) {
		shift_dist = 28;
		eword = ctx->e[i];
		// loop to process a 32-bit word of exponent E
		for (mask = 0xF0000000U; mask > 0; mask >>= 4) {
			// four modular squarings
			mod_sqr(r, r, n, *n0_, len);
			mod_sqr(r, r, n, *n0_, len);
			mod_sqr(r, r, n, *n0_, len);
			mod_sqr(r, r, n, *n0_, len);
			// one modular multiplication
			idx = (int) ((eword & mask) >> shift_dist);
			mod_mul(r, r, table[idx], n, *n0_, len);
			shift_dist -= 4;
		}
	}
}

// reduce the ciphertext modulo P or Q and do the conversion into the
// Montgomery domain of P or Q

void red_citxt(UINT32 *r, UINT32 *a, MODEXP_CTX *ctx) {
	int len = ctx->nlen;
	UINT32 *n = ctx->n, *n0_ = &(ctx->n0_);
	UINT32 tmp[2 * len];

	// Montgomery reduction modulo N (the result carries the factor 2^(-n))
	int_red_rps(r, a, n, *n0_, len);

	// convert the result into Montgomery domain via two multiplications by
	// the Montgomery radix R = 2^2n mod N
	mod_mul(r, r, ctx->r, n, *n0_, len);

	mod_mul(r, r, ctx->r, n, *n0_, len);

}

void crt_recomb(UINT32 *r, UINT32 *tp, UINT32 *tq, CRTEXP_CTX *ctx) {
	int i, carry, len = ctx->nlen;
	UINT32 *n = ctx->n, *n0_ = &(ctx->n0_);
	UINT32 tmp[2 * len];

	for (i = (len >> 1); i < len; i++)
		tp[i] = tq[i] = 0;

	mod_mul(tp, tp, ctx->yp, n, *n0_, len);
	mod_mul(tq, tq, ctx->yq, n, *n0_, len);

	carry = int_add(r, tp, tq, len);

	/*
	 carry = 0 - carry;
	 for(i=0;i<len;i++){
	 tmp[i] = n[4+len+i] & carry;
	 }
	 carry = int_sub(r, r, tmp, len);
	 */

	// at most two subtractions of N are necessary to get an n-bit result
	carry -= int_sub_cdt(r, r, &n[4 + len], carry, len);
	carry -= int_sub_cdt(r, r, n, carry, len);

	/*for (i = 0; i < len; i++) {
	 D("0x%X", r[i]);
	 }*/

}

void mod_exp_bin2(UINT32 *r, UINT32 *a, MODEXP_CTX *ctx) {
	int i = ctx->elen - 1, len = ctx->nlen;
	UINT32 *n = ctx->n, *n0_ = &(ctx->n0_);
	UINT32 mask = 0x80000000U;
	UINT32 tmp[2 * len];

	// find the leading "1" in exponent E
	while (((ctx->e[i] & mask) == 0) && (mask > 0))
		mask >>= 1;
	if (mask == 0) {
		int_set(r, 1, len);
		return;
	}

	// we start from the second-most significant bit of E
	mask >>= 1;
	int_cpy(r, a, len);
	//for (i = 0; i < len; i++) {

	//					}
	int qq;

	UINT32 tmp2[2 * 16];

	// binary exponentiation method (square-and-multiply)
	for (i = i; i >= 0; i--) {
		for (mask = mask; mask > 0; mask >>= 1) {

			mod_sqr(r, r, n, 0, len);

			//SQR_512(tmp2, r);
			//MM_512(r, tmp2, n);
			//mod_mul(r, r, r, n, 0, len);

			if (ctx->e[i] & mask){



				mod_mul(r, r, a, n, 0, len);
				for (qq = 0; qq < len; qq++) {
												D("0x%X", r[qq]);
											}

			}
		}
		//D("0x%X", r[0]);

		mask = 0x80000000U;
	}
}

void rsa_decrypt(UINT32 *pltxt, UINT32 *citxt, CRTEXP_CTX *ctx) {
	int len = ctx->nlen;

	/*UINT32 tp[32] = { 0x6D53AD10, 0x3C00E3F2, 0x2A4CF1E0, 0x6B83F730,
			0x830AA108, 0x15F4CB25, 0x621B65C8, 0xBC37B53F, 0x93CC9CD8,
			0xCC7405DC, 0xEE77E53, 0x272DD980, 0xAB6BA402, 0xFC06218C,
			0x2739E97, 0x3D1FD40 };

	UINT32 tq[32] = { 0x516E192F, 0x1862C932, 0x32C3A874, 0x844F33DA,
			0xB967381E, 0xBA8CABDE, 0x29A834A1, 0x821DB088, 0x65CAB9E3,
			0x6CB6D843, 0x9C05A8EB, 0xCF8541CB, 0xAC4154A3, 0x76FDA2B5,
			0xC04D40EA, 0x1DBC60E7 };*/
	UINT32 tp[len], tq[len];
	UINT32 tp2[len], tq2[len];

	 // reduce the ciphertext mod P, Q and convert into Montgomery domain
	 red_citxt(tp, citxt, ctx->pctx);		//correct

	 red_citxt(tq, citxt, ctx->qctx);		//correct
	 /* */
	// perform two "1/2-length" modular exponentiations according to CRT
	//mod_exp_bin(tp, tp, ctx->pctx);	//working

	/*
	int i;

	ctx->pctx->elen = 1;
	for (i = 0; i < 16; i++) {
		ctx->pctx->e[i] = 0;
	}
	ctx->pctx->e[0] = 0x3;
*/
	//mod_exp_bin(tp2, tp, ctx->pctx);

	//mod_exp_bin(tq2, tq, ctx->qctx);

	mod_exp_wdw(tp2, tp, ctx->pctx);
	mod_exp_wdw(tq2, tq, ctx->qctx);

	// convert the results from Montgomery domain into "ordinary" domain
	conv_from_mon(tp, tp2, ctx->pctx);		//correct

	conv_from_mon(tq, tq2, ctx->qctx);		//correct

	// recombine the obtained "1/2-length" results into the final result
	crt_recomb(pltxt, tp, tq, ctx);		//correct
	D("0x%X", pltxt[0]);
}

