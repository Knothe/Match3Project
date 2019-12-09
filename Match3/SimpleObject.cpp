#include "SimpleObject.h"
/*
Initializes the object
@param id: id of the object
@param imageId: id of the image
@param pos: position in graph
@param node: node that will save it
*/
SimpleObject::SimpleObject(int id, string imageId, Vec2 pos, NodoG* node) : GameObject(id, imageId, pos, node) {
	selectDestroy(id);
}
/*
Initializes the object
@param id: id of the object
@param imageId: id of the image
@param iPos: initial position relative to graph
@param finalPos: position in graph
@param node: node that will save it
*/
SimpleObject::SimpleObject(int id, string imageId, Vec2 iPos, Vec2 finalPos, NodoG* node) : GameObject(id, imageId, iPos, finalPos, node) {
	selectDestroy(id);
}
/*
Selects the image when destroying
@param id: of the object
*/
void SimpleObject::selectDestroy(int id) {
	switch (id) {
	case 0: onDestroy.LoadImage("bowDes");
		break;
	case 1: onDestroy.LoadImage("swoDes");
		break;
	case 2: onDestroy.LoadImage("gemDes");
		break;
	case 3: onDestroy.LoadImage("rupDes");
		break;
	case 4: onDestroy.LoadImage("coiDes");
		break;
	case 5: onDestroy.LoadImage("wanDes");
		break;
	}
}
/*
Selects the objects to destroy
@return vector with objects to destroy
*/
Vector<NodoG*>* SimpleObject::deleteObjects() {
	List<NodoG*> l, toDestroy;
	Vector<NodoG*>* toDelete;
	int size = -1;
	toDelete = new Vector<NodoG*>();
	size += deleteAround(myNode, Vec2(1, 0), &l);
	size += deleteAround(myNode, Vec2(-1, 0), &l);
	if (size > 3)		toDestroy.Add(&l);
	l.clear();
	size = -1;
	size += deleteAround(myNode, Vec2(0, 1), &l);
	size += deleteAround(myNode, Vec2(0, -1), &l);
	if (size > 3)		toDestroy.Add(&l);
	if (toDestroy.size > 0){
		toDestroy.push_back(myNode);
		*toDelete = &toDestroy;
		return toDelete;
	} 
	return NULL;
}
/*
Adds nodes to the list and counts how many there are
@param r: Node to check
@param dir: direction to check
@param l: list to add
@return number of added objects + 1
*/
int SimpleObject::deleteAround(NodoG* r, Vec2 dir, List<NodoG*>* l) {
	NodoG* temp;
	for (int i = 0; i < r->list.size; i++) {
		temp = r->list.get_at(i);
		if (temp) {
			if (temp->position == r->position + dir) {
				if (temp->obj->getId() == id) {
					if(!temp->obj->willDestroy())
						l->push_back(temp);
					
					return deleteAround(temp, dir, l) + 1;
				}
			}
		}
	}
	return 1;
}
