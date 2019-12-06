#pragma once
#include "State.h"
#include "Button.h"
#include "AudioManager.h"
#include "GameObject.h"

class Menu : public State
{
private:
	Platform* platform;
	AssetManager* assetManager;
	AudioManager* audioManager;
	MouseData mouseData;
	Image* testImage;
	Uint16 bgTime;
	Uint32 lastBgTime;
	Button simpleButton;
	GameObject* obj;
public:
	Menu();
	void Input() override;
	void Update() override;
	void Draw() override;
	void Init() override;
	void Close() override;
	~Menu();
};