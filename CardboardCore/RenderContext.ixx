export module RenderContext;

import Window;
import Logger;
import OpenGL;

import <Windows.h>;
import std;

export class RenderContext {
public:
	RenderContext(HWND& window_handle, std::unique_ptr<Logger>& logger, BYTE color_bits, BYTE depth_bits) {

		devicecontext_handle = GetDC(window_handle);

		/*pixelformat_desc = */
		std::memset(&pixelformat_desc, 0, sizeof(pixelformat_desc));
		pixelformat_desc = {
			.nSize = sizeof(pixelformat_desc),
			.nVersion = 1,
			.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			.iPixelType = PFD_TYPE_RGBA,
			.cColorBits = color_bits,
			.cDepthBits = depth_bits
		};

		if (!(pixelformat = ChoosePixelFormat(devicecontext_handle, &pixelformat_desc))) {
			logger->log("Pixel format of render context is null!", LOG_ERROR);
		}

		if (!SetPixelFormat(devicecontext_handle, pixelformat, &pixelformat_desc)) {
			logger->log("Failed to set pixel format for render context!", LOG_ERROR);
		}

		DescribePixelFormat(devicecontext_handle, pixelformat, sizeof(PIXELFORMATDESCRIPTOR), &pixelformat_desc);

		rendercontext_handle = wglCreateContext(devicecontext_handle);
		wglMakeCurrent(devicecontext_handle, rendercontext_handle);

		GL::load(logger);
	}

	void swapBuffers() {
		SwapBuffers(devicecontext_handle);
	}
private:
	int pixelformat;
	PIXELFORMATDESCRIPTOR pixelformat_desc;
	HGLRC rendercontext_handle;
	HDC devicecontext_handle;
};