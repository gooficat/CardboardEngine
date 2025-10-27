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
	using Sizeiptr = uint64_t;
	using Int = int32_t;
	using Boolean = bool;
	using Float = float;
	using Bitfield = uint32_t;
	using Char = char;

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
	void (*viewport)(Int x, Int y, Sizei w, Sizei h) = NULL;

	void (*clearColor)(Float r, Float g, Float b, Float a) = NULL;
	void (*clear)(Bitfield mask) = NULL;

	Uint (*createShader)(Enum type) = NULL;
	Uint (*shaderSource)(Uint shader, Sizei count, const Char **string, const Int *length) = NULL;
	Uint (*compileShader)(Uint shader) = NULL;

	Uint (*createProgram)() = NULL;
	Uint (*attachShader)(Uint shader, Uint program) = NULL;
	Uint (*linkProgram)(Uint program) = NULL;
	void (*useProgram)(Uint program) = NULL;

	Int (*getUniformLocation)(Uint program, const Char *name) = NULL;
	void (*uniformMatrix4fv)(Int location, Sizei count, Boolean transpose, Float *value) = NULL;
	void (*uniform1i)(Int location, Int value) = NULL;

	void (*genBuffers)(Sizei count, Uint *buffers) = NULL;
	void (*genVertexArrays)(Sizei count, Uint* buffers) = NULL;

	void (*bindBuffer)(Enum target, Uint buffer) = NULL;
	void (*bufferData)(Enum target, Sizeiptr size, const void *data, Enum usage) = NULL;

	void (*bindVertexArray)(Uint array) = NULL;

	void (*vertexAttribPointer)(Uint index, Int size, Enum type, Boolean normalized, Sizei stride, const void *pointer) = NULL;
	void (*enableVertexAttribArray)(Uint index) = NULL;

	//void (*drawArrays)(Enum mode, Int offset, Sizei count) = NULL;
	void (*drawElements)(Enum mode, Sizei count, Enum type, const void *indices) = NULL;

	void (*genTextures)(Sizei count, Uint* texture) = NULL;
	void (*bindTexture)(Enum target, Uint texture) = NULL;
	void (*texParameteri)(Enum target, Enum pname, Int param) = NULL;
	void (*texImage2D)(Enum target, Int level, Int internal_format, Sizei width, Sizei height, Int border, Enum format, Enum type, const void *data) = NULL;
	void (*generateMipmap)(Enum target) = NULL;


	bool load(const std::unique_ptr<Logger>& logger) {
		ASRT_PROC(viewport, "glViewport")
		ASRT_PROC(clearColor, "glClearColor")
		ASRT_PROC(clear, "glClear")

		ASRT_PROC(createShader, "glCreateShader")
		ASRT_PROC(shaderSource, "glShaderSource")
		ASRT_PROC(compileShader, "glCompileShader")

		ASRT_PROC(createProgram, "glCreateProgram")
		ASRT_PROC(attachShader, "glAttachShader")
		ASRT_PROC(linkProgram, "glLinkProgram")

		ASRT_PROC(useProgram, "glUseProgram")

		ASRT_PROC(getUniformLocation, "glGetUniformLocation")
		
		ASRT_PROC(uniformMatrix4fv, "glUniformMatrix4fv")
		ASRT_PROC(uniform1i, "glUniform1i")

		ASRT_PROC(genBuffers, "glGenBuffers")
		ASRT_PROC(genVertexArrays, "glGenVertexArrays")
		
		ASRT_PROC(bindVertexArray, "glBindVertexArray")

		ASRT_PROC(bindBuffer, "glBindBuffer")
		ASRT_PROC(bufferData, "glBufferData")
		ASRT_PROC(vertexAttribPointer, "glVertexAttribPointer")
		ASRT_PROC(enableVertexAttribArray, "glEnableVertexAttribArray")

		//ASRT_PROC(drawArrays, "glDrawArrays")
		ASRT_PROC(drawElements, "glDrawElements")

		ASRT_PROC(genTextures, "glGenTextures")
		ASRT_PROC(bindTexture, "glBindTexture")
		ASRT_PROC(texParameteri, "glTexParameteri")

		ASRT_PROC(texImage2D, "glTexImage2D")
		ASRT_PROC(generateMipmap, "glGenerateMipmap")
		return true;
	}

};