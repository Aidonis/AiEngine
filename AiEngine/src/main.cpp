#include "Framework.h"
#include "player.h"
#include "NonPlayer.h"
#include <ctime>


Framework fk;

glm::vec2 centerScreen = glm::vec2(g_WIDTH / 2, g_HEIGHT / 2);

int main(){

	srand(time(NULL));

	//Initialize
	fk.Initialize(g_WIDTH, g_HEIGHT, "The Gary Show");
	Fontbox::Instance().LoadFont("./assets/font/arial2.xml");
	Orthographic(0.f, (float)g_WIDTH, (float)g_HEIGHT, 0.f, -1.f, 1.f, Ortho);

	//Create Grass Sprite
	unsigned int gTile = fk.CreateSprite("./assets/pack_sheet.xml", "grass");
	unsigned int wTile = fk.CreateSprite("./assets/pack_sheet.xml", "water");
	unsigned int dTile = fk.CreateSprite("./assets/pack_sheet.xml", "dirt");
	unsigned int sTile = fk.CreateSprite("./assets/pack_sheet.xml", "stone");
	unsigned int stoneTile = fk.CreateSprite("./assets/pack_sheet.xml", "wall");

	//Player pieces
	unsigned int purple = fk.CreateSprite("./assets/piecePurple.xml", "purple");
	unsigned int white = fk.CreateSprite("./assets/pieceWhite.xml", "white");
	unsigned int rPlayer = fk.CreateSprite("./assets/pieceRed.xml", "red");
	unsigned int green = fk.CreateSprite("./assets/pieceGreen.xml", "green");

	std::vector<NonPlayer*> purpList;
	std::vector<NonPlayer*> whiteList;
	
	for (int i = 0; i < 20; i++){
		NonPlayer* np = new NonPlayer();
		np->Initialize();
		np->spriteID = purple;
		np->pos = glm::vec2(rand() % 600 + 1, rand() % 600 + 1);
		purpList.push_back(np);
	}

	for (int i = 0; i < 20; i++){
		NonPlayer* np = new NonPlayer();
		np->Initialize();
		np->spriteID = white;
		np->pos = glm::vec2(rand() % 600 + 1, rand() % 600 + 1);
		whiteList.push_back(np);
	}

	Graph graph(10, dTile, "dirt", true);

	//dt variable
	float timer = 0;

	//Mouse location
	double mouseX = 0;
	double mouseY = 0;
	unsigned int clickCount = 0;
	glm::vec2 mousePos1 = glm::vec2(NULL, NULL);
	glm::vec2 mousePos2 = glm::vec2(NULL, NULL);
	glm::vec2 mousePos3 = glm::vec2(NULL, NULL);

	//Start and End on grid
	GraphNode* endNode = graph.nodes[0];
	GraphNode* startNode = graph.nodes[0];

	//Player piece
	Player red = Player(rPlayer, startNode);
	fk.MoveSprite(red.spriteID, red.pos);

	do{
		float dt = GetDeltaTime() * 10;
		timer += dt;
		
		fk.ClearScreen();

		//Get mouse positionw
		fk.GetMouseLocation(mouseX, mouseY);	

		//Right Click - Set endNode
		if (fk.GetMouseButtonDown(GLFW_MOUSE_BUTTON_2)){
			mousePos2 = glm::vec2(mouseX, g_HEIGHT - mouseY);
			//If there is an old endNode
			if (!endNode == NULL){
				endNode->Reset();
				endNode->spriteID = dTile;

			}
				graph.GetNearestNode(mousePos2)->spriteID = sTile;
				endNode = graph.GetNearestNode(mousePos2);

		}
		//Left Click - Set startNode
		if (fk.GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)){
			mousePos1 = glm::vec2(mouseX, g_HEIGHT - mouseY);
			//If there is an old startNode
			if (!startNode == NULL){
				startNode->Reset();
				startNode->spriteID = dTile;
			}
			graph.GetNearestNode(mousePos1)->spriteID = sTile;
			startNode = graph.GetNearestNode(mousePos1);
		}
		//Run Dijkstra Search
		if (fk.IsKeyDown(GLFW_KEY_SPACE)){
		
			red.pathList = graph.AStarSearch(startNode, endNode, false, false);
			purpList[0]->pathList = graph.AStarSearch(startNode, endNode, false, false);

			for (NodeList::iterator i = graph.nodes.begin(); i != graph.nodes.end(); i++){
				if (!(*i)->visited && !(*i)->walked && (*i)->weight != INT_MAX){
					(*i)->spriteID = dTile;
				}
				if ((*i)->visited){
					(*i)->spriteID = gTile;
				}
				if ((*i)->walked){
					(*i)->spriteID = stoneTile;
				}
				if ((*i) == startNode || (*i) == endNode){
					(*i)->spriteID = sTile;
				}
			}
		}

		//Run AStar
		if (fk.IsKeyDown(GLFW_KEY_A)){

			red.pathList = graph.AStarSearch(startNode, endNode, false, true);
			purpList[0]->pathList = graph.AStarSearch(startNode, endNode, false, true);

			for (NodeList::iterator i = graph.nodes.begin(); i != graph.nodes.end(); i++){
				if (!(*i)->visited && !(*i)->walked && (*i)->weight != INT_MAX){
					(*i)->spriteID = dTile;
				}
				if ((*i)->visited){
					(*i)->spriteID = gTile;
				}
				if ((*i)->walked){
					(*i)->spriteID = stoneTile;
				}
				if ((*i) == startNode || (*i) == endNode){
					(*i)->spriteID = sTile;
				}
			}
		}

		if (fk.IsKeyDown(GLFW_KEY_W)){
			mousePos3 = glm::vec2(mouseX, g_HEIGHT - mouseY);
			graph.GetNearestNode(mousePos3)->spriteID = wTile;
			graph.GetNearestNode(mousePos3)->weight = INT_MAX;
			graph.GetNearestNode(mousePos3)->walkable = false;
		}

		//New Draw
		for (int i = 0; i < graph.nodes.size(); i++){
			fk.MoveSprite(graph.nodes[i]->spriteID, graph.nodes[i]->pos);
			fk.DrawSprite(graph.nodes[i]->spriteID);
		}
		if (!endNode == NULL && !startNode == NULL){
			graph.AStarSearch(startNode, endNode, false, false);
		}

		//Purple List
		float rad = PI / 2;
		for (int i = 0; i < purpList.size(); i++)
		{
			rad += PI /2 ;
			purpList[i]->SetFleeTarget(glm::vec2(mouseX,g_HEIGHT - mouseY));
			purpList[i]->SetGraph(&graph);
			fk.MoveSprite(purpList[i]->spriteID, purpList[i]->pos);
			fk.RotateSprite(purpList[i]->spriteID, purpList[i]->rotateAngle);
			purpList[i]->Update(dt, purpList);
			fk.DrawSprite(purpList[i]->spriteID);
		}

		//White List
		for (int i = 0; i < whiteList.size(); i++)
		{
			rad += PI / 2;
			whiteList[i]->SetFleeTarget(glm::vec2(mouseX, g_HEIGHT - mouseY));
			whiteList[i]->SetGraph(&graph);
			fk.MoveSprite(whiteList[i]->spriteID, whiteList[i]->pos);
			fk.RotateSprite(whiteList[i]->spriteID, whiteList[i]->rotateAngle);
			whiteList[i]->Update(dt, whiteList);
			fk.DrawSprite(whiteList[i]->spriteID);
		}

		purpList[0]->spriteID = green;
		purpList[0]->Update(dt);
		red.Update(dt);
		fk.MoveSprite(red.spriteID, red.pos);
		fk.DrawSprite(red.spriteID);
		rad = PI / 2;

		ResetDeltaTime();
	} while (fk.FrameworkUpdate());
}