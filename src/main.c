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

	for (int i = 0; i < 4096; i++) {
		uint16_t data = rgb(0, 0, 255);
		if (i % 64 < 1 || i % 64 > 62 || i / 64 < 1 || i /64 > 62) {
			data = rgb(255, 0, 0);
		}
		int write_address = SRAM_BASE_ADDR + (i << 1);
		*(uint16_t*)write_address = data;
	}

	/*load_kernel(1, square_kernel, 33);
	load_kernel(101, id_kernel, 23);
	load_kernel(201, constants, 17);
	load_kernel(301, flip, 20);
	load_kernel(350, srl, 17);
	load_kernel(400, test_64_width, 19);*/
	//load_kernel(1, draw_cross, 100);
	load_kernel(200, tunnel_kernel, 150);
	//load_kernel(500, draw_border, 100);

	int cube_radius = 0;
	int cube_radius_2 = 16;
	load_constant(10, cube_radius);

	while (1) {
		//start_kernel(1, 512);
		//start_kernel(500, 512);
		start_kernel(200, 512);

		cube_radius = (cube_radius + 1) % 32;
		cube_radius_2 = (cube_radius_2 + 1) %32;
		load_constant(10, 32 - cube_radius);
		load_constant(11, 32 - cube_radius_2);

		for (int i=0; i<200000; i++);
	}

	/* Screensaver cube */
	/*int cube_width = 20;
	int x = 20;
	int y = 10;
	int xhi = x + cube_width;
	int yhi = y + cube_width;

	load_constant(0, x);
	load_constant(1, y);
	load_constant(2, xhi);
	load_constant(3, yhi);

	int dy = 1;
	int dx = 1;
	while (1) {
		start_kernel(500, 512);

		if (x <= 0 || x >= (63 - cube_width)) {
			dx *= -1;
		}

		if (y <= 0 || y >= (63 - cube_width)) {
			dy *= -1;
		}

		x += dx;
		y += dy;
		xhi = x + cube_width;
		yhi = y + cube_width;

		load_constant(0, x);
		load_constant(1, y);
		load_constant(2, xhi);
		load_constant(3, yhi);

		for (int i=0; i<200000; i++);
	}*/
}
