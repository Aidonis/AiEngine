#define GLEW_STATIC
#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include <stdio.h>
#include <iostream>

#include "Sprite.h"
#include "Quad.h"
#include "Animator.h"
#include "Fontbox.h"
#include <Windows.h>


int main()
{
	//open an OS window using GLFW

	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3!\n");
		return 1;
	}

	GLFWwindow * window = glfwCreateWindow(g_WIDTH, g_HEIGHT, "I'm Gary Oak", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3!\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glewInit();

	Orthographic(0.f, (float)g_WIDTH, (float)g_HEIGHT, 0.f, -1.f, 1.f, Ortho);

	Sprite theSprite;
	theSprite.LoadTexture("./assets/oakSprite.png");
	theSprite.s_Animator.LoadSprites("./assets/oakSheet.xml");

	Sprite theTwin;
	theTwin.LoadTexture("./assets/oakSprite.png");
	theTwin.s_Animator.LoadSprites("./assets/oakSheet.xml");

	Fontbox::Instance().LoadFont("./assets/font/arial2.xml");
	int i = 0;
	while (!glfwWindowShouldClose(window)){
		float dt = GetDeltaTime();
		glViewport(0, 0, g_WIDTH, g_HEIGHT);
		//glClearColor(.5f, .5f, .5f, 1.0f);
		ClearScreen();

		Fontbox::Instance().DrawString("Gary Things", glm::vec2((g_WIDTH/3) + 30, (g_HEIGHT / 5) * 3), 1);

		if (i< 3){
			switch (i)
			{
			case 0:
				theSprite.s_Animator.SetSprite("left0");
				theTwin.s_Animator.SetSprite("right0");
				i++;
				break;
			case 1:
				theSprite.s_Animator.SetSprite("left1");
				theTwin.s_Animator.SetSprite("right1");
				i++;
				break;
			case 2:
				theSprite.s_Animator.SetSprite("left2");
				theTwin.s_Animator.SetSprite("right2");
				i++;
				i = 0;
				break;
			}
		}

		std::cout << dt << std::endl << std::endl;

			glm::vec3 move(5, 0, 0);
			theSprite.s_Position += move;
			theTwin.s_Position -= move;

		theTwin.Update(0.1f);
		theSprite.Update(0.1f);

		Sleep(150);

		glfwSwapBuffers(window);
		glfwPollEvents();
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, 1);
		}
		ResetDeltaTime();
	}
}