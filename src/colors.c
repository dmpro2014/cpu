#include <stdint.h>

uint16_t rgb(int red, int green, int blue) {
	uint16_t encoded_red = red << 11;
	uint16_t encoded_green = (green << 5) & 0b0000011111100000;
	uint16_t encoded_blue = blue & 0b0000000000011111;
	return ~(encoded_red + encoded_green + encoded_blue);
}

