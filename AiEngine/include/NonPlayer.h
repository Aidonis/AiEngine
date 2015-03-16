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
	void SetSeekTarget(glm::vec2 a_position);
	void SetFleeTarget(glm::vec2 a_position);

	//IBoid methods
	glm::vec2& GetVelocity();
	glm::vec2& GetPosition();
	float GetMaxVelocity();

private:
	SteeringManager* steering;
	glm::vec2 seekTarget;
	glm::vec2 fleeTarget;

};


#endif //_NonPlayer_H