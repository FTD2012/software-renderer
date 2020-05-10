#pragma once
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/image.h"

/* image creating/releasing */

image_t *image_create(int width, int height, int channels, format_t format) {
	int num_elems = width * height * channels;
	image_t *image;

	assert(width > 0 && height > 0 && channels >= 1 && channels <= 4);
	assert(format == FORMAT_LDR || format == FORMAT_HDR);

	image = (image_t*)malloc(sizeof(image_t));
	image->format = format;
	image->width = width;
	image->height = height;
	image->channels = channels;
	image->ldr_buffer = NULL;
	image->hdr_buffer = NULL;

	if (format == FORMAT_LDR) {
		int size = sizeof(unsigned char) * num_elems;
		image->ldr_buffer = (unsigned char*)malloc(size);
		memset(image->ldr_buffer, 0, size);
	}
	else {
		int size = sizeof(float) * num_elems;
		image->hdr_buffer = (float*)malloc(size);
		memset(image->hdr_buffer, 0, size);
	}

	return image;
}

void image_release(image_t *image) {
	free(image->ldr_buffer);
	free(image->hdr_buffer);
	free(image);
}