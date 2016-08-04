#include "arith.h"
#include <jni.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpu-features.h>
#include <arm_neon.h>

unsigned int DIFF_512(uint32_t* c, uint32_t sign) {
	asm(
			//"push  {r4-r12,lr}			\n\t"

			"ldmia %0,  {r2-r9} 		\n\t"
			"eor r2, r2, r1 			\n\t"
			"eor r3, r3, r1 			\n\t"
			"eor r4, r4, r1 			\n\t"
			"eor r5, r5, r1 			\n\t"

			"eor r6, r6, r1 			\n\t"
			"eor r7, r7, r1 			\n\t"
			"eor r8, r8, r1 			\n\t"
			"eor r9, r9, r1 			\n\t"

			"subs r2, r2, r1			\n\t"
			"sbcs r3, r3, r1			\n\t"
			"sbcs r4, r4, r1			\n\t"
			"sbcs r5, r5, r1			\n\t"

			"sbcs r6, r6, r1			\n\t"
			"sbcs r7, r7, r1			\n\t"
			"sbcs r8, r8, r1			\n\t"
			"sbcs r9, r9, r1			\n\t"
			"sbcs r10, r10, r10			\n\t"
			"stmia %0!, {r2-r9} 		\n\t"

			"ldmia %0,  {r2-r9} 		\n\t"
			"eor r2, r2, r1 			\n\t"
			"eor r3, r3, r1 			\n\t"
			"eor r4, r4, r1 			\n\t"
			"eor r5, r5, r1 			\n\t"

			"eor r6, r6, r1 			\n\t"
			"eor r7, r7, r1 			\n\t"
			"eor r8, r8, r1 			\n\t"
			"eor r9, r9, r1 			\n\t"

			"mov r11, #0				\n\t"
			"subs r11, r11, r10			\n\t"

			"sbcs r2, r2, r1			\n\t"
			"sbcs r3, r3, r1			\n\t"
			"sbcs r4, r4, r1			\n\t"
			"sbcs r5, r5, r1			\n\t"

			"sbcs r6, r6, r1			\n\t"
			"sbcs r7, r7, r1			\n\t"
			"sbcs r8, r8, r1			\n\t"
			"sbcs r9, r9, r1			\n\t"

			"sbcs r10, r10, r10			\n\t"
			"add  r10, r10, #1			\n\t"

			"stmia %0!, {r2-r9} 		\n\t"

			"eor r0, r10, #1				\n\t"

			:
			:"r"(&c[0]),"r"(sign)
			:"r2","r3","r4","r5","r6","r7","r8","r9","r10","r11"
	);
}

