export module App;

import EventHandler;
import Window;
import RenderContext;
import Renderer;

import Logger;

import <memory>;


export class App {
public:
	App() :
		internal_logger(std::make_unique<Logger>(
			"C:\\Projects\\CardboardEngine\\x64\\Debug\\logs\\internal_log.txt"
		)) {
		this->event_handler = std::make_unique<EventHandler>(
			
		);
		
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

		renderer = std::make_unique<OpenGL_Renderer>(
			
		);

		run();
	}

	void run() {
		internal_logger->log("Application launched, now running.", LOG_MESSAGE);

		while (true);
	}
	
	std::unique_ptr<EventHandler> event_handler;

	std::unique_ptr<Window> window;

	std::unique_ptr<RenderContext> render_context;

	std::unique_ptr<Renderer> renderer;

	inline static App *active_instance;
private:
	std::unique_ptr<Logger> internal_logger;
};