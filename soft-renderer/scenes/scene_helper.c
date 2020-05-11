#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "scene_helper.h"

static scene_light_t *read_light(FILE *file) {
	scene_light_t *light = (scene_light_t *)malloc(sizeof(scene_light_t));
	char header[LINE_SIZE];
	int items;

	memset(light, 0, sizeof(scene_light_t));
	
	items = fscanf(file, "%s", header);
	assert(equals_to(header, "lighting:"));
	items = fscanf(file, " background: %f %f %f", &light->background.x, &light->background.y, &light->background.z); // background
	assert(items == 3);
	items = fscanf(file, " environment: %s", &light->environment);
	assert(items == 1);
	items = fscanf(file, " skybox: %s", &light->skybox);
	assert(items == 1);
	items = fscanf(file, " shadow: %s", &light->shadow);
	assert(items == 1);
	items = fscanf(file, " ambient: %f", &light->ambient);
	assert(items == 1);
	items = fscanf(file, " punctual: %f", &light->punctual);
	assert(items == 1);

	return light;
}

static scene_model_t read_mode(FILE * file) {
	scene_model_t model;
	int items;

	items = fscanf(file, " model %d:", &model.index);
	assert(items == 1);
	items = fscanf(file, " primitivetype: %s", &model.primitivetype);
	assert(items == 1);
	items = fscanf(file, " mesh: %s", &model.mesh);
	assert(items == 1);
	items = fscanf(file, " skeleton: %s", &model.skeleton);
	assert(items == 1);
	items = fscanf(file, " attached: %d", &model.attached);
	assert(items == 1);
	items = fscanf(file, " material: %d", &model.material);
	assert(items == 1);
	items = fscanf(file, " transform: %d", &model.transform);
	assert(items == 1);

	return model;
}

static scene_model_t *read_models(FILE *file) {
	scene_model_t *models = NULL;
	int num_models;
	int items;

	items = fscanf(file, " models %d:", &num_models);
	assert(items == 1);
	UNUSED_VAR(items);
	for (int i = 0; i < num_models; i++) {
		darray_push(models, read_mode(file));
	}

	return models;
}

scene_t *scene_from_file(const char *filename, mat4_t root) {
	char scene_type[LINE_SIZE];
	scene_t *scene = (scene_t *)malloc(sizeof(scene_t));
	FILE *file;
	int items;

	file = fopen(filename, "rb");
	assert(file != NULL);

	scene_light_t *light = read_light(file);
	scene_model_t *model = read_models(file);




	free(light);
	darray_free(model);
	fclose(file);
	return scene;
}
