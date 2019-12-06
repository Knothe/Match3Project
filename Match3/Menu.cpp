#include "Menu.h"
#include "Game.h"
/*
Starts the menu
*/
Menu::Menu() {
	bgTime = 300;
	lastBgTime = SDL_GetTicks();
}
/*
Reads input in Menu
*/
void Menu::Input() {
	platform->CheckEvent(&mouseData);
	obj->Input(&mouseData);
	if (mouseData.rightButton)
		audioManager->VolumeMusic(MIX_MAX_VOLUME);
	if (mouseData.leftButton)
		audioManager->VolumeMusic(MIX_MAX_VOLUME / 3);
}
/*
Updates everything in Menu
*/
void Menu::Update() {
	if (simpleButton.Update(&mouseData))
		GameManager::getPtr()->SetState(new Game());

	if (SDL_TICKS_PASSED(SDL_GetTicks(), lastBgTime + bgTime))
	{
		lastBgTime = SDL_GetTicks();
		testImage->NextFrame();
	}
}
/*
Draws everything in menu
*/
void Menu::Draw() {
	platform->RenderClear();

	simpleButton.Draw();

	int scale = platform->GetScale();
	int x = testImage->GetWidth() * scale;
	int y = testImage->GetHeight() * scale;

	obj->Draw();
	/*for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			platform->RenderImage(testImage, i * x + (10 * i), j * y + (10 * j));
		}
	}*/


	platform->RenderPresent();
}
/*
Initializes everything in Menu
*/
void Menu::Init() {
	platform = Platform::GetPtr();
	assetManager = AssetManager::getPtr();
	audioManager = AudioManager::getPtr();

	assetManager->AddTexture("Arrow-Sheet.png", "arrow", 1);
	assetManager->AddTexture("Sword-Sheet.png", "sword", 1);
	assetManager->AddTexture("Sword-Sheet.png", "s", 4);

	assetManager->AddMusic("Game.wav", "game");
	assetManager->AddMusic("GameOver.wav", "gameOver");

	audioManager->PlayMusic("game", -1);
	testImage = new Image();
	//testImage->LoadImage("arrow");
	simpleButton.Init("arrow", "sword", Vec2(300, 300));

	obj = new GameObject(0, "s", Vec2(0, 0));
}
/*
Prepares for delete
*/
void Menu::Close() {
	state = false;
}

Menu::~Menu() {

}