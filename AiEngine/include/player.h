#ifndef _Player_H
#define _Player_H

#include <vector>
#include <list>
#include "Graph.h"
#include "glm\glm.hpp"
class Player{
public:
	Player();
	~Player();
	Player(unsigned int a_Sprite, glm::vec2 a_Position);

	unsigned int spriteID;
	
	glm::vec2 pos;
	std::vector<GraphNode*> pathList;
	
	float currentLerpValue = 0;

	
};


#endif //_Player_H