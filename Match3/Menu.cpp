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
	g->Input(&mouseData);
	if (mouseData.rightButton)
		audioManager->VolumeMusic(MIX_MAX_VOLUME);
	if (mouseData.leftButton)
		audioManager->VolumeMusic(MIX_MAX_VOLUME / 3);
}
/*
Updates everything in Menu
*/
void Menu::Update() {
	/*if (simpleButton.Update(&mouseData))
		GameManager::getPtr()->SetState(new Game());*/
	g->Update();

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

	g->Draw();
	//simpleButton.Draw();

	int scale = platform->GetScale();
	int x = testImage->GetWidth() * scale;
	int y = testImage->GetHeight() * scale;

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

	assetManager->AddTexture("Arrow.png", "a", 1);
	assetManager->AddTexture("Sword.png", "s", 1);

	assetManager->AddTexture("Arrow.png", "bow", 7);
	assetManager->AddTexture("Sword.png", "sword", 6);
	assetManager->AddTexture("Gem.png", "gem", 4);
	assetManager->AddTexture("Rupee.png", "rupee", 3);
	assetManager->AddTexture("Coin.png", "coin", 4);
	assetManager->AddTexture("Board.png", "board", 1);
	assetManager->AddTexture("Wand.png", "wand", 5);
	assetManager->AddTexture("Potions.png", "potion", 6);
	assetManager->AddTexture("Direction.png", "direction", 8);

	assetManager->AddTexture("Selected.png", "select", 1);

	assetManager->AddTexture("ArrowDestroy.png", "bowDes",7);
	assetManager->AddTexture("SwordDestroy.png", "swoDes", 7);
	assetManager->AddTexture("GemDestroy.png", "gemDes", 7);
	assetManager->AddTexture("RupeeDestroy.png", "rupDes", 7);
	assetManager->AddTexture("CoinDestroy.png", "coiDes", 7);
	assetManager->AddTexture("WandDestroy.png", "wanDes", 7);
	assetManager->AddTexture("PotionsDestroy.png", "potDes", 8);
	assetManager->AddTexture("DirectionDestroy.png", "dirDes", 8);

	g = new Graph();

	assetManager->AddMusic("Game.wav", "game");
	assetManager->AddMusic("GameOver.wav", "gameOver");

	//audioManager->PlayMusic("game", -1);
	testImage = new Image();
	//testImage->LoadImage("arrow");
	simpleButton.Init("a", "select", Vec2(300, 300));
}
/*
Prepares for delete
*/
void Menu::Close() {
	state = false;
}

Menu::~Menu() {

}