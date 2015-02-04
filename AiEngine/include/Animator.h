#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <string>
#include <vector>
#include <map>
#include "tinyxml2\tinyxml2.h"
#include "ToolBox.h"


typedef std::vector<std::string> frame;

struct AniSprite
{
	std::string Name;
	float width, height;
	float x0, x1, y0, y1;
};
struct Atlas{
	float width, height;
	std::string sSheet;
	std::string sAnimations;
};

class Animator{
public:

	Animator();
	~Animator();

	void Update();
	void ImportSheet();

	Atlas atlas;

	void SetUVData(glm::vec2 * a_data);
	std::map<std::string, AniSprite> mSprites;
	std::map<std::string, frame> mAnimations;

	void SetSprite(std::string a_Sprite);
	void LoadSprites(const char* a_SpriteSheet);
	glm::vec2 m_UVData[2];
	glm::vec2 m_SpriteScale;

};

#endif //_ANIMATOR_H_