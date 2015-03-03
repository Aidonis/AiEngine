#include "Framework.h"
#include "Graph.h"

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
	//unsigned int Water = fk.CreateSprite("./assets/pack_sheet.xml");

	Graph graph(8, dTile, "dirt");

	graph.SearchDJK(graph.nodes[0], graph.nodes[4], NodeCompare);


	//dt variable
	float timer = 0;
	//Mouse location
	double mouseX = 0;
	double mouseY = 0;
	glm::vec2 mousePos = glm::vec2(NULL, NULL);

	//Store Sprite Position
	glm::vec2 gridStart = glm::vec2((graph.nodes[0]->pos.x + 1) * 64, (graph.nodes[0]->pos.y + 1) * 64);
	glm::vec2 gridCurrent = gridStart;

	//OutPut currently visited nodes
	std::cout << "What has been visted!" << std::endl;
	for (int i = 0; i < graph.nodes.size(); i++){
		if (graph.nodes[i]->visited == true){
			std::cout << "(" << graph.nodes[i]->pos.x << "," << graph.nodes[i]->pos.y << ")" << std::endl;
		}
	}

	do{
		float dt = GetDeltaTime() * 10;
		timer += dt;
		fk.ClearScreen();
		//Get mouse position
		fk.GetMouseLocation(mouseX, mouseY);
		if (fk.GetMouseButtonDown(GLFW_MOUSE_BUTTON_2)){
			mousePos = glm::vec2(mouseX, g_HEIGHT - mouseY);
			std::cout << mousePos.x << " " << mousePos.y << std::endl;
		}
		if (fk.IsKeyDown(GLFW_KEY_SPACE)){

		}
		if (fk.IsKeyDown(GLFW_KEY_R)){
			graph.ResetVisted();
		}
		
		////Draw Grid
		for (int i = 0; i < 64; i++)
		{
			if (graph.nodes[i]->visited){
				graph.nodes[i]->spriteID = wTile;
			}
			if (graph.nodes[i]->isClicked(mousePos)){
				graph.nodes[i]->spriteID = gTile;
			}
			else if(!graph.nodes[i]->visited){
				graph.nodes[i]->spriteID = dTile;
			}
			fk.MoveSprite(graph.nodes[i]->spriteID, graph.nodes[i]->pos);
			fk.DrawSprite(graph.nodes[i]->spriteID);
		}


		ResetDeltaTime();
	} while (fk.FrameworkUpdate());
}