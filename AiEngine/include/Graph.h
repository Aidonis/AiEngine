#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include "glm\glm.hpp"
//#include "Framework.h"


struct Edge;

typedef std::vector<Edge> EdgeList;

class GraphNode
{
public:
	GraphNode(int a_x, int a_y);
	glm::vec2 pos;

	bool visited;
	
	//Heuristic
	GraphNode* previousNode;
	float weight;
	void ResetVisit();

	//Edges
	EdgeList edges;
	void AddEdge(GraphNode* a_node);
	void RemoveEdge(GraphNode* a_node);

	//Texture Info
	unsigned int spriteID;
	char* spriteName;
	
	//Draw
	//void Draw();

};

bool NodeCompare(const GraphNode* a_left, const GraphNode* a_Right);

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

	//static GraphNode * goal;

	void AddNode(GraphNode* a_Node);
	void RemoveNode(GraphNode* a_Node);
	NodeList nodes;

	void ResetVisted();

	bool SearchDFS(GraphNode* a_Start, GraphNode* a_End);
	bool SearchBFS(GraphNode* a_Start, GraphNode* a_End);
	bool SearchDJK(GraphNode* a_Start, GraphNode* a_End);

private:

};

#endif //_GRAPH_H_