unsigned int DIFF_1024(uint32_t* c, uint32_t sign) {
	asm(
			//"push  {r4-r12,lr}			\n\t"
			"ldmia %0,  {r2-r9} 		\n\t"
			"eor r2, r2, r1 			\n\t"
			"eor r3, r3, r1 			\n\t"
			"eor r4, r4, r1 			\n\t"
			"eor r5, r5, r1 			\n\t"

			"eor r6, r6, r1 			\n\t"
			"eor r7, r7, r1 			\n\t"
			"eor r8, r8, r1 			\n\t"
			"eor r9, r9, r1 			\n\t"

			"subs r2, r2, r1			\n\t"
			"sbcs r3, r3, r1			\n\t"
			"sbcs r4, r4, r1			\n\t"
			"sbcs r5, r5, r1			\n\t"

			"sbcs r6, r6, r1			\n\t"
			"sbcs r7, r7, r1			\n\t"
			"sbcs r8, r8, r1			\n\t"
			"sbcs r9, r9, r1			\n\t"
			"sbcs r10, r10, r10			\n\t"
			"stmia %0!, {r2-r9} 		\n\t"

			"ldmia %0,  {r2-r9} 		\n\t"
			"eor r2, r2, r1 			\n\t"
			"eor r3, r3, r1 			\n\t"
			"eor r4, r4, r1 			\n\t"
			"eor r5, r5, r1 			\n\t"

			"eor r6, r6, r1 			\n\t"
			"eor r7, r7, r1 			\n\t"
			"eor r8, r8, r1 			\n\t"
			"eor r9, r9, r1 			\n\t"

			"mov r11, #0				\n\t"
			"subs r11, r11, r10			\n\t"

			"sbcs r2, r2, r1			\n\t"
			"sbcs r3, r3, r1			\n\t"
			"sbcs r4, r4, r1			\n\t"
			"sbcs r5, r5, r1			\n\t"

			"sbcs r6, r6, r1			\n\t"
			"sbcs r7, r7, r1			\n\t"
			"sbcs r8, r8, r1			\n\t"
			"sbcs r9, r9, r1			\n\t"
			"sbcs r10, r10, r10			\n\t"
			"stmia %0!, {r2-r9} 		\n\t"

			"ldmia %0,  {r2-r9} 		\n\t"
			"eor r2, r2, r1 			\n\t"
			"eor r3, r3, r1 			\n\t"
			"eor r4, r4, r1 			\n\t"
			"eor r5, r5, r1 			\n\t"

			"eor r6, r6, r1 			\n\t"
			"eor r7, r7, r1 			\n\t"
			"eor r8, r8, r1 			\n\t"
			"eor r9, r9, r1 			\n\t"

			"mov r11, #0				\n\t"
			"subs r11, r11, r10			\n\t"

			"sbcs r2, r2, r1			\n\t"
			"sbcs r3, r3, r1			\n\t"
			"sbcs r4, r4, r1			\n\t"
			"sbcs r5, r5, r1			\n\t"

			"sbcs r6, r6, r1			\n\t"
			"sbcs r7, r7, r1			\n\t"
			"sbcs r8, r8, r1			\n\t"
			"sbcs r9, r9, r1			\n\t"
			"sbcs r10, r10, r10			\n\t"
			"stmia %0!, {r2-r9} 		\n\t"

			"ldmia %0,  {r2-r9} 		\n\t"
			"eor r2, r2, r1 			\n\t"
			"eor r3, r3, r1 			\n\t"
			"eor r4, r4, r1 			\n\t"
			"eor r5, r5, r1 			\n\t"

			"eor r6, r6, r1 			\n\t"
			"eor r7, r7, r1 			\n\t"
			"eor r8, r8, r1 			\n\t"
			"eor r9, r9, r1 			\n\t"

			"mov r11, #0				\n\t"
			"subs r11, r11, r10			\n\t"

			"sbcs r2, r2, r1			\n\t"
			"sbcs r3, r3, r1			\n\t"
			"sbcs r4, r4, r1			\n\t"
			"sbcs r5, r5, r1			\n\t"

			"sbcs r6, r6, r1			\n\t"
			"sbcs r7, r7, r1			\n\t"
			"sbcs r8, r8, r1			\n\t"
			"sbcs r9, r9, r1			\n\t"

			"sbcs r10, r10, r10			\n\t"
			"add  r10, r10, #1			\n\t"

			"stmia %0!, {r2-r9} 		\n\t"

			"eor r0, r10, #1				\n\t"

			:
			:"r"(&c[0]),"r"(sign)
			:"r2","r3","r4","r5","r6","r7","r8","r9","r10","r11"
	);
}

void AND_512(uint32_t* c, uint32_t* word_in) {
	asm(
			//1
			"ldmia %0,  {r0-r7} 		\n\t"//operand a load
			"ldmia %1,  {r8} 			\n\t"//operand b load

			"eor r8, #0xffffffff 		\n\t"
			"adds  r8, r8, #1 			\n\t"

			"and  r0, r0, r8 			\n\t"
			"and  r1, r1, r8 			\n\t"
			"and  r2, r2, r8 			\n\t"
			"and  r3, r3, r8 			\n\t"

			"and  r4, r4, r8 			\n\t"
			"and  r5, r5, r8 			\n\t"
			"and  r6, r6, r8 			\n\t"
			"and  r7, r7, r8 			\n\t"

			"stmia %0!, {r0-r7} 		\n\t"

			"ldmia %0,  {r0-r7} 		\n\t"//operand a load

			"and  r0, r0, r8 			\n\t"
			"and  r1, r1, r8 			\n\t"
			"and  r2, r2, r8 			\n\t"
			"and  r3, r3, r8 			\n\t"

			"and  r4, r4, r8 			\n\t"
			"and  r5, r5, r8 			\n\t"
			"and  r6, r6, r8 			\n\t"
			"and  r7, r7, r8 			\n\t"

			"stmia %0!, {r0-r7} 		\n\t"

			:
			:"r"(&c[0]),"r"(&word_in[0])
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8","r9"
	);
}

