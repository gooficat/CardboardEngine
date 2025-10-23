export module OpenGL;
import <Windows.h>;
import <stdint.h>;
import Logger;
import <memory>;

#pragma comment(lib, "opengl32")

#define ASRT_PROC(a, b) if (!(a(b))) {\
logger->log("Failed to load OpenGL function " + (std::string)b + "\nrequired for this specification!", LOG_ERROR);\
return false;\
}

export namespace GL {
	using Enum = uint32_t;
	using Uint = uint32_t;
	using Sizei = uint32_t;
	void* getProcAddress(const char* name) {
		void* p = (void*)wglGetProcAddress(name);
		if (p == 0 ||
			p == (void*)0x1 ||
			p == (void*)0x2 ||
			p == (void*)0x3 ||
			p == (void*)-1) {
			static const HMODULE module = LoadLibraryA("opengl32.dll");
			p = (void*)GetProcAddress(module, name);
		}
		return p;
	}

	Uint (*createShader)(Enum type) = NULL;
	Uint (*genBuffers)(Sizei count, Uint *buffers) = NULL;
	
	bool load(const std::unique_ptr<Logger>& logger) {
		ASRT_PROC(createShader = (Uint(*)(Enum))getProcAddress, "glCreateShader");
		ASRT_PROC(genBuffers = (Uint(*)(Sizei, Uint *))getProcAddress, "glGenBuffers");

		return true;
	}

};