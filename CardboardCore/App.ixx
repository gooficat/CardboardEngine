export module App;

import EventHandler;
import Window;
import RenderContext;
import OpenGL;

import Logger;

import Object;

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
				1280,
				720
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

		while (!event_handler->shouldQuit()) {
			GL::clear(0x00004100);

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
};