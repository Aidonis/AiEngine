#ifndef _Player_H
#define _Player_H

#include <vector>
#include <list>
#include "Graph.h"
#include "glm\glm.hpp"
#include "glm/gtx/compatibility.hpp"

class Player{
public:
	Player();
	~Player();
	Player(unsigned int a_Sprite, glm::vec2 a_Position);
	Player(unsigned int a_Sprite, GraphNode* a_Node);
	void Update(float deltaTime);

	unsigned int spriteID;
	glm::vec2 pos;
	
	GraphNode* goalNode;
	GraphNode* currentNode;
	GraphNode* previousNode;

	std::vector<GraphNode*> pathList;
	
	float currentLerpValue = 0;

	
};


#endif //_Player_H