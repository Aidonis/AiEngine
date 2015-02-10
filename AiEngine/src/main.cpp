#define GLEW_STATIC

#include "Framework.h"
#include <Windows.h>

Framework fk;

int main(){
	fk.Initialize(g_WIDTH, g_HEIGHT, "The Gary Show");

	Fontbox::Instance().LoadFont("./assets/font/arial2.xml");
	Orthographic(0.f, (float)g_WIDTH, (float)g_HEIGHT, 0.f, -1.f, 1.f, Ortho);

	unsigned int theSprite = fk.CreateSprite("./assets/oakSheet.xml");
	unsigned int theTwin = fk.CreateSprite("./assets/oakSheet.xml");
	unsigned int gary = fk.CreateSprite("./assets/oakSheet.xml");

	int i = 0;
	do{
		float dt = GetDeltaTime();
		fk.ClearScreen();

		Fontbox::Instance().DrawString("Gary Things", glm::vec2((g_WIDTH/3) + 30, (g_HEIGHT / 5) * 3), 1);

		fk.MoveSprite(gary, g_WIDTH/2, g_HEIGHT /2);
		fk.MoveSprite(theSprite, g_WIDTH /2 + 50, g_HEIGHT / 2);
		fk.MoveSprite(theTwin, g_WIDTH / 2 - 50, g_HEIGHT / 2);
		
		fk.DrawSprite(gary);


		if (i< 4){
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
		}

		std::cout << dt << std::endl << std::endl;

		//glm::vec3 move(5, 0, 0);
		//if (fk.IsKeyDown(GLFW_KEY_SPACE)){
		//	move *= -1;
		//}
		//theSprite.s_Position += move;
		//theTwin.s_Position -= move;


		//glm::vec3 moveY(0, 5, 0);
		//if (fk.IsKeyDown(GLFW_KEY_UP)){
		//	theSprite.s_Position += moveY;
		//	theTwin.s_Position -= moveY;
		//}
		//if (fk.IsKeyDown(GLFW_KEY_DOWN)){
		//	theSprite.s_Position += -moveY;
		//	theTwin.s_Position -= -moveY;
		//}

		//theTwin.Update(0.1f);
		//theSprite.Update(0.1f);
		fk.DrawSprite(theSprite);
		fk.DrawSprite(theTwin);
		fk.DrawSprite(gary);

		Sleep(150);
		ResetDeltaTime();
	} while (fk.FrameworkUpdate());
}