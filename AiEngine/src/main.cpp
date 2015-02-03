#include <iostream>
#include "Framework.h"

AIF::Framework fk;

GLuint texID;
GLuint texID2;
GLuint texID3;

int main()
{
	fk.Initialize(g_WIDTH, g_HEIGHT, "Hello World", vec4(0, 0, 0, 0));

	do{
		fk.ClearScreen();

	} while (fk.FrameworkUpdate());

	fk.Shutdown();
	return 0;
}