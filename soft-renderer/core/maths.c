#pragma once
#include "maths.h"

float float_saturate(float f) {
	return f < 0 ? 0 : (f > 1 ? 1 : f);
}

unsigned char float_to_uchar(float value) {
	return (unsigned char)(value * 255);
}

/* vec2 related functions */

vec2_t vec2_new(float x, float y) {
	vec2_t v = { x, y };
	return v;
}

/* vec3 related functions */
/* vec4 related functions */

vec4_t vec4_new(float x, float y, float z, float w) {
	vec4_t v = { x, y, z, w };
	return v;
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