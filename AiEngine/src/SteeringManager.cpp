#include "SteeringManager.h"

SteeringManager::SteeringManager(){
}

SteeringManager::~SteeringManager(){
}

SteeringManager::SteeringManager(IBoid* a_host)
{
	host = a_host;
	steering = glm::vec2(0, 0);
}

void SteeringManager::Update(){
	glm::vec2& velocity = host->GetVelocity();
	glm::vec2& position = host->GetPosition();

	Truncate(steering, host->GetMaxVelocity());
	velocity += steering;
	Truncate(velocity, host->GetMaxVelocity());
	position += host->GetVelocity();
}

//External Behavior
void SteeringManager::Seek(glm::vec2 a_target, float a_slowRadius){
	steering += DoSeek(a_target, a_slowRadius);
}

//void SteeringManager::Flee(glm::vec2 a_target){
//	steering += DoFlee(a_target);
//}

void SteeringManager::Wander(){
	steering += DoWander();
}

//Internal Behavior
glm::vec2 SteeringManager::DoSeek(glm::vec2 a_target, float a_slowRadius){
	glm::vec2 force = glm::vec2(0,0);
	float distance = 0.0f;

	glm::vec2 desired = a_target - host->GetPosition();
	distance = glm::length(desired);
	glm::normalize(desired);

	if (distance <= a_slowRadius){
		desired *= host->GetMaxVelocity() * distance / a_slowRadius;
	}
	else{
		desired *= host->GetMaxVelocity();
	}

	force = desired - host->GetVelocity();
	return force;
}
//
//glm::vec2 SteeringManager::DoFlee(glm::vec2 a_target){
//
//}

glm::vec2 SteeringManager::DoWander(){
	glm::vec2 circleCenter = host->GetVelocity();

	if (circleCenter == glm::vec2(0, 0)){
		float x = (rand() % 11) - 5.0f;
		float y = (rand() % 11) - 5.0f;
		circleCenter = glm::normalize(glm::vec2(x, y)) * host->GetMaxVelocity();
	}

	//normalize into vector
	circleCenter = glm::normalize(circleCenter);
	//scale vector
	circleCenter *= CIRCLE_DISTANCE;

	//jitter
	glm::vec2 jitter(0, -1);
	//scale by circle
	jitter *= CIRCLE_RADIUS;

	//random change to vector direction
	SetAngle(jitter, (float)wanderAngle);

	int r = (rand() % (ANGLE_CHANGE + 1));
	int s = (int)(ANGLE_CHANGE * .5f);
	wanderAngle += r - s;
	//return
	glm::vec2 force = (circleCenter + jitter) * WANDER_FORCE_SCALE;
	return force;

}

void SteeringManager::SetAngle(glm::vec2& a_vector, float a_value){
	float length = glm::length(a_vector);
	a_vector.x = cosf(a_value * RADIAN_CONVERSION) * length;
	a_vector.y = sinf(a_value * RADIAN_CONVERSION) * length;
}

void SteeringManager::Truncate(glm::vec2& a_original, float a_max)
{
	if (glm::length(a_original) > a_max)
	{
		a_original = glm::normalize(a_original);
		a_original *= a_max;
	}
}