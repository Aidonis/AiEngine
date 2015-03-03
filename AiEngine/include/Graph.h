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
	int weight;
	int fScore;
	int gScore;


	//Edges
	EdgeList edges;
	void AddEdge(GraphNode* a_node);
	void RemoveEdge(GraphNode* a_node);

	//Texture Info
	unsigned int spriteID;
	char* spriteName;
	
	//Util
	bool isClicked(glm::vec2 a_mousePos){
		if (GetLeft() > a_mousePos.x ||
			GetRight() < a_mousePos.x ||
			GetTop() < a_mousePos.y ||
			GetBottom() > a_mousePos.y){
			return false;
		}
		if (a_mousePos == glm::vec2(NULL, NULL)){
			return false;
		}
		else{
			return true;
		}
	}

	void ResetVisit();

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

	static GraphNode * goal;

	void AddNode(GraphNode* a_Node);
	void RemoveNode(GraphNode* a_Node);
	NodeList nodes;

	void ResetVisted();

	bool SearchDFS(GraphNode* a_Start, GraphNode* a_End);
	bool SearchBFS(GraphNode* a_Start, GraphNode* a_End);
	bool SearchDJK(GraphNode* a_Start, GraphNode* a_End, bool(*heuFunc)(const GraphNode*, const GraphNode*));
	
	void AStarSearch(GraphNode* a_Start, GraphNode* a_End);

	int DJK_Steps(GraphNode* a_Start, GraphNode* a_End, bool(*heuFunc)(const GraphNode*, const GraphNode*));

private:

};

bool Dijkstra(const GraphNode* a_left, const GraphNode* a_Right);

bool StraightLine(const GraphNode * a_left, const GraphNode * a_right);

bool Manhattan(const GraphNode * left, const GraphNode * right);

float GetHeuristic();
#endif //_GRAPH_H_