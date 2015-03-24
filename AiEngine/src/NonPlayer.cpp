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
	velocity = glm::vec2(rand() % 10, rand() % 10);
	maxVelocity = 15;

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
	float distance = 0;
	//Path Follow
	if (pathList.size() > 0){
		goalNode = pathList.front();
		goalNode->walked = true;
		previousNode = goalNode->previousNode;

		//Seek goal node
		distance = glm::distance(pos, goalNode->pos);
		if (distance > 45.f){
			SetSeekTarget(goalNode->pos);
		}
		else{
			distance = 0;
			previousNode = goalNode;
			pathList.erase(pathList.begin());
			if (pathList.size() > 0){
				goalNode = pathList.front();
			}
			if (pathList.empty()){
				steering->Wander();
			}
		}
	}
	else{
		goalNode = nullptr;
		steering->Wander();
		SetSeekTarget(glm::vec2(NULL,NULL));
	}
}

void NonPlayer::Update(float a_deltaTime, std::vector<NonPlayer*> a_list){
	if (seekTarget != glm::vec2(NULL, NULL)){
		steering->Seek(seekTarget, 10);
	}
	//steering->Wander();
	//if (fleeTarget != glm::vec2(NULL, NULL)){
	//	steering->Flee(fleeTarget, 120.f);
	//}
	steering->Avoid(collisionGraph);
	steering->Cohesion(a_list);
	steering->Align(a_list);
	steering->Seperation(a_list);

	rotateAngle = atan2f(velocity.y, velocity.x);
	rotateAngle -= PI / 2;

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

void NonPlayer::SetGraph(Graph* a_Graph){
	collisionGraph = a_Graph;
}