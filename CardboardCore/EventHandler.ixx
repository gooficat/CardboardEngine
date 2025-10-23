export module EventHandler;
import <Windows.h>;
import <stdint.h>;

export enum EventType {
	None = 0,
	WindowClose, WindowSize,
	KeyPress, KeyRelease,
	MousePress, MouseRelease,
	MouseMove, MouseScroll
};

void DEFAULT_EVENT_DUMP(int64_t w_param, int64_t l_param) {

}

export class EventHandler {
public:
	EventHandler() {
		onKeyDown = DEFAULT_EVENT_DUMP;
	}

	static LRESULT CALLBACK WindowProc(HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param) {
		switch (u_msg) {
		case WM_CLOSE:

			return 0;
		case WM_SIZE:

			return 0;
		case WM_KEYDOWN:
			onKeyDown(w_param, l_param);
			return 0;
		case WM_KEYUP:
			break;
		default:
			return DefWindowProcA(h_wnd, u_msg, w_param, l_param);
		}
	}
	bool isKeyDown(uint32_t code, uint32_t flags) {
		
	}

	static void (*onKeyDown)(int64_t code, int64_t flags);
private:
	EventHandler* active_instance;
};