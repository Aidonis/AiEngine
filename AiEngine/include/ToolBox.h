#ifndef _TOOLBOX_H_
#define _TOOLBOX_H_

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "GLFW\glfw3.h"

extern glm::mat4 Ortho;

//Window size stuff
extern int g_WIDTH;
extern int g_HEIGHT;
extern double fps;


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

void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, glm::mat4 & mat);

double GetDeltaTime();

void ResetDeltaTime();

void ClearScreen();

#endif //_TOOLBOX_H_