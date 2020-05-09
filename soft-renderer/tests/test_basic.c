#include <stddef.h>
#include "test_basic.h"
#include "test_helper.h"
#include "../scenes/basic_scenes.h"

static creator_t g_creators[] = {
	{"basic_point", basic_point_scene}

};

static void tick_function(context_t *context, void *userdata) {

}

void test_basic(int argc, char *argv[]) {
	const char *scene_name = argc > 2 ? argv[2] : NULL;
	scene_t *scene = basic_point_scene();
	if (scene) {
		test_enter_mainloop(tick_function, scene);
	}
}
