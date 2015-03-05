#include "Framework.h"
#include "player.h"

Framework fk;

glm::vec2 centerScreen = glm::vec2(g_WIDTH / 2, g_HEIGHT / 2);

int main(){

	

	//Initialize
	fk.Initialize(g_WIDTH, g_HEIGHT, "The Gary Show");
	Fontbox::Instance().LoadFont("./assets/font/arial2.xml");
	Orthographic(0.f, (float)g_WIDTH, (float)g_HEIGHT, 0.f, -1.f, 1.f, Ortho);
	

	//Create Grass Sprite
	unsigned int gTile = fk.CreateSprite("./assets/pack_sheet.xml", "grass");
	unsigned int wTile = fk.CreateSprite("./assets/pack_sheet.xml", "water");
	unsigned int dTile = fk.CreateSprite("./assets/pack_sheet.xml", "dirt");
	unsigned int sTile = fk.CreateSprite("./assets/pack_sheet.xml", "stone");
	unsigned int wallTile = fk.CreateSprite("./assets/pack_sheet.xml", "wall");


	Graph graph(10, dTile, "dirt");

	//dt variable
	float timer = 0;
	//Mouse location
	double mouseX = 0;
	double mouseY = 0;
	glm::vec2 mousePos1 = glm::vec2(NULL, NULL);
	glm::vec2 mousePos2 = glm::vec2(NULL, NULL);
	glm::vec2 mousePos3 = glm::vec2(NULL, NULL);

	//Start and End on grid
	GraphNode* endNode = graph.nodes[0];
	GraphNode* startNode = graph.nodes[0];

	//Player piece
	unsigned int rPlayer = fk.CreateSprite("./assets/pieceRed.xml", "red");
	Player red = Player(rPlayer, startNode);
	fk.MoveSprite(red.spriteID, red.pos);

	bool walking = false;

	do{
		float dt = GetDeltaTime() * 10;
		timer += dt;
		
		fk.ClearScreen();

		//Get mouse position
		fk.GetMouseLocation(mouseX, mouseY);
		if (fk.GetMouseButtonDown(GLFW_MOUSE_BUTTON_2)){
			mousePos2 = glm::vec2(mouseX, g_HEIGHT - mouseY);
			graph.GetNearestNode(mousePos2)->spriteID = sTile;
			endNode = graph.GetNearestNode(mousePos2);
		}
		if (fk.GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)){
			mousePos1 = glm::vec2(mouseX, g_HEIGHT - mouseY);
			graph.GetNearestNode(mousePos1)->spriteID = sTile;
			startNode = graph.GetNearestNode(mousePos1);
		}
		if (fk.IsKeyDown(GLFW_KEY_SPACE)){
			red.pathList = graph.AStarSearch(startNode, endNode);
		}
		if (fk.IsKeyDown(GLFW_KEY_R)){
			graph.ResetVisted();
		}

		if (fk.IsKeyDown(GLFW_KEY_W)){
			mousePos3 = glm::vec2(mouseX, g_HEIGHT - mouseY);
			graph.GetNearestNode(mousePos3)->spriteID = wallTile;
			graph.GetNearestNode(mousePos3)->weight = INT_MAX;
		}

		//New Draw
		for (int i = 0; i < graph.nodes.size(); i++){
			//if (graph.nodes[i]->visited){
			//	graph.nodes[i]->spriteID = gTile;
			//}
			//if (graph.nodes[i]->isClicked(mousePos2)){
			//	endNode = graph.nodes[i];
			//	graph.nodes[i]->spriteID = sTile;
			//}
			//if (graph.nodes[i]->isClicked(mousePos1)){
			//	startNode = graph.nodes[i];
			//	graph.nodes[i]->spriteID = sTile;
			//}

			//if (graph.nodes[i]->walked){
			//	graph.nodes[i]->spriteID = sTile;
			//}
			//else if (!graph.nodes[i]->visited){
			//	graph.nodes[i]->spriteID = dTile;
			//}

			fk.MoveSprite(graph.nodes[i]->spriteID, graph.nodes[i]->pos);
			fk.DrawSprite(graph.nodes[i]->spriteID);
		}

		graph.AStarSearch(startNode, endNode);
		red.Update(dt);
		fk.MoveSprite(red.spriteID, red.pos);
		fk.DrawSprite(red.spriteID);
		ResetDeltaTime();
	} while (fk.FrameworkUpdate());
}