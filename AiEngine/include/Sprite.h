#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <vector>

#define GLEW_STATIC

using namespace glm;

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
	Sprite(){

	}
	~Sprite(){
		delete verticesBuffer;
	}

	void Initialize(GLuint& a_ShaderProgram, int a_Width, int a_Height){
		width = a_Width;
		height = a_Height;
		this->fileName = fileName;
		loadModelVertices();
		verticesBuffer = new Vertex[modelVertices.size()];
		position = vec4();
		UVCoordinates = vec4(0, 1, 1, 0);
		LoadModelUVs();
		UpdateVertices();
	}

	void SetUVCoordinates(vec4& a_UVCoordinates){
		UVCoordinates = a_UVCoordinates;
		LoadModelUVs();
		UpdateVertices();
	}

	void SetPosition(const vec4& a_position){
		position = a_position;
		UpdateVertices();
	}

	GLuint uiTextureID;
	GLuint uiVBO;
	GLuint uiIBO;
	vec4 UVCoordinates;
	Vertex* verticesBuffer;

private:
	std::vector<vec4> modelVertices;
	std::vector<vec2> modelUVs;
	vec4 position;

	int width;
	int height;
	char* fileName;

	void UpdateVertices(){
		verticesBuffer[0].Pos = position + modelVertices[0];//some vector or shit;
		verticesBuffer[0].Color = vec4(1, 1, 1, 1);//some color vector shit;
		verticesBuffer[0].UV = modelUVs[0];//UV shit

		verticesBuffer[1].Pos = position + modelVertices[1];//some vector or shit;
		verticesBuffer[1].Color = vec4(1, 1, 1, 1);//some color vector shit;
		verticesBuffer[1].UV = modelUVs[1];//UV shit

		verticesBuffer[2].Pos = position + modelVertices[2];//some vector or shit;
		verticesBuffer[2].Color = vec4(1, 1, 1, 1);//some color vector shit;
		verticesBuffer[2].UV = modelUVs[2];//UV shit

		verticesBuffer[3].Pos = position + modelVertices[3];//some vector or shit;
		verticesBuffer[3].Color = vec4(1, 1, 1, 1);//some color vector shit;
		verticesBuffer[3].UV = modelUVs[3];//UV shit

	}
	void loadModelVertices(){
		float hWidth = width * .5f;
		float hHeight = height * .5f;

		modelVertices.push_back(vec4(0, 0, 0, 1));
		modelVertices.push_back(vec4(hWidth, 0.0f, 0, 1));
		modelVertices.push_back(vec4(hWidth, hHeight, 0, 1));
		modelVertices.push_back(vec4(0, hHeight, 0, 1));
	}

	void LoadModelUVs(){
		modelUVs.clear();
		modelUVs.push_back(glm::vec2(UVCoordinates.x, UVCoordinates.y));
		modelUVs.push_back(glm::vec2(UVCoordinates.z, UVCoordinates.y));
		modelUVs.push_back(glm::vec2(UVCoordinates.z, UVCoordinates.w));
		modelUVs.push_back(glm::vec2(UVCoordinates.x, UVCoordinates.w));
	}

	void LoadModelUVs(vec4 a_UVs){
		modelUVs.push_back(glm::vec2(a_UVs.x, a_UVs.y));	//minX, maxY
		modelUVs.push_back(glm::vec2(a_UVs.z, a_UVs.y));	//maxX, maxY
		modelUVs.push_back(glm::vec2(a_UVs.z, a_UVs.w));	//maxX, minY
		modelUVs.push_back(glm::vec2(a_UVs.x, a_UVs.w));	//minX, minY
	}
};

#endif //_PLAYER_H_