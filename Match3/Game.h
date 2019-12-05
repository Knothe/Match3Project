#pragma once
#include "State.h"

class Game : public State
{
private:
	Platform* platform;
	MouseData mouseData;
	Image* testImage;
	Uint16 bgTime;
	Uint32 lastBgTime;

public:
	Game();
	void Input() override;
	void Update() override;
	void Draw() override;
	void Init() override;
	void Close() override;
	~Game();
};

