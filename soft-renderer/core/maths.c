#pragma once
#include "maths.h"

unsigned char float_to_uchar(float value) {
	return (unsigned char)(value * 255);
}


/* mat3 related functions */

/* mat4 related functions */
mat4_t mat4_identity(void) {
	mat4_t m = { {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	} };
	return m;
}