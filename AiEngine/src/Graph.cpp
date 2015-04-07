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
	size = glm::vec2(64, 64);
	walkable = true;
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

void GraphNode::Reset(){
	weight = 1;
	gScore = INT_MAX;
	visited = false;
	walked = false;
	fScore = 0;
	walkable = true;
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

Graph::Graph(unsigned int a_size, unsigned int a_spriteID, char* a_spriteName, bool a_diagonal){

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
			if (a_diagonal){
				//top right
				if (r < a_size - 1 && c < a_size - 1){
					nodes[(r * a_size) + c]->AddEdge(nodes[((r + 1) * a_size) + c + 1]);
				}
				//top left
				if (r < a_size - 1 && c > 0){
					nodes[(r * a_size) + c]->AddEdge(nodes[((r + 1) * a_size) + c - 1]);
				}
				//bottom right
				if (r > 0 && c < a_size - 1){
					nodes[(r * a_size) + c]->AddEdge(nodes[((r - 1) * a_size) + c + 1]);
				}
				//bottom left
				if (r > 0 && c > 0){
					nodes[(r * a_size) + c]->AddEdge(nodes[((r - 1) * a_size) + c - 1]);
				}
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

void Graph::ResetVisited(){
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

std::vector<GraphNode*> Graph::AStarSearch(GraphNode* a_Start, GraphNode* a_End, bool a_smoothPath, bool a_star){
	//Reset Nodes/Weights - Set to Null and Infinity
	ResetVisited();

	//Push start node onto the priority queue
	std::list<GraphNode*> priorityQ;
	a_Start->previousNode = a_Start;
	a_Start->gScore = 0;
	priorityQ.push_front(a_Start);
	goal = a_End;

	while (!priorityQ.empty()){
		if (a_star){
			priorityQ.sort(NodeCompare);
		}
		else{
			priorityQ.sort(Manhattan);
		}
		GraphNode* current = priorityQ.front();
		priorityQ.pop_front();

		current->visited = true;

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
	if (a_End == NULL){
		return pathList;
	}

	pathList.push_back(a_End);
	GraphNode* parent = a_End->previousNode;
	pathList.insert(pathList.begin(), parent);
	while (parent != a_Start){
		parent->walked = true;
		parent = parent->previousNode;
		pathList.insert(pathList.begin(), parent);
	}

	if (a_smoothPath){
		if (pathList.size() < 3){
			return pathList;
		}
		GraphNode* start = *pathList.begin();
		GraphNode* end = *(pathList.begin() + 2);

		while (std::find(pathList.begin(), pathList.end(), end) + 1 != pathList.end()){
			if (StraightLine(start, end)){
				pathList.erase(std::find(pathList.begin(), pathList.end(), start) + 1);
				if (std::find(pathList.begin(), pathList.end(), end) + 1 != pathList.end()){
					end = *(std::find(pathList.begin(), pathList.end(), end) + 1);
				}
			}
			else{
				start = *(std::find(pathList.begin(), pathList.end(), start) + 1);
				if (std::find(pathList.begin(), pathList.end(), end) + 1 != pathList.end()){
					end = *(std::find(pathList.begin(), pathList.end(), end) + 1);
				}
			}
		}
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

bool Manhattan(const GraphNode * left, const GraphNode * right) {
	float leftF = left->weight + abs(left->pos.x - Graph::goal->pos.x) + abs(left->pos.y - Graph::goal->pos.y);

	float rightF = right->weight + abs(right->pos.x - Graph::goal->pos.x) + abs(right->pos.y - Graph::goal->pos.y);

	return (leftF < rightF);
}

glm::vec2 Graph::GetRayDirection(const glm::vec2& a_pointA, const glm::vec2& a_pointB){
	return glm::normalize(a_pointB - a_pointA);
}

std::vector<GraphNode*> Graph::GetTilesInLine(Ray& a_ray, GraphNode* a_end){
	std::vector<GraphNode*> result;
	glm::vec2 currentPosition = a_ray.origin;
	GraphNode* currentNode = nullptr;

	while (currentNode != a_end){
		currentPosition += a_end->size * a_ray.direction;
		currentNode = GetNearestNode(currentPosition);
		if (std::find(result.begin(), result.end(), currentNode) == result.end()){
			result.push_back(currentNode);
		}
	}
	return result;
}

AABB Graph::GetAABB(GraphNode* a_node){
	float hHeight = a_node->size.x * .5;
	float hWidth = a_node->size.x * .5;
	return AABB(glm::vec2(a_node->pos.x - hWidth, a_node->pos.y - hHeight), glm::vec2(a_node->pos.x + hWidth, a_node->pos.y + hHeight));
}

bool Graph::RayAABBIntersect(Ray& a_ray, AABB& a_box, float& enter, float& exit){
	glm::vec2 min = (a_box.minPoint - a_ray.origin) / a_ray.direction;
	glm::vec2 max = (a_box.maxPoint - a_ray.origin) / a_ray.direction;

	glm::vec2 near = glm::min(min, max);
	glm::vec2 far = glm::max(min, max);

	enter = glm::max(glm::max(near.x, near.y), 0.0f);
	exit = glm::min(far.x, far.y);

	return (exit > 0.0f && enter < exit);
}

bool Graph::StraightLine(GraphNode* a_start, GraphNode* a_end){
	Ray ray(a_start->pos, GetRayDirection(a_start->pos, a_end->pos));
	std::vector<GraphNode*> nodeList = GetTilesInLine(ray, a_end);
	for (GraphNode* node : nodeList){
		if (!node->walkable){
			AABB box = GetAABB(node);
			float enter = 0.0f;
			float exit = 0.0f;
			if (RayAABBIntersect(ray, box, enter, exit)){
				return false;
			}
		}
	}
	return true;
}