#include "player.h"

Player::Player(){

}

Player::~Player(){

}

Player::Player(unsigned int a_Sprite, glm::vec2 a_Position){
	pos = a_Position;
	spriteID = a_Sprite;
}