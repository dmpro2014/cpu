#include "bus.h"
#include "ebi_setup.h"
#include "em_gpio.h"

void start_kernel(uint16_t kernel_address, uint16_t number_of_batches) {
	int write_address = FPGA_BASE_ADDR + ((OFFSET_KERNEL_START + kernel_address) << 1);
	*(uint16_t*)write_address = number_of_batches;

	while(1) {
		if (GPIO_PinInGet( gpioPortD, 2 ) == 1) {
			return;
		}
	}
}

void load_kernel(uint16_t address, uint32_t *instructions, int kernel_length) {
	for (int i = 0; i < kernel_length; i++) {
		load_instruction(address + i, instructions[i]);
	}
}

void flip_framebuffer() {
	GPIO_PinOutToggle( gpioPortC, 4 );
}

void load_constant(uint16_t address, uint16_t data) {
	int write_address = FPGA_BASE_ADDR + (address << 1);
	*(uint16_t*)write_address = data;
}

void load_instruction(uint16_t address, uint32_t instruction) {
	int write_address = FPGA_BASE_ADDR + ((OFFSET_INSTRUCTION_MEMORY + address) << 1);
	*(uint32_t*)write_address = instruction;
}
