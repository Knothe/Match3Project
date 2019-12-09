#include "NodoG.h"
/*
Initializes the Node
@param o: object to save in the node
@param pos: position in graph
*/
NodoG::NodoG(GameObject* o, Vec2 pos) : obj(o), position(pos) {
	visited = false;
}
/*
Initializes the Node
@param pos: position in graph
*/
NodoG::NodoG(Vec2 pos) : position(pos) {
	visited = false;
	obj = NULL;
}
/*
Adds a new object to the node
@param o: object to add
@param oldPos: old position of this object
*/
void NodoG::SetNewObject(GameObject* o, Vec2 oldPos) {
	obj = o;
	obj->setMovement(oldPos, position);
	obj->setNewNode(this);
}
/*
Creates list of objects to destroy
@return true if the list was created
*/
bool NodoG::CreateListObject() {
	if (obj->willDestroy())
		return false;
	toDelete = obj->deleteObjects();
	if (toDelete) {
		for (int i = 0; i < toDelete->GetSize(); i++) {
			toDelete->GetAt(i)->obj->destroy();
		}
		return true;
	}
	return false;
}
/*
Checks if a node is over another one
@param other: other node to compare
@return true if this is under other
*/
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