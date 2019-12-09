#pragma once
#include "State.h"
#include "Text.h"

class HighScoreMenu : public State
{
private:
	Platform* platform;
	AssetManager* assetManager;
	Image backGround;
	Text* title;
	Vector<Text*> scores;
public:
	HighScoreMenu();
	void Input() override;
	void Update() override;
	void Draw() override;
	void Init() override;
	void Close() override;
	~HighScoreMenu();
};

