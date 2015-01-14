#include <GL\glew.h>
#include <GL\wglew.h>

//GLEW includes must be first!
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <soil\SOIL.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>

#include "Application.h"
#include "Player.h"

#define GLEW_STATIC

GLuint CreateShader(GLenum a_ShaderType, const char* a_strShaderFile);

GLuint CreateProgram(const char* a_vertex, const char* a_frag);

float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);

int main()
{
	////Initialise GLFW
	//if (!glfwInit())
	//{
	//	return -1;
	//}

	////create a windowed mode window and it's OpenGL context
	//GLFWwindow* window;
	//window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
	//if (!window)
	//{
	//	glfwTerminate();
	//	return -1;
	//}

	////make the window's context current
	//glfwMakeContextCurrent(window);

	////start GLEW
	//if (glewInit() != GLEW_OK)
	//{
	//	//openGL didn't start shutdown GLFW and return error code
	//	glfwTerminate();
	//	return -1;
	//}
	Application appInstance;
	appInstance.Initialize(MNF::Globals::SCREEN_WIDTH, MNF::Globals::SCREEN_HEIGHT, "Hello World");


	Player spaceShip;
	spaceShip.Initialize(vec4(680/2, 480/2 , 0 , 0));

	//create shader program
	GLuint programFlat = CreateProgram(".\\src\\VertexShader.glsl", ".\\src\\FlatFragmentShader.glsl");

	//create textured shader program
	GLuint programTexture = CreateProgram(".\\src\\VertexShader.glsl", ".\\src\\TexturedFragmentShader.glsl");

	//find the position of the matrix variable int the shader program
	GLuint IDFlat = glGetUniformLocation(programFlat, "MVP");

	//set up mapping to the screen to pixel coordinates
	float* orthographicProjection = getOrtho(0, 1024, 0, 720, 0, 100);

	//loop until the user closes the window
	//while (!glfwWindowShouldClose(appInstance.windowHandle))
	//{
	//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	////enable shaders
	//	glUseProgram(programTexture);

	//	//send ortho projection info to shader
	//	glUniformMatrix4fv(IDFlat, 1, GL_FALSE, orthographicProjection);

	//	//enable the vertex array states
	//	glEnableVertexAttribArray(0);
	//	glEnableVertexAttribArray(1);
	//	glEnableVertexAttribArray(2);

	//	//draw code goes here
	//	spaceShip.Draw();

	//	//swap front and back buffers
	//	glfwSwapBuffers(appInstance.windowHandle);

	//	//poll for and process events
	//	glfwPollEvents();
	//}

	//glfwTerminate();
	//return 0;

	do{
		appInstance.ClearScreen();

		////enable shaders
		glUseProgram(programTexture);

		//send ortho projection info to shader
		glUniformMatrix4fv(IDFlat, 1, GL_FALSE, orthographicProjection);

		//enable the vertex array states
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//draw code goes here
		spaceShip.Draw();

	} while (appInstance.FrameworkUpdate());

	appInstance.Shutdown();
	return 0;
}

GLuint CreateShader(GLenum a_ShaderType, const char* a_ShaderFile)
{
	std::string shaderCode;
	//open shader file
	std::ifstream shaderStream(a_ShaderFile);
	//if that worked ok, load file line by line
	if (shaderStream.is_open())
	{
		std::string line = "";
		while (std::getline(shaderStream, line))
		{
			shaderCode += "\n" + line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const* shaderSourcePointer = shaderCode.c_str();

	//create shader ID
	GLuint shader = glCreateShader(a_ShaderType);
	//load source code
	glShaderSource(shader, 1, &shaderSourcePointer, NULL);

	//compile shader
	glCompileShader(shader);

	//check for errors
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);

		const char* shaderType = NULL;
		switch (a_ShaderType)
		{
		case GL_VERTEX_SHADER:
			shaderType = "vertex";
			break;
		case GL_FRAGMENT_SHADER:
			shaderType = "fragment";
			break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", shaderType, infoLog);
		delete[] infoLog;
	}

	return shader;

}

GLuint CreateProgram(const char* a_vertex, const char* a_frag)
{
	//ofstream file;
	//file.open(a_vertex, ios::in);
	//cout << file.is_open() << endl;

	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint program = glCreateProgram();

	//attach shaders
	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glAttachShader(program, *shader);
	}

	//link program
	glLinkProgram(program);

	//check for link errors and output them
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);

		fprintf(stderr, "Linker failure: %s\n", infoLog);
		delete[] infoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(program, *shader);
		glDeleteShader(*shader);
	}
	return program;
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