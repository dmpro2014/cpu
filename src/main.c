#include "em_device.h"
#include "em_chip.h"

#include "ebi_setup.h"
#include "instructions.h"

int main(void) {
	/* Chip errata */
	CHIP_Init();

	/* Init correct ebi banks */
	ebi_setup();

	load_kernel(0, square_kernel);

	/* Infinite loop */
	int i = 20;
	while (1) {
		load_constant(0, i);
		start_kernel(0, 16384);
		flip_framebuffer();

		if (i < 40) i++;
		else i = 20;
	}
}
