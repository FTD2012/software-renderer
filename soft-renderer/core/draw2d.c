#include <stdlib.h>
#include <assert.h>
#include "draw2d.h"
#include "graphics.h"
#include "maths.h"

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
	assert(row >= 0 && row < framebuffer->height);
	assert(col >= 0 && col < framebuffer->width);
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

void draw2d_draw_line_dda(framebuffer_t *framebuffer, vec4_t color, vec2_t point0, vec2_t point1) {
    unsigned char color_[4];
    int dx, dy, steps, k, row0, col0, row1, col1;
    float xIncreament, yIncreament, x, y;
    convert_color(color, color_);
    convert_point(framebuffer, point0, &col0, &row0);
    convert_point(framebuffer, point1, &col1, &row1);
    
    x = col0;
    y = row0;
    
    dx = col1 - col0;
    dy = row1 - row0;
    
    steps = max(abs(dx), abs(dy));
    
    xIncreament = dx*1.0 / steps;
    yIncreament = dy*1.0 / steps;
    
    draw_point(framebuffer, color_, y, x);
    for (k = 0; k < steps; k++) {
        x += xIncreament;
        y += yIncreament;
        draw_point(framebuffer, color_, y, x);
    }
    
    
    
}


void draw2d_draw_line(framebuffer_t *framebuffer, vec4_t color, vec2_t point0, vec2_t point1) {



}
