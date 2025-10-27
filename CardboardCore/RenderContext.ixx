export module RenderContext;

// does this even need to be here?
import Window;
import Logger;
import OpenGL;

import <Windows.h>;
import std;
import <stdint.h>;

export class RenderContext {
public:
	RenderContext(HWND& window_handle, std::unique_ptr<Logger>& logger, const PixelFormat& format) {
		RenderContext::active_instance = this;

		devicecontext_handle = GetDC(window_handle);

		// pay no heed, child, for i hardly know either
		int format_attribs[] = {
			0x2001, 1,
			0x2010, 1,
			0x2011, 1,
			0x2003, 0x2027,
			0x2013, 0x202B,
			0x2014, 24,
			0x2022, 24,
			0x2023, 8,
			0
		};
		int pixel_format;
		UINT num_formats;

		wglChoosePixelFormatARB(devicecontext_handle, format_attribs, 0, 1, &pixel_format, &num_formats);

		if (!num_formats) {
			logger->log("Pixel format of render context is null!", LOG_ERROR);
		}

		PIXELFORMATDESCRIPTOR pfd;
		DescribePixelFormat(devicecontext_handle, pixel_format, sizeof(pfd), &pfd);

		if (!SetPixelFormat(devicecontext_handle, pixel_format, &pfd)) {
			logger->log("Failed to set pixel format for render context!", LOG_ERROR);
		}

		int gl33_attribs[] = {
			0x2091, 3,
			0x2092, 3,
			0x9126, 0x00000001,
			0
		};

		rendercontext_handle = wglCreateContextAttribsARB(devicecontext_handle, 0, gl33_attribs);
		if (!rendercontext_handle) {
			logger->log("Failed to create context for 3.3!", LOG_ERROR);
		}
		if (!wglMakeCurrent(devicecontext_handle, rendercontext_handle)) {
			logger->log("Failed to make 3.3 context current!", LOG_ERROR);
		}

		GL::load(logger);
	}

	void swapBuffers() {
		SwapBuffers(devicecontext_handle);
	}

	void resize(uint32_t width, uint32_t height) {
		GL::viewport(0, 0, width, height);
	}

	static PixelFormat generateFormat() {
		return PixelFormat{
			NULL
		};
	}

	inline static RenderContext *active_instance;
private:
	int pixelformat;
	HGLRC rendercontext_handle;
	HDC devicecontext_handle;
};