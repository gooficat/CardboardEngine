export module Window;
import std;

//import EventHandler;

import Logger;

import "Api.h";
import <Windows.h>;
import <cstdint>;


// this should move to render context later
export HGLRC ( *wglCreateContextAttribsARB )( HDC hdc, HGLRC h_share_context, const int* attrib_list );
export BOOL ( *wglChoosePixelFormatARB )( HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats );

namespace Cardboard
{

	export class WindowSpec
	{
	public:
		const char* title;
		uint16_t width;
		uint16_t height;
	};

	export class PixelFormat
	{
	public:
		PIXELFORMATDESCRIPTOR internal_descriptor;
	};


	export class Window
	{
	public:
		Window( const WindowSpec& spec, LRESULT( *EventProcedure )( HWND, UINT, WPARAM, LPARAM ), const std::unique_ptr<Logger>& logger ) :
			should_close( false )
		{

			WNDCLASSA dummy_class = {
				.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
				.lpfnWndProc = DefWindowProcA,
				.hInstance = GetModuleHandle( 0 ),
				.lpszClassName = "WGL_Dummy_ExtensionLoader"
			};

			if ( !RegisterClassA( &dummy_class ) )
			{
				logger->log( "Failed to make window class to check GL extensions!", LOG_ERROR );
			}

			HWND dummy_window_handle = CreateWindowExA(
				0,
				dummy_class.lpszClassName,
				spec.title,
				0,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				0,
				0,
				dummy_class.hInstance,
				0
			);

			if ( !dummy_window_handle )
			{
				logger->log( "Failed to make window handle to check GL extensions!", LOG_ERROR );
			}

			HDC dummy_context_handle = GetDC( dummy_window_handle );

			PIXELFORMATDESCRIPTOR pfd { 0 };
			pfd = {
				.nSize = sizeof( pfd ),
				.nVersion = 1,
				.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				.iPixelType = PFD_TYPE_RGBA,
				.cColorBits = 24,
				.cAlphaBits = 8,
				.cDepthBits = 24,
				.cStencilBits = 8,
				.iLayerType = PFD_MAIN_PLANE
			};

			int pixel_format = ChoosePixelFormat( dummy_context_handle, &pfd );
			if ( !( pixel_format ) )
			{
				logger->log( "Pixel format of dummy context is null!", LOG_ERROR );
			}

			if ( !SetPixelFormat( dummy_context_handle, pixel_format, &pfd ) )
			{
				logger->log( "Failed to set pixel format for dummy context!", LOG_ERROR );
			}

			HGLRC dummy_context;
			if ( !( dummy_context = wglCreateContext( dummy_context_handle ) ) )
			{
				logger->log( "Failed to make dummy context!", LOG_ERROR );
			}

			if ( !wglMakeCurrent( dummy_context_handle, dummy_context ) )
			{
				logger->log( "Failed to make dummy context current!", LOG_ERROR );
			}

			wglCreateContextAttribsARB = ( decltype( wglCreateContextAttribsARB ) ) wglGetProcAddress( "wglCreateContextAttribsARB" );
			wglChoosePixelFormatARB = ( decltype( wglChoosePixelFormatARB ) ) wglGetProcAddress( "wglChoosePixelFormatARB" );

			wglMakeCurrent( dummy_context_handle, 0 );
			wglDeleteContext( dummy_context );
			ReleaseDC( dummy_window_handle, dummy_context_handle );
			DestroyWindow( dummy_window_handle );


			// the "real" window creation starts here:

			Window::active_instance = this;

			instance_handle = GetModuleHandle( 0 );
			window_class = {
				.lpfnWndProc = EventProcedure,
				.hInstance = instance_handle,
				.lpszClassName = spec.title
			};

			RegisterClassA( &window_class );

			this->window_handle = CreateWindowExA(
				0,
				spec.title,
				spec.title,
				WS_OVERLAPPEDWINDOW | WS_EX_COMPOSITED,
				CW_USEDEFAULT, CW_USEDEFAULT,
				spec.width, spec.height,
				NULL,
				NULL,
				instance_handle,
				NULL
			);
			if ( window_handle == NULL )
			{
				Logger::active_instance->log( "The window failed to initialize.", LOG_ERROR );
				return;
			}

			this->width = spec.width;
			this->height = spec.height;
		}

		void show()
		{
			ShowWindow( window_handle, SW_SHOW );
		}

		uint32_t getWidth()
		{
			return width;
		}

		uint32_t getHeight()
		{
			return height;
		}

		HWND& getHandle()
		{
			return window_handle;
		}

		PixelFormat& getFormat()
		{
			return format;
		}

		PixelFormat format;

		bool should_close;
		inline static Window* active_instance;

		uint32_t width;
		uint32_t height;
	private:

		HWND window_handle;
		HINSTANCE instance_handle;
		WNDCLASSA window_class;

	};

}