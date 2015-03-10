#include "NonPlayer.h"
#include "Seek.h"
#include "Flee.h"

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
	velocity = glm::vec2(20, 20);
	maxVelocity = 6;
	behaviour = nullptr;
	LoadSteering();

}

void NonPlayer::Update(float a_deltaTime){
	Seek* seek = nullptr;
	Flee* flee = nullptr;

	seek = dynamic_cast<Seek*>(SteeringBehaviourList[SEEK]);
	flee = dynamic_cast<Flee*>(SteeringBehaviourList[FLEE]);

	if (seek->target != NULL){
		velocity += seek->getForce() * a_deltaTime;
		magnitude = glm::length(velocity);
		velocity = glm::normalize(velocity) * glm::min(magnitude, maxVelocity);
		pos += (velocity + .5f) * a_deltaTime;
	}
	if (flee->target != NULL){
		velocity += flee->getForce() * a_deltaTime;
		magnitude = glm::length(velocity);
		velocity = glm::normalize(velocity) * glm::min(magnitude, maxVelocity);
		pos += velocity * a_deltaTime;
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
}

void NonPlayer::LoadSteering(){
	Seek* s = new Seek;
	s->owner = this;
	SteeringBehaviourList[SEEK] = s;

	Flee* f = new Flee;
	f->owner = this;
	SteeringBehaviourList[FLEE] = f;
}

void NonPlayer::SetSeekTarget(NonPlayer* a_target){
	dynamic_cast<Seek*>(SteeringBehaviourList[SEEK])->target = a_target;
}

void NonPlayer::SetFleeTarget(NonPlayer* a_target){
	dynamic_cast<Flee*>(SteeringBehaviourList[FLEE])->target = a_target;
}