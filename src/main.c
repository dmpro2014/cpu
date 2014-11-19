#include "em_device.h"
#include "em_chip.h"

#include "ebi_setup.h"
#include "instructions.h"
#include "bus.h"
#include "colors.h"

int main(void) {
	/* Chip errata */
	CHIP_Init();

	/* Init correct ebi banks */
	ebi_setup();


	for (int i = 0; i < 1024; i++) {
		uint16_t data = rgb(0, 0, 255);
		int write_address = SRAM_BASE_ADDR + (i << 1);
		*(uint16_t*)write_address = data;
	}

	load_kernel(1, square_kernel, 33);
	load_kernel(101, id_kernel, 23);
	load_kernel(201, constants, 17);
	load_kernel(301, flip, 20);
	load_kernel(350, srl, 17);

	/* Infinite loop */
	int i = 0;
	while (1) {
		load_constant(2, i);
		load_constant(1, rgb(0, 255, 255));
		//load_kernel(1, test_kernel, 15);
	    //load_kernel(1, id_kernel, 23);
		//load_kernel(1, square_kernel, 35);


		start_kernel(350, 1024);

		//start_kernel(101, 512);

		//start_kernel(201, 512);

		flip_framebuffer();
		if (i % 2) {
			load_constant(0, 4096);
		} else {
			load_constant(0, 0);
		}

		i++;
		if (i==4) i = 0;
	}
}
