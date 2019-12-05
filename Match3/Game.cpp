#include "Game.h"
Game::Game() {

}
/*
Checks inputs in game
*/
void Game::Input() {
	platform->CheckEvent(&mouseData);
	
	if (mouseData.rightButton)
		state = false;
	mouseData.ResetClicks();
}
/*
Updates everything in game
*/
void Game::Update() {
	platform->RenderClear();
	platform->RenderPresent();
}
/*
Draws everything in game
*/
void Game::Draw() {

}
/*
Initializes everything in game
*/
void Game::Init() {
	platform = Platform::GetPtr();
}
/*
Prepares Game for delete
*/
void Game::Close() {
	state = false;
}

Game::~Game() {

}