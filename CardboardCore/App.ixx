export module App;

import EventHandler;
import Window;
import RenderContext;
import OpenGL;

import Logger;

import Object;
import Mathematics;

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
			24,
			24
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
		const GL::Char *vertexShaderSource = R"(
			layout (location = 0) in vec3 a_pos;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

			void main() {
				gl_Position = projection * view * model * vec4(a_pos + vec3(0.5f, 0.0f, 0.0f), 1.0f);
			}
		)";
		const GL::Char *fragmentShaderSource = R"(
			void main() {
				gl_FragColor = vec4(1.0f, 0.4f, 0.8f, 1.0f);
			}
		)";

		test_shaderprogram = GL::createProgram();
		GL::Uint test_vert = GL::createShader(0x8B31);
		GL::shaderSource(test_vert, 1, &vertexShaderSource, NULL);
		GL::compileShader(test_vert);

		Transform test_transform;
		test_transform.position.x = -0.5f;
		test_transform.rotation.x = -0.9f;

		test_projection = Mat4::simpleOrtho(2, 2, 2);//orthographic(0, 2, 0, 2, 0, 2);
		test_view = Mat4::identity();
		test_model = test_transform.getMatrix();

		GL::Uint test_frag = GL::createShader(0x8B30);
		GL::shaderSource(test_frag, 1, &fragmentShaderSource, NULL);
		GL::compileShader(test_frag);

		GL::attachShader(test_shaderprogram, test_vert);
		GL::attachShader(test_shaderprogram, test_frag);
		GL::linkProgram(test_shaderprogram);
		

		GL::genVertexArrays(1, &test_vao);
		GL::bindVertexArray(test_vao);
		GL::genBuffers(1, &test_buffer);
		GL::bindBuffer(0x8892, test_buffer);
		GL::bufferData(0x8892, 9 * sizeof(GL::Float), &vertices[0], 0x88E4);
		GL::enableVertexAttribArray(0);
		GL::vertexAttribPointer(0, 3, 0x1406, 0, 3 * sizeof(GL::Float), (void*)0);
		GL::bindVertexArray(0);

		while (!event_handler->shouldQuit()) {
			test_transform.rotation.z += 0.001f;
			test_transform.position.x += 0.0001f;
			GL::clear(0x00004100);

			GL::useProgram(test_shaderprogram);
			test_model = test_transform.getMatrix();

			GL::uniformMatrix4fv(GL::getUniformLocation(test_shaderprogram, "model"), 1, 0, &test_model.x1);
			GL::uniformMatrix4fv(GL::getUniformLocation(test_shaderprogram, "view"), 1, 0, &test_view.x1);
			GL::uniformMatrix4fv(GL::getUniformLocation(test_shaderprogram, "projection"), 1, 0, &test_projection.x1);

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


	GL::Uint test_buffer, test_vao, test_shaderprogram;
	Mat4 test_model, test_view, test_projection;

};