void AND_1024(uint32_t* c, uint32_t* word_in) {
	asm(
			//1
			"ldmia %0,  {r0-r7} 		\n\t"//operand a load
			"ldmia %1,  {r8} 			\n\t"//operand b load

			"eor r8, #0xffffffff 		\n\t"
			"adds  r8, r8, #1 			\n\t"

			"and  r0, r0, r8 			\n\t"
			"and  r1, r1, r8 			\n\t"
			"and  r2, r2, r8 			\n\t"
			"and  r3, r3, r8 			\n\t"

			"and  r4, r4, r8 			\n\t"
			"and  r5, r5, r8 			\n\t"
			"and  r6, r6, r8 			\n\t"
			"and  r7, r7, r8 			\n\t"

			"stmia %0!, {r0-r7} 		\n\t"

			"ldmia %0,  {r0-r7} 		\n\t"//operand a load

			"and  r0, r0, r8 			\n\t"
			"and  r1, r1, r8 			\n\t"
			"and  r2, r2, r8 			\n\t"
			"and  r3, r3, r8 			\n\t"

			"and  r4, r4, r8 			\n\t"
			"and  r5, r5, r8 			\n\t"
			"and  r6, r6, r8 			\n\t"
			"and  r7, r7, r8 			\n\t"

			"stmia %0!, {r0-r7} 		\n\t"

			"ldmia %0,  {r0-r7} 		\n\t"//operand a load

			"and  r0, r0, r8 			\n\t"
			"and  r1, r1, r8 			\n\t"
			"and  r2, r2, r8 			\n\t"
			"and  r3, r3, r8 			\n\t"

			"and  r4, r4, r8 			\n\t"
			"and  r5, r5, r8 			\n\t"
			"and  r6, r6, r8 			\n\t"
			"and  r7, r7, r8 			\n\t"

			"stmia %0!, {r0-r7} 		\n\t"

			"ldmia %0,  {r0-r7} 		\n\t"//operand a load

			"and  r0, r0, r8 			\n\t"
			"and  r1, r1, r8 			\n\t"
			"and  r2, r2, r8 			\n\t"
			"and  r3, r3, r8 			\n\t"

			"and  r4, r4, r8 			\n\t"
			"and  r5, r5, r8 			\n\t"
			"and  r6, r6, r8 			\n\t"
			"and  r7, r7, r8 			\n\t"

			"stmia %0!, {r0-r7} 		\n\t"

			:
			:"r"(&c[0]),"r"(&word_in[0])
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8","r9"
	);
}

void ADD_512_WORD(uint32_t* c, uint32_t* word_in) {

	asm(

			//1
			"ldmia %0,  {r0-r7} 		\n\t"//operand a load
			"ldmia %1,  {r8} 			\n\t"//operand b load

			"mov r9, #0 				\n\t"

			"adds  r0, r0, r8 			\n\t"
			"adcs  r1, r1, #0 			\n\t"
			"adcs  r2, r2, #0 			\n\t"
			"adcs  r3, r3, #0 			\n\t"

			"adcs  r4, r4, #0 			\n\t"
			"adcs  r5, r5, #0 			\n\t"
			"adcs  r6, r6, #0 			\n\t"
			"adcs  r7, r7, #0 			\n\t"
			"adcs  r9, r9, #0 			\n\t"

			"stmia %0!, {r0-r7} 		\n\t"

			"ldmia %0,  {r0-r7} 		\n\t"//operand a load

			"adcs  r0, r0, r9 			\n\t"
			"adcs  r1, r1, #0 			\n\t"
			"adcs  r2, r2, #0 			\n\t"
			"adcs  r3, r3, #0 			\n\t"

			"adcs  r4, r4, #0 			\n\t"
			"adcs  r5, r5, #0 			\n\t"
			"adcs  r6, r6, #0 			\n\t"
			"adcs  r7, r7, #0 			\n\t"

			"stmia %0!, {r0-r7} 		\n\t"

			:
			:"r"(&c[0]),"r"(&word_in[0])
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8","r9"
	);
}

