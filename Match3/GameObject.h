#pragma once
#include <iostream>
#include "Platform.h"
#include "AssetManager.h"
#include "NodoG.h"

class NodoG;

class GameObject
{
protected:
	int id;											

	Platform* platform;

	Image sprite;	
	Image onSelect;	
	Image onDestroy;

	Vec2 offset;
	Vec2 size;
	Vec2 position;
	Vec2 finalPosition;
	Vec2 movement;

	Uint16 frameTime;
	Uint32 lastFrameTime = 0;

	NodoG* myNode;

	bool isOver = false;
	bool isDestroying;
	bool moving = false;

	bool MouseIsOver(MouseData* mouseData);
public:

	GameObject(int id, string imageId, Vec2 pos, NodoG* node);
	GameObject(int id, string imageId, Vec2 iPos, Vec2 finalPos, NodoG* node);
	~GameObject();

	bool Input(MouseData* mouseData);
	bool Update();
	void Draw(bool s);

	void setPos(Vec2 pos);
	void setMovement(Vec2 iPos, Vec2 finalPos);
	void setNewNode(NodoG* node);

	int getId();
	Vec2 getPos();
	bool isMoving();
	bool willDestroy();

	virtual void onDraw(bool s);
	virtual Vector<NodoG*>* deleteObjects() = 0;
	void destroy();
};

