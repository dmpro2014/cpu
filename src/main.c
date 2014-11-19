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
    load_kernel(400, test_64_width, 19);
	load_kernel(500, draw_square, 40);

	/* Infinite loop */
	int x = 10;
	int y = 10;
	int xhi = 40;
	int yhi = 40;

	load_constant(0, x);
	load_constant(1, y);
	load_constant(2, xhi);
	load_constant(3, yhi);

	int i = 0;
	while (1) {

		start_kernel(500, 1024);

		//x = (x + 1) % 64;
		//xhi = (xhi + 1) % 64;

		i++;
		if (i==4) i = 0;
	}
}
