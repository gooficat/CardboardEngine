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
import Mesh;

import <memory>;

namespace Cardboard
{
	export class App
	{
	public:
		App() :
			internal_logger( std::make_unique<Logger>(
				"x64/Debug/logs/internal_log.txt"
			) ),
			logger( std::make_unique<Logger>(
				"x64/Debug/logs/log.txt"
			) )
		{
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
		}

		virtual void customOnDrawStuff()
		{

		}

		void run()
		{

			while ( !event_handler->shouldQuit() )
			{
				GL::clear( 0x4000 | 0x100 );
				customOnDrawStuff();
				render_context->swapBuffers();
				event_handler->pollEvents();
			}
		}

		std::unique_ptr<EventHandler> event_handler;

		std::unique_ptr<Window> window;

		std::unique_ptr<RenderContext> render_context;

		inline static App* active_instance;

		static App* createApp();

		std::unique_ptr<Logger> logger;

	private:
		std::unique_ptr<Logger> internal_logger;


		//GL::Uint test_buffer, test_vao;
		Mat4 test_model, test_view, test_projection;

	};
}