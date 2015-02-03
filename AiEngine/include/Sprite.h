#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Quad.h"
#include "ToolBox.h"
#include "SOIL/SOIL.h"
#include "TextFileReader.h"

class Sprite{
public:
	Sprite();
	~Sprite();

	Quad s_Quad;
	Transform s_Transform;
	glm::vec3 s_Position;
	glm::vec3 s_Velocity;
	glm::vec3 s_Rotation;
	glm::vec2 s_Scale;

	GLuint s_TexId;
	GLuint tex_Location;
	GLuint s_UVO;
	glm::vec2 s_UVData[4];

	void Update(float a_DeltaTime);
	void Draw();
	void LoadTexture(const char* a_Texture);

	void SetUVData();

private:

};

#endif //_SPRITE_H_