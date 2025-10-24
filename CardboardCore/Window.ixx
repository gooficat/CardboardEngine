export module Window;
import std;

//import EventHandler;

import Logger;

import "Api.h";
import <Windows.h>;
import <cstdint>;

export class WindowSpec {
public:
	const char *title;
	uint16_t width;
	uint16_t height;
};


export class Window {
public:
	Window(const WindowSpec& spec, LRESULT(*EventProcedure)(HWND, UINT, WPARAM, LPARAM), const std::unique_ptr<Logger>& logger) :
		should_close(false) {
		Window::active_instance = this;
		instance_handle = GetModuleHandle(0);
		window_class = {
			.lpfnWndProc = EventProcedure,
			.hInstance = instance_handle,
			.lpszClassName = (wchar_t*)spec.title
		};
		RegisterClass(&window_class);

		this->window_handle = CreateWindowExA(
			0,
			spec.title,
			spec.title,
			WS_OVERLAPPEDWINDOW | WS_EX_COMPOSITED,
			CW_USEDEFAULT, CW_USEDEFAULT,
			spec.width, spec.height,
			NULL,
			NULL,
			instance_handle,
			NULL
		);
		if (window_handle == NULL) {
			logger->log("The window failed to initialize.", LOG_ERROR);
			return;
		}

		this->width = spec.width;
		this->height = spec.height;
	}

	void show() {
		ShowWindow(window_handle, SW_SHOW);
	}

	uint32_t getWidth() {
		return width;
	}

	uint32_t getHeight() {
		return height;
	}

	HWND& getHandle() {
		return window_handle;
	}
	bool should_close;
	inline static Window* active_instance;

	uint32_t width;
	uint32_t height;
private:

	HWND window_handle;
	HINSTANCE instance_handle;
	WNDCLASS window_class;

};