void ADD_1024_WORD(uint32_t* c, uint32_t* word_in) {

	asm(

			//1
			"ldmia %0,  {r0-r7} 		\n\t"//operand a load
			"ldmia %1,  {r8} 			\n\t"//operand b load

			"mov r9, #0 				\n\t"

			"adds  r0, r0, r8 			\n\t"
			"adcs  r1, r1, #0 			\n\t"
			"adcs  r2, r2, #0 			\n\t"
			"adcs  r3, r3, #0 			\n\t"

			"adcs  r4, r4, #0 			\n\t"
			"adcs  r5, r5, #0 			\n\t"
			"adcs  r6, r6, #0 			\n\t"
			"adcs  r7, r7, #0 			\n\t"
			"adcs  r9, r9, #0 			\n\t"
			"stmia %0!, {r0-r7} 		\n\t"

			"ldmia %0,  {r0-r7} 		\n\t"//operand a load

			"adcs  r0, r0, r9 			\n\t"
			"adcs  r1, r1, #0 			\n\t"
			"adcs  r2, r2, #0 			\n\t"
			"adcs  r3, r3, #0 			\n\t"

			"adcs  r4, r4, #0 			\n\t"
			"adcs  r5, r5, #0 			\n\t"
			"adcs  r6, r6, #0 			\n\t"
			"adcs  r7, r7, #0 			\n\t"
			"mov 	r9, #0 				\n\t"
			"adcs  r9, r9, #0 			\n\t"
			"stmia %0!, {r0-r7} 		\n\t"

			//2
			"ldmia %0,  {r0-r7} 		\n\t"//operand a load
			"adcs  r0, r0, r9 			\n\t"
			"adcs  r1, r1, #0 			\n\t"
			"adcs  r2, r2, #0 			\n\t"
			"adcs  r3, r3, #0 			\n\t"

			"adcs  r4, r4, #0 			\n\t"
			"adcs  r5, r5, #0 			\n\t"
			"adcs  r6, r6, #0 			\n\t"
			"adcs  r7, r7, #0 			\n\t"
			"mov 	r9, #0 				\n\t"
			"adcs  r9, r9, #0 			\n\t"
			"stmia %0!, {r0-r7} 		\n\t"

			"ldmia %0,  {r0-r7} 		\n\t"//operand a load
			"adcs  r0, r0, r9 			\n\t"
			"adcs  r1, r1, #0 			\n\t"
			"adcs  r2, r2, #0 			\n\t"
			"adcs  r3, r3, #0 			\n\t"

			"adcs  r4, r4, #0 			\n\t"
			"adcs  r5, r5, #0 			\n\t"
			"adcs  r6, r6, #0 			\n\t"
			"adcs  r7, r7, #0 			\n\t"

			"stmia %0!, {r0-r7} 		\n\t"

			:
			:"r"(&c[0]),"r"(&word_in[0])
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8","r9"
	);
}

unsigned int ADD_512(uint32_t* c, uint32_t* a, uint32_t* b) {
	unsigned int out = 0;
	asm(
			"eor r8,r8,r8 				\n\t"
			//1
			"ldmia %1!,  {r0-r3}		\n\t"//operand a load
			"ldmia %2!,  {r4-r7} 		\n\t"//operand b load

			"adds  r0, r0, r4 			\n\t"
			"adcs  r1, r1, r5 			\n\t"
			"adcs  r2, r2, r6 			\n\t"
			"adcs  r3, r3, r7 			\n\t"

			"stmia %0!, {r0-r3} 		\n\t"

			//2
			"ldmia %2!,  {r4-r7} 		\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 		\n\t"//operand a load

			"adcs  r0, r0, r4 			\n\t"
			"adcs  r1, r1, r5 			\n\t"
			"adcs  r2, r2, r6 			\n\t"
			"adcs  r3, r3, r7 			\n\t"

			"stmia %0!, {r0-r3} 		\n\t"

			//3
			"ldmia %2!,  {r4-r7} 		\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 		\n\t"//operand a load

			"adcs  r0, r0, r4 			\n\t"
			"adcs  r1, r1, r5 			\n\t"
			"adcs  r2, r2, r6 			\n\t"
			"adcs  r3, r3, r7 			\n\t"

			"stmia %0!, {r0-r3} 		\n\t"

			//4
			"ldmia %2!,  {r4-r7} 		\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 		\n\t"//operand a load

			"adcs  r0, r0, r4 			\n\t"
			"adcs  r1, r1, r5 			\n\t"
			"adcs  r2, r2, r6 			\n\t"
			"adcs  r3, r3, r7 			\n\t"
			"adcs  r8, r8, r8 			\n\t"

			"stmia %0!, {r0-r3} 		\n\t"
			"stmia %3, {r8} 			\n\t"

			:
			:"r"(&c[0]),"r"(&a[0]),"r"(&b[0]),"r"(&out)
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8"
	);

	return out;
}

