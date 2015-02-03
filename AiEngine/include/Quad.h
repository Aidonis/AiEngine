#ifndef _QUAD_H_
#define _QUAD_H_

#include "GL\glew.h"
#include "GL\wglew.h"
#include "glm\gtc\type_ptr.hpp"
//glew must be included first
#include "ToolBox.h"

class Quad
{
public:
	Quad();
	~Quad();

	GLuint q_VBO; //Vertex Buffer
	GLuint q_EBO; //Element Buffer
	GLuint q_VAO; //Vertex Attrib

	GLuint q_FragmentShader;
	GLuint q_VertexShader;

	GLuint q_ShaderProgram;

	glm::mat4 q_MVP;

	void Draw();

};

#endif // !_QUAD_H_
