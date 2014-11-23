#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include <stdint.h>
#include "demolicious.h"

instruction_t square_kernel[] = {
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
		0x40000000 // thread_finished
};

instruction_t id_kernel[] = {
		0x00022804, // add $data, $0, $2
		0x00000000, // nop
		0x00011804, // add $3, $0, $1
		0x00000000, // nop
		0x00022004, // add $4, $0, $2
		0x00000000, // nop
		0x10000000, // sw
		0x00000000, // nop
		0x40000000 // thread_finished
};
instruction_t test_kernel[] = {
		0x0405f81f, // addi $5, $0, 0b1111100000011111
		0x00011804, // add $3, $0, $1
		0x00022004, // add $4, $0, $2
		0x10000000, // sw
		0x40000000 // thread_finished
};

instruction_t led_kernel[] = {
		0x7C000000, // led on
		0x40000000 // thread_finished
};

instruction_t constants[] = {
		0x08050001, // ldc $5, 1
		0x00011804, // add $3, $0, $1
		0x00022004, // add $4, $0, $2
		0x10000000, // sw
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x40000000 // thread_finished
};

instruction_t flip[] = {
		0x08070000, // ldc $7, 0 ; Load framebuffer offset
		0x00e22004, // add $4, $7, $2 ; Setup write address
		0x00073003, // slt $6, $0, $7 ; Enable masking
		0x00002804, // add $5, $0, $0 ; Reset register
		0x840507ff, // ? addi $5, $0, 0b0000011111111111 ; Conditionally write red
		0x10000000, // sw
		0x40000000 // thread_finished
};

instruction_t srl[] = {
		0x00022981, // srl $5, $2, 3
		0x00011804, // add $3, $0, $1
		0x00022004, // add $4, $0, $2
		0x10000000, // sw
		0x00000000, // nop
		0x00000000, // nop
		0x00000000, // nop
		0x40000000 // thread_finished
};

instruction_t test_64_width[] = {
        0x040507ff, // addi $5, $0, 0b0000011111111111 ; load red
        0x00022004, // add $4, $0, $2 ; setup address
        0x04070040, // addi $7, $0, 0b0000000001000000 ;
        0x00e23006, // and $6, $7, $2 ; enable maskin if id % 64
        0x8405f81f, // ? addi $5, $0, 0b1111100000011111 ; load green conditionally
        0x10000000, // sw
        0x40000000 // thread_finished
};

instruction_t draw_square[] = {
	    0x080c0000, //-- ldc $12, 0
	    0x080d0001, //-- ldc $13, 1
	    0x080e0002, //-- ldc $14, 2
	    0x080f0003, //-- ldc $15, 3
	    0x00023981, //-- srl $7, $2, 6 ; load y value
	    0x0408003f, //-- addi $8, $0, 63
	    0x01024006, //-- and $8, $8, $id_lo ; load x value
	    0x04060000, //-- addi $mask, $0, 0 ; Disable masking
	    0x04052893, //-- addi $lsu_data, $0, 0b0010100010010011 ; Set default color
	    0x010c3003, //-- slt $mask, $8, $12 ; x < near
	    0x80ed3003, //-- ? slt $mask, $7, $13 ; y < near
	    0x81c83003, //-- ? slt $mask, $14, $8 ; far < x
	    0x81e73003, //-- ? slt $mask, $15, $7 ; far < y
	    0x8405f800, //-- ? addi $5, $0, 0b1111100000000000 ; red
	    0x00011804, //-- add $address_hi, $0, $id_hi
	    0x00022004, //-- add $address_lo, $0, $id_lo
	    0x10000000, //-- sw
	    0x40000000 //- thread_finished
};

instruction_t draw_cross[] = {
		0x040f003f, // addi $15, $0, 0b111111 ; 63 bitmask
		0x01e23806, // and $7, $15, $id_lo ; x value
		0x00024181, // srl $8, $id_lo, 6 ; y value
		0x01e87005, // sub $14, $15, $8 ; negative y value
		0x04050000, // addi $lsu_data, $0, 0b1111100000000000 ; Default to white
		0x00e84805, // sub $9, $7, $8 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b3008, // xor $mask, $10, $11
		0x8405ffff, // ? addi $lsu_data, $0, 0xffff ; black
		0x01c74805, // sub $9, $14, $7 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b3008, // xor $mask, $10, $11
		0x8405ffff, // ? addi $lsu_data, $0, 0xffff ; black
		0x080a0005, // ldc $10, 5 ; Framebuffer offset
		0x01422004, // add $address_lo, $10, $id_lo
		0x10000000, // sw
		0x40000000 // thread_finished
};

