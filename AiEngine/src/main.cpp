#include "Graph.h"
//#include "Tile.h"
Framework fk;

glm::vec2 centerScreen = glm::vec2(g_WIDTH / 2, g_HEIGHT / 2);

int main(){

	

	//Initialize
	fk.Initialize(g_WIDTH, g_HEIGHT, "The Gary Show");
	Fontbox::Instance().LoadFont("./assets/font/arial2.xml");
	Orthographic(0.f, (float)g_WIDTH, (float)g_HEIGHT, 0.f, -1.f, 1.f, Ortho);
	
	Graph graph(5);

	//Create Grass Sprite
	unsigned int grass = fk.CreateSprite("./assets/pack_sheet.xml");
	//unsigned int water = fk.CreateSprite("./assets/pack_sheet.xml");

	graph.SearchDFS(graph.nodes[2], graph.nodes[12]);

	//dt variable
	float timer = 0;
	//Mouse location
	double mouseX = 0;
	double mouseY = 0;
	int j = 0;
	glm::vec2 mousePos = glm::vec2(0, 0);

	//Sprite Position
	std::vector<glm::vec2>spritePositionList;

	//Store Sprite Position
	glm::vec2 gridStart = glm::vec2((graph.nodes[0]->pos.x + 1) * 64, (graph.nodes[0]->pos.y + 1) * 64);
	glm::vec2 gridCurrent = gridStart;

	//Store Sprite Positions the lame way
	for (int row = 0; row < 5; row++){
		for (int col = 0; col < 5; col++){
			spritePositionList.push_back(gridCurrent);
			gridCurrent.x += 55;
		}
		gridCurrent.x = gridStart.x;
		gridCurrent.y += 55;
	}

	do{
		float dt = GetDeltaTime() * 10;
		timer += dt;
		fk.ClearScreen();
		//Get mouse position
		fk.GetMouseLocation(mouseX, mouseY);
		if (fk.GetMouseButtonDown(GLFW_MOUSE_BUTTON_2)){
			mousePos = glm::vec2(mouseX, g_HEIGHT - mouseY);
		}

		//Draw Grid
		graph.nodes[0]->pos = centerScreen;
		graph.nodes[0]->Draw();


		ResetDeltaTime();
	} while (fk.FrameworkUpdate());
}