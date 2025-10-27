export module App;

import EventHandler;
import Window;
import RenderContext;
import OpenGL;

import Logger;

import Object;
import Mathematics;
import Shader;
import Texture;

import <memory>;


export class App {
public:
	App() :
		internal_logger(std::make_unique<Logger>(
			"C:\\Projects\\CardboardEngine\\x64\\Debug\\logs\\internal_log.txt"
		)) {
		App::active_instance = this;

		this->event_handler = std::make_unique<EventHandler>(
			
		);
		
		PixelFormat pixel_format = RenderContext::generateFormat();

		this->window = std::make_unique<Window>(
			WindowSpec {
				" ",
				640,
				360
			},
			EventHandler::MessageHandler,
			this->internal_logger
		);
		this->render_context = std::make_unique<RenderContext>(
			window->getHandle(),
			this->internal_logger,
			window->getFormat()
		);
		window->show();
		
		run();
	}

	void run() {
		internal_logger->log("Application launched, now running.", LOG_MESSAGE);

		GL::viewport(0, 0, window->getWidth(), window->getHeight());
		GL::clearColor(0.2f, 0.4f, 0.5f, 1.0f);


		GL::Float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		const GL::Char *vertexShaderSource = R"(#version 330 core
			layout (location = 0) in vec3 a_pos;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;
			
			out vec2 texPos;

			void main() {
				gl_Position = projection * view * model * vec4(a_pos, 1.0f);

				texPos = a_pos.xy + vec2(0.5f, 0.5f);
			}
		)";
		const GL::Char *fragmentShaderSource = R"(#version 330 core
			out vec4 color;
			uniform sampler2D diffuse;
			in vec2 texPos;
			void main() {
				color = vec4(texture(diffuse, texPos).rgb, 1.0f);
			}
		)";
		Shader test_shader(vertexShaderSource, fragmentShaderSource);

		Transform test_transform;

		test_projection = test_projection.simpleOrtho(4/3.0f, 1, 1);//orthographic(0, 2, 0, 2, 0, 2);
		test_view = test_view.identity(); // this just quietens intellisense. Mat4::identity() and Mat4::simpleOrtho are static.
		test_model = test_transform.getMatrix();

		Texture tex("C:/Projects/CardboardEngine/CardboardCore/resources/DiamondPlate009_1K-PNG_Color.bmp", internal_logger);
		GL::genVertexArrays(1, &test_vao);
		GL::bindVertexArray(test_vao);
		GL::genBuffers(1, &test_buffer);
		GL::bindBuffer(0x8892, test_buffer);
		GL::bufferData(0x8892, 9 * sizeof(GL::Float), &vertices[0], 0x88E4);
		GL::enableVertexAttribArray(0);
		GL::vertexAttribPointer(0, 3, 0x1406, 0, 3 * sizeof(GL::Float), (void*)0);
		GL::bindVertexArray(0);

		while (!event_handler->shouldQuit()) {
			test_transform.rotation.x += 0.001f;
			test_transform.rotation.y += 0.001f;
			test_transform.position.y += 0.0001f;
			test_model = test_transform.getMatrix();
			GL::clear(0x00004100);

			test_shader.use();

			tex.use(test_shader);

			test_shader.setMat4("model", test_model);

			test_shader.setMat4("view", test_view);
			test_shader.setMat4("projection", test_projection);

			GL::bindVertexArray(test_vao);
			GL::drawArrays(0x0004, 0, 3);
			//std::cout << "I'm in a loop!" << std::endl;


			render_context->swapBuffers();
			event_handler->pollEvents();
		}
	}
	
	std::unique_ptr<EventHandler> event_handler;

	std::unique_ptr<Window> window;

	std::unique_ptr<RenderContext> render_context;

	inline static App *active_instance;
private:
	std::unique_ptr<Logger> internal_logger;


	GL::Uint test_buffer, test_vao;
	Mat4 test_model, test_view, test_projection;

};