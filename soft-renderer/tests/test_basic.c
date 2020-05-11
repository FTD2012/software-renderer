#include <stddef.h>
#include "test_basic.h"
#include "test_helper.h"
#include "../scenes/basic_scenes.h"

static creator_t g_creators[] = {
	{"basic_point", basic_point_scene}
};

static void tick_function(context_t *context, void *userdata) {
	// back ground
	static int delta = 0;
    int i,j;
	for (i = 0; i < context->framebuffer->width * context->framebuffer->height; i++) {
		context->framebuffer->color_buffer[i * 4 + 0] = delta % 255;
		context->framebuffer->color_buffer[i * 4 + 1] = delta % 255;
		context->framebuffer->color_buffer[i * 4 + 2] = delta % 255;
		context->framebuffer->color_buffer[i * 4 + 3] = delta % 255;
	}
	delta++;

    draw2d_draw_line_dda(context->framebuffer, vec4_new(1, 0, 0, 1), vec2_new(0.25, 0.5), vec2_new(0.75, 0.5));
    
	for (j = 0; j < 500; j++) {
		float cow = j*1.0 / context->framebuffer->width;
		float col = j * 1.0 / context->framebuffer->height;
		draw2d_draw_point(context->framebuffer, vec4_new(1, 1, 1, 1), vec2_new(cow, col));
	}
}

void test_basic(int argc, char *argv[]) {
	const char *scene_name = argc > 2 ? argv[2] : NULL;
	scene_t *scene = basic_point_scene();
	if (scene) {
		test_enter_mainloop(tick_function, scene);
	}
}
