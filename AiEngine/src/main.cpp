#include "Framework.h"
#include "Graph.h"

Framework fk;
glm::vec2 centerScreen = glm::vec2(g_WIDTH / 2, g_HEIGHT / 2);

Graph graph(5);

int main(){
	fk.Initialize(g_WIDTH, g_HEIGHT, "The Gary Show");

	Fontbox::Instance().LoadFont("./assets/font/arial2.xml");
	Orthographic(0.f, (float)g_WIDTH, (float)g_HEIGHT, 0.f, -1.f, 1.f, Ortho);

	unsigned int grass = fk.CreateSprite("./assets/pack_sheet.xml");

	int i = 0;
	float timer = 0;

	double mouseX = 0;
	double mouseY = 0;

	glm::vec2 mousePos = glm::vec2(0, 0);
	glm::vec2 spritePos = centerScreen;

	do{
		float dt = GetDeltaTime() * 10;
		timer += dt;
		fk.ClearScreen();
		fk.SetSprite(grass, "grass");

		glm::vec2 start = glm::vec2(50, 50);
		glm::vec2 current = start;
		fk.MoveSprite(grass, start);
		for (int row = 0; row < 5; row++){
			for (int col = 0; col < 5; col++){
				fk.DrawSprite(grass);
				fk.MoveSprite(grass, current.x += 60, current.y);
				
			}
			current.x = start.x;
			fk.MoveSprite(grass, current.x, current.y += 60);
			
		}

		ResetDeltaTime();
	} while (fk.FrameworkUpdate());
}