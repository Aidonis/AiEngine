#include "Graph.h"

//Graph Nodes
GraphNode::GraphNode(int a_x, int a_y){
	pos.x = a_x;
	pos.y = a_y;
	visited = false;
	previousNode = NULL;
	fScore = 0;
	gScore = INT_MAX;
	weight = 1;
	spriteID = NULL;
	spriteName = NULL;
}

GraphNode * Graph::goal = NULL;

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
	weight = INT_MAX;

}
//Graphnode Util
float GraphNode::GetTop(){
	return pos.y + (64 / 2);
}
float GraphNode::GetBottom(){
	return pos.y - (64 / 2);
}
float GraphNode::GetLeft(){
	return pos.x - (64 / 2);
}
float GraphNode::GetRight(){
	return pos.x + (64 / 2);
}

bool GraphNode::isClicked(glm::vec2 a_mousePos){
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

//Graph
Graph::Graph(unsigned int a_size, unsigned int a_spriteID){

	//unsigned int ID = fk.CreateSprite("./assets/pack_sheet.xml");
	//Assign Nodes
	for (unsigned int r = 0; r < a_size; r++) {
		for (unsigned int c = 0; c < a_size; c++) {
			//Set Position //TODO: No magic numbers
			nodes.push_back(new GraphNode((c*64) + 30, (r *64) +30));
		}
	}
	//Assign Edges < ^ > v
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
			nodes[(r*a_size) + c]->spriteID = a_spriteID;
			nodes[(r*a_size) + c]->spriteName = "grass";
		}
	}
}

Graph::Graph(unsigned int a_size, unsigned int a_spriteID, char* a_spriteName){

	//unsigned int ID = fk.CreateSprite("./assets/pack_sheet.xml");
	//Assign Nodes
	for (unsigned int r = 0; r < a_size; r++) {
		for (unsigned int c = 0; c < a_size; c++) {
			//Set Position //TODO: No magic numbers
			nodes.push_back(new GraphNode((c * 64) + 30, (r * 64) + 30));
		}
	}
	//Assign Edges < ^ > v
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
			nodes[(r*a_size) + c]->spriteID = a_spriteID;
			nodes[(r*a_size) + c]->spriteName = a_spriteName;
		}
	}
}

void Graph::AddNode(GraphNode* a_node){
	nodes.push_back(a_node);
}

void Graph::ResetVisted(){
	for (NodeList::iterator i = nodes.begin(); i != nodes.end(); i++){
		(*i)->visited = false;
		(*i)->gScore = INT_MAX;
		(*i)->fScore = 0;
		(*i)->walked = false;
		pathList.clear();
	}
}

bool Graph::SearchDFS(GraphNode* a_Start, GraphNode* a_End){
	std::stack<GraphNode*> NodeStack;
	NodeStack.push(a_Start);

	while (!NodeStack.empty()){
		GraphNode* current = NodeStack.top();
		NodeStack.pop();
		if (current->visited == true){
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

std::vector<GraphNode*> Graph::AStarSearch(GraphNode* a_Start, GraphNode* a_End){
	//Reset Nodes/Weights - Set to Null and Infinity
	ResetVisted();

	//Push start node onto the priority queue
	std::list<GraphNode*> priorityQ;
	a_Start->previousNode = a_Start;
	a_Start->gScore = 0;
	priorityQ.push_front(a_Start);
	goal = a_End;

	while (!priorityQ.empty()){
		priorityQ.sort(NodeCompare);
		GraphNode* current = priorityQ.front();
		priorityQ.pop_front();

		current->visited = true;
		//if (current != a_Start && current != a_End){
		//	//change color ?
		//}

		if (current == a_End){
			break;
		}
		for (EdgeList::iterator i = current->edges.begin(); i != current->edges.end(); i++){
			GraphNode* neighbor = (*i).End;
			if (!neighbor->visited){
				float fScore = current->gScore + neighbor->weight;
				if (fScore < neighbor->gScore){
					neighbor->previousNode = current;
					neighbor->gScore = current->gScore + neighbor->weight;
					neighbor->fScore = fScore;
					if (std::find(priorityQ.begin(), priorityQ.end(), neighbor) == priorityQ.end()){
						priorityQ.push_back(neighbor);
					}
				}
			}
		}
	}
	if (a_End->previousNode == nullptr){
		break;
	}

	pathList.push_back(a_End);
	GraphNode* parent = a_End->previousNode;
	pathList.insert(pathList.begin(), parent);
	while (parent != a_Start){
		parent->walked = true;
		parent = parent->previousNode;
		pathList.insert(pathList.begin(), parent);
	}
	return pathList;
}

GraphNode* Graph::GetNearestNode(glm::vec2 a_position){

	for(NodeList::iterator i = nodes.begin(); i != nodes.end(); i++){
		if ((*i)->isClicked(a_position)){
			return (*i);
		}
	}
}


bool Neighbors(GraphNode* a_nodeA, GraphNode* a_nodeB){
	for (int i = 0; i < 4; i++){
		if (a_nodeA->edges[i].End == a_nodeB){
			return true;
		}
	}
	return false;
}

bool NodeCompare(const GraphNode * left, const GraphNode * right) {
	return (left->weight < right->weight);
}

bool StraightLine(const GraphNode* a_left, const GraphNode* a_right){
	float leftF = a_left->weight + (a_left->pos + Graph::goal->pos).length();

	float rightF = a_right->weight + (a_right->pos + Graph::goal->pos).length();

	return (leftF < rightF);
}

bool Manhattan(const GraphNode * left, const GraphNode * right) {
	float leftF = left->weight + abs(left->pos.x - Graph::goal->pos.x) + abs(left->pos.y - Graph::goal->pos.y);

	float rightF = right->weight + abs(right->pos.x - Graph::goal->pos.x) + abs(right->pos.y - Graph::goal->pos.y);

	return (leftF < rightF);
}