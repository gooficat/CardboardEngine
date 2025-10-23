export module OpenGL;
import <Windows.h>;
import <stdint.h>;
import Logger;
import <memory>;

//#pragma comment(lib, "opengl32")

#define ASRT_PROC(a, b) if ((a = (decltype(a))loadFunction(b)) == NULL) {\
logger->log("Failed to load OpenGL function " + (std::string)b + "\nrequired for this specification!\n", LOG_ERROR);\
std::cout << "value is actually: " << a << std::endl;\
return false;\
}

export namespace GL {
	using Enum = uint32_t;
	using Uint = uint32_t;
	using Sizei = uint32_t;
	using Int = int32_t;
	using Boolean = bool;
	using Float = float;
	void * loadFunction(const char* name) {
		void *p = (void *)wglGetProcAddress(name);
		if (p == 0 ||
			p == (void *)0x1 ||
			p == (void *)0x2 ||
			p == (void *)0x3 ||
			p == (void *)-1) {
			HMODULE module = LoadLibraryA("opengl32.dll");
			p = (void *)GetProcAddress(module, name);
		}
		return p;
	}
	void (*useProgram)(Uint program) = NULL;
	Uint (*createShader)(Enum type) = NULL;
	Uint (*genBuffers)(Sizei count, Uint *buffers) = NULL;
	void (*viewport)(Int x, Int y, Sizei w, Sizei h) = NULL;

	bool load(const std::unique_ptr<Logger>& logger) {
		ASRT_PROC(useProgram, "glUseProgram");
		ASRT_PROC(createShader, "glCreateShader");
		ASRT_PROC(genBuffers, "glGenBuffers");
		ASRT_PROC(viewport, "glViewport");

		return true;
	}

};