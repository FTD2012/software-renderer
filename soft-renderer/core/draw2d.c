#include <stdlib.h>
#include <assert.h>
#include "draw2d.h"
#include "graphics.h"

static void convert_color(vec4_t input, unsigned char ouput[4]) {
	ouput[0] = float_to_uchar(input.x);
	ouput[1] = float_to_uchar(input.y);
	ouput[2] = float_to_uchar(input.z);
	ouput[3] = float_to_uchar(input.w);
}

static void convert_point(framebuffer_t *framebuffer, vec2_t input, int *row, int *col) {
	*row = (int)(framebuffer->width * float_saturate(input.x) + 0.5f);
	*col = (int)(framebuffer->height * float_saturate(input.y) + 0.5f);
}

static void draw_point(framebuffer_t * framebuffer, unsigned char color[4], int row, int col) {
	assert(row >= 0 && row < framebuffer->width);
	assert(col >= 0 && col < framebuffer->height);
	int index = (row * framebuffer->width + col) * 4;
		
	framebuffer->color_buffer[index + 0] = color[0];
	framebuffer->color_buffer[index + 1] = color[1];
	framebuffer->color_buffer[index + 2] = color[2];
	framebuffer->color_buffer[index + 3] = color[3];
}


void draw2d_draw_point(framebuffer_t *framebuffer, vec4_t color, vec2_t point) {
	unsigned char color_[4];
	int row, col;
	convert_color(color, color_);
	convert_point(framebuffer, point, &row, &col);
	draw_point(framebuffer, color_, row, col);
}


void draw2d_draw_line(framebuffer_t *framebuffer, vec4_t color, vec2_t point0, vec2_t point1) {



}