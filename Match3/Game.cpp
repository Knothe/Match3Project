#include "Game.h"
#include "Pause.h"
#include "Endgame.h"
/*
Initializes variables and adds textures
*/
Game::Game() {
	assetManager = AssetManager::getPtr();
	platform = Platform::GetPtr();
	audioManager = AudioManager::getPtr();
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
	assetManager->AddTexture("ArrowDestroy.png", "bowDes", 7);
	assetManager->AddTexture("SwordDestroy.png", "swoDes", 7);
	assetManager->AddTexture("GemDestroy.png", "gemDes", 7);
	assetManager->AddTexture("RupeeDestroy.png", "rupDes", 7);
	assetManager->AddTexture("CoinDestroy.png", "coiDes", 7);
	assetManager->AddTexture("WandDestroy.png", "wanDes", 7);
	assetManager->AddTexture("PotionsDestroy.png", "potDes", 8);
	assetManager->AddTexture("DirectionDestroy.png", "dirDes", 8);
	assetManager->AddTexture("BackGroundGame.png", "game", 1);
	
}
/*
Checks inputs in game
*/
void Game::Input() {
	Vector<int> input;
	platform->CheckEvent(&input, &mouseData);
	for (int i = 0; i < input.GetSize(); i++) {
		if (input.GetAt(i) == SDLK_p)	GameManager::getPtr()->SetState(new Pause(this));
		if (input.GetAt(i) == SDLK_ESCAPE)	state = false; 
	}
	g->Input(&mouseData);
	mouseData.ResetClicks();
}
/*
Updates everything in game
*/
void Game::Update() {
	score += g->Update();
	maxTime -= (SDL_GetTicks() - lastTime);
	if (maxTime <= 0)
		GameManager::getPtr()->SetState(new EndGame(this, score));
	scoreT = new Text(Vec2(30, 30), std::to_string(score), "sma", { 255, 255, 255 });
	timeT = new Text(Vec2(30, 130), std::to_string(maxTime / 1000), "sma", { 255, 255, 255 });
}
/*
Draws everything in game
*/
void Game::Draw() {
	platform->RenderClear();
	PauseDraw();
	platform->RenderPresent();
}
/*
Draws everything but doesnt render
*/
void Game::PauseDraw() {
	lastTime = SDL_GetTicks();
	platform->RenderImage(&backGround, Vec2(0, 0));
	g->Draw();
	scoreText->Draw();
	timeText->Draw();
	scoreT->Draw();
	timeT->Draw();
}
/*
Initializes everything in game
*/
void Game::Init() {
	g = new Graph();
	audioManager->PlayMusic("game");
	backGround.LoadImage("game");
	scoreText = new Text(Vec2(0, 0), "Score", "med", { 255,255,255 });
	timeText = new Text(Vec2(0, 100), "Time", "med", { 255,255,255 });
	score = 0;
	lastTime = SDL_GetTicks();
	maxTime = 30000;
}
/*
Prepares Game for delete
*/
void Game::Close() {
	audioManager->PlayMusic("menu");
}

Game::~Game() {

}