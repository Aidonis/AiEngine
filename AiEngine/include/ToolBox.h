#ifndef _TOOLBOX_H_
#define _TOOLBOX_H_

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "GLFW\glfw3.h"

extern glm::mat4 Ortho;

//Window size stuff
extern int g_WIDTH;
extern int g_HEIGHT;

struct Vertex{
	glm::vec4 Pos;
	glm::vec4 Color;
	glm::vec2 UV;
};

struct Transform{
	glm::mat4 viewTranslate;
	glm::mat4 viewRotateZ;
	glm::mat4 modelScale;
	glm::mat4 MVP;
};

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

#endif //_TOOLBOX_H_