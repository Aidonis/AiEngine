#include "Wander.h"
#include "NonPlayer.h"

Wander::Wander(){
	radius = 0;
	distance = 0;
	wanderAngle = 0;
	angleChange = 0;
}


glm::vec2 Wander::getForce(){

	//Create center circle based on owner velocity
	glm::vec2 circleCenter = owner->velocity;
	//normalize
	circleCenter = glm::normalize(circleCenter);
	//scale vector
	circleCenter *= distance;

	//Displacement Force
	//Vector aligned with y axies
	glm::vec2 displacement(0, -1);
	//scale vector
	displacement *= radius;
	
	//Chang current angle
	SetAngle(displacement, wanderAngle);

	//Jitter angle
	int r = (rand() % (angleChange + 1));
	int s = (angleChange * .5);

	wanderAngle += r - s;

	//Return force
	glm::vec2 force = (circleCenter + displacement) * 8.0f;
	return force;

}

void Wander::SetAngle(glm::vec2& a_vector, float a_value){
	float length = glm::length(a_vector);
	a_vector.x = cosf(a_value * RADIAN_CONVERSION) * length;
	a_vector.y = sinf(a_value * RADIAN_CONVERSION) * length;
}

glm::vec2 Wander::GetRandomCirclePoint(const float a_radius, const glm::vec2 a_pos){
	float x = radius * cosf((rand() % 360) * RADIAN_CONVERSION);
	float y = radius * sin((rand() % 360) * RADIAN_CONVERSION);
	return glm::vec2(x, y) + a_pos;
}