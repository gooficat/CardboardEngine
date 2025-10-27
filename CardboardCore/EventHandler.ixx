export module EventHandler;
import <Windows.h>;
import <stdint.h>;
import std;

import Window;
import RenderContext;

export enum EventType {
	None = 0,
	WindowClose, WindowSize,
	KeyPress, KeyRelease,
	MousePress, MouseRelease,
	MouseMove, MouseScroll
};

export enum class KeyCode {
	ESC = 0x1B,
	SPACE = 0x20,
	N0 = 0x30,
	N1,
	N2,
	N3,
	N4,
	N5,
	N6,
	N7,
	N8,
	N9,
	A = 0x41,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	LSHIFT = 0xA0,
	RSHIFT,
	LCTRL,
	RCTRL
};

export class EventHandler {
public:
	EventHandler() {
		onKeyDown = [](uint8_t, int64_t){};
		onKeyUp = [](int64_t, int64_t) {};

		onMouseButtonDown = [](int64_t, int64_t) {};
		onMouseButtonUp = [](int64_t, int64_t) {};

		quit_requested = false;
		active_instance = this;
	}

	static LRESULT CALLBACK MessageHandler(HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param) {
		static PAINTSTRUCT paint_struct;
		switch (u_msg) {
		case WM_CLOSE:
			EventHandler::active_instance->quit_requested = true;
			Window::active_instance->should_close = true;
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
			Window::active_instance->width = LOWORD(l_param);
			Window::active_instance->height = HIWORD(l_param);
			RenderContext::active_instance->resize(LOWORD(l_param), HIWORD(l_param));
			return 0;
		default:
			return DefWindowProcA(h_wnd, u_msg, w_param, l_param);
		}
	}
	bool isButtonDown(uint8_t code) {
		return GetKeyState(code);
	}
	
	bool shouldQuit() {
		return quit_requested;
	}
	
	void requestQuit() {
		quit_requested = true;
	}

	void pollEvents() {
		static MSG message;
		if (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}

	inline static void (*onKeyDown)(uint8_t code, int64_t flags);
	inline static void (*onKeyUp)(int64_t code, int64_t flags);

	inline static void (*onMouseButtonDown)(int64_t code, int64_t flags);
	inline static void (*onMouseButtonUp)(int64_t code, int64_t flags);

private:
	inline static EventHandler* active_instance;

	bool quit_requested;
};