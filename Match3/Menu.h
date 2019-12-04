#pragma once
#include "State.h"

class Menu : public State
{
private:
	Platform* platform;
	int posX;
	int posY;
	bool right;
	bool left;
	bool down;
	bool up;
public:
	Menu();
	void Input() override;
	void Update() override;
	void Draw() override;
	void Init() override;
	void Close() override;
	~Menu();
};