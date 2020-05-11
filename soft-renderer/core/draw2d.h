#pragma once
#include "graphics.h"
#include "maths.h"

void draw2d_draw_point(framebuffer_t *framebuffer, vec4_t color, vec2_t point);

void draw2d_draw_line_dda(framebuffer_t *framebuffer, vec4_t color, vec2_t point, vec2_t point1);
