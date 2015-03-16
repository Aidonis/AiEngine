#include "NonPlayer.h"

NonPlayer::NonPlayer(){

}

NonPlayer::~NonPlayer(){

}

NonPlayer::NonPlayer(unsigned int a_sprite, glm::vec2 a_position) : Player(a_sprite, a_position){
	steering = new SteeringManager(this);
	velocity = glm::vec2(10, 10);
	maxVelocity = 5;
}

void NonPlayer::Initialize(){
	steering = new SteeringManager(this);
	velocity = glm::vec2(10, 10);
	maxVelocity = 3;
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
	if (seekTarget != glm::vec2(NULL, NULL)){
		steering->Seek(seekTarget, 10);
	}
	steering->Wander();
	steering->Update(a_deltaTime);

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

void NonPlayer::Update(float a_deltaTime, std::vector<NonPlayer*> a_list){
	if (seekTarget != glm::vec2(NULL, NULL)){
		steering->Seek(seekTarget, 10);
	}
	steering->Cohesion(a_list);
	steering->Align(a_list);
	steering->Update(a_deltaTime);

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

void NonPlayer::SetSeekTarget(glm::vec2 a_pos){
	seekTarget = a_pos;
}

void NonPlayer::SetFleeTarget(glm::vec2 a_pos){
	fleeTarget = a_pos;
}