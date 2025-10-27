export module Mesh;

import std;
import OpenGL;
import Texture;
import Shader;

export class Mesh {
public:
	Mesh(const std::vector<GL::Float>& positions, const std::vector<GL::Uint>& indices) {
		generate(positions, indices);
	}

	void draw(Shader& shader) {
		GL::bindVertexArray(VAO);
		GL::drawElements(0x0004, indexCount, 0x1405, 0);
	}
protected:
	GL::Uint VAO, VBO, EBO;
	void generate(const std::vector<GL::Float>& positions, const std::vector<GL::Uint>& indices) {
		GL::genVertexArrays(1, &VAO);
		GL::genBuffers(1, &VBO);
		GL::genBuffers(1, &EBO);
		GL::bindVertexArray(VAO);
		GL::bindBuffer(0x8892, VBO);
		GL::bindBuffer(0x8893, EBO);
		GL::bufferData(0x8892, positions.size() * sizeof(GL::Float), positions.data(), 0x88E4);
		GL::bufferData(0x8893, indices.size() * sizeof(GL::Uint), indices.data(), 0x88E4);
		GL::enableVertexAttribArray(0);
		GL::vertexAttribPointer(0, 3, 0x1406, 0, 3 * sizeof(GL::Float), (void*)0);

		indexCount = indices.size();
	}
	GL::Sizei indexCount;
private:
};