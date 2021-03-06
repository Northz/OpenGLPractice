#include "Display.h"
#include <GL\glew.h>
#include <iostream>

Display::Display( int width, int height, const std::string & title )
{
	//Initialize SDL window
	SDL_Init( SDL_INIT_EVERYTHING );

	//Color pixel data, at least 8 bits for each parameter, at least 32 bits in total for each pixel
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
	//Allocates space for a 2nd window that won't be displayed
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	//Set the window 
	m_window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL );
	//Create OpenGL context (let's GPU draw to the window)
	m_glContext = SDL_GL_CreateContext( m_window );

	//Find all OpenGL functions that's supported
	GLenum status = glewInit();
	if( status != GLEW_OK )
	{
		std::cerr << "Glew failed to initialize." << std::endl;
	}
	m_isClosed = false;
}

void Display::Clear( float r, float g, float b, float a )
{
	glClearColor( r, g, b, a );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Display::Update()
{
	SDL_GL_SwapWindow( m_window );

	SDL_Event e;
	while( SDL_PollEvent( &e ) )
	{
		if( e.type == SDL_QUIT )
		{
			m_isClosed = true;
		}
	}
}

bool Display::IsClosed()
{
	return m_isClosed;
}

Display::~Display()
{
	//De-initialize everything, cleanup all resources
	SDL_GL_DeleteContext( m_glContext );
	SDL_DestroyWindow( m_window );
	SDL_Quit();
}
