#define GLEW_STATIC

#include "Framework.h"

Framework fk;
glm::vec2 centerScreen = glm::vec2(g_WIDTH / 2, g_HEIGHT / 2);


int main(){
	fk.Initialize(g_WIDTH, g_HEIGHT, "The Gary Show");

	Fontbox::Instance().LoadFont("./assets/font/arial2.xml");
	Orthographic(0.f, (float)g_WIDTH, (float)g_HEIGHT, 0.f, -1.f, 1.f, Ortho);

	unsigned int grass = fk.CreateSprite("./assets/pack_sheet.xml");

	int i = 0;
	float timer = 0;

	double mouseX = 0;
	double mouseY = 0;
	float percent = 0.f;
	bool startLerp = false;
	glm::vec2 mousePos = glm::vec2(0, 0);

	do{
		float dt = GetDeltaTime() * 10;
		timer += dt;
		fk.ClearScreen();

		fk.MoveSprite(grass, g_WIDTH / 2 + 50, g_HEIGHT / 2 + 100);


		fk.SetSprite(grass, "grass");

		fk.DrawSprite(grass);


		ResetDeltaTime();
	} while (fk.FrameworkUpdate());
}