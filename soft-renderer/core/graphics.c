#pragma once
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"
#include "macro.h"
#include "maths.h"

/* framebuffer management */

framebuffer_t *framebuffer_create(int width, int height) {
	assert(width > 0 && height > 0);

	int color_buffer_size = width * height * 4;
	int depth_buffer_size = sizeof(float) * width * height;
	vec4_t default_color = { 0, 0, 0, 1 };
	float default_depth = 1;
	framebuffer_t *framebuffer;

	framebuffer = (framebuffer_t *)malloc(sizeof(framebuffer_t));
	framebuffer->width = width;
	framebuffer->height = height;
	framebuffer->color_buffer = (unsigned char *)malloc(color_buffer_size);
	framebuffer->depth_buffer = (float *)malloc(depth_buffer_size);

	framebuffer_clear_color(framebuffer, default_color);
	framebuffer_clear_depth(framebuffer, default_depth);

	return framebuffer;
}

void framebuffer_release(framebuffer_t *framebuffer) {
	free(framebuffer->color_buffer);
	free(framebuffer->depth_buffer);
	free(framebuffer);
}

void framebuffer_clear_color(framebuffer_t *framebuffer, vec4_t color) {
	for (int i = 0; i < framebuffer->width * framebuffer->height; i++) {
		framebuffer->color_buffer[i * 4 + 0] = float_to_uchar(color.x);
		framebuffer->color_buffer[i * 4 + 1] = float_to_uchar(color.y);
		framebuffer->color_buffer[i * 4 + 2] = float_to_uchar(color.z);
		framebuffer->color_buffer[i * 4 + 3] = float_to_uchar(color.w);
	}
}

void framebuffer_clear_depth(framebuffer_t *framebuffer, float depth) {
	for (int i = 0; i < framebuffer->width * framebuffer->height; i++) {
		framebuffer->depth_buffer[i] = depth;
	}
}