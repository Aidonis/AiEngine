#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_
#define GLEW_STATIC
#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include <stdio.h>
#include <iostream>

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

	windowHandle = glfwCreateWindow(a_Width, a_Height, a_title, NULL, NULL);
	if (!windowHandle)
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

}

bool FrameworkUpdate(){
	if (glfwWindowShouldClose(windowHandle)){
		return false;
	}

	glfwSwapBuffers(windowHandle);
	glfwPollEvents();
	if (GLFW_PRESS == glfwGetKey(windowHandle, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(windowHandle, 1);
	}
	return true;
}

#endif //_FRAMEWORK_H_