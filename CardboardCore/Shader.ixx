export module Shader;
import std;
import OpenGL;
import Mathematics;

export class Shader {
public:
	GL::Uint ID;
	Shader(const GL::Char * vertex_source, const GL::Char * fragment_source) {
		GL::Uint vertex = GL::createShader(0x8B31);
		GL::Uint fragment = GL::createShader(0x8B30);
		GL::shaderSource(vertex, 1, &vertex_source, nullptr);
		GL::shaderSource(fragment, 1, &fragment_source, nullptr);
		GL::compileShader(vertex);
		GL::compileShader(fragment);
		this->ID = GL::createProgram();
		GL::attachShader(ID, vertex);
		GL::attachShader(ID, fragment);
		GL::linkProgram(ID);
	}

	void use() const {
		GL::useProgram(ID);
	}

	void setMat4(const GL::Char * name, Mat4& data) {
		GL::uniformMatrix4fv(GL::getUniformLocation(ID, name), 1, 0, &data[0]);
	}
	void setInt(const GL::Char * name, GL::Int data) {
		GL::uniform1i(GL::getUniformLocation(ID, name), data);
	}
private:
};