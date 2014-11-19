#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include <stdint.h>

uint32_t square_kernel[] = {
		0x00000000,
		0x00000000,
		0x08090000, // ldc $9, 2 ; x & y offset
		0x000239c1, // srl $7, $2, 7 ; load y value
		0x00015a40, // sll $11, $1, 9 ; Load shifted hi value
		0x00eb3804, // add $7, $7, $11 ; Stitch together hi and low
		0x0408007f, // addi $8, $0, 127
		0x01024006, // and $8, $8, $2 ; load x value
		0x04060000, // addi $6, $0, 0 ; Disable masking
		0x04050000, // addi $5, $0, 0 ; Set default color to black
		0x00e93003, // slt $6, $7, $9
		0x81093003, // ? slt $6, $8, $9
		0x040a0080, // addi $10, $0, 128
		0x01495005, // sub $10, $10, $9
		0x81483003, // ? slt $6, $10, $8
		0x040a0040, // addi $10, $0, 64
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
		0x00000000, // nop
		0x00022804, // add $5, $0, $2
		0x00000000, // nop
		0x00011804, // add $3, $0, $1
		0x00000000, // nop
		0x00022004, // add $4, $0, $2
		0x00000000, // nop
		0x10000000, // sw
		0x00000000, // nop
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

uint32_t led_kernel[] = {
		0x00000000, // nop
		0x00000000, // nop
		0x7C000000, // led on
		//0x00000000, // nop
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

uint32_t constants[] = {
		0x00000000, // nop
		0x00000000, // nop
		0x08050001, // ldc $5, 1
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

uint32_t flip[] = {
		0x00000000,
		0x00000000,
		0x08070000, // ldc $7, 0 ; Load framebuffer offset
		0x00e22004, // add $4, $7, $2 ; Setup write address
		0x00073003, // slt $6, $0, $7 ; Enable masking
		0x00002804, // add $5, $0, $0 ; Reset register
		0x840507ff, // ? addi $5, $0, 0b0000011111111111 ; Conditionally write red
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

uint32_t srl[] = {
		0x00000000,
		0x00000000,
		0x00022981, // srl $5, $2, 3
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

uint32_t test_64_width[] = {
        0x00000000, // nop
        0x00000000, // nop
        0x040507ff, // addi $5, $0, 0b0000011111111111 ; load red
        0x00022004, // add $4, $0, $2 ; setup address
        0x04070040, // addi $7, $0, 0b0000000001000000 ;
        0x00e23006, // and $6, $7, $2 ; enable maskin if id % 64
        0x8405f81f, // ? addi $5, $0, 0b1111100000011111 ; load green conditionally
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

uint32_t draw_square[] = {
	    0x00000000, ///-- ; $8 -> x value
	    0x00000000, //-- ; $9 -> y value
	    0x00000000, //-- ;
	    0x00000000, //-- ; $12 -> near, x value
	    0x00000000, //-- ; $13 -> near, y value
	    0x00000000, //-- ; $14 -> far, x value
	    0x00000000, //-- ; $15 -> far, y value
	    0x00000000, //-- ;
	    0x080c0000, //-- ldc $12, 0
	    0x080d0001, //-- ldc $13, 1
	    0x080e0002, //-- ldc $14, 2
	    0x080f0003, //-- ldc $15, 3
	    0x00000000, //-- ;
	    0x000239c1, //-- srl $7, $2, 7 ; load y value
	    0x00015a40, //-- sll $11, $1, 9 ; Load shifted hi value
	    0x00eb3804, //-- add $7, $7, $11 ; Stitch together hi and low
	    0x00000000, //-- ;
	    0x0408003f, //-- addi $8, $0, 63
	    0x01024006, //-- and $8, $8, $id_lo ; load x value
	    0x04060000, //-- addi $mask, $0, 0 ; Disable masking
	    0x04052893, //-- addi $lsu_data, $0, 0b0010100010010011 ; Set default color
	    0x00000000, //-- ;
	    0x010c3003, //-- slt $mask, $8, $12 ; x < near
	    0x80ed3003, //-- ? slt $mask, $7, $13 ; y < near
	    0x00000000, //-- ;
	    0x81c83003, //-- ? slt $mask, $14, $8 ; far < x
	    0x81e73003, //-- ? slt $mask, $15, $7 ; far < y
	    0x00000000, //-- ;
	    0x8405f800, //-- ? addi $5, $0, 0b1111100000000000 ; red
	    0x00000000, //-- ;
	    0x00011804, //-- add $address_hi, $0, $id_hi
	    0x00022004, //-- add $address_lo, $0, $id_lo
	    0x10000000, //-- sw
	    0x40000000 //- thread_finished
};

#endif /* INSTRUCTIONS_H_ */
