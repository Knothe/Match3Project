#include "DestroySame.h"
DestroySame::DestroySame(Vec2 pos, NodoG* node, bool* isVisited) : GameObject(6, "potion", pos, node) {
	onDestroy.LoadImage("potDes");
	isSelected = false;
	isVisitedCheck = isVisited;
}


Vector<NodoG*>* DestroySame::DeleteObjects() {
	if (!isSelected)
		return NULL;
	Vector<NodoG*>* toDelete;
	Vec2 dir = movement.normalize();
	NodoG* temp;
	toDelete = new Vector<NodoG*>();
	for (int i = 0; i < myNode->list.size; i++) {
		temp = myNode->list.get_at(i);
		if (temp->position == myNode->position - dir) {
			idToDestroy = temp->obj->GetId();
			break;
		}
	}
	deleteSame(myNode, toDelete);
	*isVisitedCheck = !*isVisitedCheck;
	toDelete->PushBack(myNode);
	return toDelete;
}

void DestroySame::onDraw(bool s) {
	isSelected = s;
}


void DestroySame::deleteSame(NodoG* r, Vector<NodoG*>* l) {
	if (r->visited == *isVisitedCheck)
		return;
	if (r->obj) {
		if (r->obj->GetId() == idToDestroy)
			l->PushBack(r);
	}
	else
		std::cout << "Hola" << std::endl;
	r->visited = *isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		deleteSame(r->list.get_at(i), l);
	}
}