#include "Framework.h"
#include "Graph.h"

Framework fk;
glm::vec2 centerScreen = glm::vec2(g_WIDTH / 2, g_HEIGHT / 2);

Graph graph(5);

int main(){
	//Initialize
	fk.Initialize(g_WIDTH, g_HEIGHT, "The Gary Show");
	Fontbox::Instance().LoadFont("./assets/font/arial2.xml");
	Orthographic(0.f, (float)g_WIDTH, (float)g_HEIGHT, 0.f, -1.f, 1.f, Ortho);
	
	//Create Grass Sprite
	unsigned int grass = fk.CreateSprite("./assets/pack_sheet.xml");

	fk.SetSprite(grass, "grass");


	//dt variable
	float timer = 0;
	//Mouse location
	double mouseX = 0;
	double mouseY = 0;
	glm::vec2 mousePos = glm::vec2(0, 0);

	//Sprite Position
	std::vector<glm::vec2>spritePositionList;

	//Store Sprite Position
	glm::vec2 gridStart = glm::vec2((graph.nodes[0]->pos.x + 1) * 64, (graph.nodes[0]->pos.y + 1) * 64);
	glm::vec2 gridCurrent = gridStart;

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

		//////Draw 5x5 grid of sprites
		//for (int row = 0; row < 5; row++){
		//	for (int col = 0; col < 5; col++){
		//		fk.DrawSprite(grass);

		//		fk.MoveSprite(grass,);
		//		
		//	}
		//	gridCurrent.x = gridStart.x;
		//	fk.MoveSprite(grass, gridCurrent.x, gridCurrent.y += 55);
		//}

		for (int i = 0; i < 25; i++){
			fk.MoveSprite(grass, spritePositionList[i]);
			fk.DrawSprite(grass);

		}

		ResetDeltaTime();
	} while (fk.FrameworkUpdate());
}