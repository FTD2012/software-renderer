#pragma once

typedef struct window window_t;
typedef enum { KEY_A, KEY_D, KEY_S, KEY_W, KEY_SPACE, KEY_NUM } keycode_t;
typedef enum { BUTTON_L, BUTTON_R, BUTTON_NUM } button_t;
typedef struct {
	void(*key_callback)(window_t *window, keycode_t key, int pressed);
	void(*button_callback)(window_t *window, button_t button, int pressed);
	void(*scroll_callback)(window_t *window, float offset);
} callbacks_t;