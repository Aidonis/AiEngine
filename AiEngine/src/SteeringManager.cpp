#include "SteeringManager.h"
#include "NonPlayer.h"

SteeringManager::SteeringManager(){
}

SteeringManager::~SteeringManager(){
}

SteeringManager::SteeringManager(IBoid* a_host)
{
	host = a_host;
	steering = glm::vec2(0, 0);
}

void SteeringManager::Update(float a_deltaTime){
	glm::vec2& velocity = host->GetVelocity();
	glm::vec2& position = host->GetPosition();

	Truncate(steering, host->GetMaxVelocity());
	velocity += steering * a_deltaTime;
	Truncate(velocity, host->GetMaxVelocity());
	position += host->GetVelocity() * a_deltaTime;
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

void SteeringManager::Align(std::vector<NonPlayer*> a_list){
	steering += DoAlign(a_list);
}

void SteeringManager::Cohesion(std::vector<NonPlayer*> a_list){
	steering += DoCohesion(a_list);
}
void SteeringManager::Seperation(std::vector<NonPlayer*> a_list){
	steering += DoSeperation(a_list);
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

glm::vec2 SteeringManager::DoAlign(std::vector<NonPlayer*> a_list){
	unsigned int neighborCount = 0;
	glm::vec2 force;
	for (int i = 0; i < a_list.size(); i++){
		if (a_list[i] != host){
			float distance = glm::length(host->GetPosition() - a_list[i]->GetPosition());
			if (distance <= neighborRadius){
				force += a_list[i]->velocity;
				neighborCount++;
			}
		}
	}
	if (neighborCount == 0){
		return DoWander();
	}
	force = force / (float)neighborCount;
	return force - host->GetVelocity();
}

glm::vec2 SteeringManager::DoCohesion(std::vector<NonPlayer*> a_list){
	unsigned int neighborCount = 0;
	float cohesionForce = 5.f;
	glm::vec2 force;
	glm::vec2 medianPos;
	for (int i = 0; i < a_list.size(); i++){
		if (a_list[i] != host){
			float distance = glm::length(host->GetPosition() - a_list[i]->GetPosition());
			if (distance <= neighborRadius){
				medianPos += a_list[i]->GetPosition();
				neighborCount++;
			}
		}
	}
	if (neighborCount == 0){
		return DoWander();
	}
	medianPos /= (float)neighborCount;
	return glm::normalize(medianPos - host->GetPosition()) / (glm::length(medianPos - host->GetPosition()) * cohesionForce);
}

glm::vec2 SteeringManager::DoSeperation(std::vector<NonPlayer*> a_list){
	unsigned int neighborCount = 0;
	float repulsion = 6.f;
	glm::vec2 velocity;
	for (int i = 0; i < a_list.size(); i++){
		if (a_list[i] != host){
			glm::vec2 direction = host->GetPosition() - a_list[i]->GetPosition();
			float distance = glm::length(direction);
			if (distance <= neighborRadius){
				neighborCount++;
				velocity += glm::normalize(direction) / (distance * repulsion);
			}
		}
	}
	if (neighborCount == 0){
		return DoWander();
	}
	velocity = velocity / (float)neighborCount;
	return velocity;
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