export module App;

import Window;
import RenderContext;

import Logger;

import OpenGL;

import <memory>;


export class App {
public:
	App() :
		internal_logger(std::make_unique<Logger>(
			"C:\\Projects\\CardboardEngine\\x64\\Debug\\logs\\internal_log.txt"
		)) {
		this->window = std::make_unique<Window>(
			WindowSpec {
				" ",
				640,
				360
			},
			this->internal_logger
		);
		this->render_context = std::make_unique<RenderContext>(
			window->getHandle(),
			this->internal_logger,
			24,
			24
		);
		window->show();
		
		App::active_instance = this;

		if (!GL::load(this->internal_logger)) {
			delete this;
		}
		else {
			run();
		}
	}

	void run() {
		internal_logger->log("Application launched, now running.", LOG_MESSAGE);
		while (true);
	}
	
	std::unique_ptr<Window> window;

	std::unique_ptr<RenderContext> render_context;

	inline static App *active_instance;
private:
	std::unique_ptr<Logger> internal_logger;
};