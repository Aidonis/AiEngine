#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <GL\glew.h>
#include <GL\wglew.h>
#include <glm\glm.hpp>
#include <soil\SOIL.h>

#include <vector>

#define GLEW_STATIC

using namespace glm;

struct Vertex{
	vec4 positions;
	vec4 colors;
	vec2 uvs;
};

class Player
{

public:
	/*
	Origin - Where player is drawn from
	Points - How far from the origin
	Color - Color of the points
	UV - UV mapping of points
	Vertices - 1 Vertex contains a position/color/uv
	Pointer to an Array of Vertices - Array containing Vertices
	*/

	Player(){
		verticesBuffer = new Vertex[3];
		int width = 32, height = 32, bpp = 4;
		textureID = loadTexture(".\\assets\\dirt.png", width, height, bpp);
	}

	void Initialize(vec4& a_origin){
		origin = a_origin;
		glGenBuffers(1, &uiVBO);
		glGenBuffers(1, &uiIBO);
		loadModelVertices();
		LoadModelUVs();
		UpdateVertices();
	}

	void Draw()
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)* 2));

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

protected:
	GLuint uiVBO;
	GLuint uiIBO;
	GLuint textureID;
	Vertex* verticesBuffer;
	std::vector<vec4> modelVertices;
	std::vector<vec2> modelUVs;
	vec4 origin;

	void UpdateVBO(){
		//bind vbo
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		//allocate space for vertices on the graphics card
		//size of buffer needs to be 3 vec4 for vertices and 3 vec4 for 
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 3, NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy data to graphics card
		memcpy(vBuffer, verticesBuffer, sizeof(Vertex)* 3);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void UpdateIBO(){
		//bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
		//allocate space for index info on  the graphics card
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on GPU
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify order to draw vertices
		//in this case it's in sequential order
		for (int i = 0; i < 3; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind 
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	/*ToDo
	current vertex position = (origin of object + offset)
	*/
	void UpdateVertices(){
		verticesBuffer[0].positions = origin + modelVertices[0];//some vector or shit;
		verticesBuffer[0].colors = vec4(1, 0, 1, 1);//some color vector shit;
		verticesBuffer[0].uvs = modelUVs[0];//UV shit

		verticesBuffer[1].positions = origin + modelVertices[1];//some vector or shit;
		verticesBuffer[1].colors = vec4(1, 0, 1, 1);//some color vector shit;
		verticesBuffer[1].uvs = modelUVs[1];//UV shit

		verticesBuffer[2].positions = origin + modelVertices[2];//some vector or shit;
		verticesBuffer[2].colors = vec4(1, 0, 1, 1);//some color vector shit;
		verticesBuffer[2].uvs = modelUVs[2];//UV shit
		UpdateVBO();
		UpdateIBO();
	}

	void loadModelVertices(){
		modelVertices.push_back(vec4(0, 150.f, 0, 1));
		modelVertices.push_back(vec4(-150.0f, -10.0f, 0, 1));
		modelVertices.push_back(vec4(150.0f, -10.0f, 0, 1));
	}

	void LoadModelUVs(){
		modelUVs.push_back(glm::vec2(0.5f, 1.0f));
		modelUVs.push_back(glm::vec2(0.2f, 0.5f));
		modelUVs.push_back(glm::vec2(0.7f, 0.5f));
	}

	unsigned int loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP)
	{
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

};

#endif //_PLAYER_H_