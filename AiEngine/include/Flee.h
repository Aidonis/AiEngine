#ifndef _FLEE_H_
#define _FLEE_H_

#include "SteeringBehaviour.h"

class Flee : public SteeringBehaviour {
public:
	NonPlayer* target;

	glm::vec2 getForce();
};

#endif //_SEEK_H_