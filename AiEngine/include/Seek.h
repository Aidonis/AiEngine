#ifndef _SEEK_H_
#define _SEEK_H_

#include "SteeringBehaviour.h"

class Seek : public SteeringBehaviour {
public:
	NonPlayer* target;

	glm::vec2 getForce();
};

#endif //_SEEK_H_