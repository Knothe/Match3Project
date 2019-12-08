#pragma once
#include <iostream>
#include "Platform.h"
#include "AssetManager.h"
#include "NodoG.h"

class NodoG;

class GameObject
{
protected:
	int id;											// *

	Platform* platform;								// *

	Image sprite;									// *
	Image onSelect;									// *
	Image onDestroy;								// *

	Vec2 offset;									// *
	Vec2 size;										// *
	Vec2 position;									// *
	Vec2 finalPosition;
	Vec2 movement;

	Uint16 frameTime;								// *
	Uint32 lastFrameTime = 0;						// *

	NodoG* myNode;

	bool isOver = false;							// *
	bool isDestroying;
	bool moving = false;

	bool MouseIsOver(MouseData* mouseData);			// *
public:
	virtual bool Input(MouseData* mouseData);		// *
	virtual bool Update();
	bool Draw(bool s);								// *
	void SetPos(Vec2 pos);							// *
	int GetId();
	void SetMovement(Vec2 iPos, Vec2 finalPos);
	void SetNewNode(NodoG* node);
	bool isMoving();
	Vec2 GetPos();									// *
	void Destroy();
	virtual Vector<NodoG*>* DeleteObjects();
	bool willDestroy();
	virtual void onDraw(bool s);
	GameObject(int id, string imageId, Vec2 pos, NodoG* node);
	GameObject(int id, string imageId, Vec2 iPos,Vec2 finalPos, NodoG* node);
	
	~GameObject();
};

