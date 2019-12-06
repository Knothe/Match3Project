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
	Button(std::string imageLoc1, std::string imageLoc2, Vec2 pos);
	bool Update(MouseData* mouseData);
	void Draw();
	void Init(std::string imageLoc1, std::string imageLoc2, Vec2 pos);
	void SetPos(Vec2 pos);
	~Button();
};

