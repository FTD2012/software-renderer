#pragma once

typedef struct {
	float frame_time;
	float delta_time;
} context_t;

typedef void tickfunc_t(context_t *context, void * userdata);

void test_enter_mainloop(tickfunc_t *tickfunc, void *userdata);

