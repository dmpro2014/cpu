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

	/* Infinite loop */
	int i = 0;
	while (1) {
		load_constant(0, i);
		//load_kernel(1, test_kernel, 15);
	    //load_kernel(1, id_kernel, 23);
		//load_kernel(1, square_kernel, 35);


		start_kernel(1, 128);
		//flip_framebuffer();

		i++;
		if (i==4) i = 0;
	}
}
