#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_
#define GLEW_STATIC
#include "GL\glew.h"
#include "GL\wglew.h"

#include "GLFW/glfw3.h"

#include "Sprite.h"
#include "Quad.h"
#include "Animator.h"
#include "Fontbox.h"

GLFWwindow* windowHandle;
GLuint shaderProgram;

int Initialize(int a_Width, int a_Height, const char* a_title){
	//open an OS window using GLFW

	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3!\n");
		return -1;
	}

	GLFWwindow * window = glfwCreateWindow(a_Width, a_Height, a_title, NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3!\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(windowHandle);
	if (glewInit() != GLEW_OK)
	{
		//openGL didn't start shutdown GLFW and return error code
		glfwTerminate();
		return -1;
	}

	Fontbox::Instance().LoadFont("./assets/font/arial2.xml");
	Orthographic(0.f, (float)a_Width, (float)a_Height, 0.f, -1.f, 1.f, Ortho);
}

bool FrameworkUpdate(){
	if (glfwWindowShouldClose(windowHandle)){
		return false;
	}

	glfwSwapBuffers(windowHandle);
	glfwPollEvents();
	return true;
}

#endif //_FRAMEWORK_H_