#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#include "GL\glew.h"
#include "GL\wglew.h"

//glew must be included first
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include <soil\SOIL.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

typedef GLuint uint;

using namespace glm;

namespace AIF{
	class Framework{
	public:

		GLFWwindow* windowHandle;
		GLuint programFlat;
		GLuint programTexture;

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

			//create shader program
			programFlat = CreateProgram(".\\src\\VertexShader.glsl", ".\\src\\FlatFragmentShader.glsl");

			//create textured shader program
			programTexture = CreateProgram(".\\src\\VertexShader.glsl", ".\\src\\TexturedFragmentShader.glsl");

			verticesBuffer = new Vertex[4];

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

		GLuint CreateProgram(const char* a_vertex, const char* a_frag){
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

		unsigned int CreateSprite(const char* a_TextureName, int a_Width, int a_Height){
			int height = 32, width = 32, bpp = 4;
			textureID = loadTexture(a_TextureName, width, height, bpp);
			origin = vec4(0, 0, 0, 0);
			glGenBuffers(1, &uiVBO);
			glGenBuffers(1, &uiIBO);
			loadModelVertices(a_Width, a_Height);
			LoadModelUVs();
			modelTextures.push_back(textureID);
			return modelTextures[modelTextures.size() - 1];
		}

		void MoveSprite(unsigned int a_textureID, float a_XPos, float a_YPos){
			origin = vec4(a_XPos, a_YPos, 0, 0);
			UpdateVertices();
		}

		void DrawSprite(unsigned int a_textureID){
				glBindTexture(GL_TEXTURE_2D, textureID);
				glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);

				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)* 2));

				glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, NULL);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	protected:
		struct Vertex{
			vec4 positions;
			vec4 colors;
			vec2 uvs;
		};
		GLuint uiVBO;
		GLuint uiIBO;
		GLuint textureID;
		Vertex* verticesBuffer;
		std::vector<vec4> modelVertices;
		std::vector<vec2> modelUVs;
		std::vector<unsigned int> modelTextures;
		vec4 origin;

		void UpdateVBO(){
			//bind vbo
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			//allocate space for vertices on the graphics card
			//size of buffer needs to be 3 vec4 for vertices and 3 vec4 for 
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* sizeof(verticesBuffer), NULL, GL_STATIC_DRAW);
			//get pointer to allocated space on the graphics card
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

			//copy data to graphics card
			memcpy(vBuffer, verticesBuffer, sizeof(Vertex)* sizeof(verticesBuffer));
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void UpdateIBO(){
			//bind IBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
			//allocate space for index info on  the graphics card
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verticesBuffer)* sizeof(char), NULL, GL_STATIC_DRAW);
			//get pointer to newly allocated space on GPU
			GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
			//specify order to draw vertices
			//in this case it's in sequential order
			for (int i = 0; i < sizeof(verticesBuffer); i++)
			{
				((char*)iBuffer)[i] = i;
			}
			//unmap and unbind 
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		}

		void UpdateVertices(){
			verticesBuffer[0].positions = origin + modelVertices[0];//some vector or shit;
			verticesBuffer[0].colors = vec4(1, 1, 1, 1);//some color vector shit;
			verticesBuffer[0].uvs = modelUVs[0];//UV shit

			verticesBuffer[1].positions = origin + modelVertices[1];//some vector or shit;
			verticesBuffer[1].colors = vec4(1, 1, 1, 1);//some color vector shit;
			verticesBuffer[1].uvs = modelUVs[1];//UV shit

			verticesBuffer[2].positions = origin + modelVertices[2];//some vector or shit;
			verticesBuffer[2].colors = vec4(1, 1, 1, 1);//some color vector shit;
			verticesBuffer[2].uvs = modelUVs[2];//UV shit

			verticesBuffer[3].positions = origin + modelVertices[3];//some vector or shit;
			verticesBuffer[3].colors = vec4(1, 1, 1, 1);//some color vector shit;
			verticesBuffer[3].uvs = modelUVs[3];//UV shit

			UpdateVBO();
			UpdateIBO();
		}

		void loadModelVertices(int a_Width, int a_Height){
		modelVertices.push_back(vec4(0, a_Height, 0, 1));
		modelVertices.push_back(vec4(a_Width, a_Height, 0, 1));
		modelVertices.push_back(vec4(a_Width, 0.0f, 0, 1));
		modelVertices.push_back(vec4(0, 0, 0, 1));
		}

		void LoadModelUVs(){
		modelUVs.push_back(glm::vec2(0.0f, 1.0f));
		modelUVs.push_back(glm::vec2(1.0f, 1.0f));
		modelUVs.push_back(glm::vec2(1.0f, 0.0f));
		modelUVs.push_back(glm::vec2(0.0f, 0.0f));
		}

		unsigned int loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP){
			unsigned int uiTextureID = 0;
			//check file exists
			if (a_pFilename != nullptr)
			{
				//read in image data from file
				unsigned char* pImageData = SOIL_load_image(a_pFilename, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_AUTO);

				//check for successful read
				if (pImageData)
				{
					//create opengl texture handle
					uiTextureID = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP,
						SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
					//clear what was read in from file now that it is stored in the handle
					SOIL_free_image_data(pImageData);
				}

				//check for errors
				if (uiTextureID == 0)
				{
					std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
				}
				return uiTextureID;
			}
		}
	private:
		
	};
}

#endif //_FRAMWORK_H_