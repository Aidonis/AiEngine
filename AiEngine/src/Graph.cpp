#include "Graph.h"

//Graph Nodes
GraphNode::GraphNode(int a_x, int a_y){
	pos.x = a_x;
	pos.y = a_y;
	visited = false;
	weight = 0;
	previousNode = NULL;
	weight = INFINITY;
	spriteID = NULL;
	spriteName = NULL;
}

void GraphNode::AddEdge(GraphNode * a_node){
	Edge newEdge;
	newEdge.Start = this;
	newEdge.End = a_node;
	newEdge.cost = 1;
	edges.push_back(newEdge);
}

void GraphNode::RemoveEdge(GraphNode * a_node){
	EdgeList::iterator edgeToDelete = edges.end();
	for (EdgeList::iterator e = edges.begin(); e != edges.end(); e++){
		if ((*e).End == a_node){
			edgeToDelete = e;
		}
	}
	if (edgeToDelete != edges.end()){
		edges.erase(edgeToDelete);
	}
}

void GraphNode::ResetVisit(){
	previousNode = NULL;
	visited = false;
	weight = INFINITY;

}

void GraphNode::Draw(){
	fk.SetSprite(spriteID, spriteName);
	fk.MoveSprite(spriteID, pos);
	fk.DrawSprite(spriteID);
}

//Graph
Graph::Graph(unsigned int a_size){
	unsigned int ID = fk.CreateSprite("./assets/pack_sheet.xml");
	for (unsigned int r = 0; r < a_size; r++) {
		for (unsigned int c = 0; c < a_size; c++) {
			nodes.push_back(new GraphNode(r, c));
		}
	}
	// < v > ^
	for (unsigned int r = 0; r < a_size; r++) {
		for (unsigned int c = 0; c < a_size; c++) {
			if (c > 0) {
				nodes[(r * a_size) + c]->AddEdge(nodes[(r * a_size) + c - 1]);
			}
			if (r < a_size - 1) {
				nodes[(r * a_size) + c]->AddEdge(nodes[((r + 1) * a_size) + c]);
			}
			if (c < a_size - 1) {
				nodes[(r * a_size) + c]->AddEdge(nodes[(r * a_size) + c + 1]);
			}
			if (r > 0) {
				nodes[(r * a_size) + c]->AddEdge(nodes[((r - 1) * a_size) + c]);
			}
		}
	}
	//Assign Sprite Info
	for (unsigned int r = 0; r < a_size; r++) {
		for (unsigned int c = 0; c < a_size; c++) {
			nodes[(r*a_size) + c]->spriteID = ID;
			nodes[(r*a_size) + c]->spriteName = "grass";
		}
	}
}

void Graph::AddNode(GraphNode* a_node){
	nodes.push_back(a_node);
}

void Graph::ResetVisted(){
	for (NodeList::iterator i = nodes.begin(); i != nodes.end(); i++){
		(*i)->visited = false;
	}
}

bool Graph::SearchDFS(GraphNode* a_Start, GraphNode* a_End){
	std::stack<GraphNode*> NodeStack;
	NodeStack.push(a_Start);

	while (!NodeStack.empty()){
		GraphNode* current = NodeStack.top();
		NodeStack.pop();
		if (current->visited == true){
			current->spriteName = "water";
			continue;
		}
		current->visited = true;

		if (current == a_End){
			return true;
		}
		for (int i = 0; i < current->edges.size(); i++){
			NodeStack.push(current->edges[i].End);
		}
	}

	return false;

}

bool Graph::SearchBFS(GraphNode* a_Start, GraphNode* a_End){
	std::queue<GraphNode*> NodeQueue;
	NodeQueue.push(a_Start);

	while (!NodeQueue.empty()){
		GraphNode* current = NodeQueue.front();
		NodeQueue.pop();
		if (current->visited == true){
			continue;
		}
		current->visited = true;
		if (current == a_End){
			return true;
		}
		for (int i = 0; i < current->edges.size(); i++){
			NodeQueue.push(current->edges[i].End);
		}
	}
	return false;
}

bool Graph::SearchDJK(GraphNode* a_Start, GraphNode* a_End){
	//Reset Nodes/Weights
	ResetVisted();

	//Push start node onto the priority queue
	std::list<GraphNode*> nodeList;
	a_Start->previousNode = a_Start;
	a_Start->weight = 0;
	nodeList.push_front(a_Start);
	//goal = a_End;

	//While queue not empty
	while (!nodeList.empty()){
		//Sort
		nodeList.sort(NodeCompare);

		//Get current node off the end of the queue and remove it
		GraphNode* currentNode = nodeList.back();
		nodeList.pop_back();

		//Mark as traversed
		if (currentNode == a_End){
			return true;
		}
		currentNode->visited = true;

		//Loop through the edges
		for (EdgeList::iterator i = currentNode->edges.begin(); i != currentNode->edges.end(); i++){
			GraphNode* endNode = (*i).End;

			//If end node not traversed
			if (!endNode->visited){
				//Calculate current node's weight = edge cost
				float cost = currentNode->weight + (*i).cost;

				//If cost is less than existing weight cost in end node
				if (cost < endNode->weight){
					//set end node previous node to current node
					endNode->previousNode = currentNode;

					//set end node weight to current node weight + edge cost
					endNode->weight = cost;

					//if end node not in queue
					if (!endNode->visited){
						//push end node onto the queue
						nodeList.push_front(endNode);
					}
				}
			}
		}
	}
	return false;
}

bool Neighbors(GraphNode* a_nodeA, GraphNode* a_nodeB){
	for (int i = 0; i < 4; i++){
		if (a_nodeA->edges[i].End == a_nodeB){
			return true;
		}
	}
	return false;
}

bool NodeCompare(const GraphNode* a_left, const GraphNode* a_right){
	return (a_left->weight < a_right->weight);
}