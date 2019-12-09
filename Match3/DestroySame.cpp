#include "DestroySame.h"
/*
Initializes object
@param pos: position in the graph
@param node: node that has this object
@param isvisited: pointer to the isvisitedCheck bool
*/
DestroySame::DestroySame(Vec2 pos, NodoG* node, bool* isVisited) : GameObject(6, "potion", pos, node) {
	onDestroy.LoadImage("potDes");
	isSelected = false;
	isVisitedCheck = isVisited;
}
/*
Checks all the objects available to delete
@return vector with the objects to delete
*/
Vector<NodoG*>* DestroySame::deleteObjects() {
	if (!isSelected)
		return NULL;
	Vector<NodoG*>* toDelete;
	Vec2 dir = movement.normalize();
	NodoG* temp;
	toDelete = new Vector<NodoG*>();
	for (int i = 0; i < myNode->list.size; i++) {
		temp = myNode->list.get_at(i);
		if (temp->position == myNode->position - dir) {
			idToDestroy = temp->obj->getId();
			break;
		}
	}
	deleteSame(myNode, toDelete);
	*isVisitedCheck = !*isVisitedCheck;
	toDelete->PushBack(myNode);
	return toDelete;
}
/*
Gets if the object is currently selected
@param s: if object is selected
*/
void DestroySame::onDraw(bool s) {
	isSelected = s;
}

void DestroySame::deleteSame(NodoG* r, Vector<NodoG*>* l) {
	if (r->visited == *isVisitedCheck)
		return;
	if (r->obj) {
		if (r->obj->getId() == idToDestroy)
			l->PushBack(r);
	}
	else
		std::cout << "Hola" << std::endl;
	r->visited = *isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		deleteSame(r->list.get_at(i), l);
	}
}