#include "Game.h"
Game::Game() {

}

void Game::Input() {
	platform->CheckEvent(&mouseData);
	
	if (mouseData.rightButton)
		state = false;
	mouseData.ResetClicks();
}

void Game::Update() {
	platform->RenderClear();
	platform->RenderPresent();
}

void Game::Draw() {

}

void Game::Init() {
	platform = Platform::GetPtr();
}

void Game::Close() {
	state = false;
}

Game::~Game() {

}