#pragma once
#include "State.h"
#include "AudioManager.h"
#include "Graph.h"
#include "Game.h"

class EndGame : public State
{
private:
	Platform* platform;
	AssetManager* assetManager;
	AudioManager* audioManager;
	Game* game;
	MouseData mouseData;
	Image backGround;
	Image gameOver;
	Image highScore;
	Image finish;
	Text* scoreText1;
	Text* scoreText2;
	bool newHighScore;
public:
	EndGame(Game* game, int score);
	void Input() override;
	void Update() override;
	void Draw() override;
	void Init() override;
	void Close() override;
	~EndGame();
};

