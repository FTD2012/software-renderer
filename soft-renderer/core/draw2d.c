#include <stdlib.h>
#include <assert.h>
#include "draw2d.h"
#include "graphics.h"
#include "maths.h"

static void swap_integers(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}


static void convert_color(vec4_t input, unsigned char ouput[4]) {
	ouput[0] = float_to_uchar(input.x);
	ouput[1] = float_to_uchar(input.y);
	ouput[2] = float_to_uchar(input.z);
	ouput[3] = float_to_uchar(input.w);
}

static void convert_point(framebuffer_t *framebuffer, vec2_t input, int *x, int *y) {
	*x = (int)(framebuffer->width * float_saturate(input.x) + 0.5f);
	*y = (int)(framebuffer->height * float_saturate(input.y) + 0.5f);
}

static void draw_point_row_col(framebuffer_t * framebuffer, unsigned char color[4],
					   int row, int col) {
	assert(row >= 0 && row < framebuffer->height);
	assert(col >= 0 && col < framebuffer->width);
	int index = (row * framebuffer->width + col) * 4;
		
	framebuffer->color_buffer[index + 0] = color[0];
	framebuffer->color_buffer[index + 1] = color[1];
	framebuffer->color_buffer[index + 2] = color[2];
	framebuffer->color_buffer[index + 3] = color[3];
}

static void draw_point(framebuffer_t *framebuffer, unsigned char color[4],
						int x, int y) {
	draw_point_row_col(framebuffer, color, y, x);
}

void draw2d_draw_point(framebuffer_t *framebuffer, vec4_t color,
				       vec2_t point) {
	unsigned char color_[4];
	int x, y;
	convert_color(color, color_);
	convert_point(framebuffer, point, &x, &y);
	draw_point(framebuffer, color_, x, y);
}

void draw2d_draw_line_dda(framebuffer_t *framebuffer, vec4_t color,
						  vec2_t point0, vec2_t point1) {
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
    
    steps = int_max(abs(dx), abs(dy));
    
    xIncreament = dx*1.0 / steps;
    yIncreament = dy*1.0 / steps;
    
    draw_point(framebuffer, color_, x, y);
    for (k = 0; k < steps; k++) {
        x += xIncreament;
        y += yIncreament;
        draw_point(framebuffer, color_, x, y);
    }
}


// Bresenham 本质上比较的是距离上下点的距离，选择距离短的作为下一个绘制的点
// 大量使用delta的目的在于消除浮点数运算
// 优化及采样： https://zhuanlan.zhihu.com/p/30553006
void draw2d_draw_line(framebuffer_t *framebuffer, vec4_t color,
	                  vec2_t point0, vec2_t point1) {
	unsigned char color_[4];
	int row0, col0, row1, col1, x0, y0, x1, y1;
	int deltaX, deltaY, delta2Y, delta;
	int pk;
	int x;
	int steep = 0;
	convert_color(color, color_);
	convert_point(framebuffer, point0, &x0, &y0);
	convert_point(framebuffer, point1, &x1, &y1);

	if (abs(x1 - x0) < abs(y1 - y0)) {
		swap_integers(&x0, &y0);
		swap_integers(&x1, &y1);
		steep = 1;
	}

	if (x1 < x0) {
		swap_integers(&x0, &x1);
		swap_integers(&y0, &y1);
	}

	deltaX = x1 - x0;
	deltaY = y1 - y0;
	delta2Y = abs(deltaY) * 2;
	delta = delta2Y - deltaX * 2;
	pk = delta2Y - deltaX;
	
	for (x = x0; x <= x1; x++) {

		if (steep) {
			draw_point(framebuffer, color_, y0, x);
		}
		else {
			draw_point(framebuffer, color_, x, y0);
		}

		if (pk < 0) {
			pk += delta2Y;
		}
		else {
			y0 += y1 > y0 ? 1 : -1;
			pk += delta;
		}

	}
}

static draw_cirle_eight_point(framebuffer_t *framebuffer, unsigned char color_[4],
							  int x, int y, int x0, int y0) {
	draw_point(framebuffer, color_, x + x0, y + y0);
	draw_point(framebuffer, color_, y + x0, x + y0);
	draw_point(framebuffer, color_, -x + x0, y + y0);
	draw_point(framebuffer, color_, -y + x0, x + y0);
	draw_point(framebuffer, color_, x + x0, -y + y0);
	draw_point(framebuffer, color_, y + x0, -x + y0);
	draw_point(framebuffer, color_, -y + x0, -x + y0);
	draw_point(framebuffer, color_, -x + x0, -y + y0);
}

void draw2d_draw_cirle(framebuffer_t *frambuffer, vec4_t color,
					   vec2_t point, int r) {
	unsigned char color_[4];
	int x0, y0, x, y;
	float pk;
	convert_color(color, color_);
	convert_point(frambuffer, point, &x0, &y0);

	x = 0;
	y = r;
	pk = 5 / 4.0 - r;

	draw_point(frambuffer, color_, x + x0, y + y0);
	while (x <= y) {
		x++;
		pk += 2 * x + 1;
		if (pk >=  0) {
			y -= 1;
			pk -= 2 * y;
		}
		draw_cirle_eight_point(frambuffer, color_, x , y, x0, y0);
	}

}
