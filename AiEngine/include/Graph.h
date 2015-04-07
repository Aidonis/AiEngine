#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include "glm\glm.hpp"


struct Edge;

typedef std::vector<Edge> EdgeList;

struct Ray
{
	glm::vec2 origin;
	glm::vec2 direction;

	Ray(glm::vec2 a_origin, glm::vec2 a_direction)
	{
		origin = a_origin;
		direction = a_direction;
	}
};

struct AABB
{
	glm::vec2 minPoint;
	glm::vec2 maxPoint;
	glm::vec2 center;

	AABB(glm::vec2 a_minPoint, glm::vec2 a_maxPoint)
	{
		minPoint = a_minPoint;
		maxPoint = a_maxPoint;
	}
};

class GraphNode
{
public:
	GraphNode(int a_x, int a_y);
	glm::vec2 pos;

	bool visited;
	bool walked;
	bool walkable;

	//Heuristic
	GraphNode* previousNode;
	int weight;
	int fScore;
	int gScore;
	glm::vec2 size;


	//Edges
	EdgeList edges;
	void AddEdge(GraphNode* a_node);
	void RemoveEdge(GraphNode* a_node);

	//Texture Info
	unsigned int spriteID;
	char* spriteName;
	
	//Util
	bool isClicked(glm::vec2 a_mousePos);

	//

	void Reset();

private:
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();
	
};

bool Neighbors(GraphNode* a_nodeA, GraphNode* a_nodeB);

struct Edge{
	GraphNode* Start;
	GraphNode* End;
	float cost;
};


typedef std::vector<GraphNode*>NodeList;

class Graph{
public:
	Graph();
	Graph(unsigned int a_size, unsigned int a_spriteID);
	Graph(unsigned int a_size, unsigned int a_spriteID, char* a_spriteName);
	Graph(unsigned int a_size, unsigned int a_spriteID, char* a_spriteName, bool a_diagonal);

	static GraphNode * goal;

	void AddNode(GraphNode* a_Node);
	void RemoveNode(GraphNode* a_Node);
	NodeList nodes;

	void ResetVisited();

	bool SearchDFS(GraphNode* a_Start, GraphNode* a_End);
	bool SearchBFS(GraphNode* a_Start, GraphNode* a_End);
	
	GraphNode* GetNearestNode(glm::vec2 a_position);

	std::vector<GraphNode*> AStarSearch(GraphNode* a_Start, GraphNode* a_End, bool a_smoothPath, bool a_star);
	std::vector<GraphNode*> pathList;

	//
	glm::vec2 GetRayDirection(const glm::vec2& a_pointA, const glm::vec2& a_pointB);
	AABB GetAABB(GraphNode* a_node);
	bool RayAABBIntersect(Ray& a_ray, AABB& a_box, float& enter, float& exit);
	std::vector<GraphNode*> GetTilesInLine(Ray& a_ray, GraphNode* a_end);
	bool StraightLine(GraphNode * a_start, GraphNode * a_end);
	//GraphNode* NearestNode(glm::vec2 a_pos, Graph* a_graph);

private:

};

bool NodeCompare(const GraphNode* a_left, const GraphNode* a_Right);

bool Manhattan(const GraphNode * left, const GraphNode * right);





float GetHeuristic();
#endif //_GRAPH_H_