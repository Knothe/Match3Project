#include "NodoG.h"

NodoG::NodoG(GameObject* o, Vec2 pos) : obj(o), position(pos) {
	visited = false;
}

NodoG::NodoG(Vec2 pos) : position(pos) {
	visited = false;
	obj = NULL;
}

void NodoG::SetNewObject(GameObject* o, Vec2 oldPos) {
	obj = o;
	obj->SetMovement(oldPos, position);
	obj->SetNewNode(this);
}

bool NodoG::CreateListObject() {
	if (obj->willDestroy())
		return false;
	toDelete = obj->DeleteObjects();
	if (toDelete) {
		ApplyDestruction();
		return true;
	}
	return false;
}

void NodoG::ApplyDestruction() {
	for (int i = 0; i < toDelete->GetSize(); i++) {
		toDelete->GetAt(i)->obj->Destroy();
	}
}

bool NodoG::operator<(NodoG other) {
	if (obj == other.obj) {
		if (position.x == other.position.x) {
			if (position.y < other.position.y)	return true;
		}
		else {
			if (position.x < other.position.x)	return true;
		}
	}
	else {
		if (obj)	return true;
	}
	
	return false;
}