#include "Menu.h"
#include "Game.h"
#include "HighScoreMenu.h"
/*
Starts the menu
*/
Menu::Menu() {
	platform = Platform::GetPtr();
	assetManager = AssetManager::getPtr();
	audioManager = AudioManager::getPtr();
	assetManager->AddMusic("Menu.wav", "menu");
	assetManager->AddMusic("Game.wav", "game");
	assetManager->AddMusic("GameOver.wav", "gameOver");

	assetManager->AddTexture("Title.png", "title", 1);
	assetManager->AddTexture("StartButton1.png", "s1", 1);
	assetManager->AddTexture("StartButton2.png", "s2", 1);
	assetManager->AddTexture("HighScore1.png", "h1", 1);
	assetManager->AddTexture("HighScore2.png", "h2", 1);
	assetManager->AddTexture("SoundOn.png", "sn", 1);
	assetManager->AddTexture("SoundOff.png", "sf", 1);
	assetManager->AddTexture("BackGroundMenu.png", "menu", 1);

	assetManager->AddFont("pixelart.ttf", "med", 25);
	assetManager->AddFont("pixelart.ttf", "big", 50);
	assetManager->AddFont("pixelart.ttf", "sma", 20);
}
/*
Reads input in Menu
*/
void Menu::Input() {
	platform->CheckEvent(&mouseData);
	if (startButton.Update(&mouseData))
		GameManager::getPtr()->SetState(new Game());
	if (highScoreButton.Update(&mouseData))
		GameManager::getPtr()->SetState(new HighScoreMenu());
	if (hasSound) {
		if (soundButtonOn.Update(&mouseData)) {
			audioManager->VolumeMusic(0);
			hasSound = false;
		}
	}
	else {
		if (soundButtonOff.Update(&mouseData)) {
			audioManager->VolumeMusic(MIX_MAX_VOLUME);
			hasSound = true;
		}
	}

	mouseData.ResetClicks();
}
/*
Updates everything in Menu
*/
void Menu::Update() {
	
}
/*
Draws everything in menu
*/
void Menu::Draw() {
	platform->RenderClear();
	platform->RenderImage(&backGround, Vec2(0, 0));
	platform->RenderImage(&title, Vec2(36, 60));
	highScoreButton.Draw();
	startButton.Draw();
	if(hasSound)
		soundButtonOn.Draw();
	else
		soundButtonOff.Draw();
	platform->DrawRect(207, 290, 450, 90);
	platform->DrawRect(207, 400, 450, 90);
	platform->DrawRect(207, 510, 450, 90);
	platform->RenderPresent();
}
/*
Initializes everything in Menu
*/
void Menu::Init() {
	audioManager->PlayMusic("menu", -1);
	if (audioManager->VolumeMusic(-1) > 0)
		hasSound = true;
	else
		hasSound = false;
	title.LoadImage("title");
	backGround.LoadImage("menu");
	startButton.Init("s1", "s2", Vec2( 312, 290));
	highScoreButton.Init("h1", "h2", Vec2( 192, 400));
	soundButtonOn.Init("sn", "sf", Vec2( 375, 510));
	soundButtonOff.Init("sf", "sn", Vec2( 375, 510));

}
/*
Prepares for delete
*/
void Menu::Close() {
	state = false;
}

Menu::~Menu() {

}