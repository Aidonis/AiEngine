#ifndef _FONT_H_
#define _FONT_H_

#include "tinyxml2\tinyxml2.h"
#include "Sprite.h"
#include "ToolBox.h"
#include <vector>

struct Char{
	std::string Name;
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
	void LoadFont(const char* a_FontSheet);
	void DrawString();

private:

	Fontbox();
	~Fontbox();

	Sprite text;
	Font fontAtlas;
	std::map<char, Char> charMap;
	std::vector<Char> Drawlist;
	int CharCount;
	glm::vec2 f_uvScale;
};


#endif //_FONT_H_