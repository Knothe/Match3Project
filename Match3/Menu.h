#pragma once
#include "State.h"
#include "Button.h"


class Menu : public State
{
private:
	Platform* platform;
	MouseData mouseData;
	Image* testImage;
	Uint16 bgTime;
	Uint32 lastBgTime;
	Button simpleButton;

public:
	Menu();
	void Input() override;
	void Update() override;
	void Draw() override;
	void Init() override;
	void Close() override;
	~Menu();
};