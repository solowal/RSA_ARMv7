/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Montgomery Reduction 1024-bit
 */

#include "mont1024.h"
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>
#include <arm_neon.h>

void MM_1024(uint32_t* out, uint32_t* in, uint32_t* m) {

	asm(
			"mov r9, %0 				\n\t"

			"veor q12,q12,q12 			\n\t" //initialization
			"veor q13,q13,q13 			\n\t"
			"veor q14,q14,q14 			\n\t"
			"veor q15,q15,q15 			\n\t"

			"vpush {q12-q15} 			\n\t"//padding

			"mov r7, #0 				\n\t"//count set	(n-1) 3 + last 1
			"OUTER1: 					\n\t"
			"adds r7, r7, #1 			\n\t"//count begin

			"vldmia %1!,  {q3-q4} 		\n\t"//operand in load
			"vldmia %2!,  {q0-q2} 		\n\t"//operand m' || 1 || mixed m  load
			"vtrn.32 q3, q4 			\n\t"

			//step1
			"vmull.u32 q8,  d6, d1[0] 	\n\t"//expansion
			"vmull.u32 q9,  d8, d1[0] 	\n\t"
			"vmull.u32 q10, d7, d1[0] 	\n\t"
			"vmull.u32 q11, d9, d1[0] 	\n\t"

			"vmull.u32 q5, d0, d16 		\n\t"//m' * p

			"veor q12,q12,q12 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q14,q14,q14			\n\t"
			"veor q15,q15,q15 			\n\t"

			"vmlal.u32 q8,  d2, d10[0] 	\n\t"//M4M0 X Q0Q0
			"vmlal.u32 q9,  d3, d10[0] 	\n\t"//M5M1 X Q0Q0
			"vmlal.u32 q10,  d4, d10[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q11,  d5, d10[0] \n\t"//M7M3 X Q0Q0

			//////////////////////////////////////SAVE
			"vext.8 d12, d12, d10, #4 	\n\t"
			//////////////////////////////////////SAVE

			"vtrn.32 q8, q12  			\n\t"
			"vtrn.32 q9, q13 			\n\t"
			"vtrn.32 q10, q14 			\n\t"
			"vtrn.32 q11, q15 			\n\t"

			"vadd.i64  q9 , q9 , q12  	\n\t"//q
			"vadd.i64  q10 , q10 , q13 	\n\t"//q
			"vadd.i64  q11 , q11 , q14 	\n\t"//q
			"vqadd.u64 d30, d30, d17 	\n\t"//d

			//step2
			"vmull.u32 q5, d0, d18 		\n\t"//m' * p

			"veor q12,q12,q12 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q14,q14,q14 			\n\t"
			"veor q8,q8,q8 				\n\t"

			"vmlal.u32 q9,   d2, d10[0] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q10,  d3, d10[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q11,  d4, d10[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q15,  d5, d10[0] \n\t"//M7M3 X Q0Q0

			//////////////////////////////////////SAVE
			"vext.8 d12, d12, d10, #4 	\n\t"
			//////////////////////////////////////SAVE

			"vtrn.32 q9,  q8  			\n\t"
			"vtrn.32 q10, q12 			\n\t"
			"vtrn.32 q11, q13 			\n\t"
			"vtrn.32 q15, q14 			\n\t"

			"vadd.i64  q10, q10 , q8  	\n\t"//q
			"vadd.i64  q11 , q11 , q12 	\n\t"//q
			"vadd.i64  q15 , q15 , q13 	\n\t"//q

			"vqadd.u64 d28, d28, d19 	\n\t"//d

			//step3
			"vmull.u32 q5, d0, d20 		\n\t"//m' * p

			"veor q12,q12,q12 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q8 ,q8 ,q8 			\n\t"

			"vmlal.u32 q10,   d2, d10[0]\n\t"//M4M0 X Q0Q0
			"vmlal.u32 q11,  d3, d10[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q15,  d4, d10[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q14,  d5, d10[0] \n\t"//M7M3 X Q0Q0

			//////////////////////////////////////SAVE
			"vext.8 d13, d13, d10, #4 	\n\t"
			//////////////////////////////////////SAVE

			"vtrn.32 q10, q9  			\n\t"
			"vtrn.32 q11, q8  			\n\t"
			"vtrn.32 q15, q12 			\n\t"
			"vtrn.32 q14, q13 			\n\t"

			"vadd.i64  q11 , q11 , q9  	\n\t"//q
			"vadd.i64  q15 , q15 , q8 	\n\t"//q
			"vadd.i64  q14 , q14 , q12 	\n\t"//q

			"vqadd.u64 d26, d26, d21 	\n\t"//d

			//step4
			"vmull.u32 q5, d0, d22 		\n\t"//m' * p

			"veor q12,q12,q12 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q8 ,q8 ,q8 			\n\t"

			"vmlal.u32 q11,  d2, d10[0] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q15,  d3, d10[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q14,  d4, d10[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q13,  d5, d10[0] \n\t"//M7M3 X Q0Q0

			//////////////////////////////////////SAVE
			"vext.8 d13, d13, d10, #4 	\n\t"
			//////////////////////////////////////SAVE

			"vtrn.32 q11, q10  			\n\t"
			"vtrn.32 q15, q9   			\n\t"
			"vtrn.32 q14, q8   			\n\t"
			"vtrn.32 q13, q12  			\n\t"

			"vadd.i64  q15 , q15 , q10  \n\t"//q
			"vadd.i64  q14 , q14 , q9  	\n\t"//q
			"vadd.i64  q13 , q13 , q8  	\n\t"//q

			"vqadd.u64 d24, d24, d23 	\n\t"//d

			//step5
			"vmull.u32 q5, d0, d30 		\n\t"//m' * p

			"veor q11,q11,q11 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q8 ,q8 ,q8 			\n\t"

			"vmlal.u32 q15,  d2, d10[0] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q14,  d3, d10[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q13,  d4, d10[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q12,  d5, d10[0] \n\t"//M7M3 X Q0Q0

			//////////////////////////////////////SAVE
			"vext.8 d14, d14, d10, #4 	\n\t"
			//////////////////////////////////////SAVE

			"vtrn.32 q15, q11  			\n\t"
			"vtrn.32 q14, q10  			\n\t"
			"vtrn.32 q13, q9  			\n\t"
			"vtrn.32 q12, q8  			\n\t"

			"vadd.i64  q14 , q14 , q11  \n\t"//q
			"vadd.i64  q13 , q13 , q10  \n\t"//q
			"vadd.i64  q12 , q12 , q9  	\n\t"//q

			"vqadd.u64 d16, d16, d31 	\n\t"//d

			//step6
			"vmull.u32 q5, d0, d28 		\n\t"//m' * p

			"veor q11,q11,q11 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q15 ,q15 ,q15 		\n\t"

			"vmlal.u32 q14,  d2, d10[0] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q13,  d3, d10[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q12,  d4, d10[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q8 ,  d5, d10[0] \n\t"//M7M3 X Q0Q0

			//////////////////////////////////////SAVE
			"vext.8 d14, d14, d10, #4 	\n\t"
			//////////////////////////////////////SAVE

			"vtrn.32 q14, q15  			\n\t"
			"vtrn.32 q13, q11  			\n\t"
			"vtrn.32 q12, q10 			\n\t"
			"vtrn.32 q8 , q9  			\n\t"

			"vadd.i64  q13 , q13 , q15  \n\t"//q
			"vadd.i64  q12 , q12 , q11  \n\t"//q
			"vadd.i64  q8  , q8  , q10  \n\t"//q

			"vqadd.u64 d18, d18, d29 	\n\t"//d

			//step7
			"vmull.u32 q5, d0, d26 		\n\t"//m' * p

			"veor q11,q11,q11 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q14 ,q14 ,q14 		\n\t"
			"veor q15 ,q15 ,q15 		\n\t"

			"vmlal.u32 q13,  d2, d10[0] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q12,  d3, d10[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q8 ,  d4, d10[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q9 ,  d5, d10[0] \n\t"//M7M3 X Q0Q0

			//////////////////////////////////////SAVE
			"vext.8 d15, d15, d10, #4 	\n\t"
			//////////////////////////////////////SAVE

			"vtrn.32 q13, q15  			\n\t"
			"vtrn.32 q12, q14  			\n\t"
			"vtrn.32 q8 , q11 			\n\t"
			"vtrn.32 q9 , q10 			\n\t"

			"vadd.i64  q12 , q12 , q15  \n\t"//q
			"vadd.i64  q8  , q8  , q14  \n\t"//q
			"vadd.i64  q9  , q9  , q11  \n\t"//q

			"vqadd.u64 d20, d20, d27 	\n\t"//d
			//step8
			"vmull.u32 q5, d0, d24 		\n\t"//m' * p

			"veor q11,q11,q11 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q14 ,q14 ,q14 		\n\t"
			"veor q15 ,q15 ,q15 		\n\t"

			"vmlal.u32 q12,  d2, d10[0] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q8 ,  d3, d10[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q9 ,  d4, d10[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q10,  d5, d10[0] \n\t"//M7M3 X Q0Q0

			//////////////////////////////////////SAVE
			"vext.8 d15, d15, d10, #4 	\n\t"
			//////////////////////////////////////SAVE

			"vtrn.32 q12, q15  			\n\t"
			"vtrn.32 q8 , q14  			\n\t"
			"vtrn.32 q9 , q13 			\n\t"
			"vtrn.32 q10, q11 			\n\t"

			"vadd.i64  q8  , q8, q15  	\n\t"//q
			"vadd.i64  q9  , q9, q14  	\n\t"//q
			"vadd.i64  q10  , q10, q13	\n\t"//q

			"vqadd.u64 d22, d22, d25 	\n\t"//d

			/////////////////////////////////////////////////////////INNER LOOP
			/////////////////////////////////////////////////////////part2

			"mov r8, #0 				\n\t"//count set
			"INNER1: 					\n\t"
			"adds r8, r8, #1 			\n\t"//count begin

			"vldmia %1,  {q3-q4} 		\n\t"//operand in load
			"vldmia %2!,  {q1-q2} 		\n\t"//mixed m  load
			"vtrn.32 q3, q4 			\n\t"

			//step1
			"vmlal.u32 q8,  d6, d1[0] 	\n\t"//expansion
			"vmlal.u32 q9,  d8, d1[0] 	\n\t"//
			"vmlal.u32 q10, d7, d1[0] 	\n\t"//
			"vmlal.u32 q11, d9, d1[0] 	\n\t"//

			"veor q12,q12,q12 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q14,q14,q14 			\n\t"
			"veor q3,q3,q3 				\n\t"

			"vtrn.32 q8, q12  			\n\t"
			"vtrn.32 q9, q13 			\n\t"
			"vtrn.32 q10, q14 			\n\t"
			"vtrn.32 q11, q3 			\n\t"

			"vadd.i64  q9 , q9 , q12  	\n\t"//q
			"vadd.i64  q10 , q10 , q13 	\n\t"//q
			"vadd.i64  q11 , q11 , q14 	\n\t"//q
			"vqadd.u64 d17, d17, d6 	\n\t"//d

			//d7
			"veor q12,q12,q12 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q14,q14,q14 			\n\t"
			"veor q15,q15,q15 			\n\t"

			"vmlal.u32 q8,  d2, d12[0] 	\n\t"//M4M0 X Q0Q0
			"vmlal.u32 q9,  d3, d12[0] 	\n\t"//M5M1 X Q0Q0
			"vmlal.u32 q10,  d4, d12[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q11,  d5, d12[0] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q8, q12  			\n\t"
			"vtrn.32 q9, q13 			\n\t"
			"vtrn.32 q10, q14 			\n\t"
			"vtrn.32 q11, q15 			\n\t"

			"vadd.i64  q9 , q9 , q12  	\n\t"//q
			"vadd.i64  q10 , q10 , q13 	\n\t"//q
			"vadd.i64  q11 , q11 , q14 	\n\t"//q

			"vqadd.u64 d30, d30, d17 	\n\t"//d
			"vqadd.u64 d31, d31, d7 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d6, d6, d16, #4 	\n\t"
			//////////////////////////////////////SAVE

			//step2

			"veor q12,q12,q12 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q14,q14,q14 			\n\t"
			"veor q8,q8,q8 				\n\t"

			"vmlal.u32 q9,   d2, d12[1] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q10,  d3, d12[1] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q11,  d4, d12[1] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q15,  d5, d12[1] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q9,  q8  			\n\t"
			"vtrn.32 q10, q12 			\n\t"
			"vtrn.32 q11, q13 			\n\t"
			"vtrn.32 q15, q14 			\n\t"

			"vadd.i64  q10, q10 , q8  	\n\t"//q
			"vadd.i64  q11 , q11 , q12 	\n\t"//q
			"vadd.i64  q15 , q15 , q13 	\n\t"//q

			"vqadd.u64 d28, d28, d19 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d6, d6, d18, #4 	\n\t"
			//////////////////////////////////////SAVE

			//step3
			"veor q12,q12,q12 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q8 ,q8 ,q8 			\n\t"

			"vmlal.u32 q10,   d2, d13[0]\n\t"//M4M0 X Q0Q0
			"vmlal.u32 q11,  d3, d13[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q15,  d4, d13[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q14,  d5, d13[0] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q10, q9  			\n\t"
			"vtrn.32 q11, q8  			\n\t"
			"vtrn.32 q15, q12 			\n\t"
			"vtrn.32 q14, q13 			\n\t"

			"vadd.i64  q11 , q11 , q9  	\n\t"//q
			"vadd.i64  q15 , q15 , q8 	\n\t"//q
			"vadd.i64  q14 , q14 , q12 	\n\t"//q

			"vqadd.u64 d26, d26, d21 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d7, d7, d20, #4 	\n\t"
			//////////////////////////////////////SAVE

			//step4
			"veor q12,q12,q12 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q8 ,q8 ,q8 			\n\t"

			"vmlal.u32 q11,  d2, d13[1] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q15,  d3, d13[1] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q14,  d4, d13[1] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q13,  d5, d13[1] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q11, q10  			\n\t"
			"vtrn.32 q15, q9   			\n\t"
			"vtrn.32 q14, q8   			\n\t"
			"vtrn.32 q13, q12  			\n\t"

			"vadd.i64  q15 , q15 , q10  \n\t"//q
			"vadd.i64  q14 , q14 , q9  	\n\t"//q
			"vadd.i64  q13 , q13 , q8  	\n\t"//q

			"vqadd.u64 d24, d24, d23 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d7, d7, d22, #4 	\n\t"
			//////////////////////////////////////SAVE

			//step5
			"veor q11,q11,q11 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q8 ,q8 ,q8 			\n\t"

			"vmlal.u32 q15,  d2, d14[0] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q14,  d3, d14[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q13,  d4, d14[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q12,  d5, d14[0] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q15, q11  			\n\t"
			"vtrn.32 q14, q10  			\n\t"
			"vtrn.32 q13, q9  			\n\t"
			"vtrn.32 q12, q8  			\n\t"

			"vadd.i64  q14 , q14 , q11  \n\t"//q
			"vadd.i64  q13 , q13 , q10  \n\t"//q
			"vadd.i64  q12 , q12 , q9  	\n\t"//q

			"vqadd.u64 d16, d16, d31 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d8, d8, d30, #4 	\n\t"
			//////////////////////////////////////SAVE

			//step6

			"veor q11,q11,q11 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q15 ,q15 ,q15 		\n\t"

			"vmlal.u32 q14,  d2, d14[1] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q13,  d3, d14[1] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q12,  d4, d14[1] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q8 ,  d5, d14[1] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q14, q15  			\n\t"
			"vtrn.32 q13, q11  			\n\t"
			"vtrn.32 q12, q10 			\n\t"
			"vtrn.32 q8 , q9  			\n\t"

			"vadd.i64  q13 , q13 , q15  \n\t"//q
			"vadd.i64  q12 , q12 , q11  \n\t"//q
			"vadd.i64  q8  , q8  , q10  \n\t"//q

			"vqadd.u64 d18, d18, d29 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d8, d8, d28, #4 	\n\t"
			//////////////////////////////////////SAVE
			//step7

			"veor q11,q11,q11 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q14 ,q14 ,q14 		\n\t"
			"veor q15 ,q15 ,q15 		\n\t"

			"vmlal.u32 q13,  d2, d15[0] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q12,  d3, d15[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q8 ,  d4, d15[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q9 ,  d5, d15[0] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q13, q15  			\n\t"
			"vtrn.32 q12, q14  			\n\t"
			"vtrn.32 q8 , q11 			\n\t"
			"vtrn.32 q9 , q10 			\n\t"

			"vadd.i64  q12 , q12 , q15  \n\t"//q
			"vadd.i64  q8  , q8  , q14  \n\t"//q
			"vadd.i64  q9  , q9  , q11  \n\t"//q

			"vqadd.u64 d20, d20, d27 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d9, d9, d26, #4 	\n\t"
			//////////////////////////////////////SAVE
			//step8

			"veor q11,q11,q11 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q14 ,q14 ,q14 		\n\t"
			"veor q15 ,q15 ,q15 		\n\t"

			"vmlal.u32 q12,  d2, d15[1] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q8 ,  d3, d15[1] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q9 ,  d4, d15[1] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q10,  d5, d15[1] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q12, q15  			\n\t"
			"vtrn.32 q8 , q14  			\n\t"
			"vtrn.32 q9 , q13 			\n\t"
			"vtrn.32 q10, q11 			\n\t"

			"vadd.i64  q8  , q8 , q15  	\n\t"//q
			"vadd.i64  q9  , q9  , q14  \n\t"//q
			"vadd.i64  q10  , q10, q13	\n\t"//q

			"vqadd.u64 d22, d22, d25 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d9, d9, d24, #4 	\n\t"
			//////////////////////////////////////SAVE

			"vstmia %1!,  {q3-q4} 		\n\t"

			"cmp  r8, #1 				\n\t"//two times
			"ble  INNER1	 			\n\t"

			//////////////////////////////////////////////part3
			"vpop   {q1-q4} 			\n\t"

			"vadd.i64  q8 , q8 , q1  	\n\t"//q
			"vadd.i64  q9 , q9 , q2  	\n\t"//q
			"vadd.i64  q10 , q10 , q3  	\n\t"//q
			"vadd.i64  q11 , q11 , q4  	\n\t"//q

			"vldmia %1,  {q3-q4} 		\n\t"//operand in load
			"vldmia %2!,  {q1-q2} 		\n\t"//mixed m  load
			"vtrn.32 q3, q4 			\n\t"

			//step1
			"vmlal.u32 q8,  d6, d1[0] 	\n\t"//expansion
			"vmlal.u32 q9,  d8, d1[0] 	\n\t"//
			"vmlal.u32 q10, d7, d1[0] 	\n\t"//
			"vmlal.u32 q11, d9, d1[0] 	\n\t"//

			"veor q12,q12,q12 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q14,q14,q14 			\n\t"
			"veor q3,q3,q3 				\n\t"

			"vtrn.32 q8, q12  			\n\t"
			"vtrn.32 q9, q13 			\n\t"
			"vtrn.32 q10, q14 			\n\t"
			"vtrn.32 q11, q3 			\n\t"

			"vadd.i64  q9 , q9 , q12  	\n\t"//q
			"vadd.i64  q10 , q10 , q13 	\n\t"//q
			"vadd.i64  q11 , q11 , q14 	\n\t"//q
			"vqadd.u64 d17, d17, d6 	\n\t"//d

			//d7
			"veor q12,q12,q12 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q14,q14,q14 			\n\t"
			"veor q15,q15,q15 			\n\t"

			"vmlal.u32 q8,  d2, d12[0] 	\n\t"//M4M0 X Q0Q0
			"vmlal.u32 q9,  d3, d12[0] 	\n\t"//M5M1 X Q0Q0
			"vmlal.u32 q10,  d4, d12[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q11,  d5, d12[0] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q8, q12  			\n\t"
			"vtrn.32 q9, q13 			\n\t"
			"vtrn.32 q10, q14 			\n\t"
			"vtrn.32 q11, q15 			\n\t"

			"vadd.i64  q9 , q9 , q12  	\n\t"//q
			"vadd.i64  q10 , q10 , q13 	\n\t"//q
			"vadd.i64  q11 , q11 , q14 	\n\t"//q

			"vqadd.u64 d30, d30, d17 	\n\t"//d
			"vqadd.u64 d31, d31, d7 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d6, d6, d16, #4 	\n\t"
			//////////////////////////////////////SAVE

			//step2

			"veor q12,q12,q12 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q14,q14,q14 			\n\t"
			"veor q8,q8,q8 				\n\t"

			"vmlal.u32 q9,   d2, d12[1] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q10,  d3, d12[1] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q11,  d4, d12[1] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q15,  d5, d12[1] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q9,  q8  			\n\t"
			"vtrn.32 q10, q12 			\n\t"
			"vtrn.32 q11, q13 			\n\t"
			"vtrn.32 q15, q14 			\n\t"

			"vadd.i64  q10, q10 , q8  	\n\t"//q
			"vadd.i64  q11 , q11 , q12 	\n\t"//q
			"vadd.i64  q15 , q15 , q13 	\n\t"//q

			"vqadd.u64 d28, d28, d19 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d6, d6, d18, #4 	\n\t"
			//////////////////////////////////////SAVE

			//step3
			"veor q12,q12,q12 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q8 ,q8 ,q8 			\n\t"

			"vmlal.u32 q10,   d2, d13[0]\n\t"//M4M0 X Q0Q0
			"vmlal.u32 q11,  d3, d13[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q15,  d4, d13[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q14,  d5, d13[0] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q10, q9  			\n\t"
			"vtrn.32 q11, q8  			\n\t"
			"vtrn.32 q15, q12 			\n\t"
			"vtrn.32 q14, q13 			\n\t"

			"vadd.i64  q11 , q11 , q9  	\n\t"//q
			"vadd.i64  q15 , q15 , q8 	\n\t"//q
			"vadd.i64  q14 , q14 , q12 	\n\t"//q

			"vqadd.u64 d26, d26, d21 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d7, d7, d20, #4 	\n\t"
			//////////////////////////////////////SAVE

			//step4
			"veor q12,q12,q12 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q8 ,q8 ,q8 			\n\t"

			"vmlal.u32 q11,  d2, d13[1] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q15,  d3, d13[1] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q14,  d4, d13[1] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q13,  d5, d13[1] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q11, q10  			\n\t"
			"vtrn.32 q15, q9   			\n\t"
			"vtrn.32 q14, q8   			\n\t"
			"vtrn.32 q13, q12  			\n\t"

			"vadd.i64  q15 , q15 , q10  \n\t"//q
			"vadd.i64  q14 , q14 , q9  	\n\t"//q
			"vadd.i64  q13 , q13 , q8  	\n\t"//q

			"vqadd.u64 d24, d24, d23 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d7, d7, d22, #4 	\n\t"
			//////////////////////////////////////SAVE

			//step5
			"veor q11,q11,q11 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q8 ,q8 ,q8 			\n\t"

			"vmlal.u32 q15,  d2, d14[0] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q14,  d3, d14[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q13,  d4, d14[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q12,  d5, d14[0] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q15, q11  			\n\t"
			"vtrn.32 q14, q10  			\n\t"
			"vtrn.32 q13, q9  			\n\t"
			"vtrn.32 q12, q8  			\n\t"

			"vadd.i64  q14 , q14 , q11  \n\t"//q
			"vadd.i64  q13 , q13 , q10  \n\t"//q
			"vadd.i64  q12 , q12 , q9  	\n\t"//q

			"vqadd.u64 d16, d16, d31 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d8, d8, d30, #4 	\n\t"
			//////////////////////////////////////SAVE

			//step6

			"veor q11,q11,q11 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q9 ,q9 ,q9 			\n\t"
			"veor q15 ,q15 ,q15 		\n\t"

			"vmlal.u32 q14,  d2, d14[1] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q13,  d3, d14[1] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q12,  d4, d14[1] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q8 ,  d5, d14[1] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q14, q15  			\n\t"
			"vtrn.32 q13, q11  			\n\t"
			"vtrn.32 q12, q10 			\n\t"
			"vtrn.32 q8 , q9  			\n\t"

			"vadd.i64  q13 , q13 , q15  \n\t"//q
			"vadd.i64  q12 , q12 , q11  \n\t"//q
			"vadd.i64  q8  , q8  , q10  \n\t"//q

			"vqadd.u64 d18, d18, d29 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d8, d8, d28, #4 	\n\t"
			//////////////////////////////////////SAVE
			//step7

			"veor q11,q11,q11 			\n\t"
			"veor q10,q10,q10 			\n\t"
			"veor q14 ,q14 ,q14 		\n\t"
			"veor q15 ,q15 ,q15 		\n\t"

			"vmlal.u32 q13,  d2, d15[0] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q12,  d3, d15[0] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q8 ,  d4, d15[0] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q9 ,  d5, d15[0] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q13, q15  			\n\t"
			"vtrn.32 q12, q14  			\n\t"
			"vtrn.32 q8 , q11 			\n\t"
			"vtrn.32 q9 , q10 			\n\t"

			"vadd.i64  q12 , q12 , q15  \n\t"//q
			"vadd.i64  q8  , q8  , q14  \n\t"//q
			"vadd.i64  q9  , q9  , q11  \n\t"//q

			"vqadd.u64 d20, d20, d27 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d9, d9, d26, #4 	\n\t"
			//////////////////////////////////////SAVE
			//step8

			"veor q11,q11,q11 			\n\t"
			"veor q13,q13,q13 			\n\t"
			"veor q14 ,q14 ,q14 		\n\t"
			"veor q15 ,q15 ,q15 		\n\t"

			"vmlal.u32 q12,  d2, d15[1] \n\t"//M4M0 X Q0Q0
			"vmlal.u32 q8 ,  d3, d15[1] \n\t"//M5M1 X Q0Q0
			"vmlal.u32 q9 ,  d4, d15[1] \n\t"//M6M2 X Q0Q0
			"vmlal.u32 q10,  d5, d15[1] \n\t"//M7M3 X Q0Q0

			"vtrn.32 q12, q15  			\n\t"
			"vtrn.32 q8 , q14  			\n\t"
			"vtrn.32 q9 , q13 			\n\t"
			"vtrn.32 q10, q11 			\n\t"

			"vadd.i64  q8  , q8 , q15  	\n\t"//q
			"vadd.i64  q9  , q9  , q14  \n\t"//q
			"vadd.i64  q10  , q10, q13	\n\t"//q

			"vqadd.u64 d22, d22, d25 	\n\t"//d

			//////////////////////////////////////SAVE
			"vext.8 d9, d9, d24, #4 	\n\t"
			//////////////////////////////////////SAVE

			"vpush {q8-q11} 			\n\t"
			"vstmia %1!,  {q3-q4} 		\n\t"

			"subs %1, %1, #96 			\n\t"//offset	//intermediate
			"subs %2, %2, #144 			\n\t"//offset	//modulus

			"cmp  r7, #3 				\n\t"
			"ble  OUTER1 				\n\t"

			//last
			"vpop {q8-q11} 				\n\t"
			"adds %1, %1, #96 			\n\t"//offset	//intermediate

			"vldmia %1,  {q5-q6} 		\n\t"//operand in load
			"vtrn.32 q5, q6 			\n\t"

			//step1
			"vmlal.u32 q8,  d10, d1[0] 	\n\t"//expansion
			"vmlal.u32 q9,  d12, d1[0] 	\n\t"//
			"vmlal.u32 q10, d11, d1[0] 	\n\t"//
			"vmlal.u32 q11, d13, d1[0] 	\n\t"//

			"vmov r0, r1, d16 			\n\t"
			"vmov r2, r3, d18 			\n\t"
			"vmov r4, r5, d20 			\n\t"
			"vmov r6, r7, d22 			\n\t"

			"adds r1, r1, r2 			\n\t"
			"adcs r2, r3, r4 			\n\t"
			"adcs r3, r5, r6 			\n\t"
			"adcs r7, r7, #0 			\n\t"

			"stmia %1!,  {r0-r3} 		\n\t"//operand in load
			"mov r0,r7 					\n\t"

			"vmov r1, r2, d17 			\n\t"
			"vmov r3, r4, d19 			\n\t"
			"vmov r5, r6, d21 			\n\t"
			"vmov r7, r8, d23 			\n\t"

			"adcs r0, r0, r1 			\n\t"
			"adcs r1, r2, r3 			\n\t"
			"adcs r2, r4, r5 			\n\t"
			"adcs r3, r6, r7 			\n\t"
			"adcs r7, r8, #0 			\n\t"

			"stmia %1!,  {r0-r3} 		\n\t"//operand in load

			//could be optimized
			"subs %1, %1, #128 			\n\t"//offset	//intermediate
			"vldmia %1!,  {q0-q7} 		\n\t"//operand in load
			"vstmia %0,  {q0-q7} 		\n\t"//operand in load
			//could be optimized

			//"eor r7, #0xffffffff		\n\t"
			//"add r7, r7, #1				\n\t"
			//"mov r7, #0					\n\t"

			"sub r7, r7, #1				\n\t"
			"and r7, r7, #128			\n\t"
			"adds %2, %2, r7 			\n\t"//offset	//intermediate
			//"cmp  r7, #0 				\n\t"//two times
			//"ble  inner		 			\n\t"

			///if
			"adds %2, %2, #144 			\n\t"//offset	//intermediate

			"ldmia %2!,  {r4-r7} 		\n\t"//modular
			"ldmia %0,  {r0-r3} 		\n\t"//results
			"subs  r4, r0, r4 			\n\t"
			"sbcs  r5, r1, r5 			\n\t"
			"sbcs  r6, r2, r6 			\n\t"
			"sbcs  r7, r3, r7 			\n\t"
			"stmia %0!,  {r4-r7} 		\n\t"

			"ldmia %2!,  {r4-r7} 		\n\t"//2
			"ldmia %0,  {r0-r3} 		\n\t"
			"sbcs  r4, r0, r4 			\n\t"
			"sbcs  r5, r1, r5 			\n\t"
			"sbcs  r6, r2, r6 			\n\t"
			"sbcs  r7, r3, r7 			\n\t"
			"stmia %0!,  {r4-r7} 		\n\t"

			"ldmia %2!,  {r4-r7} 		\n\t"
			"ldmia %0,  {r0-r3} 		\n\t"
			"sbcs  r4, r0, r4 			\n\t"
			"sbcs  r5, r1, r5 			\n\t"
			"sbcs  r6, r2, r6 			\n\t"
			"sbcs  r7, r3, r7 			\n\t"
			"stmia %0!,  {r4-r7} 		\n\t"

			"ldmia %2!,  {r4-r7} 		\n\t"//4
			"ldmia %0,  {r0-r3} 		\n\t"
			"sbcs  r4, r0, r4 			\n\t"
			"sbcs  r5, r1, r5 			\n\t"
			"sbcs  r6, r2, r6 			\n\t"
			"sbcs  r7, r3, r7 			\n\t"
			"stmia %0!,  {r4-r7} 		\n\t"

			"ldmia %2!,  {r4-r7} 		\n\t"
			"ldmia %0,  {r0-r3} 		\n\t"
			"sbcs  r4, r0, r4 			\n\t"
			"sbcs  r5, r1, r5 			\n\t"
			"sbcs  r6, r2, r6 			\n\t"
			"sbcs  r7, r3, r7 			\n\t"
			"stmia %0!,  {r4-r7} 		\n\t"

			"ldmia %2!,  {r4-r7} 		\n\t"//6
			"ldmia %0,  {r0-r3} 		\n\t"
			"sbcs  r4, r0, r4 			\n\t"
			"sbcs  r5, r1, r5 			\n\t"
			"sbcs  r6, r2, r6 			\n\t"
			"sbcs  r7, r3, r7 			\n\t"
			"stmia %0!,  {r4-r7} 		\n\t"

			"ldmia %2!,  {r4-r7} 		\n\t"
			"ldmia %0,  {r0-r3} 		\n\t"
			"sbcs  r4, r0, r4 			\n\t"
			"sbcs  r5, r1, r5 			\n\t"
			"sbcs  r6, r2, r6 			\n\t"
			"sbcs  r7, r3, r7 			\n\t"
			"stmia %0!,  {r4-r7} 		\n\t"

			"ldmia %2!,  {r4-r7} 		\n\t"//8
			"ldmia %0,  {r0-r3} 		\n\t"
			"sbcs  r4, r0, r4 			\n\t"
			"sbcs  r5, r1, r5 			\n\t"
			"sbcs  r6, r2, r6 			\n\t"
			"sbcs  r7, r3, r7 			\n\t"
			"stmia %0!,  {r4-r7} 		\n\t"



			:
			:"r"(&out[0]),"r"(&in[0]),"r"(&m[0])
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","q0","q1","q2","q3","q4","q5","q6","q7","q8","q9","q10","q11","q12","q13","q14","q15"
	);
}
