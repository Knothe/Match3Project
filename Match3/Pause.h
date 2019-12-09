#pragma once
#include "State.h"
#include "AudioManager.h"
#include "Graph.h"
#include "Game.h"
#include "Button.h"

class Pause : public State
{
private:
	Platform* platform;
	AssetManager* assetManager;
	AudioManager* audioManager;
	Game* game;
	MouseData mouseData;
	Image backGround;
	bool hasMusic; 
	Button soundButtonOn;
	Button soundButtonOff;
public:
	Pause(Game* game);
	void Input() override;
	void Update() override;
	void Draw() override;
	void Init() override;
	void Close() override;
	~Pause();
};

