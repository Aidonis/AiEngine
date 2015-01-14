#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#include "GL\glew.h"
#include "GL\wglew.h"

//glew must be included first
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

namespace AIF{
	class Framework{
	public:

		int Initialize(int a_screenWidth, int a_screenHeight, const char* a_title){
			//Initialise GLFW
			if (!glfwInit())
			{
				return -1;
			}

			//create a windowed mode window and it's OpenGL context
			windowHandle = glfwCreateWindow(a_screenWidth, a_screenHeight, a_title, NULL, NULL);
			if (!windowHandle)
			{
				glfwTerminate();
				return -1;
			}

			//make the window's context current
			glfwMakeContextCurrent(windowHandle);

			//start GLEW
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
			return true;
		}

		void ClearScreen(){
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		static void Shutdown(){
			glfwTerminate();
		}

		GLFWwindow* windowHandle;

	protected:

	private:
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
	};
}

#endif //_FRAMWORK_H_