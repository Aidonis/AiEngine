#ifndef _NonPlayer_H
#define _NonPlayer_H

#include "SteeringManager.h"
#include "IBoid.h"
#include "player.h"

class NonPlayer : 
	public Player,
	public IBoid
{
public:

	NonPlayer();
	~NonPlayer();

	NonPlayer(unsigned int a_SpriteID, glm::vec2 a_position);
	void Initialize();
	void Update(float a_deltaTime);
	void Update(float a_deltaTime, std::vector<NonPlayer*> a_list);

	void SetSeekTarget(glm::vec2 a_position);
	void SetFleeTarget(glm::vec2 a_position);
	void SetGraph(Graph* a_graph);
	
	glm::vec2 velocity;
	float magnitude;
	float maxVelocity;
	float rotateAngle;


	//IBoid methods
	glm::vec2& GetVelocity();
	glm::vec2& GetPosition();
	float GetMaxVelocity();
	float& GetHeight();
	float& GetWidth();

	//alignment

private:
	SteeringManager* steering;
	glm::vec2 seekTarget;
	glm::vec2 fleeTarget;
	Graph* collisionGraph;



};


#endif //_NonPlayer_H