#pragma once
#include "GameObject.h"

class SimpleObject : public GameObject
{
private:
	int totalDestroy = 0;
	int currentLine = 0;
	void SelectDestroy(int id);
	int deleteAround(NodoG* r, Vec2 dir, List<NodoG*>* l);
public:
	SimpleObject(int id, string imageId, Vec2 pos, NodoG* node);
	SimpleObject(int id, string imageId, Vec2 iPos, Vec2 finalPos, NodoG* node);
	Vector<NodoG*>* DeleteObjects();
};

