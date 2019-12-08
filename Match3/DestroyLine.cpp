#include "DestroyLine.h"

DestroyLine::DestroyLine(Vec2 pos, NodoG* node) : GameObject(6, "direction", pos, node) {
	onDestroy.LoadImage("dirDes");
	isSelected = false;
}

Vector<NodoG*>* DestroyLine::DeleteObjects() {
	if (!isSelected)
		return NULL;
	Vector<NodoG*>* toDelete;

	toDelete = new Vector<NodoG*>();

	if (movement.y == 0) {
		deleteLine(myNode, Vec2(0, 1), toDelete);
		deleteLine(myNode, Vec2(0, -1), toDelete);
	}
	else {
		deleteLine(myNode, Vec2(1, 0), toDelete);
		deleteLine(myNode, Vec2(-1, 0), toDelete);
	}
	toDelete->PushBack(myNode);
	return toDelete;
}

void DestroyLine::onDraw(bool s) {
	isSelected = s;
}

void DestroyLine::deleteLine(NodoG* r, Vec2 dir, Vector<NodoG*>* l) {
	NodoG* temp;
	for (int i = 0; i < r->list.size; i++) {
		temp = r->list.get_at(i);
		if (temp) {
			if (temp->position == r->position + dir) {
				if (!temp->obj->willDestroy())
					l->PushBack(temp);
				deleteLine(temp, dir, l);
				return;
			}
		}
	}
}