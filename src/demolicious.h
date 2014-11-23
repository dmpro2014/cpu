#ifndef BUS_H_
#define BUS_H_

#include <stdint.h>
#include "ebi_setup.h"
#include "colors.h"

typedef uint16_t kernel_t;
typedef uint32_t instruction_t;

kernel_t load_kernel(uint32_t *instructions);
void run_kernel(kernel_t kernel_address, uint16_t number_of_batches);
void load_parameter(kernel_t kernel_address, uint16_t offset, uint16_t data);

void load_constant(uint16_t address, uint16_t data);
void load_instruction(uint16_t address, uint32_t instruction);
void flip_framebuffer();

void write_data(int address, uint16_t data);
uint16_t read_data(int address);

#endif /* BUS_H_ */
