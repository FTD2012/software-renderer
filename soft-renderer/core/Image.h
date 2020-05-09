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