unsigned int ADD_1024(uint32_t* c, uint32_t* a, uint32_t* b) {
	unsigned int out = 0;
	asm(
			"eor r8,r8,r8 \n\t"
			//1
			"ldmia %1!,  {r0-r3} \n\t"//operand a load
			"ldmia %2!,  {r4-r7} \n\t"//operand b load

			"adds  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//2
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//3
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//4
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//5
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//6
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//7
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//8
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"
			"adcs  r8, r8, r8 		\n\t"

			"stmia %0!, {r0-r3} \n\t"
			"stmia %3, {r8} \n\t"

			:
			:"r"(&c[0]),"r"(&a[0]),"r"(&b[0]),"r"(&out)
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8"
	);

	return out;
}

unsigned int ADD_2048(uint32_t* c, uint32_t* a, uint32_t* b) {
	unsigned int out = 0;
	asm(
			"eor r8,r8,r8 \n\t"
			//1
			"ldmia %1!,  {r0-r3} \n\t"//operand a load
			"ldmia %2!,  {r4-r7} \n\t"//operand b load

			"adds  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//2
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//3
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//4
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//5
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//6
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//7
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//8
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//9
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//0
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//1
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//2
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//3
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//4
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//5
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//6
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"adcs  r0, r0, r4 		\n\t"
			"adcs  r1, r1, r5 		\n\t"
			"adcs  r2, r2, r6 		\n\t"
			"adcs  r3, r3, r7 		\n\t"
			"adcs  r8, r8, r8 		\n\t"

			"stmia %0!, {r0-r3} \n\t"
			"stmia %3, {r8} \n\t"

			:
			:"r"(&c[0]),"r"(&a[0]),"r"(&b[0]),"r"(&out)
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8"
	);

	return out;
}

unsigned int SUB_CDT_512(uint32_t* c, uint32_t* a, uint32_t* b, uint32_t carry) {
	asm(
			"sub r8,r8,r8 			\n\t"

			"ldmia %3, {r0}			\n\t"
			"sub r8,r8,r0 			\n\t"

			//1
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"subs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//2
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//3
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//4
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			//
			"sbcs  r8, r8, r8 		\n\t"

			"sub r4, r4, r4			\n\t"
			"sub r4, r4, #1			\n\t"
			"eor r4, r4, r8			\n\t"
			"add r4, r4, #1			\n\t"

			"stmia %0!, {r0-r3} 	\n\t"
			"stmia %3, {r4} 		\n\t"

			:
			:"r"(&c[0]),"r"(&a[0]),"r"(&b[0]),"r"(&carry)
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8"
	);

	return carry;
}

unsigned int SUB_CDT_1024(uint32_t* c, uint32_t* a, uint32_t* b,
		uint32_t carry) {
	asm(
			"sub r8,r8,r8 			\n\t"

			"ldmia %3, {r0}			\n\t"
			"sub r8,r8,r0 			\n\t"

			//1
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"subs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//2
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//3
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//4
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//5
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//6
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//7
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//8
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			//
			"sbcs  r8, r8, r8 		\n\t"

			"sub r4, r4, r4			\n\t"
			"sub r4, r4, #1			\n\t"
			"eor r4, r4, r8			\n\t"
			"add r4, r4, #1			\n\t"

			"stmia %0!, {r0-r3} 	\n\t"
			"stmia %3, {r4} 		\n\t"

			:
			:"r"(&c[0]),"r"(&a[0]),"r"(&b[0]),"r"(&carry)
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8"
	);

	return carry;
}

