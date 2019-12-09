#pragma once
#include "State.h"
#include "AudioManager.h"
#include "Graph.h"
#include "Text.h"

class Game : public State
{
private:
	Platform* platform;
	AssetManager* assetManager;
	AudioManager* audioManager;
	MouseData mouseData;
	Graph* g;
	Image backGround;
	Text* scoreText;
	Text* timeText;
	Text* scoreT;
	Text* timeT;

	int score;
	int maxTime;
	Uint32 lastTime;

public:
	Game();
	void Input() override;
	void Update() override;
	void Draw() override;
	void Init() override;
	void Close() override;
	void PauseDraw();
	~Game();
};

