#ifndef _NonPlayer_H
#define _NonPlayer_H

#include <map>

#include "player.h"
#include "SteeringBehaviour.h"

class NonPlayer : public Player {
public:

	NonPlayer();
	NonPlayer(unsigned int a_SpriteID, glm::vec2 a_position);
	~NonPlayer();

	glm::vec2 velocity;
	float magnitude;
	float maxVelocity;
	SteeringBehaviour* behaviour;

	void Update(float a_deltaTime);
	void LoadSteering();
	void SetSeekTarget(NonPlayer* a_target);
	void SetFleeTarget(NonPlayer* a_target);

private:
	std::map<STEERING_BEHAVIOUR_TYPE, SteeringBehaviour*> SteeringBehaviourList;

};


#endif //_NonPlayer_H