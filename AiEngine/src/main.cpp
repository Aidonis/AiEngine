#include <iostream>
#include "Framework.h"

AIF::Framework fk;

GLuint texID;
GLuint texID2;

int main()
{
	fk.Initialize(AIF::Globals::SCREEN_WIDTH, AIF::Globals::SCREEN_HEIGHT, "Hello World", vec4(0, 0, 0, 0));


	//unsigned int texID = appInstance.CreateSprite(".\\assets\\test4.png", 32, 32);
	texID = fk.CreateSprite(".\\assets\\test4.png", 50, 50, vec4(.6f, .6f, 1.0f, 1.0f));
	texID2 = fk.CreateSprite(".\\assets\\test2.png", 100, 100, vec4(.6f, .6f, 1.0f, 1.0f));


	do{
		fk.ClearScreen();



		fk.MoveSprite(texID2, 10, 10);
		//draw code goes here
		fk.DrawSprite(texID2);

	} while (fk.FrameworkUpdate());

	fk.Shutdown();
	return 0;
}