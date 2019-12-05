#include "Menu.h"
#include "Game.h"

Menu::Menu() {
	bgTime = 300;
	lastBgTime = SDL_GetTicks();
}
void Menu::Input() {
	platform->CheckEvent(&mouseData);

	if (mouseData.rightButton)
			state = false;
}

void Menu::Update() {
	
	if (simpleButton.Update(&mouseData))
		GameManager::getPtr()->SetState(new Game());



	if (SDL_TICKS_PASSED(SDL_GetTicks(), lastBgTime + bgTime))
	{
		lastBgTime = SDL_GetTicks();
		testImage->NextFrame();
	}
}

void Menu::Draw() {
	platform->RenderClear();

	simpleButton.Draw();

	/*int scale = platform->GetScale();
	int x = testImage->GetWidth() * scale;
	int y = testImage->GetHeight() * scale;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			platform->RenderImage(testImage, i * x + (10 * i), j * y + (10 * j));
		}
	}*/


	platform->RenderPresent();
}

void Menu::Init() {
	platform = Platform::GetPtr();
	testImage = new Image();
	testImage->LoadImage("Arrow-Sheet.png", 4,1);
	simpleButton.Init("Arrow-Sheet.png", "Sword-Sheet.png", Vec2(300, 300));
}

void Menu::Close() {
	state = false;
}

Menu::~Menu() {

}