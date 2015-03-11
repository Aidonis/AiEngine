#include "SteeringManager.h"

SteeringManager::SteeringManager(){
}

SteeringManager::~SteeringManager(){
}

void SteeringManager::Update(){
	glm::vec2 velocity = host->GetVelocity();
	glm::vec2 position = host->GetPosition();

	velocity += steering;

	position += velocity;
}

//External Behavior
void SteeringManager::Seek(glm::vec2 a_target, float a_slowRadius){
	steering += DoSeek(a_target, a_slowRadius);
}

//void SteeringManager::Flee(glm::vec2 a_target){
//	steering += DoFlee(a_target);
//}

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