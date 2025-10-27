export module Texture;

import std;
import OpenGL;
import Logger;
import <stdint.h>;

import Shader;


export class Texture {
public:
	GL::Uint ID;
	const GL::Char *name;
	Texture(const std::string& path, std::unique_ptr<Logger>& logger) {
		uint8_t header[54];
		uint32_t data_pos;
		uint32_t width, height;
		uint32_t size;

		uint8_t *data;

		std::basic_ifstream<uint8_t> f(path, std::ios::binary);

		if (!f) {
			logger->log(std::string("Failed to open texture of path ") + path + " !", LOG_ERROR);
		}

		if (!f.read(header, 54)) {
			logger->log(std::string(path) + " is not a valid bitmap!", LOG_ERROR);
		}

		if (header[0] != 'B' || header[1] != 'M') {
			logger->log(std::string(path) + " is not a valid bitmap!", LOG_ERROR);
		}

		data_pos = *(int32_t*)&(header[0x0A]);
		size = *(int32_t*)&(header[0x22]);
		width = *(int32_t*)&(header[0x12]);
		height = *(int32_t*)&(header[0x16]);

		if (size == 0) {
			size = width * height * 4;
		}
		if (data_pos == 0) {
			data_pos = 54;
		}

		data = new uint8_t[size];

		f.read(data, size);
		f.close();

		GL::genTextures(1, &ID);

		GL::bindTexture(0x0DE1, ID);

		GL::texImage2D(0x0DE1, 0, 0x1907, width, height, 0, 0x80E0, 0x1401, data);

		GL::texParameteri(0x0DE1, 0x2802, 0x8370); //el problemo
		GL::texParameteri(0x0DE1, 0x2803, 0x8370);// biEn?
		GL::texParameteri(0x0DE1, 0x2800, 0x2601);
		GL::texParameteri(0x0DE1, 0x2801, 0x2703);

		GL::generateMipmap(0x0DE1);
	}

	void use(Shader& shader) {
		GL::bindTexture(0x0DE1, ID);
		//shader.setInt("diffuse", ID);
	}
};