unsigned int SUB_CDT_2048(uint32_t* c, uint32_t* a, uint32_t* b,
		uint32_t carry) {
	asm(
			"sub r8,r8,r8 			\n\t"

			"ldmia %3, {r0}			\n\t"
			"sub r8,r8,r0 			\n\t"

			//1
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"subs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//2
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//3
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//4
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//5
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//6
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//7
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//8
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"
			//9
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"
			//10
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"
			//11
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//12
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"
			//13
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"
			//14
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//15
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} 	\n\t"

			//16
			"ldmia %2!,  {r4-r7} 	\n\t"//operand b load
			"ldmia %1!,  {r0-r3} 	\n\t"//operand a load

			"and r4, r4, r8			\n\t"
			"and r5, r5, r8			\n\t"
			"and r6, r6, r8			\n\t"
			"and r7, r7, r8			\n\t"

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			//
			"sbcs  r8, r8, r8 		\n\t"

			"sub r4, r4, r4			\n\t"
			"sub r4, r4, #1			\n\t"
			"eor r4, r4, r8			\n\t"
			"add r4, r4, #1			\n\t"

			"stmia %0!, {r0-r3} 	\n\t"
			"stmia %3, {r4} 		\n\t"

			:
			:"r"(&c[0]),"r"(&a[0]),"r"(&b[0]),"r"(&carry)
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8"
	);

	return carry;
}

unsigned int SUB_512(uint32_t* c, uint32_t* a, uint32_t* b) {
	unsigned int out = 0;
	asm(
			"eor r8,r8,r8 \n\t"
			//1
			"ldmia %1!,  {r0-r3} \n\t"//operand a load
			"ldmia %2!,  {r4-r7} \n\t"//operand b load

			"subs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//2
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//3
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//4
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"
			"sbcs  r8, r8, r8 		\n\t"

			"stmia %0!, {r0-r3} \n\t"
			"stmia %3, {r8} \n\t"

			:
			:"r"(&c[0]),"r"(&a[0]),"r"(&b[0]),"r"(&out)
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8"
	);

	return out;
}

unsigned int SUB_1024(uint32_t* c, uint32_t* a, uint32_t* b) {
	unsigned int out = 0;
	asm(
			"eor r8,r8,r8 \n\t"
			//1
			"ldmia %1!,  {r0-r3} \n\t"//operand a load
			"ldmia %2!,  {r4-r7} \n\t"//operand b load

			"subs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//2
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//3
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//4
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//5
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//6
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//7
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//8
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"
			"sbcs  r8, r8, r8 		\n\t"

			"stmia %0!, {r0-r3} \n\t"
			"stmia %3, {r8} \n\t"

			:
			:"r"(&c[0]),"r"(&a[0]),"r"(&b[0]),"r"(&out)
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8"
	);

	return out;
}

unsigned int SUB_2048(uint32_t* c, uint32_t* a, uint32_t* b) {
	unsigned int out = 0;
	asm(
			"eor r8,r8,r8 \n\t"
			//1
			"ldmia %1!,  {r0-r3} \n\t"//operand a load
			"ldmia %2!,  {r4-r7} \n\t"//operand b load

			"subs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//2
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//3
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//4
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//5
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//6
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//7
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//8
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//9
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//0
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//1
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//2
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//3
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//4
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//5
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"

			"stmia %0!, {r0-r3} \n\t"

			//6
			"ldmia %2!,  {r4-r7} \n\t"//operand b load
			"ldmia %1!,  {r0-r3} \n\t"//operand a load

			"sbcs  r0, r0, r4 		\n\t"
			"sbcs  r1, r1, r5 		\n\t"
			"sbcs  r2, r2, r6 		\n\t"
			"sbcs  r3, r3, r7 		\n\t"
			"sbcs  r8, r8, r8 		\n\t"

			"stmia %0!, {r0-r3} \n\t"
			"stmia %3, {r8} \n\t"

			:
			:"r"(&c[0]),"r"(&a[0]),"r"(&b[0]),"r"(&out)
			:"memory","r0","r1","r2","r3","r4","r5","r6","r7","r8"
	);

	return out;
}
