#pragma once
#include "Platform.h"
#include "AssetManager.h"
#include <string>
#include <iostream>

class Button
{
private:
	Image plainImage;
	Image hoverImage;
	Vec2 position;
	Vec2 size;
	bool isOver;
	Platform* platform;
public:
	Button();
	Button(string imageLoc1, string imageLoc2, Vec2 pos);
	bool Update(MouseData* mouseData);
	void Draw();
	void Init(string imageLoc1, string imageLoc2, Vec2 pos);
	void SetPos(Vec2 pos);
	~Button();
};

