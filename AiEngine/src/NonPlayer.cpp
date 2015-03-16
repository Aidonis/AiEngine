#include "NonPlayer.h"
#include "Seek.h"
#include "Flee.h"
#include "Wander.h"

NonPlayer::NonPlayer(){

}

NonPlayer::~NonPlayer(){
	for (auto behaviour : SteeringBehaviourList)
	{
		delete behaviour.second;
	}
	SteeringBehaviourList.clear();
}

NonPlayer::NonPlayer(unsigned int a_sprite, glm::vec2 a_position) : Player(a_sprite, a_position){
	steering = new SteeringManager(this);
	velocity = glm::vec2(10, 10);
	maxVelocity = 2;
	behaviour = nullptr;
	//LoadSteering();
	

}

//IBoiD
glm::vec2& NonPlayer::GetVelocity(){
	return velocity;
}
glm::vec2& NonPlayer::GetPosition(){
	return pos;
}
float NonPlayer::GetMaxVelocity(){
	return maxVelocity;
}



void NonPlayer::Update(float a_deltaTime){
	//Seek* seek = nullptr;
	//Flee* flee = nullptr;
	//Wander* wander = nullptr;

	//seek = dynamic_cast<Seek*>(SteeringBehaviourList[SEEK]);
	//flee = dynamic_cast<Flee*>(SteeringBehaviourList[FLEE]);
	//wander = dynamic_cast<Wander*>(SteeringBehaviourList[WANDER]);

	//if (seek->target != NULL){
	//	velocity += seek->getForce() * a_deltaTime;
	//	magnitude = glm::length(velocity);
	//	velocity = glm::normalize(velocity) * glm::min(magnitude, maxVelocity);
	//	pos += (velocity + 1.f) * a_deltaTime;
	//}
	//if (flee->target != NULL){
	//	velocity += flee->getForce() * a_deltaTime;
	//	magnitude = glm::length(velocity);
	//	velocity = glm::normalize(velocity) * glm::min(magnitude, maxVelocity);
	//	pos += (velocity)* a_deltaTime;
	//}
	//if (wander != nullptr){
	//	velocity += wander->getForce() * a_deltaTime;
	//	magnitude = glm::length(velocity);
	//	velocity = glm::normalize(velocity) * glm::min(magnitude, maxVelocity);
	//	pos += (velocity + 3.5f) * a_deltaTime;
	//}


	//steering->Wander();
	//steering->Wander();
	steering->Seek(seekTarget, 10);
	steering->Update();

	if (pos.x > 640){
		pos.x -= 640;
	}
	if (pos.x < 0){
		pos.x += 640;
	}
	if (pos.y > 640){
		pos.y -= 640;
	}
	if (pos.y < 0){
		pos.y += 640;
	}
}

void NonPlayer::LoadSteering(){
	Seek* s = new Seek;
	s->owner = this;
	SteeringBehaviourList[SEEK] = s;

	Flee* f = new Flee;
	f->owner = this;
	SteeringBehaviourList[FLEE] = f;

	Wander* w = new Wander;
	w->owner = this;
	SteeringBehaviourList[WANDER] = w;
}

void NonPlayer::SetSeekTarget(NonPlayer* a_target){
	dynamic_cast<Seek*>(SteeringBehaviourList[SEEK])->target = a_target;
}

void NonPlayer::SetSeekTarget(glm::vec2 a_pos){
	seekTarget = a_pos;
}

void NonPlayer::SetFleeTarget(NonPlayer* a_target){
	dynamic_cast<Flee*>(SteeringBehaviourList[FLEE])->target = a_target;
}

void NonPlayer::SetWander(){
	Wander* w = dynamic_cast<Wander*>(SteeringBehaviourList[WANDER]);
	w->angleChange = 10;
	w->radius = 25;
	w->distance = 30;
}