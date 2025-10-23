export module App;

import Window;
import Logger;

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
		
		App::active_instance = this;
	}

	void run() {
		internal_logger->log("Application launched.", LOG_MESSAGE);
	}
	
	std::unique_ptr<Window> window;

	inline static App *active_instance;
private:
	std::unique_ptr<Logger> internal_logger;
};