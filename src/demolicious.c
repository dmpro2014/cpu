#include "demolicious.h"
#include "ebi_setup.h"
#include "em_gpio.h"

static uint16_t next_instruction = 1;

void run_kernel(kernel_t kernel_address, uint16_t number_of_batches) {
	int write_address = FPGA_BASE_ADDR + OFFSET_KERNEL_START + (kernel_address << 1);
	*(uint16_t *)write_address = number_of_batches;

	while (1) {
		if (GPIO_PinInGet( gpioPortC, 2 ) == 1) {
			return;
		}
	}
}

kernel_t load_kernel(instruction_t *instructions) {
	kernel_t kernel_address = (kernel_t)next_instruction;
	int i = 0;
	while (1) {
		load_instruction(next_instruction++, instructions[i]);
		if (instructions[i] == 0x40000000) { // thread_finished
			return kernel_address;
		}
		i++;
	}
}

void flip_framebuffer() {
	GPIO_PinOutToggle( gpioPortC, 1 );
}

void load_constant(uint16_t address, uint16_t data) {
	int write_address = FPGA_BASE_ADDR + (address << 1);
	*(uint16_t *)write_address = data;
}

void load_parameter(kernel_t kernel_address, uint16_t offset, uint16_t data) {
	load_constant(kernel_address + offset, data);
}

void load_instruction(uint16_t address, uint32_t instruction) {
	int write_address_lo = FPGA_BASE_ADDR + OFFSET_INSTRUCTION_MEMORY + (address << 2);
	int write_address_hi = write_address_lo | 2;
	uint16_t instruction_hi = (uint16_t)(instruction >> 16);
	uint16_t instruction_lo = (uint16_t)instruction;

	*(uint16_t *)write_address_lo = instruction_lo;
	*(uint16_t *)write_address_hi = instruction_hi;
}

void write_data(int address, uint16_t data) {
	*(uint16_t *)(SRAM_BASE_ADDR + (address << 1)) = data;
}

uint16_t read_data(int address) {
	return *(uint16_t *)(SRAM_BASE_ADDR + (address << 1));
}
