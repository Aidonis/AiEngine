#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#include "GL\glew.h"
#include "GL\wglew.h"

//glew must be included first
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include <soil\SOIL.h>

#include "Sprite.h"
#include "Globals.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace glm;

namespace AIF{
	class Framework{
	public:

		GLFWwindow* windowHandle;
		GLuint shaderProgram;

		int Initialize(int a_screenWidth, int a_screenHeight, const char* a_title, vec4 a_backgroundColor){
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

			CreateShaderProgram();

			IDTexture = glGetUniformLocation(shaderProgram, "MVP");
			orthographicProjection = getOrtho(0, AIF::Globals::SCREEN_WIDTH, 0, AIF::Globals::SCREEN_HEIGHT, 0, 100);
			backgroundColor = a_backgroundColor;

			//Enable Blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

		void Shutdown(){
			//glDeleteBuffers(1, &mySprite.uiVBO);
	/*		for (Sprite* s : spriteList)
			{
				glDeleteBuffers(1, &s->uiVBO);
				delete s;
			}
			spriteList.clear();*/

			glfwTerminate();
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
			else{
				std::cout << "error stuff" << std::endl;
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

		//create textured shader program
		void CreateShaderProgram()
		{
			shaderProgram = CreateProgram(".\\src\\VertexShader.glsl", ".\\src\\TexturedFragmentShader.glsl");
		}

		GLuint CreateProgram(const char* a_vertex, const char* a_frag){


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

		//Create sprite ID from given file and given UVs.
		//UV given as (x1,y1,x2,y2) where (x1,y1) is the bottom left and (x2,y2) is the top right
		unsigned int CreateSprite(const char* a_FileName, int a_Width, int a_Height){
			Sprite* newSprite = new Sprite;

			glGenBuffers(1, &newSprite->uiVBO);
			glGenBuffers(1, &newSprite->uiIBO);
			int textureWidth = 50, textureHeight = 50, textureBPP = 4;

			newSprite->Initialize(shaderProgram, a_Width, a_Height);
			newSprite->uiTextureID = loadTexture(a_FileName, textureWidth, textureHeight, textureBPP);
			spriteList.push_back(newSprite);

			return spriteList.size() - 1;

		}

		unsigned int CreateSprite(const char* a_FileName, int a_Width, int a_Height, vec4& a_UVCoordinates){
			Sprite* newSprite = new Sprite;

			glGenBuffers(1, &(newSprite->uiVBO));
			glGenBuffers(1, &newSprite->uiIBO);
			int textureWidth = 50, textureHeight = 50, textureBPP = 4;
			
			newSprite->Initialize(shaderProgram, a_Width, a_Height);
			newSprite->uiTextureID = loadTexture(a_FileName, textureWidth, textureHeight, textureBPP);
			newSprite->SetUVCoordinates(a_UVCoordinates);
			spriteList.push_back(newSprite);

			return spriteList.size() - 1;

		}

		void SetSpriteUVCoordinates(const uint spriteID, vec4 a_UVCoordinates){
			spriteList[spriteID]->SetUVCoordinates(a_UVCoordinates);
			UpdateVBO(spriteList[spriteID]->uiVBO, spriteList[spriteID]->verticesBuffer, 4);
			//UpdateIBO(spriteList[spriteID]->uiVBO, spriteList[spriteID]->verticesBuffer, 4);
		}

		//Move given sprite ID to x,y
		void MoveSprite(unsigned int a_SpriteID, float a_XPos, float a_YPos){
			Sprite* list = spriteList[a_SpriteID];
			
			list->SetPosition(vec4(a_XPos, a_YPos, 0, 0));
			UpdateVBO(list->uiVBO, list->verticesBuffer, 4);
			//UpdateIBO(list->uiVBO, list->verticesBuffer, 4);
		}

		//Draw the given sprite ID
		void DrawSprite(unsigned int a_SpriteID){
			////enable shaders
			glUseProgram(shaderProgram);

			//send ortho projection info to shader
			glUniformMatrix4fv(IDTexture, 1, GL_FALSE, orthographicProjection);

			//enable the vertex array states
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);


			//glEnable(GL_BLEND);
			//glEnable(GL_ALPHA_TEST);
			//glAlphaFunc(GL_GREATER, .5f);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBindTexture(GL_TEXTURE_2D, spriteList[a_SpriteID]->uiTextureID);

			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image)
			glBindBuffer(GL_ARRAY_BUFFER, spriteList[a_SpriteID]->uiVBO);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteList[a_SpriteID]->uiIBO);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)* 2));

			glEnable(GL_BLEND);

			glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(Vertex));
			//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, NULL);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_TEXTURE_2D, 0);
		}

	protected:
		GLuint IDTexture;
		std::vector<Sprite*> spriteList;

		void UpdateVBO(GLuint a_VBO, Vertex* a_VerticeBuffer, int a_size){
			//bind vbo
			glBindBuffer(GL_ARRAY_BUFFER, a_VBO);
			//allocate space for vertices on the graphics card
			//size of buffer needs to be 3 vec4 for vertices and 3 vec4 for 
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* a_size, a_VerticeBuffer, GL_STATIC_DRAW);
			//get pointer to allocated space on the graphics card
			//GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

			////copy data to graphics card
			//memcpy(vBuffer, a_VerticeBuffer, sizeof(Vertex)* sizeof(a_VerticeBuffer));
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		//void UpdateIBO(GLuint a_IBO, Vertex* a_VerticeBuffer, int a_size){
		//	//bind IBO
		//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a_IBO);
		//	//allocate space for index info on  the graphics card
		//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(a_VerticeBuffer)* a_size, a_VerticeBuffer, GL_STATIC_DRAW);
		//	//get pointer to newly allocated space on GPU
		//	GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//	//specify order to draw vertices
		//	//in this case it's in sequential order
		//	for (int i = 0; i < a_size; i++)
		//	{
		//		((char*)iBuffer)[i] = i;
		//	}
		//	//unmap and unbind 
		//	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//}

		unsigned int loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP){
			unsigned int uiTextureID = 0;
			//check file exists
			if (a_pFilename != nullptr)
			{
				//read in image data from file
				//unsigned char* pImageData = SOIL_load_image(a_pFilename, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_RGBA);

				////check for successful read
				//if (pImageData)
				//{
				//	//create opengl texture handle
				//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, a_iWidth, a_iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pImageData)

				//	//uiTextureID = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP,
				//		//SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
				//	//clear what was read in from file now that it is stored in the handle
				//	SOIL_free_image_data(pImageData);
				//}

				uiTextureID = SOIL_load_OGL_texture(a_pFilename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);

				//check for errors
				if (uiTextureID == 0)
				{
					std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
				}
				return uiTextureID;
			}
		}
	private:
		float* orthographicProjection;
		vec4 backgroundColor;

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
	};
}

#endif //_FRAMWORK_H_