#include <iostream>
#include "Framework.h"

AIF::Framework fk;

GLuint texID;
GLuint texID2;
GLuint texID3;

int main()
{
	fk.Initialize(AIF::Globals::SCREEN_WIDTH, AIF::Globals::SCREEN_HEIGHT, "Hello World", vec4(0, 0, 0, 0));

	int texID[12];

	//unsigned int texID = appInstance.CreateSprite(".\\assets\\test4.png", 32, 32);
	texID[0] = fk.CreateSprite(".\\assets\\oaksprite.png", 150, 150, vec4(0.0f, 0.0f, .33f, 0.25f));
	//texID[1] = fk.CreateSprite(".\\assets\\oakSprite.png", 150, 150, vec4(.6f, .6f, 1.0f, 1.0f));
	//texID[2] = fk.CreateSprite(".\\assets\\oakSprite.png", 100, 100, vec4(.6f, .6f, 1.0f, 1.0f));

	int a = 1024/2;
	int b = 768/2;


	do{
		fk.ClearScreen();

		fk.MoveSprite(texID[0], a, b);
		//fk.MoveSprite(texID[1], 10, 10);
		//fk.MoveSprite(texID[2], 110, 110);
		//draw code goes here
		fk.DrawSprite(texID[0]);
		//fk.DrawSprite(texID[1]);
		//fk.DrawSprite(texID[2]);
		

	} while (fk.FrameworkUpdate());

	fk.Shutdown();
	return 0;
}