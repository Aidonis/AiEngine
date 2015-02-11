#define GLEW_STATIC

#include "Framework.h"

Framework fk;
glm::vec2 centerScreen = glm::vec2(g_WIDTH / 2, g_HEIGHT / 2);


int main(){
	fk.Initialize(g_WIDTH, g_HEIGHT, "The Gary Show");

	Fontbox::Instance().LoadFont("./assets/font/arial2.xml");
	Orthographic(0.f, (float)g_WIDTH, (float)g_HEIGHT, 0.f, -1.f, 1.f, Ortho);

	unsigned int theSprite = fk.CreateSprite("./assets/oakSheet.xml");
	unsigned int theTwin = fk.CreateSprite("./assets/oakSheet.xml");
	unsigned int gary = fk.CreateSprite("./assets/oakSheet.xml");

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
		fk.GetMouseLocation(mouseX, mouseY);

		Fontbox::Instance().DrawString("Gary Things", glm::vec2((g_WIDTH/3) + 30, (g_HEIGHT / 5) * 3), 1);

		fk.MoveSprite(gary,centerScreen);
		fk.MoveSprite(theSprite, g_WIDTH /2 + 50, g_HEIGHT / 2);
	
		if (fk.GetMouseButtonDown(GLFW_MOUSE_BUTTON_2)){
			mousePos = glm::vec2(mouseX, g_HEIGHT - mouseY);
			startLerp = true;
		}

		if (timer > 1.5f){
			if (startLerp){
				if (percent < 1.f){
					fk.LerpSprite(theTwin, mousePos, percent);
					percent += .1f;
				}
				else{
					startLerp = false;
					percent = 0.f;
				}
			}
			if (i < 4){
				switch (i){
				case 0:
					fk.SetSprite(theSprite, "left0");
					fk.SetSprite(theTwin, "right0");
					fk.SetSprite(gary, "left0");
					i++;
					break;
				case 1:
					fk.SetSprite(theSprite, "left1");
					fk.SetSprite(theTwin, "right1");
					fk.SetSprite(gary, "right0");
					i++;
					break;
				case 2:
					fk.SetSprite(theSprite, "left2");
					fk.SetSprite(theTwin, "right2");
					fk.SetSprite(gary, "back0");
					i++;
					break;
				case 3:
					fk.SetSprite(gary, "front0");
					i = 0;
					break;
				}
				centerScreen -= glm::vec2(0, 1);
			}
			timer = 0;
		}

		fk.DrawSprite(theSprite);
		fk.DrawSprite(theTwin);
		fk.DrawSprite(gary);

		ResetDeltaTime();
	} while (fk.FrameworkUpdate());
}