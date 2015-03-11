#include "Flee.h"
#include "NonPlayer.h"

glm::vec2 Flee::getForce(){
	glm::vec2 force;
	force = glm::vec2(2,1);
	force += glm::normalize(owner->pos - target->pos);
	force *= owner->maxVelocity;
	return force - owner->velocity;
}