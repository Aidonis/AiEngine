#ifndef _STEERING_MANAGER_H_
#define _STEERING_MANAGER_H_

#include "IBoid.h"
#include <vector>

#define PI 3.14159265359
#define RADIAN_CONVERSION PI / 180.0f

class Graph;
class NonPlayer;

class SteeringManager{
public:
	SteeringManager();
	~SteeringManager();

	SteeringManager(IBoid* host);

	//Vars
	glm::vec2 steering;
	IBoid* host;

	//Behavior
	void Seek(glm::vec2 a_target, float a_slowRadius);
	void Flee(glm::vec2 a_target, float a_radius);
	void Wander();
	void Avoid(Graph* a_Graph);
	void Path();
	//void Evade(IBoid& a_target);
	void Pursue(IBoid& a_target);

	//
	void Align(std::vector<NonPlayer*> a_list);
	void Cohesion(std::vector<NonPlayer*> a_list);
	void Seperation(std::vector<NonPlayer*> a_list);

	//Update
	void Update(float a_deltaTime);

	//Reset
	void Reset();

private:
	//Numbers
	const float CIRCLE_DISTANCE = 50;
	const float CIRCLE_RADIUS = 25.0f;
	const int ANGLE_CHANGE = 6.f;
	const float WANDER_FORCE_SCALE = 5.0f;

	const float COHESION_FORCE = 5.5f;
	const float REPULSION_FORCE = 5.5f;
	const float ALIGN_FORCE = 5.f;

	float NEIGHBOR_RADIUS = 120.f;

	float WANDER_ANGLE = 5.0f;


	glm::vec2 DoSeek(glm::vec2 a_target, float a_slowRadius);
	glm::vec2 DoFlee(glm::vec2 a_target, float a_radius);
	glm::vec2 DoWander();
	glm::vec2 DoAvoid(Graph* a_Graph);
	//glm::vec2 DoPath();
	//glm::vec2 DoEvade(glm::vec2& a_target, glm::vec2& a_velocity);
	//glm::vec2 DoPersue(IBoid& a_target);

	//
	glm::vec2 DoAlign(std::vector<NonPlayer*> a_target);
	glm::vec2 DoCohesion(std::vector<NonPlayer*> a_target);
	glm::vec2 DoSeperation(std::vector<NonPlayer*> a_list);

	void SetAngle(glm::vec2& a_vector, float a_value);
	void Truncate(glm::vec2& a_original, float a_max);


};

#endif //_STEERING_MANAGER_H_