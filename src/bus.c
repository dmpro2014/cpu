#include "bus.h"
#include "ebi_setup.h"
#include "em_gpio.h"

void start_kernel(uint16_t *kernel_address, uint16_t number_of_batches) {
	*(OFFSET_KERNEL_START + kernel_address) = number_of_batches;

	while(1) {
		if (GPIO_PinInGet( gpioPortD, 2 ) == 1) {
			return;
		}
	}
}

void load_kernel(uint16_t *address, uint32_t *instructions) {
	int i = 0;
	while (1) {
		load_instruction(address + i, instructions[i]);

		if (instructions[i] == 0x40000000) {
			return;
		}
	}
}

void flip_framebuffer() {
	GPIO_PinOutToggle( gpioPortC, 4 );
}

void load_constant(uint16_t *address, uint16_t data) {
	*(OFFSET_CONSTANT_MEMORY + address) = data;
}

void load_instruction(uint16_t *address, uint32_t instruction) {
	*(OFFSET_INSTRUCTION_MEMORY + address) = instruction;
}
