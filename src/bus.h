#ifndef BUS_H_
#define BUS_H_

#include <stdint.h>

void start_kernel(uint16_t *kernel_address, uint16_t number_of_batches);
void load_constant(uint16_t *address, uint16_t data);
void load_instruction(uint16_t *address, uint32_t instruction);
void load_kernel(uint16_t *address, uint32_t *instructions);
void flip_framebuffer();

#endif /* BUS_H_ */
