#ifndef _FONT_H_
#define _FONT_H_

#include "tinyxml2\tinyxml2.h"
#include "Sprite.h"
#include "ToolBox.h"
#include <vector>

struct Char{
	std::string id;
	float width, height;
	float x0, x1, y0, y1;
	float offset;
};

struct Font{
	glm::vec2 v2Size;
	std::string sSheet;
	float kerning;
};

class Fontbox{
public:
	static Fontbox& Instance();

	void LoadFont(const char* a_FontSheet);
	void DrawString(std::string, glm::vec2 pos, float scale);

private:

	Fontbox();
	~Fontbox();
	void LoadStr(std::string str);

	Sprite text;
	Font fontAtlas;
	std::map<char, Char> charMap;
	std::vector<Char> Drawlist;
	int CharCount;
	glm::vec2 f_uvScale;

	GLuint PositionBuffer;
	GLuint ColorBuffer;
	GLuint UVBuffer;
	GLuint MatrixBuffer;

	static Fontbox* MInstance;
};


#endif //_FONT_H_