#define GLEW_STATIC

#include "Framework.h"
#include <Windows.h>


int main(){
	Initialize(g_WIDTH, g_HEIGHT, "The Gary Show");

	Fontbox::Instance().LoadFont("./assets/font/arial2.xml");
	Orthographic(0.f, (float)g_WIDTH, (float)g_HEIGHT, 0.f, -1.f, 1.f, Ortho);

	Sprite theSprite;
	theSprite.LoadTexture("./assets/oakSprite.png");
	theSprite.s_Animator.LoadSprites("./assets/oakSheet.xml");

	Sprite theTwin;
	theTwin.LoadTexture("./assets/oakSprite.png");
	theTwin.s_Animator.LoadSprites("./assets/oakSheet.xml");

	int texID[10];

	unsigned int gary = CreateSprite();

	int i = 0;
	do{
		float dt = GetDeltaTime();
		ClearScreen();

		Fontbox::Instance().DrawString("Gary Things", glm::vec2((g_WIDTH/3) + 30, (g_HEIGHT / 5) * 3), 1);

		MoveSprite(gary, 50, 50);
		DrawSprite(gary);


		if (i< 3){
			switch (i){
			case 0:
				theSprite.s_Animator.SetSprite("left0");
				theTwin.s_Animator.SetSprite("right0");
				i++;
				break;
			case 1:
				theSprite.s_Animator.SetSprite("left1");
				theTwin.s_Animator.SetSprite("right1");
				i++;
				break;
			case 2:
				theSprite.s_Animator.SetSprite("left2");
				theTwin.s_Animator.SetSprite("right2");
				i = 0;
				break;
			}
		}

		std::cout << dt << std::endl << std::endl;

		glm::vec3 move(5, 0, 0);
		if (IsKeyDown(GLFW_KEY_SPACE)){
			move *= -1;
		}
		theSprite.s_Position += move;
		theTwin.s_Position -= move;


		glm::vec3 moveY(0, 5, 0);
		if (IsKeyDown(GLFW_KEY_UP)){
			theSprite.s_Position += moveY;
			theTwin.s_Position -= moveY;
		}
		if (IsKeyDown(GLFW_KEY_DOWN)){
			theSprite.s_Position += -moveY;
			theTwin.s_Position -= -moveY;
		}

		theTwin.Update(0.1f);
		theSprite.Update(0.1f);

		Sleep(150);
		ResetDeltaTime();
	} while (FrameworkUpdate());
}