#ifndef _SPRITE_H_
#define _SPRITE_H_

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

class Sprite
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

	~Sprite(){
		delete verticesBuffer;
	}

	void Initialize(GLuint& a_ShaderProgram, int width, int height){

	}

	//Player(){
	//	verticesBuffer = new Vertex[4];
	//	int width = 32, height = 32, bpp = 4;
	//	textureID = loadTexture(".\\assets\\test2.png", width, height, bpp);
	//}

	//void Initialize(vec4& a_origin){
	//	origin = a_origin;
	//	glGenBuffers(1, &uiVBO);
	//	glGenBuffers(1, &uiIBO);
	//	loadModelVertices();
	//	LoadModelUVs();
	//	UpdateVertices();
	//}

	void Initialize(GLuint& a_ShaderProgram, int a_Width, int a_Height){
		width = a_Width;
		height = a_Height;
		position = vec4(0,0,0,0);
		glGenBuffers(1, &uiVBO);
		glGenBuffers(1, &uiIBO);
		loadModelVertices();
		LoadModelUVs();
		UpdateVertices();
	}

	//unsigned int CreateSprite(const char* a_TextureName, int a_Width, int a_Height){
	//	int bpp = 4;
	//	textureID = loadTexture(a_TextureName, a_Width, a_Height, bpp);
	//	modelTextures.push_back(textureID);
	//	return modelTextures[modelTextures.size() -1];
	//	
	//}

	Vertex* verticesBuffer;

private:
	std::vector<vec4> modelVertices;
	std::vector<vec2> modelUVs;
	vec4 position;

	int width;
	int height;
	char* filename;

	void UpdateVertices(){
		verticesBuffer[0].positions = position + modelVertices[0];//some vector or shit;
		verticesBuffer[0].colors = vec4(1, 1, 1, 1);//some color vector shit;
		verticesBuffer[0].uvs = modelUVs[0];//UV shit

		verticesBuffer[1].positions = position + modelVertices[1];//some vector or shit;
		verticesBuffer[1].colors = vec4(1, 1, 1, 1);//some color vector shit;
		verticesBuffer[1].uvs = modelUVs[1];//UV shit

		verticesBuffer[2].positions = position + modelVertices[2];//some vector or shit;
		verticesBuffer[2].colors = vec4(1, 1, 1, 1);//some color vector shit;
		verticesBuffer[2].uvs = modelUVs[2];//UV shit

		verticesBuffer[3].positions = position + modelVertices[3];//some vector or shit;
		verticesBuffer[3].colors = vec4(1, 1, 1, 1);//some color vector shit;
		verticesBuffer[3].uvs = modelUVs[3];//UV shit

	}
	void loadModelVertices(int a_Width, int a_Height){
		modelVertices.push_back(vec4(0, 0, 0, 1));
		modelVertices.push_back(vec4(a_Width, 0.0f, 0, 1));
		modelVertices.push_back(vec4(a_Width, a_Height, 0, 1));
		modelVertices.push_back(vec4(0, a_Height, 0, 1));
	}

	void LoadModelUVs(){
		modelUVs.push_back(glm::vec2(0.0f, 0.0f));
		modelUVs.push_back(glm::vec2(.5f, 0.0f));
		modelUVs.push_back(glm::vec2(.5f, 1.0f));
		modelUVs.push_back(glm::vec2(0.0f, 1.0f));
	}

	void LoadModelUVs(vec4 a_UVs){
		modelUVs.push_back(glm::vec2(a_UVs.x, a_UVs.y));
		modelUVs.push_back(glm::vec2(a_UVs.z, a_UVs.y));
		modelUVs.push_back(glm::vec2(a_UVs.z, a_UVs.w));
		modelUVs.push_back(glm::vec2(a_UVs.x, a_UVs.w));
	}
};

#endif //_PLAYER_H_