#pragma once
#include "State.h"


class Menu : public State
{
private:
	Platform* platform;
	MouseData mouseData;
	Vector<Vec2> points;
public:
	Menu();
	void Input() override;
	void Update() override;
	void Draw() override;
	void Init() override;
	void Close() override;
	~Menu();
};