#include <iostream>
#include <GL\glew.h>
#include "Display.h"
#undef main

int main()
{
	Display display( 800, 600, "Hello world!" );

	while( !display.IsClosed() )
	{
		display.Clear( 0.0f, 0.15f, 0.3f, 1.0f );

		display.Update();
	}

	return 0;
}