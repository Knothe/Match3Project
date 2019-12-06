#pragma once
#include <iostream>
#include "Platform.h"
#include "AssetManager.h"

class GameObject
{
protected:
	Platform* platform;
	Image sprite;
	int id;
	Vec2 offset;
	Vec2 size;
	Vec2 position;
	bool isOver = false;	
	Uint16 frameTime;
	Uint32 lastFrameTime = 0;
	bool MouseIsOver(MouseData* mouseData);
public:
	void Input(MouseData* mouseData);
	bool Update();
	void Draw();
	void SetPos(Vec2 pos);
	GameObject();
	GameObject(int id, string imageId);
	GameObject(int id, string imageId, Vec2 pos);
	~GameObject();
};

