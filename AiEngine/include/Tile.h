#ifndef _TILE_H_
#define _TILE_H_

#include "Framework.h"

class Tile{
public:
	glm::vec2 pos;
	unsigned int spriteID;
	char* spriteName;


	void Draw();
};


#endif //_TILE_H_
