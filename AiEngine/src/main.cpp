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
	unsigned int tile = fk.CreateSprite("./assets/pack_sheet.xml", "grass");
	//unsigned int Water = fk.CreateSprite("./assets/pack_sheet.xml");

	Graph graph(2, tile, "grass");

	//graph.SearchDFS(graph.nodes[0], graph.nodes[1]);

	//dt variable
	float timer = 0;
	//Mouse location
	double mouseX = 0;
	double mouseY = 0;
	int j = 0;
	glm::vec2 mousePos = glm::vec2(0, 0);

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
		}

		////Draw Grid
		/*for (int i = 0; i < 4; i++)
		{
		}*/
		//fk.SetSprite(grass, "grass");
		/*if (dt > 20){
			fk.SetSprite(tile, "water");
		}
		else{
			fk.SetSprite(tile, "grass");
		}*/
		//fk.SetSprite(tile, "grass");
		//fk.MoveSprite(tile, centerScreen.x, centerScreen.y);
		//fk.DrawSprite(tile);

		//fk.SetSprite(tile, "grass");
		//fk.MoveSprite(tile, centerScreen.x + 100, centerScreen.y);
		//fk.DrawSprite(tile);

		//fk.SetSprite(tile, "water");
		//fk.MoveSprite(tile, centerScreen.x, centerScreen.y + 100);
		//fk.DrawSprite(tile);

		//fk.SetSprite(tile, "water");
		//fk.MoveSprite(tile, centerScreen.x + 100, centerScreen.y + 100);
		//fk.DrawSprite(tile);

		ResetDeltaTime();
	} while (fk.FrameworkUpdate());
}