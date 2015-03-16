#ifndef _NonPlayer_H
#define _NonPlayer_H

#include <map>
#include "SteeringManager.h"
#include "IBoid.h"
#include "player.h"
#include "SteeringBehaviour.h"

class NonPlayer : 
	public Player,
	public IBoid
{
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
	void SetSeekTarget(glm::vec2 a_position);
	void SetFleeTarget(NonPlayer* a_target);
	void SetWander();

	//IBoid methods
	glm::vec2& GetVelocity();
	glm::vec2& GetPosition();
	float GetMaxVelocity();

private:
	std::map<STEERING_BEHAVIOUR_TYPE, SteeringBehaviour*> SteeringBehaviourList;
	SteeringManager* steering;
	glm::vec2 seekTarget;

};


#endif //_NonPlayer_H