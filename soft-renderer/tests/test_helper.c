#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_helper.h"
#include "../core/api.h"

/* mainloop related functions */
static const char *WINDOW_TITLE = "Viewer";
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

void test_enter_mainloop(tickfunc_t *tickfunc, void *userdata) {
	window_t *window;
	//framebuffer_t *framebuffer;
	//camera_t *camera;
	//record_t record;
	//callbacks_t callbacks;
	context_t context;
	float aspect;
	float prev_time;
	float print_time;
	int num_frames;

	window = window_create(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

	while (!window_should_close(window)) {

		input_poll_events();

	}
	window_destroy(window);

}

