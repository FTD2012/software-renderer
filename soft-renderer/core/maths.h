#pragma once

typedef struct { float x, y, z, w; } vec4_t;
typedef struct { float m[4][4] } mat4_t;

unsigned char float_to_uchar(float value);