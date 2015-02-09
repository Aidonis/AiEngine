#define GLEW_STATIC
#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include <stdio.h>
#include <iostream>

#include "Sprite.h"
#include "Quad.h"
#include "Animator.h"
#include <Windows.h>


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
	theSprite.s_Animator.LoadSprites("./assets/oakSheet.xml");

	int i = 0;
	while (!glfwWindowShouldClose(window)){
		glViewport(0, 0, g_WIDTH, g_HEIGHT);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		if (i < 3){
			switch (i)
			{
			case 0:
				theSprite.s_Animator.SetSprite("left0");
				i++;
				break;
			case 1:
				theSprite.s_Animator.SetSprite("left1");
				i++;
				break;
			case 2:
				theSprite.s_Animator.SetSprite("left2");
				i++;
				i = 0;
				break;
			}
		}

		theSprite.s_Position += glm::vec3(5, 0, 0);

		theSprite.Update(0.1f);
		Sleep(150);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}