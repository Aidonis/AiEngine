#ifndef _WANDER_H_
#define _WANDER_H_

#include "SteeringBehaviour.h"

class Wander : public SteeringBehaviour{
public:
	Wander();

	NonPlayer* target;

	glm::vec2 getForce();
	
	float distance;
	float radius;
	int wanderAngle;
	int angleChange;

private:
	glm::vec2 GetRandomCirclePoint(const float a_radius, const glm::vec2 a_pos);
	void SetAngle(glm::vec2& a_vector, float a_value);
};


#endif //_WANDER_H_