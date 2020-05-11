#pragma once
#include "../core/api.h"

typedef struct {
	vec3_t background;
	char environment[LINE_SIZE];
	char skybox[LINE_SIZE];
	char shadow[LINE_SIZE];
	float ambient;
	float punctual;
} scene_light_t;

typedef struct {
	char primitivetype[LINE_SIZE];
	int index;
	char mesh[LINE_SIZE];
	char skeleton[LINE_SIZE];
	int attached;
	int material;
	int transform;
} scene_model_t;

scene_t *scene_from_file(const char *filename, mat4_t root);