#include <assert.h>
#include <stdlib.h>
#include <direct.h>
#include <windows.h>
#include <stdio.h>

#include "../core/Image.h"
#include "../core/platform.h"
#include "../core/macro.h"

struct window {
	HWND handle;
	HDC memory_dc;
	image_t *surface;
	/* common data */
	int should_close;
	char keys[KEY_NUM];
	char buttons[BUTTON_NUM];
	callbacks_t callbacks;
	void *userdata;
};

#ifdef UNICODE
static const wchar_t *WINDOW_CLASS_NAME = L"Class";
static const wchar_t *WINDOW_ENTRY_NAME = L"Entry";
#else
static const char *WINDOW_CLASS_NAME = "Class";
static const char *WINDOW_ENTRY_NAME = "Entry";
#endif

static int g_initialized = 0;

static LRESULT CALLBACK process_message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	window_t *window = (window_t*)GetProp(hWnd, WINDOW_ENTRY_NAME);
	if (uMsg != WM_PAINT) {
		printf("process_message: %d\n", uMsg);
	}
	if (window == NULL) {
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	else if (uMsg == WM_CLOSE) {
		window->should_close = 1;
		return 0;
	}
	else {
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

static void register_class(void) {
    ATOM class_atom;
    WNDCLASS window_class;
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = process_message;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = GetModuleHandle(NULL);
	window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	window_class.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	window_class.lpszMenuName = NULL;
	window_class.lpszClassName = WINDOW_CLASS_NAME;
	class_atom = RegisterClass(&window_class);
	assert(class_atom != 0);
	UNUSED_VAR(class_atom);
}

static void unregister_class(void) {
	UnregisterClass(WINDOW_CLASS_NAME, GetModuleHandle(NULL));
}

static void initialize_path(void) {
#ifdef UNICODE
	wchar_t path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	*wcsrchr(path, L'\\') = L'\0';
	_wchdir(path);
	_wchdir(L"assets");
#else
	char path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	*strrchr(path, '\\') = '\0';
	_chdir(path);
	_chdir("assets");
#endif
}

void platform_initialize(void) {
	assert(g_initialized == 0);
	register_class();
	initialize_path();
	g_initialized = 1;
}

void platform_terminate(void) {
	assert(g_initialized == 1);
	unregister_class();
	g_initialized = 0;
}

static HWND create_window(const char *title_, int width, int height) {
	DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	RECT rect;
	HWND handle;

#ifdef UNICODE
	wchar_t title[LINE_SIZE];
	mbstowcs(title, title_, LINE_SIZE);
#else
	const char *title = title_;
#endif

	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = height;
	AdjustWindowRect(&rect, style, 0);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	handle = CreateWindow(WINDOW_CLASS_NAME, title, style,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, GetModuleHandle(NULL), NULL);
	assert(handle != NULL);
	return handle;
}

window_t *window_create(const char *title, int width, int height) {
	window_t *window;
	HWND handle;
	image_t *surface;
	HDC memory_dc;

	assert(g_initialized && width > 0 && height > 0);

	handle = create_window(title, width, height);
	//create_surface(handle, width, height, &surface, &memory_dc);

	window = (window_t*)malloc(sizeof(window_t));
	memset(window, 0, sizeof(window_t));
	window->handle = handle;
	//window->memory_dc = memory_dc;
	//window->surface = surface;

	SetProp(handle, WINDOW_ENTRY_NAME, window);
	ShowWindow(handle, SW_SHOW);
	return window;
}

void window_destroy(window_t *window) {
	ShowWindow(window->handle, SW_HIDE);
	RemoveProp(window->handle, WINDOW_ENTRY_NAME);

	DeleteDC(window->memory_dc);
	DestroyWindow(window->handle);

	//window->surface->ldr_buffer = NULL;
	//image_release(window->surface);
	free(window);
}

int window_should_close(window_t *window) {
	return window->should_close;
}

void input_poll_events(void) {
	MSG message;
	while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

/* misc platform functions */

static double get_native_time(void) {
	static double period = -1;
	LARGE_INTEGER counter;
	if (period < 0) {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		period = 1 / (double)frequency.QuadPart;
	}
	QueryPerformanceCounter(&counter);
	return counter.QuadPart * period;
}

float platform_get_time(void) {
	static double initial = -1;
	if (initial < 0) {
		initial = get_native_time();
	}
	return (float)(get_native_time() - initial);
}



