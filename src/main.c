#include "em_device.h"
#include "em_chip.h"

#include "ebi_setup.h"
#include "instructions.h"
#include "bus.h"

int main(void) {
	/* Chip errata */
	CHIP_Init();

	/* Init correct ebi banks */
	ebi_setup();



	for (int i = 0; i < 3000; i++) {
		uint16_t data = 0xFFFF;
		int write_address = SRAM_BASE_ADDR + (i << 1);
		*(uint16_t*)write_address = data;
	}

	/* Infinite loop */
	int i = 20;
	while (1) {
		//load_constant(0, i);
		load_kernel(1, id_kernel, 18);

		start_kernel(1, 5000);
		flip_framebuffer();

		if (i < 40) i++;
		else i = 20;
	}
}
