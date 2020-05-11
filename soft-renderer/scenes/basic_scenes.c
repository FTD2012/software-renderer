#include "malloc.h" // temp for malloc
#include "../core/api.h"
#include "basic_scenes.h"
#include "scene_helper.h"

scene_t *basic_point_scene(void) {
	scene_t *scene = (scene_t*)malloc(sizeof(scene_t));
	mat4_t root = mat4_identity();
	return scene_from_file("aaa/point.scn", root);
}