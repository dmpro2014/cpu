#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include <stdint.h>

uint32_t square_kernel[] = {
		0x08090000, // ldc $9, 0 ; x & y offset
		0x00023a41, // srl $7, $2, 9 ; load y value
		0x000159c0, // sll $11, $1, 7 ; Load shifted hi value
		0x00eb3804, // add $7, $7, $11 ; Stitch together hi and low
		0x040801ff, // addi $8, $0, 511
		0x01024006, // and $8, $8, $2 ; load x value
		0x04060000, // addi $6, $0, 0 ; Disable masking
		0x04050000, // addi $5, $0, 0 ; Set default color to black
		0x00e93003, // slt $6, $7, $9
		0x81093003, // ? slt $6, $8, $9
		0x040a0200, // addi $10, $0, 512
		0x01495005, // sub $10, $10, $9
		0x81483003, // ? slt $6, $10, $8
		0x040a0100, // addi $10, $0, 256
		0x01495005, // sub $10, $10, $9
		0x81473003, // ? slt $6, $10, $7
		0x8405f800, // ? addi $5, $0, 0b1111100000000000 ; red
		0x00011804, // add $3, $0, $1
		0x00022004, // add $4, $0, $2
		0x10000000, // sw
		0x40000000, // thread_finished
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000 // nop
};

uint32_t id_kernel[] = {
		0x00000000, // nop
		0x00000000, // nop
		0x00022804, // add $5, $0, $2
		0x00011804, // add $3, $0, $1
		0x00022004, // add $4, $0, $2
		0x10000000, // sw
		0x40000000, // thread_finished
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000 // nop
};
uint32_t test_kernel[] = {
		0x0405f81f, // addi $5, $0, 0b1111100000011111
		0x00011804, // add $3, $0, $1
		0x00022004, // add $4, $0, $2
		0x10000000, // sw
		0x40000000, // thread_finished
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000 // nop
};

#endif /* INSTRUCTIONS_H_ */
