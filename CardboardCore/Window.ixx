export module Window;
import std;

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
	Window(const WindowSpec& spec, const std::unique_ptr<Logger>& logger) {
#ifdef _WIN32
		instance_handle = GetModuleHandle(0);
		window_class = {
			.lpfnWndProc = Window::WindowProc,
			.hInstance = instance_handle,
			.lpszClassName = (wchar_t*)spec.title
		};
		RegisterClass(&window_class);

		this->window_handle = CreateWindowExA(
			0,
			spec.title,
			spec.title,
			WS_OVERLAPPEDWINDOW,
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
	}

	void show() {
		ShowWindow(window_handle, SW_SHOW);
	}

	static LRESULT CALLBACK WindowProc(HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param) {
		switch (u_msg) {
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProcA(h_wnd, u_msg, w_param, l_param);
		}
	}
	HWND& getHandle() {
		return window_handle;
	}
#endif
private:
	static Window* active_instance;
#ifdef _WIN32
	HWND window_handle;
	HINSTANCE instance_handle;
	WNDCLASS window_class;
#endif
};