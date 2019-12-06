#pragma once
#include "List.h"
#include "GameObject.h"

class NodoG
{
public:
	GameObject* obj;
	bool visited;
	Vec2 position;
	List<NodoG*> list;
	NodoG(GameObject* o, Vec2 pos);
	NodoG(Vec2 pos);
	void SetNewObject(GameObject* o);
};

