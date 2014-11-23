#include "em_device.h"
#include "em_chip.h"

#include "instructions.h"
#include "demolicious.h"

int main(void) {
	/* Chip errata */
	CHIP_Init();

	/* Init correct ebi banks */
	ebi_setup();

	kernel_t cross_kernel = load_kernel(draw_cross);
	kernel_t tunnel_kernel = load_kernel(draw_tunnel);
	kernel_t border_kernel = load_kernel(draw_border);
	kernel_t mem_kernel = load_kernel(test_mem);

	int cube_radius = 0;
	int cube_radius_2 = 16;
	load_constant(10, cube_radius);
	int fb_offset = 4096;
	load_constant(5, fb_offset);
	write_data(0, rgb(255, 0, 0));
	write_data(1, rgb(0, 0, 255));
	while (1) {
		cube_radius = (cube_radius + 1) % 32;
		cube_radius_2 = (cube_radius_2 + 1) % 32;

		//start_kernel(cross_kernel, 512); // Draw cross

		load_constant(10, 32 - cube_radius_2);
		//run_kernel(border_kernel, 512); // First border
		load_constant(11, 32 - cube_radius);
		//run_kernel(border_kernel, 512); // Second border
		//run_kernel(tunnel_kernel, 512); // 4096

		run_kernel(mem_kernel, 1024);

		fb_offset = 4096 - fb_offset;
		load_constant(5, 0);
		//flip_framebuffer();

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
