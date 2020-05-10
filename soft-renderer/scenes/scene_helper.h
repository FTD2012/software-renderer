#pragma once
#include "../core/api.h"

typedef struct {
	vec4_t backgroud;

	/* light intensity */
	float ambient_intensity;
	float punctual_intensity;


} scene_t;