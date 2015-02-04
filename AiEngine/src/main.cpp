#define GLEW_STATIC
#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include <stdio.h>


#include "Sprite.h"
#include "Quad.h"


int main()
{
	//open an OS window using GLFW

	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3!\n");
		return 1;
	}

	GLFWwindow * window = glfwCreateWindow(g_WIDTH, g_HEIGHT, "Hello Triangle", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3!\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	//start Glew
	//glewExperimental = GLU_TRUE;
	glewInit();

	Orthographic(0.f, (float)g_WIDTH, (float)g_HEIGHT, 0.f, -1.f, 1.f, Ortho);

	Quad theSquare;
	Sprite theSprite;

	theSprite.LoadTexture("./assets/oakSprite.png");

	while (!glfwWindowShouldClose(window)){
		glViewport(0, 0, g_WIDTH, g_HEIGHT);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		theSprite.Draw();
		theSprite.SetUVData();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}