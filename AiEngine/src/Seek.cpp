#include "Seek.h"
#include "NonPlayer.h"

glm::vec2 Seek::getForce(){
	glm::vec2 force;
	force = glm::normalize(target->pos - owner->pos);
	force *= owner->maxVelocity;
	return force - owner->velocity;
}