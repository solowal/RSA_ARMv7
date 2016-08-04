/*
 * Written by Hwajeong Seo
 * 2015-11-29
 * Multiplication 512-bit
 */

#include "mul.h"
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>
#include <arm_neon.h>

void MUL_512(uint32_t* c, uint32_t* a, uint32_t* b) {

	asm(
			"push  {r4-r11}				\n\t"
			"vpush {q4-q7}				\n\t"


			"mov r3, %2 				\n\t"
			"vldmia %1,  {q4-q7} 		\n\t"//operand a load
			"vldmia %2!,  {q2-q3} 		\n\t"//operand b load

			"vtrn.32 q4, q5 			\n\t "//shuffle 6 2 4 0
									 	 	  //shuffle 7 3 5 1
			"vtrn.32 q6, q7 			\n\t "//shuffle 6 2 4 0
									 	  	  //shuffle 7 3 5 1
			"vmov 	q0, q4 				\n\t"
			"vmov 	q1, q5 				\n\t"
			"vpush 	{q6-q7} 			\n\t"

			 //step 1
			"vmull.u32 q13, d0, d4[0] 	\n\t"//A4A0 X B0B0
			"vmull.u32 q12, d2, d4[0] 	\n\t"//A5A1 X B0B0
			"vmull.u32 q11, d1, d4[0] 	\n\t"//A6A2 X B0B0
			"vmull.u32 q10, d3, d4[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q8,q8,q8 				\n\t"

			"vtrn.32 q13, q5 			\n\t"
			"vtrn.32 q12, q6 			\n\t"
			"vtrn.32 q11, q7 			\n\t"
			"vtrn.32 q10, q8 			\n\t"

			"vadd.i64  q12, q12, q5 	\n\t"//q
			"vadd.i64  q11, q11, q6 	\n\t"//q
			"vadd.i64  q10, q10, q7 	\n\t"//q

			"vqadd.u64 d16, d16, d27 	\n\t"//d

			"vext.8 d28, d28, d26, #4 	\n\t"

			//step 2
			"vmlal.u32 q12, d0, d4[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q11, d2, d4[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q10, d1, d4[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q8 , d3, d4[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7				\n\t"
			"veor q9,q9,q9 				\n\t"

			"vtrn.32 q12, q5 			\n\t"
			"vtrn.32 q11, q6 			\n\t"
			"vtrn.32 q10, q7 			\n\t"
			"vtrn.32 q8 , q9 			\n\t"

			"vadd.i64  q11, q11, q5 	\n\t"//q
			"vadd.i64  q10, q10, q6 	\n\t"//q
			"vadd.i64  q8 , q8 , q7 	\n\t"//q
			"vqadd.u64 d18, d18, d25 	\n\t"//d

			"vext.8 d28, d28, d24, #4 	\n\t"

			//step 3
			"vmlal.u32 q11, d0, d5[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q10, d2, d5[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q8,  d1, d5[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q9,  d3, d5[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q12,q12,q12 			\n\t"

			"vtrn.32 q11, q5  			\n\t"
			"vtrn.32 q10, q6  			\n\t"
			"vtrn.32 q8,  q7  			\n\t"
			"vtrn.32 q9,  q12 			\n\t"

			"vadd.i64  q10, q10, q5 	\n\t"//q
			"vadd.i64  q8 , q8 , q6 	\n\t"//q
			"vadd.i64  q9,  q9, q7 		\n\t"//q
			"vqadd.u64 d24, d24, d23 	\n\t"//d

			"vext.8 d29, d29, d22, #4 	\n\t"

			//step 4
			"vmlal.u32 q10, d0, d5[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q8,  d2, d5[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q9,  d1, d5[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q12, d3, d5[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q11,q11,q11 			\n\t"

			"vtrn.32 q10, q5 			\n\t"
			"vtrn.32 q8 , q6 			\n\t"
			"vtrn.32 q9,  q7 			\n\t"
			"vtrn.32 q12, q11 			\n\t"

			"vadd.i64  q8,  q8, q5 		\n\t"//q
			"vadd.i64  q9,  q9, q6 		\n\t"//q
			"vadd.i64  q12, q12, q7 	\n\t"//q
			"vqadd.u64 d22, d22, d21 	\n\t"//d

			"vext.8 d29, d29, d20, #4 	\n\t"

			//step 5
			"vmlal.u32 q8 , d0, d6[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q9 , d2, d6[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q12, d1, d6[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q11, d3, d6[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q10,q10,q10 			\n\t"

			"vtrn.32 q8,  q5 			\n\t"
			"vtrn.32 q9,  q6 			\n\t"
			"vtrn.32 q12, q7 			\n\t"
			"vtrn.32 q11, q10 			\n\t"

			"vadd.i64  q9, q9, q5 		\n\t"//q
			"vadd.i64  q12, q12, q6 	\n\t"//q
			"vadd.i64  q11, q11, q7 	\n\t"//q
			"vqadd.u64 d20, d20, d17 	\n\t"//d

			"vext.8 d30, d30, d16, #4 	\n\t"

			//step 6
			"vmlal.u32 q9 , d0, d6[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q12, d2, d6[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q11, d1, d6[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q10, d3, d6[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q8,q8,q8 				\n\t"

			"vtrn.32 q9 , q5 			\n\t"
			"vtrn.32 q12, q6 			\n\t"
			"vtrn.32 q11, q7 			\n\t"
			"vtrn.32 q10, q8 			\n\t"

			"vadd.i64  q12, q12, q5 	\n\t"//q
			"vadd.i64  q11, q11, q6 	\n\t"//q
			"vadd.i64  q10, q10, q7 	\n\t"//q
			"vqadd.u64 d16, d16, d19 	\n\t"//d

			"vext.8 d30, d30, d18, #4 	\n\t"

			//step 7
			"vmlal.u32 q12, d0, d7[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q11, d2, d7[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q10, d1, d7[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q8 , d3, d7[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q9,q9,q9 				\n\t"

			"vtrn.32 q12, q5 			\n\t"
			"vtrn.32 q11, q6 			\n\t"
			"vtrn.32 q10, q7 			\n\t"
			"vtrn.32 q8 , q9 			\n\t"

			"vadd.i64  q11, q11, q5 	\n\t"//q
			"vadd.i64  q10, q10, q6 	\n\t"//q
			"vadd.i64  q8 , q8 , q7 	\n\t"//q
			"vqadd.u64 d18, d18, d25 	\n\t"//d

			"vext.8 d31, d31, d24, #4 	\n\t"

			//step 8
			"vmlal.u32 q11, d0, d7[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q10, d2, d7[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q8 , d1, d7[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q9, d3, d7[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q13,q13,q13 			\n\t"

			"vtrn.32 q11, q5 			\n\t"
			"vtrn.32 q10, q6 			\n\t"
			"vtrn.32 q8,  q7 			\n\t"
			"vtrn.32 q9,  q13 			\n\t"

			"vadd.i64  q10, q10, q5 	\n\t"//q
			"vadd.i64  q8 , q8 , q6 	\n\t"//q
			"vadd.i64  q9 , q9 , q7 	\n\t"//q
			"vqadd.u64 d26, d26, d23 	\n\t"//d

			"vext.8 d31, d31, d22, #4 	\n\t"

			//second
			"vldmia %2!,  {q2-q3} 		\n\t"//operand b load
			"vstmia %0!,  {q14-q15} 	\n\t"//store results

			//#1
			"vmlal.u32 q10, d0, d4[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q8,  d2, d4[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q9,  d1, d4[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q13, d3, d4[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q11,q11,q11 			\n\t"

			"vtrn.32 q10, q5 			\n\t"
			"vtrn.32 q8 , q6 			\n\t"
			"vtrn.32 q9,  q7 			\n\t"
			"vtrn.32 q13, q11 			\n\t"

			"vadd.i64  q8,  q8, q5 		\n\t"//q
			"vadd.i64  q9,  q9, q6 		\n\t"//q
			"vadd.i64  q13, q13, q7 	\n\t"//q
			"vqadd.u64 d22, d22, d21 	\n\t"//d

			"vext.8 d28, d28, d20, #4 	\n\t"

			//#2
			"vmlal.u32 q8 , d0, d4[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q9 , d2, d4[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q13, d1, d4[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q11, d3, d4[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q10,q10,q10 			\n\t"

			"vtrn.32 q8,  q5 			\n\t"
			"vtrn.32 q9,  q6 			\n\t"
			"vtrn.32 q13, q7 			\n\t"
			"vtrn.32 q11, q10 			\n\t"

			"vadd.i64  q9, q9, q5 		\n\t"//q
			"vadd.i64  q13, q13, q6 	\n\t"//q
			"vadd.i64  q11, q11, q7 	\n\t"//q
			"vqadd.u64 d20, d20, d17 	\n\t"//d

			"vext.8 d28, d28, d16, #4 	\n\t"

			//# 3
			"vmlal.u32 q9 , d0, d5[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q13, d2, d5[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q11, d1, d5[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q10, d3, d5[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q8,q8,q8 				\n\t"

			"vtrn.32 q9 , q5			\n\t"
			"vtrn.32 q13, q6 			\n\t"
			"vtrn.32 q11, q7 			\n\t"
			"vtrn.32 q10, q8			\n\t"

			"vadd.i64  q13, q13, q5 	\n\t"//q
			"vadd.i64  q11, q11, q6 	\n\t"//q
			"vadd.i64  q10, q10, q7 	\n\t"//q
			"vqadd.u64 d16, d16, d19 	\n\t"//d

			"vext.8 d29, d29, d18, #4 	\n\t"

			//step 4

			"vmlal.u32 q13, d0, d5[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q11, d2, d5[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q10, d1, d5[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q8 , d3, d5[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q9,q9,q9 				\n\t"

			"vtrn.32 q13, q5 			\n\t"
			"vtrn.32 q11, q6 			\n\t"
			"vtrn.32 q10, q7 			\n\t"
			"vtrn.32 q8 , q9 			\n\t"

			"vadd.i64  q11, q11, q5 	\n\t"//q
			"vadd.i64  q10, q10, q6 	\n\t"//q
			"vadd.i64  q8 , q8 , q7 	\n\t"//q
			"vqadd.u64 d18, d18, d27 	\n\t"//d

			"vext.8 d29, d29, d26, #4 	\n\t"

			//step 5

			"vmlal.u32 q11, d0, d6[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q10, d2, d6[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q8 , d1, d6[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q9,  d3, d6[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q13,q13,q13 			\n\t"

			"vtrn.32 q11, q5 			\n\t"
			"vtrn.32 q10, q6 			\n\t"
			"vtrn.32 q8,  q7 			\n\t"
			"vtrn.32 q9,  q13 			\n\t"

			"vadd.i64  q10, q10, q5 	\n\t"//q
			"vadd.i64  q8 , q8 , q6 	\n\t"//q
			"vadd.i64  q9 , q9 , q7 	\n\t"//q
			"vqadd.u64 d26, d26, d23 	\n\t"//d

			"vext.8 d30, d30, d22, #4 	\n\t"

			//step 6
			"vmlal.u32 q10, d0, d6[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q8,  d2, d6[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q9,  d1, d6[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q13, d3, d6[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q11,q11,q11 			\n\t"

			"vtrn.32 q10, q5 			\n\t"
			"vtrn.32 q8 , q6 			\n\t"
			"vtrn.32 q9,  q7 			\n\t"
			"vtrn.32 q13, q11 			\n\t"

			"vadd.i64  q8,  q8, q5 		\n\t"//q
			"vadd.i64  q9,  q9, q6 		\n\t"//q
			"vadd.i64  q13, q13, q7 	\n\t"//q
			"vqadd.u64 d22, d22, d21 	\n\t"//d

			"vext.8 d30, d30, d20, #4 	\n\t"

			//step 7
			"vmlal.u32 q8 , d0, d7[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q9 , d2, d7[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q13, d1, d7[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q11, d3, d7[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q10,q10,q10 			\n\t"

			"vtrn.32 q8,  q5 			\n\t"
			"vtrn.32 q9,  q6 			\n\t"
			"vtrn.32 q13, q7 			\n\t"
			"vtrn.32 q11, q10 			\n\t"

			"vadd.i64  q9, q9, q5 		\n\t"//q
			"vadd.i64  q13, q13, q6 	\n\t"//q
			"vadd.i64  q11, q11, q7 	\n\t"//q
			"vqadd.u64 d20, d20, d17 	\n\t"//d

			"vext.8 d31, d31, d16, #4 	\n\t"

			//#8
			"vmlal.u32 q9 , d0, d7[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q13, d2, d7[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q11, d1, d7[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q10, d3, d7[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q8,q8,q8 				\n\t"

			"vtrn.32 q9 , q5 			\n\t"
			"vtrn.32 q13, q6 			\n\t"
			"vtrn.32 q11, q7 			\n\t"
			"vtrn.32 q10, q8 			\n\t"

			"vadd.i64  q13, q13, q5 	\n\t"//q
			"vadd.i64  q11, q11, q6 	\n\t"//q
			"vadd.i64  q10, q10, q7 	\n\t"//q
			"vqadd.u64 d16, d16, d19 	\n\t"//d

			"vext.8 d31, d31, d18, #4 	\n\t"

			//13 11 10 16
			//third

			"vpop   {q0-q1} 			\n\t"
			//"vstmia %0!,  {q14-q15} \n\t"	//store results

//////////////////////////////////////////////////////////////////////////////////completed..

			"vmov.i64 d8, #0x0 			\n\t"
			"vmov.i64 d9, #0xFFFFFFFFFFFFFFFF \n\t"
			"vsub.i64  d8, d8, d9 		\n\t"//q

			"vpush {q8} 				\n\t"
			"vpush {q10} 				\n\t"
			"vpush {q11} 				\n\t"
			"vpush {q13} 				\n\t"

			"vtrn.32 q14 , q15 			\n\t"

			//expansion

			"vmull.u32 q10 , d28, d8[0] \n\t"//A4A0 X B0B0
			"vmull.u32 q8 ,  d30, d8[0] \n\t"//A4A0 X B0B0
			"vmull.u32 q9 ,  d29, d8[0] \n\t"//A4A0 X B0B0
			"vmull.u32 q13 , d31, d8[0] \n\t"//A4A0 X B0B0

			"vldmia r3!,  {q2-q3} 		\n\t"//operand b load

			//#1
			"vmlal.u32 q10, d0, d4[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q8,  d2, d4[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q9,  d1, d4[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q13, d3, d4[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q11,q11,q11 			\n\t"

			"vtrn.32 q10, q5			\n\t"
			"vtrn.32 q8 , q6 			\n\t"
			"vtrn.32 q9,  q7 			\n\t"
			"vtrn.32 q13, q11 			\n\t"

			"vadd.i64  q8,  q8, q5 		\n\t"//q
			"vadd.i64  q9,  q9, q6 		\n\t"//q
			"vadd.i64  q13, q13, q7 	\n\t"//q
			"vqadd.u64 d22, d22, d21 	\n\t"//d

			"vext.8 d28, d28, d20, #4 	\n\t"

			//#2
			"vmlal.u32 q8 , d0, d4[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q9 , d2, d4[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q13, d1, d4[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q11, d3, d4[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q10,q10,q10 			\n\t"

			"vtrn.32 q8,  q5 			\n\t"
			"vtrn.32 q9,  q6 			\n\t"
			"vtrn.32 q13, q7 			\n\t"
			"vtrn.32 q11, q10 			\n\t"

			"vadd.i64  q9, q9, q5 		\n\t"//q
			"vadd.i64  q13, q13, q6 	\n\t"//q
			"vadd.i64  q11, q11, q7 	\n\t"//q
			"vqadd.u64 d20, d20, d17 	\n\t"//d

			"vext.8 d28, d28, d16, #4 	\n\t"

			//# 3
			"vmlal.u32 q9 , d0, d5[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q13, d2, d5[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q11, d1, d5[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q10, d3, d5[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q8,q8,q8 				\n\t"

			"vtrn.32 q9 , q5 			\n\t"
			"vtrn.32 q13, q6 			\n\t"
			"vtrn.32 q11, q7 			\n\t"
			"vtrn.32 q10, q8 			\n\t"

			"vadd.i64  q13, q13, q5 	\n\t"//q
			"vadd.i64  q11, q11, q6 	\n\t"//q
			"vadd.i64  q10, q10, q7 	\n\t"//q
			"vqadd.u64 d16, d16, d19 	\n\t"//d

			"vext.8 d29, d29, d18, #4 	\n\t"

			//step 4

			"vmlal.u32 q13, d0, d5[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q11, d2, d5[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q10, d1, d5[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q8 , d3, d5[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q9,q9,q9 				\n\t"

			"vtrn.32 q13, q5 			\n\t"
			"vtrn.32 q11, q6 			\n\t"
			"vtrn.32 q10, q7 			\n\t"
			"vtrn.32 q8 , q9 			\n\t"

			"vadd.i64  q11, q11, q5 	\n\t"//q
			"vadd.i64  q10, q10, q6 	\n\t"//q
			"vadd.i64  q8 , q8 , q7 	\n\t"//q
			"vqadd.u64 d18, d18, d27 	\n\t"//d

			"vext.8 d29, d29, d26, #4 	\n\t"

			//middle
			//"vadd.i64  q11, q11, q5 \n\t"		//q
			//"vadd.i64  q10, q10, q6 \n\t"		//q
			//"vadd.i64  q8 , q8 , q7 \n\t"		//q
			//"vadd.i64  q9 , q9 , q7 \n\t"		//q

			//step 5

			"vmlal.u32 q11, d0, d6[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q10, d2, d6[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q8 , d1, d6[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q9,  d3, d6[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q13,q13,q13 			\n\t"

			"vtrn.32 q11, q5 			\n\t"
			"vtrn.32 q10, q6 			\n\t"
			"vtrn.32 q8,  q7 			\n\t"
			"vtrn.32 q9,  q13 			\n\t"

			"vadd.i64  q10, q10, q5 	\n\t"//q
			"vadd.i64  q8 , q8 , q6 	\n\t"//q
			"vadd.i64  q9 , q9 , q7 	\n\t"//q
			"vqadd.u64 d26, d26, d23 	\n\t"//d

			"vext.8 d30, d30, d22, #4 	\n\t"

			//step 6
			"vmlal.u32 q10, d0, d6[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q8,  d2, d6[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q9,  d1, d6[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q13, d3, d6[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q11,q11,q11 			\n\t"

			"vtrn.32 q10, q5 			\n\t"
			"vtrn.32 q8 , q6 			\n\t"
			"vtrn.32 q9,  q7 			\n\t"
			"vtrn.32 q13, q11 			\n\t"

			"vadd.i64  q8,  q8, q5 		\n\t"//q
			"vadd.i64  q9,  q9, q6		\n\t"//q
			"vadd.i64  q13, q13, q7 	\n\t"//q
			"vqadd.u64 d22, d22, d21 	\n\t"//d

			"vext.8 d30, d30, d20, #4 	\n\t"

			//step 7
			"vmlal.u32 q8 , d0, d7[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q9 , d2, d7[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q13, d1, d7[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q11, d3, d7[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q10,q10,q10 			\n\t"

			"vtrn.32 q8,  q5 			\n\t"
			"vtrn.32 q9,  q6 			\n\t"
			"vtrn.32 q13, q7 			\n\t"
			"vtrn.32 q11, q10 			\n\t"

			"vadd.i64  q9, q9, q5 		\n\t"//q
			"vadd.i64  q13, q13, q6 	\n\t"//q
			"vadd.i64  q11, q11, q7 	\n\t"//q
			"vqadd.u64 d20, d20, d17 	\n\t"//d

			"vext.8 d31, d31, d16, #4 	\n\t"

			//#8
			"vmlal.u32 q9 , d0, d7[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q13, d2, d7[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q11, d1, d7[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q10, d3, d7[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q8,q8,q8 				\n\t"

			"vtrn.32 q9 , q5 			\n\t"
			"vtrn.32 q13, q6 			\n\t"
			"vtrn.32 q11, q7 			\n\t"
			"vtrn.32 q10, q8 			\n\t"

			"vadd.i64  q13, q13, q5 	\n\t"//q
			"vadd.i64  q11, q11, q6 	\n\t"//q
			"vadd.i64  q10, q10, q7 	\n\t"//q
			"vqadd.u64 d16, d16, d19 	\n\t"//d

			"vext.8 d31, d31, d18, #4 	\n\t"

			//////
			"vpop   {q4-q7} 			\n\t"

			"vadd.i64  q13, q13, q4 	\n\t"//q
			"vadd.i64  q11, q11, q5 	\n\t"//q
			"vadd.i64  q10 , q10 , q6 	\n\t"//q
			"vadd.i64  q8 , q8 , q7 	\n\t"//q

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q12,q12,q12 			\n\t"

			"vtrn.32 q13, q5 			\n\t"
			"vtrn.32 q11, q6 			\n\t"
			"vtrn.32 q10, q7 			\n\t"
			"vtrn.32 q8 , q12 			\n\t"

			"vadd.i64  q11, q11, q5 	\n\t"//q
			"vadd.i64  q10, q10,  q6 	\n\t"//q
			"vadd.i64  q8,  q8,  q7 	\n\t"//q
			"vqadd.u64 d27, d27, d24 	\n\t"//d

			"vpush {d25} 				\n\t"//saving upper part...

			"vstmia %0!,  {q14-q15} 	\n\t"//store results

			///fourth

			"vldmia r3!,  {q2-q3} 		\n\t"//operand b load

			//step 1

			"vmlal.u32 q13, d0, d4[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q11, d2, d4[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q10, d1, d4[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q8 , d3, d4[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q9,q9,q9 				\n\t"

			"vtrn.32 q13, q5 			\n\t"
			"vtrn.32 q11, q6 			\n\t"
			"vtrn.32 q10, q7 			\n\t"
			"vtrn.32 q8 , q9 			\n\t"

			"vadd.i64  q11, q11, q5 	\n\t"//q
			"vadd.i64  q10, q10, q6 	\n\t"//q
			"vadd.i64  q8 , q8 , q7 	\n\t"//q
			"vqadd.u64 d18, d18, d27 	\n\t"//d

			"vext.8 d28, d28, d26, #4 	\n\t"

			//step 2

			"vmlal.u32 q11, d0, d4[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q10, d2, d4[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q8 , d1, d4[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q9,  d3, d4[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q13,q13,q13 			\n\t"

			"vtrn.32 q11, q5 			\n\t"
			"vtrn.32 q10, q6 			\n\t"
			"vtrn.32 q8,  q7 			\n\t"
			"vtrn.32 q9,  q13 			\n\t"

			"vadd.i64  q10, q10, q5 	\n\t"//q
			"vadd.i64  q8 , q8 , q6 	\n\t"//q
			"vadd.i64  q9 , q9 , q7 	\n\t"//q
			"vqadd.u64 d26, d26, d23 	\n\t"//d

			"vext.8 d28, d28, d22, #4 	\n\t"

			//step 3
			"vmlal.u32 q10, d0, d5[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q8,  d2, d5[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q9,  d1, d5[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q13, d3, d5[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q11,q11,q11 			\n\t"

			"vtrn.32 q10, q5 			\n\t"
			"vtrn.32 q8 , q6 			\n\t"
			"vtrn.32 q9,  q7 			\n\t"
			"vtrn.32 q13, q11 			\n\t"

			"vadd.i64  q8,  q8, q5 		\n\t"//q
			"vadd.i64  q9,  q9, q6 		\n\t"//q
			"vadd.i64  q13, q13, q7 	\n\t"//q
			"vqadd.u64 d22, d22, d21 	\n\t"//d

			"vext.8 d29, d29, d20, #4 	\n\t"

			//step 4
			"vmlal.u32 q8 , d0, d5[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q9 , d2, d5[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q13, d1, d5[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q11, d3, d5[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q10,q10,q10 			\n\t"

			"vtrn.32 q8,  q5 			\n\t"
			"vtrn.32 q9,  q6 			\n\t"
			"vtrn.32 q13, q7 			\n\t"
			"vtrn.32 q11, q10 			\n\t"

			"vadd.i64  q9, q9, q5 		\n\t"//q
			"vadd.i64  q13, q13, q6 	\n\t"//q
			"vadd.i64  q11, q11, q7 	\n\t"//q
			"vqadd.u64 d20, d20, d17 	\n\t"//d

			"vext.8 d29, d29, d16, #4 	\n\t"

			//#5
			"vmlal.u32 q9 , d0, d6[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q13, d2, d6[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q11, d1, d6[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q10, d3, d6[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q8,q8,q8 				\n\t"

			"vtrn.32 q9 , q5 			\n\t"
			"vtrn.32 q13, q6 			\n\t"
			"vtrn.32 q11, q7 			\n\t"
			"vtrn.32 q10, q8 			\n\t"

			"vadd.i64  q13, q13, q5 	\n\t"//q
			"vadd.i64  q11, q11, q6 	\n\t"//q
			"vadd.i64  q10, q10, q7 	\n\t"//q
			"vqadd.u64 d16, d16, d19 	\n\t"//d

			"vext.8 d30, d30, d18, #4 	\n\t"

			//step 6

			"vmlal.u32 q13, d0, d6[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q11, d2, d6[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q10, d1, d6[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q8 , d3, d6[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q9,q9,q9 				\n\t"

			"vtrn.32 q13, q5 			\n\t"
			"vtrn.32 q11, q6 			\n\t"
			"vtrn.32 q10, q7 			\n\t"
			"vtrn.32 q8 , q9 			\n\t"

			"vadd.i64  q11, q11, q5 	\n\t"//q
			"vadd.i64  q10, q10, q6 	\n\t"//q
			"vadd.i64  q8 , q8 , q7 	\n\t"//q
			"vqadd.u64 d18, d18, d27 	\n\t"//d

			"vext.8 d30, d30, d26, #4 	\n\t"

			//step 7
			"vmlal.u32 q11, d0, d7[0] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q10, d2, d7[0] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q8 , d1, d7[0] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q9,  d3, d7[0] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q13,q13,q13 			\n\t"

			"vtrn.32 q11, q5 			\n\t"
			"vtrn.32 q10, q6 			\n\t"
			"vtrn.32 q8,  q7 			\n\t"
			"vtrn.32 q9,  q13 			\n\t"

			"vadd.i64  q10, q10, q5 	\n\t"//q
			"vadd.i64  q8 , q8 , q6 	\n\t"//q
			"vadd.i64  q9 , q9 , q7 	\n\t"//q
			"vqadd.u64 d26, d26, d23 	\n\t"//d

			"vext.8 d31, d31, d22, #4 	\n\t"

			//step 8
			"vmlal.u32 q10, d0, d7[1] 	\n\t"//A4A0 X B0B0
			"vmlal.u32 q8,  d2, d7[1] 	\n\t"//A5A1 X B0B0
			"vmlal.u32 q9,  d1, d7[1] 	\n\t"//A6A2 X B0B0
			"vmlal.u32 q13, d3, d7[1] 	\n\t"//A7A3 X B0B0

			"veor q5,q5,q5 				\n\t"
			"veor q6,q6,q6 				\n\t"
			"veor q7,q7,q7 				\n\t"
			"veor q11,q11,q11 			\n\t"

			"vtrn.32 q10, q5 			\n\t"
			"vtrn.32 q8 , q6 			\n\t"
			"vtrn.32 q9,  q7 			\n\t"
			"vtrn.32 q13, q11 			\n\t"

			"vpop {d4} 					\n\t"//restoring upper part...	it would be used later...
			"vadd.i64  q8,  q8, q5 		\n\t"//q
			"vadd.i64  q9,  q9, q6 		\n\t"//q
			"vadd.i64  q13, q13, q7 	\n\t"//q
			"vqadd.u64 d22, d22, d21 	\n\t"//d
			"vqadd.u64 d16, d16, d4 	\n\t"//d

			"vext.8 d31, d31, d20, #4 	\n\t"

//last	d19
			"vmov r3, r4, d16 			\n\t"
			"vmov r5, r6, d18 			\n\t"
			"vmov r7, r8, d26 			\n\t"
			"vmov r9, r10, d22 			\n\t"

			"vstmia %0!,  {q14-q15} 	\n\t"//store results

			"adds r4, r4, r5 			\n\t"
			"adcs r5, r6, r7 			\n\t"
			"adcs r6, r8, r9 			\n\t"
			"adcs r10, r10, #0 			\n\t"

			"stmia %0!,  {r3-r6} 		\n\t"//operand in load
			"mov r3,r10 				\n\t"

			"vmov r4, r5, d17 			\n\t"
			"vmov r6, r7, d19 			\n\t"
			"vmov r8, r9, d27 			\n\t"
			"vmov r10, r11, d23 		\n\t"

			"adcs r3, r3, r4 			\n\t"
			"adcs r4, r5, r6 			\n\t"
			"adcs r5, r7, r8 			\n\t"
			"adcs r6, r9, r10 			\n\t"

			"stmia %0!,  {r3-r6} 	\n\t"//operand in load

			"vpop {q4-q7}				\n\t"
			"pop  {r4-r11}				\n\t"

			:
			:"r"(&c[0]),"r"(&a[0]),"r"(&b[0])
			:
	);
}
