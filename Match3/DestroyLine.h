#pragma once
#include "GameObject.h"

class DestroyLine : public GameObject
{
private:
	bool isSelected;
	void deleteLine(NodoG* r, Vec2 dir, Vector<NodoG*>* l);
	void onDraw(bool s);
public:
	DestroyLine(Vec2 pos, NodoG* node);
	Vector<NodoG*>* DeleteObjects();

};

