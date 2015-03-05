#include "player.h"

Player::Player(){

}

Player::~Player(){

}

Player::Player(unsigned int a_Sprite, glm::vec2 a_Position){
	pos = a_Position;
	spriteID = a_Sprite;
}

Player::Player(unsigned int a_Sprite, GraphNode* a_Node){
	currentNode = a_Node;
	pos = currentNode->pos;
	spriteID = a_Sprite;
}

void Player::Update(float deltaTime){
	if (pathList.size() > 0){
		goalNode = pathList.front();
		goalNode->walked = true;
		previousNode = goalNode->previousNode;
		if (currentLerpValue < 1){
			pos = glm::lerp(previousNode->pos, goalNode->pos, currentLerpValue);
			currentLerpValue += .5 * deltaTime;
			
		}
		else{
			currentLerpValue = 0;
			previousNode = goalNode;
			pathList.erase(pathList.begin());
			if (pathList.size() > 0){
				goalNode = pathList.front();
			}
			if (pathList.empty()){
				pos = goalNode->pos;
			}
		}
	}
	else
	{
		goalNode = nullptr;
	}
}