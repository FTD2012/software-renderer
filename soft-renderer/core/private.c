#pragma once
#include <assert.h>
#include <string.h>
#include "graphics.h"
#include "image.h"

/* framebuffer blitting */

void private_blit_bgr(framebuffer_t *src, image_t *dst) {
	int width = dst->width;
	int height = dst->height;
	int r, c;

	assert(src->width == dst->width && src->height == dst->height);
	assert(dst->format == FORMAT_LDR && dst->channels == 4);

	for (r = 0; r < height; r++) {
		for (c = 0; c < width; c++) {
			int flipped_r = height - 1 - r;
			int src_index = (r * width + c) * 4;
			int dst_index = (flipped_r * width + c) * 4;
			unsigned char *src_pixel = &src->color_buffer[src_index];
			unsigned char *dst_pixel = &dst->ldr_buffer[dst_index];
			dst_pixel[0] = src_pixel[2];  /* blue */
			dst_pixel[1] = src_pixel[1];  /* green */
			dst_pixel[2] = src_pixel[0];  /* red */
		}
	}
}