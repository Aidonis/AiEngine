#include "SteeringManager.h"
#include "NonPlayer.h"
#include "Graph.h"

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
	
	//Diagonal 
	//if (velocity.x > 0 && velocity.y > 0){
	//	velocity.x = velocity.y;
	//	
	//}
	//if (velocity.x < 0 && velocity.y > 0){
	//	velocity.x = -velocity.y;
	//	
	//}
	//if (velocity.x > 0 && velocity.y < 0){
	//	velocity.y = -velocity.x;
	//	
	//}
	//if (velocity.x < 0 && velocity.y < 0){
	//	velocity.x = velocity.y;
	//}
	position += host->GetVelocity() * a_deltaTime;
}

//External Behavior
void SteeringManager::Seek(glm::vec2 a_target, float a_slowRadius){
	steering += DoSeek(a_target, a_slowRadius);
}

void SteeringManager::Flee(glm::vec2 a_target, float a_radius){
	steering += DoFlee(a_target, a_radius);
}

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

void SteeringManager::Avoid(Graph* a_Graph){
	steering += DoAvoid(a_Graph);
}

//void SteeringManager::Evade(IBoid& a_target){
//	steering += DoEvade(a_target.GetPosition(), a_target.GetVelocity());
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

glm::vec2 SteeringManager::DoFlee(glm::vec2 a_target, float a_radius){
	float distance = glm::distance(host->GetPosition(), a_target);
	if (distance > 125.f){
		return glm::vec2();
	}
	return (-DoSeek(a_target, 200)*5.f);
}

glm::vec2 SteeringManager::DoWander(){
	glm::vec2 circleCenter = host->GetVelocity();

	//normalize into vector
	circleCenter = glm::normalize(circleCenter);
	//scale vector
	circleCenter *= CIRCLE_DISTANCE;

	//jitter
	glm::vec2 jitter(0, -1);
	//scale by circle
	jitter *= CIRCLE_RADIUS;

	//random change to vector direction
	SetAngle(jitter, WANDER_ANGLE);

	int r = (rand() % (ANGLE_CHANGE + 1));
	int s = (int)(ANGLE_CHANGE * .5f);
	WANDER_ANGLE += r - s;
	//return
	glm::vec2 force = (circleCenter + jitter) * WANDER_FORCE_SCALE;
	return force *.25f;
}

glm::vec2 SteeringManager::DoAlign(std::vector<NonPlayer*> a_list){
	unsigned int neighborCount = 0;
	glm::vec2 force;
	for (int i = 0; i < a_list.size(); i++){
		if (a_list[i] != host){
			float distance = glm::distance(host->GetPosition(), a_list[i]->GetPosition());
			if (distance < NEIGHBOR_RADIUS){
				force += a_list[i]->velocity;
				neighborCount++;
			}
			//
			if (neighborCount < 3){
				return glm::vec2();
			}
			force /= neighborCount;
			force -= host->GetVelocity();

			float desiredMag = glm::length(force);

			if (desiredMag < 0.000001f && desiredMag > -0.0000001f){
				return glm::vec2();
			}

			force /= desiredMag;
			force *= ALIGN_FORCE;
		}

	}
	
	return force;
}

glm::vec2 SteeringManager::DoCohesion(std::vector<NonPlayer*> a_list){
	unsigned int neighborCount = 0;
	glm::vec2 medianPos;
	for (int i = 0; i < a_list.size(); i++){
		if (a_list[i] != host){
			float distance = glm::distance(host->GetPosition(), a_list[i]->GetPosition());
			if (distance > NEIGHBOR_RADIUS * .5f && distance < NEIGHBOR_RADIUS){
				medianPos += a_list[i]->GetPosition();
				neighborCount++;
			}
			///
			if (neighborCount < 0.000001f && neighborCount > -0.0000001f){
				return glm::vec2();
			}

			medianPos /= (float)neighborCount;
			medianPos -= host->GetPosition();

			float magnitude = glm::length(medianPos);

			if (magnitude< 0.000001f && magnitude > -0.0000001f){
				return glm::vec2();
			}

			medianPos /= magnitude;
			medianPos *= COHESION_FORCE;
			//glm::normalize(medianPos);
		}

	}
	return medianPos;
	//return glm::normalize(medianPos - host->GetPosition()) / (glm::length(medianPos - host->GetPosition()) * COHESION_FORCE);
}

glm::vec2 SteeringManager::DoSeperation(std::vector<NonPlayer*> a_list){
	unsigned int neighborCount = 0;
	glm::vec2 velocity;
	for (int i = 0; i < a_list.size(); i++){
		if (a_list[i] != host){
			glm::vec2 currentRepulsion = (a_list[i]->GetPosition() - host->GetPosition());
			float distance = glm::distance(host->GetPosition(), a_list[i]->GetPosition());
			if (distance < NEIGHBOR_RADIUS /2 ){
				neighborCount++;
				//velocity += glm::normalize(distance) / (distance * REPULSION_FORCE);
				velocity += currentRepulsion;
			}
		}
		///
		//float magnitude = glm::length(velocity);
		float magnitude = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));

		if (magnitude < 0.0000001 && magnitude > -0.0000001){
			return glm::vec2(0, 0);
		}

		velocity /= magnitude;
		velocity *= REPULSION_FORCE;
	}
	return velocity;
}

//glm::vec2 SteeringManager::DoPath(){
//
//}

glm::vec2 SteeringManager::DoAvoid(Graph* a_Graph){
	float distance;
	for (NodeList::iterator i = a_Graph->nodes.begin(); i != a_Graph->nodes.end(); i++){
		if ((*i)->walkable != true){
			distance = glm::distance(host->GetPosition(), (*i)->pos);
			if (distance < 64.f){
				return (-DoSeek((*i)->pos, 200)*15.f);
			}
		}
	}
	return glm::vec2(NULL,NULL);
}
//glm::vec2 SteeringManager::DoEvade(glm::vec2& a_target, glm::vec2& a_velocity){
//	glm::vec2 future = a_target + a_velocity;
//	return DoFlee(future);
//}

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