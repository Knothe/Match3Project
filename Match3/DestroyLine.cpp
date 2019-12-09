#include "DestroyLine.h"

/*
Initializes variables of the object
@param pos: position of the object
@param node: node where it will be stored
*/
DestroyLine::DestroyLine(Vec2 pos, NodoG* node) : GameObject(6, "direction", pos, node) {
	onDestroy.LoadImage("dirDes");
	isSelected = false;
}
/*
Creates a list with the nodes that will have their object deleted, dependinig on how you move this tile
@return vector with the nodes
*/
Vector<NodoG*>* DestroyLine::deleteObjects() {
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
/*
When the Draw function is called, it will save isSelected
@param s: if is selected
*/
void DestroyLine::onDraw(bool s) {
	isSelected = s;
}
/*
Adds the entire line to the list
@param r: Node to delete
@param dir: direction to delete
@param l: Vector with all the nodes to delete
*/
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