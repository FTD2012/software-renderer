#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/api.h"
#include "test_helper.h"

/* mainloop related functions */
static const char *WINDOW_TITLE = "Viewer";
static const int WINDOW_WIDTH = 1080;
static const int WINDOW_HEIGHT = 720;


static void key_callback(window_t *window, keycode_t key, int pressed) {
	if (key == KEY_ESC) {
		window_set_close(window, 1);
	}
}

void test_enter_mainloop(tickfunc_t *tickfunc, void *userdata) {
	window_t *window;
	framebuffer_t *framebuffer;
	//camera_t *camera;
	//record_t record;
	callbacks_t callbacks;
	context_t context;
	float aspect;
	float prev_time;
	float print_time;
	int num_frames;

	window = window_create(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
	framebuffer = framebuffer_create(WINDOW_WIDTH, WINDOW_HEIGHT);

	memset(&callbacks, 0, sizeof(callbacks));
	callbacks.key_callback = key_callback;

	memset(&context, 0, sizeof(context_t));
	context.framebuffer = framebuffer;

	input_set_callbacks(window, callbacks);

	while (!window_should_close(window)) {

		tickfunc(&context, userdata);

		window_draw_buffer(window, framebuffer);


		input_poll_events();

	}
	window_destroy(window);

}

