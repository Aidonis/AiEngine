#include "ToolBox.h"


glm::mat4 Ortho;
int g_WIDTH = 640;
int g_HEIGHT = 480;
double fps, elapsedTime;
double deltaTime = 0;
int frames;

double GetDeltaTime()
{
	return deltaTime;
}

void ResetDeltaTime()
{

	deltaTime = glfwGetTime();
	elapsedTime += deltaTime;
	frames++;
	if (elapsedTime > 0.25)
	{
		fps = (double)frames / elapsedTime;
		elapsedTime = 0;
		frames = 0;
	}
	glfwSetTime(0);

}

void Initialize(){

}

void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, glm::mat4 & mat)
{

	float deltaX = a_fRight - a_fLeft;
	float deltaY = a_fTop - a_fBottom;
	float deltaZ = a_fNear - a_fFar;

	mat[0].x = 2.f / deltaX;
	mat[0].y = 0.f;
	mat[0].z = 0.f;
	mat[0].w = 0.f;

	mat[1].x = 0.f;
	mat[1].y = 2.f / deltaY;
	mat[1].z = 0.f;
	mat[1].w = 0.f;

	mat[2].x = 0.f;
	mat[2].y = 0.f;
	mat[2].z = 2.f / deltaZ;
	mat[2].w = 0.f;

	mat[3].x = ((a_fLeft + a_fRight) / (a_fLeft - a_fRight));
	mat[3].y = ((a_fBottom + a_fTop) / (a_fBottom - a_fTop));
	mat[3].z = (-(a_fNear + a_fFar) / (a_fFar - a_fNear));
	mat[3].w = 1.f;
}

//Math stuff
glm::vec2 Lerp(glm::vec2 a_start, glm::vec2 a_end, float a_percent){
	return (a_start + (a_end - a_start) * a_percent);
}