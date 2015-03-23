#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Quad.h"
#include "ToolBox.h"
#include "SOIL\SOIL.h"
#include "TextFileReader.h"
#include "Animator.h"

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
	float s_rotz;

	GLuint s_TexId;
	GLuint tex_Location;
	GLuint s_UVO;
	glm::vec2 s_UVData[4];

	Animator s_Animator;

	void Update();
	void Draw();
	void LoadTexture(const char* a_Texture);

	void SetUVData();
	void Initialize();
	void SetRotation(const float a_angle);


private:

};

#endif //_SPRITE_H_