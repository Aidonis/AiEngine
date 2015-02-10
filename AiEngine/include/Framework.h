#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_
#define GLEW_STATIC
#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include "Sprite.h"
#include "Fontbox.h"
#include <stdio.h>
#include <iostream>


class Framework{
public:
//Initialize new window
int Initialize(int a_Width, int a_Height, const char* a_title){
	//open an OS window using GLFW
	if (!glfwInit()){
		fprintf(stderr, "ERROR: could not start GLFW3!\n");
		return -1;
	}

	windowHandle = glfwCreateWindow(a_Width, a_Height, a_title, NULL, NULL);
	if (!windowHandle){
		fprintf(stderr, "ERROR: could not open window with GLFW3!\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(windowHandle);
	if (glewInit() != GLEW_OK){
		//openGL didn't start shutdown GLFW and return error code
		glfwTerminate();
		return -1;
	}

}

//Key Handeling
bool IsKeyDown(int a_Key){
	if (GLFW_PRESS == glfwGetKey(windowHandle, a_Key)) {
		return true;
}	
	else
		return false;
}

bool FrameworkUpdate(){
	if (glfwWindowShouldClose(windowHandle)){
		return false;
	}

	glfwSwapBuffers(windowHandle);
	glfwPollEvents();
	if(IsKeyDown(GLFW_KEY_ESCAPE)){
		glfwSetWindowShouldClose(windowHandle, 1);
	}
	return true;
}

//Clear screen to grey
void ClearScreen(){
	glViewport(0, 0, g_WIDTH, g_HEIGHT);
	glClearColor(0.5f, 0.5f, 0.5f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}




//Create sprite from given sprite name on given xmlsheet
unsigned int CreateSprite(const char* a_xmlSheet){
	Sprite* newSprite = new Sprite;

	newSprite->s_Animator.LoadSprites(a_xmlSheet);
	newSprite->LoadTexture(newSprite->s_Animator.atlas.sSheet.c_str());
	newSprite->s_Animator.SetSprite("front0");
	spriteList.push_back(newSprite);

	return spriteList.size() - 1;
}

void SetSprite(unsigned int a_SpriteID, const char* a_SpriteName){
	Sprite* sp = spriteList[a_SpriteID];
	sp->s_Animator.SetSprite(a_SpriteName);
}

//Move sprite to given position
void MoveSprite(unsigned int a_SpriteID, float a_XPos, float a_YPos){
	Sprite* list = spriteList[a_SpriteID];

	list->s_Position = glm::vec3(a_XPos, a_YPos, 1);
}

//Draw the given sprite
void DrawSprite(unsigned int a_SpriteID){
	Sprite* sp = spriteList[a_SpriteID];

	sp->Update(0.1f);
}

private:
	std::vector<Sprite*> spriteList;
	GLFWwindow* windowHandle;
};

#endif //_FRAMEWORK_H_