instruction_t draw_border[] = {
		0x040f003f, // addi $15, $0, 0b111111 ; 63 bitmask
		0x040e0040, // addi $14, $0, 64 ; width & height
		0x01e23806, // and $7, $15, $id_lo ; x value
		0x00024181, // srl $8, $id_lo, 6 ; y value
		0x01422004, // add $address_lo, $10, $id_lo
		0x20000000, // lw
		0x00057804, // add $15, $0, $lsu_data ; Cache for later - might not needed
		0x040507ff, // addi $lsu_data, $0, 0b0000011111111111 ; Default to red
		0x080d000a, // ldc $13, 10 ; Offset from edges
		0x01cd7005, // sub $14, $14, $13 ; offset from opposite edges
		0x00003004, // add $mask, $0, $0 ; init mask
		0x00006004, // add $12, $0, $0 ; shadow mask - mask is write only
		0x00ed4805, // sub $9, $7, $13 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a85803, // slt $11, $13, $8
		0x014b5006, // and $10, $10, $11
		0x010e5803, // slt $11, $8, $14
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x00ee4805, // sub $9, $7, $14 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a85803, // slt $11, $13, $8
		0x014b5006, // and $10, $10, $11
		0x010e5803, // slt $11, $8, $14
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x010d4805, // sub $9, $8, $13 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a75803, // slt $11, $13, $7 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x00ee5803, // slt $11, $7, $14 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x010e4805, // sub $9, $8, $14 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a75803, // slt $11, $13, $7 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x00ee5803, // slt $11, $7, $14 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x000c3004, // add $mask, $0, $12
		0x800f2804, // ? add $lsu_data, $0, $15 ; alpha
		0x10000000, // sw
		0x40000000 // thread_finished
};

instruction_t draw_tunnel[] = {
		0x040f003f, // addi $15, $0, 0b111111 ; 63 bitmask
		0x040e0040, // addi $14, $0, 64 ; width & height
		0x01e23806, // and $7, $15, $id_lo ; x value
		0x00024181, // srl $8, $id_lo, 6 ; y value
		0x0405f800, // addi $lsu_data, $0, 0b1111100000000000 ; Default to red
		0x00006004, // add $12, $0, $0 ; shadow mask - mask is write only
		0x080d000a, // ldc $13, 10 ; Offset from edges
		0x01cd7005, // sub $14, $14, $13 ; offset from opposite edges
		0x00ed4805, // sub $9, $7, $13 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a85803, // slt $11, $13, $8
		0x014b5006, // and $10, $10, $11
		0x010e5803, // slt $11, $8, $14
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x00ee4805, // sub $9, $7, $14 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a85803, // slt $11, $13, $8
		0x014b5006, // and $10, $10, $11
		0x010e5803, // slt $11, $8, $14
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x010d4805, // sub $9, $8, $13 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a75803, // slt $11, $13, $7 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x00ee5803, // slt $11, $7, $14 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x010e4805, // sub $9, $8, $14 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a75803, // slt $11, $13, $7 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x00ee5803, // slt $11, $7, $14 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x040e0040, // addi $14, $0, 64 ; width & height
		0x080d000b, // ldc $13, 11 ; Offset from edges
		0x01cd7005, // sub $14, $14, $13 ; offset from opposite edges
		0x00ed4805, // sub $9, $7, $13 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a85803, // slt $11, $13, $8
		0x014b5006, // and $10, $10, $11
		0x010e5803, // slt $11, $8, $14
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x00ee4805, // sub $9, $7, $14 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a85803, // slt $11, $13, $8
		0x014b5006, // and $10, $10, $11
		0x010e5803, // slt $11, $8, $14
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x010d4805, // sub $9, $8, $13 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a75803, // slt $11, $13, $7 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x00ee5803, // slt $11, $7, $14 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x010e4805, // sub $9, $8, $14 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x01a75803, // slt $11, $13, $7 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x00ee5803, // slt $11, $7, $14 ; Check x-offset
		0x014b5006, // and $10, $10, $11
		0x018a6007, // or $12, $12, $10
		0x00e84805, // sub $9, $7, $8 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x018a6007, // or $12, $12, $10
		0x040d003f, // addi $13, $0, 0b111111 ; 63 bitmask
		0x01a87005, // sub $14, $13, $8 ; negative y value
		0x01c74805, // sub $9, $14, $7 ; equal
		0x01205003, // slt $10, $9, $0 ; diff less than zero
		0x00095803, // slt $11, $0, $9 ; diff greater than zero
		0x014b5007, // or $10, $10, $11
		0x040b0001, // addi $11, $0, 1
		0x016a5005, // sub $10, $11, $10
		0x018a6007, // or $12, $12, $10
		0x000c3004, // add $mask, $0, $12 ; Store mask value
		0x84050000, // ? addi $lsu_data, $0, 0x0000 ; color, blue?
		0x080a0005, // ldc $10, 5
		0x01422004, // add $address_lo, $10, $id_lo
		0x10000000, // sw
		0x40000000 // thread_finished
};

instruction_t test_mem[] = {
		0x00001804, // add $address_hi, $0, $0
		0x00002004, // add $address_lo, $0, $0
		0x20000000, // lw
		0x00011804, // add $address_hi, $0, $id_hi
		0x04080002, // addi $8, $0, 2
		0x01022004, // add $address_lo, $8, $id_lo
		0x00000000, // nop
		0x10000000, // sw
		0x00000000, // nop
		0x40000000 // thread_finished
};

#endif /* INSTRUCTIONS_H_ */
