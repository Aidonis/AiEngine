#include <iostream>
#include "Framework.h"

AIF::Framework fk;

GLuint texID;

int main()
{
	fk.Initialize(AIF::Globals::SCREEN_WIDTH, AIF::Globals::SCREEN_HEIGHT, "Hello World", vec4(0, 0, 0, 0));


	//unsigned int texID = appInstance.CreateSprite(".\\assets\\test4.png", 32, 32);
	texID = fk.CreateSprite(".\\assets\\test4.png", 32, 32, vec4(.6f, .6f, 1.0f, 1.0f));

	fk.MoveSprite(texID, 1, 1);

	do{
		fk.ClearScreen();



		//draw code goes here
		fk.DrawSprite(texID);

	} while (fk.FrameworkUpdate());

	fk.Shutdown();
	return 0;
}