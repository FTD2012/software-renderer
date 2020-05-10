#include "malloc.h" // temp for malloc
#include "../core/api.h"
#include "basic_scenes.h"

scene_t *basic_point_scene(void) {
	scene_t *scene = (scene_t*)malloc(sizeof(scene_t));
	return scene;
}