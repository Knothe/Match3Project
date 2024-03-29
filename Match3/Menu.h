#pragma once
#include "State.h"
#include "Button.h"
#include "AudioManager.h"
#include "Text.h"

class Menu : public State
{
private:
	Platform* platform;
	AssetManager* assetManager;
	AudioManager* audioManager;
	MouseData mouseData;
	Button startButton;
	Button highScoreButton;
	Button soundButtonOn;
	Button soundButtonOff;
	bool hasSound;
	Image title;
	Image backGround;
public:
	Menu();
	void Input() override;
	void Update() override;
	void Draw() override;
	void Init() override;
	void Close() override;
	~Menu();
};