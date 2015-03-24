#ifndef _QUAD_TREE_H_
#define _QUAD_TREE_H_

#include "NonPlayer.h"

struct Rectangle
{
	glm::vec2 minPoint;
	glm::vec2 maxPoint;
	glm::vec2 center;
	Rectangle(){

	}
	Rectangle(glm::vec2 a_minPoint,glm::vec2 a_maxPoint )
	{
		minPoint = a_minPoint;
		maxPoint = a_maxPoint;
	}
	float width = maxPoint.x - minPoint.x;
	float height = maxPoint.y - minPoint.y;

};

class QuadTree{
public:

	QuadTree();
	~QuadTree();

	QuadTree(unsigned int a_level, Rectangle a_bounds);

	const int MAX_OBJECTS = 10;
	const int MAX_LEVELS = 4;

	unsigned int m_level;
	//List of Objects
	std::vector<NonPlayer*> objects;
	//Bounds of quad tree
	Rectangle m_bounds;
	//List of nodes
	std::vector<QuadTree> nodeList;

	void Clear();
	void Split();
	int GetIndex(Rectangle a_rect);
	void Insert(Rectangle a_rect);
};

#endif //_QUAD_TREE_H_