#ifndef _QUAD_TREE_H_
#define _QUAD_TREE_H_

#include "NonPlayer.h"

struct Box
{
	glm::vec2 minPoint;
	glm::vec2 maxPoint;
	glm::vec2 center;
	float width;
	float height;
	Box(){

	}
	Box(glm::vec2 a_minPoint,glm::vec2 a_maxPoint )
	{
		minPoint = a_minPoint;
		maxPoint = a_maxPoint;
		center = glm::vec2(a_maxPoint.x * .5f, a_maxPoint.y * .5f);
		width = maxPoint.x - minPoint.x;
		height = maxPoint.y - minPoint.y;
	}


};

class QuadTree{
public:

	QuadTree();
	~QuadTree();

	QuadTree(unsigned int a_level, Box a_bounds);

	const int MAX_OBJECTS = 10;
	const int MAX_LEVELS = 4;

	unsigned int m_level;
	//List of Objects
	std::vector<Box> objects;
	//Bounds of quad tree
	Box m_bounds;
	//List of nodes
	std::vector<QuadTree*> nodeList;

	void Initialize(unsigned int a_level, Box a_bounds);
	void Clear();
	void Split();
	int GetIndex(Box a_rect);
	void Insert(Box a_rect);
};

#endif //_QUAD_TREE_H_