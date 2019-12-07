#pragma once
#include <iostream>
#include "Platform.h"
#include "AssetManager.h"
#include "NodoG.h"

class NodoG;

class GameObject
{
protected:
	Platform* platform;								// *
	Image sprite;									// *
	Image onSelect;									// *
	Image onDestroy;								// *
	int id;											// *
	Vec2 offset;									// *
	Vec2 size;										// *
	Vec2 position;									// *
	bool isOver = false;							// *
	Uint16 frameTime;								// *
	Uint32 lastFrameTime = 0;						// *
	bool isDestroying;
	bool MouseIsOver(MouseData* mouseData);			// *
public:
	virtual bool Input(MouseData* mouseData);		// *
	bool Draw(bool s);								// *
	void SetPos(Vec2 pos);							// *
	Vec2 GetPos();									// *
	GameObject(int id, string imageId, Vec2 pos);
	~GameObject();
};

