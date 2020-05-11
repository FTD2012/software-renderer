#pragma once

typedef struct { float x, y; } vec2_t;
typedef struct { float x, y, z; } vec3_t;
typedef struct { float x, y, z, w; } vec4_t;
typedef struct { float m[4][4]; } mat4_t;

int max(int left, int right);
float float_saturate(float f);
unsigned char float_to_uchar(float value);

/* vec2 related functions */

vec2_t vec2_new(float x, float y);


/* vec3 related functions */
/* vec4 related functions */

vec4_t vec4_new(float x, float y, float z, float w);

/* mat3 related functions */

/* mat4 related functions */
mat4_t mat4_identity(void);
