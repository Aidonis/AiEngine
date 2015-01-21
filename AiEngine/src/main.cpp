#include <soil\SOIL.h>

#include <time.h>

#include "Application.h"
#include "Sprite.h"

#define GLEW_STATIC

float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);

int main()
{
	Application appInstance;
	appInstance.Initialize(MNF::Globals::SCREEN_WIDTH, MNF::Globals::SCREEN_HEIGHT, "Hello World");


//	Player spaceShip;
//	spaceShip.Initialize();

	//unsigned int texID = appInstance.CreateSprite(".\\assets\\test4.png", 32, 32);
	unsigned int texID = appInstance.CreateSprite(".\\assets\\test4.png", 32, 32, vec4(.6,.6,1,1));

	appInstance.MoveSprite(texID, 1, 1);


	//find the position of the matrix variable int the shader program
	GLuint IDFlat = glGetUniformLocation(appInstance.programFlat, "MVP");
	
	//set up mapping to the screen to pixel coordinates
	float* orthographicProjection = getOrtho(0, 1024, 0, 720, 0, 100);

	do{
		appInstance.ClearScreen();

		////enable shaders
		glUseProgram(appInstance.programTexture);

		//send ortho projection info to shader
		glUniformMatrix4fv(IDFlat, 1, GL_FALSE, orthographicProjection);

		//enable the vertex array states
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//draw code goes here
		appInstance.DrawSprite(texID);

	} while (appInstance.FrameworkUpdate());

	appInstance.Shutdown();
	return 0;
}

float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	//to correspond with mat4 in the shader
	//ideally this function would be part of your matrix class
	//however I wasn't willing to write your matrix class for you just to show you this
	//so here we are in array format!
	//add this to your matrix class as a challenge if you like!
	float* toReturn = new float[12];
	toReturn[0] = 2.0 / (right - left);;
	toReturn[1] = toReturn[2] = toReturn[3] = toReturn[4] = 0;
	toReturn[5] = 2.0 / (top - bottom);
	toReturn[6] = toReturn[7] = toReturn[8] = toReturn[9] = 0;
	toReturn[10] = 2.0 / (a_fFar - a_fNear);
	toReturn[11] = 0;
	toReturn[12] = -1 * ((right + left) / (right - left));
	toReturn[13] = -1 * ((top + bottom) / (top - bottom));
	toReturn[14] = -1 * ((a_fFar + a_fNear) / (a_fFar - a_fNear));
	toReturn[15] = 1;
	return toReturn;
}