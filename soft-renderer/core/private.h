#pragma once
#include "graphics.h"
#include "image.h"

void private_blit_bgr(framebuffer_t *src, image_t *dst);
void private_blit_rgb(framebuffer_t *src, image_t *dst);
