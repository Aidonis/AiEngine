#include "QuadTree.h"


QuadTree::QuadTree(){

}

QuadTree::~QuadTree(){

}

QuadTree::QuadTree(unsigned int a_level, Box a_bounds){
	m_level = a_level;
	m_bounds = a_bounds;
	
	//objects = a_nonPlayerList;

}

void QuadTree::Initialize(unsigned int a_level, Box a_bounds){
	m_level = a_level;
	m_bounds = a_bounds;
}

void QuadTree::Clear(){
	objects.clear();

	for (int i = 0; i < nodeList.size(); i++){
		nodeList[i]->Clear();
	}
}

void QuadTree::Split(){
	float subWidth = (m_bounds.width * .5f);
	float subHeight = (m_bounds.height * .5f);
	float x = m_bounds.center.x;
	float y = m_bounds.center.y;

	for (int i = 0; i < 4; i++){
		QuadTree* node = new QuadTree();
		nodeList.push_back(node);
	}
	nodeList[0]->Initialize(m_level + 1, Box(glm::vec2(x + subWidth, y), glm::vec2(subWidth, subHeight)));
	nodeList[1]->Initialize(m_level + 1, Box(glm::vec2(x, y), glm::vec2(subWidth, subHeight)));
	nodeList[2]->Initialize(m_level + 1, Box(glm::vec2(x, y + subHeight), glm::vec2(subWidth, subHeight)));
	nodeList[3]->Initialize(m_level + 1, Box(glm::vec2(x + subWidth, y + subHeight), glm::vec2(subWidth, subHeight)));
}

//Determine which node the object belongs to.
//-1 means cannot fit within child node but part of parent node
int QuadTree::GetIndex(Box a_rect){
	int index = -1;
	float verticalMid = m_bounds.center.x + (m_bounds.width * 0.5f);
	float horizantalMid = m_bounds.center.y + (m_bounds.height * 0.5f);

	//Can fit in top quad
	bool topQuad = (a_rect.center.y < horizantalMid && a_rect.height < horizantalMid);
	//Can fit in bottom quad
	bool botQuad = (a_rect.center.y > horizantalMid);
	//Can fit in left quad
	if (a_rect.center.x < verticalMid && a_rect.center.x + a_rect.width < verticalMid){
		if (topQuad){
			index = 1;
		}
		else if (botQuad){
			index = 2;
		}
	}
	else if (a_rect.center.x > verticalMid){
		if (topQuad){
			index = 0;
		}
		else if (botQuad){
			index = 3;
		}
	}
	return index;
}

//Insert obect into the quad tree
//If it exceeds capacity
//split and add all objects to proper nodes
void QuadTree::Insert(Box a_rect){
	for (int i = 0; i < nodeList.size(); i++){
		if (nodeList[0] != NULL){

			int index = GetIndex(a_rect);

			if (index != -1){
				nodeList[index]->Insert(a_rect);
				return;
			}
		}

		objects.push_back(a_rect);

		if (objects.size() > MAX_OBJECTS && m_level < MAX_LEVELS){
			Split();
			int i = 0;
			while (i < objects.size()){
				int index = GetIndex(objects[i]);
				if (index != -1){
					nodeList[index]->Insert(objects[i]);
					objects.erase(objects.begin() + i);
				}
				else{
					i++;
				}
			}
		}
	}
}