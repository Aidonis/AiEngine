#ifndef _SteeringBehaviour_H_
#define _SteeringBehaviour_H_

#include "glm\glm.hpp"

class NonPlayer;

enum STEERING_BEHAVIOUR_TYPE
{
	FLEE,
	SEEK,
	WANDER,
	PURSUE,
	EVADE
};

class SteeringBehaviour{
public:
	NonPlayer* owner = nullptr;

	virtual glm::vec2 getForce() = 0;

};

#endif _SteeringBehaviour_H_