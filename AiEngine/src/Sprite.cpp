#include "Sprite.h"

Sprite::Sprite(){

}

void Sprite::Initialize(){

	//Load shader to string
	std::string vString = textFileReader("./src/VertexShader.glsl");
	std::string fString = textFileReader("./src/TexturedFragmentShader.glsl");

	//Convert to Char*
	const char* vs = vString.c_str();
	const char* fs = fString.c_str();

	//Compile Vert Shader
	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &vs, NULL);
	glCompileShader(VertexShader);

	//Compile Frag Shader
	GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader, 1, &fs, NULL);
	glCompileShader(FragShader);

	//Link shaders into shader program
	GLuint ShaderProgram = glCreateProgram();

	glAttachShader(ShaderProgram, FragShader);
	glAttachShader(ShaderProgram, VertexShader);

	glLinkProgram(ShaderProgram);

	s_Quad.q_ShaderProgram = ShaderProgram;
	glUseProgram(s_Quad.q_ShaderProgram);

	//Bind VAO
	glBindVertexArray(s_Quad.q_VAO);
	//GEN/BIND/BUFFER UVO
	glGenBuffers(1, &s_UVO);
	glBindBuffer(GL_ARRAY_BUFFER, s_UVO); //Ask a question about this at some point!
	glBufferData(GL_ARRAY_BUFFER, sizeof(s_UVData), s_UVData, GL_STATIC_DRAW);

	//BIND UVO
	//glBindBuffer(GL_ARRAY_BUFFER, s_UVO);// <------

	GLint texAttrib = glGetAttribLocation(s_Quad.q_ShaderProgram, "texcoord");

	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 2 * (sizeof(float)), 0);

	//Clear Buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	s_Position = glm::vec3((float)g_WIDTH / 2, (float)g_HEIGHT / 2, 1);
	s_Scale = glm::vec2(50, 50);
	s_Rotation = glm::vec3(0, 0, 1);
	s_rotz = 0.0f;
}

Sprite::~Sprite(){

}

void Sprite::SetUVData(){
	glBindBuffer(GL_ARRAY_BUFFER, s_UVO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(s_UVData), s_UVData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Update(){

	s_Transform.viewTranslate = glm::translate(glm::mat4(), s_Position);
	s_Transform.modelScale = glm::scale(glm::mat4(), glm::vec3(s_Scale, 1));
	s_Transform.viewRotateZ = glm::rotate(glm::mat4(), s_rotz, s_Rotation );
	s_Transform.MVP = Ortho * s_Transform.viewTranslate * s_Transform.modelScale * s_Transform.viewRotateZ;
	s_Quad.q_MVP = s_Transform.MVP;

	s_Animator.SetUVData(s_UVData); //<--- clear this shit out
	SetUVData(); //<--- make this work
	Draw();

}

void Sprite::Draw(){
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, .5);
	glEnable(GL_ALPHA);
	glEnable(GL_CULL_FACE); // cull face
	glCullFace(GL_BACK); // cull back face
	glFrontFace(GL_CW); // GL_CCW for counter clock-wise
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, s_TexId);
	glUniform1i(tex_Location, 0);
	s_Quad.Draw();
	//SetUVData();//<--- go away
}

void Sprite::LoadTexture(const char* a_Texture){
	s_TexId = 0;

	glGenTextures(1, &s_TexId);
	glActiveTexture(GL_TEXTURE0);

	int width, height;

	unsigned char* image = SOIL_load_image(a_Texture, &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, s_TexId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	tex_Location = glGetUniformLocation(s_Quad.q_ShaderProgram, "diffuseTexture");
}

void Sprite::SetRotation(const float a_angle){
	s_rotz = a_angle;
}