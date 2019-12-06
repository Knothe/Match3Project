#include "NodoG.h"

NodoG::NodoG(GameObject* o, Vec2 pos) : obj(o), position(pos) {
	visited = false;
}

NodoG::NodoG(Vec2 pos) : position(pos) {
	visited = false;
	obj = NULL;
}

void NodoG::SetNewObject(GameObject* o) {
	obj = o;
	obj->SetPos(position);
}