#ifndef _STEERING_MANAGER_H_
#define _STEERING_MANAGER_H_

#include "IBoid.h"

class SteeringManager{
	SteeringManager();
	~SteeringManager();

	//Vars
	glm::vec2 steering;
	IBoid* host;

	//Behavior
	void Seek(glm::vec2 a_target, float a_slowRadius);
	void Flee(glm::vec2 a_target);
	void Wander();
	void Evade(IBoid& a_target);
	void Pursue(IBoid& a_target);

	//Update
	void Update();

	//Reset
	void Reset();

private:
	//Numbers
	const float CIRCLE_DISTANCE = 50;
	const float CIRCLE_RADIUS = 100;
	const int ANGLE_CHANGE = 10;
	const float WANDER_FORCE_SCALE = 8.0f;

	glm::vec2 DoSeek(glm::vec2 a_target, float a_slowRadius);
	//glm::vec2 DoFlee(glm::vec2 a_target);
	//glm::vec2 DoWander();
	//glm::vec2 DoEvade(IBoid& a_target);
	//glm::vec2 DoPersue(IBoid& a_target);


};

#endif //_STEERING_MANAGER_H_