#pragma once

typedef enum {
	FORMAT_LDR,
	FORMAT_HDR
} format_t;

typedef struct {
	format_t format;
	int width, height, channels;
	unsigned char *ldr_buffer;
	float *hdr_buffer;
} image_t;

image_t *image_create(int width, int height, int channels, format_t format);
void image_release(image_t *image);