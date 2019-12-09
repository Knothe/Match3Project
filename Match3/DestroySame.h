#pragma once
#include "GameObject.h"

class DestroySame : public GameObject
{
private:
	bool* isVisitedCheck;
	int idToDestroy;
	bool isSelected;
	void deleteSame(NodoG* r, Vector<NodoG*>* l);
	void onDraw(bool s);
public:
	DestroySame(Vec2 pos, NodoG* node, bool* isVisited);
	Vector<NodoG*>* deleteObjects();
};

