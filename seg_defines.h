/*
 * seg_defines.h
 *
 *  Created on: 15 нояб. 2015 г.
 *      Author: Shtucer
 */

#ifndef SEG_DEFINES_H_
#define SEG_DEFINES_H_

#define SEGA	0b00000001
#define SEGB	0b00000010
#define SEGC	0b00000100
#define SEGE	0b00001000
#define SEGD	0b00010000
#define SEGF	0b00100000
#define SEGG	0b01000000
#define SEGdot	0b10000000

// dp G F D E C B A
unsigned char DIGITS[]={
		0b11000000	// 0
		,0b11111001	// 1
		,0b10100100	// 2
		,0b10101000	// 3
		,0b10011001	// 4
		,0b10001010	// 5
		,0b10000010	// 6
		,0b11111000	// 7
		,0b10000000	// 8
		,0b10001000	// 9
};

unsigned char SYMBOLS[]={
		 0xFF & ~(SEGG) // "-"
		 ,0xFF & ~(SEGA | SEGF | SEGG | SEGD | SEGE) // E

};



#endif /* SEG_DEFINES_H_ */
