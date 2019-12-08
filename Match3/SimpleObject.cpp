#include "SimpleObject.h"

SimpleObject::SimpleObject(int id, string imageId, Vec2 pos, NodoG* node) : GameObject(id, imageId, pos, node) {
	SelectDestroy(id);
}

SimpleObject::SimpleObject(int id, string imageId, Vec2 iPos, Vec2 finalPos, NodoG* node) : GameObject(id, imageId, iPos, finalPos, node) {
	SelectDestroy(id);
}

void SimpleObject::SelectDestroy(int id) {
	switch (id) {
	case 0: onDestroy.LoadImage("arrDes");
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

bool SimpleObject::Update() {
	return true;
}

Vector<NodoG*>* SimpleObject::DeleteObjects() {
	List<NodoG*> l, toDestroy;
	Vector<NodoG*>* toDelete;

	int size = -1;
	toDelete = new Vector<NodoG*>();
	size += DeleteAround(myNode, Vec2(1, 0), &l);
	size += DeleteAround(myNode, Vec2(-1, 0), &l);
	if (size > 3)	
		toDestroy.Add(&l);
	l.clear();

	size = -1;
	size += DeleteAround(myNode, Vec2(0, 1), &l);
	size += DeleteAround(myNode, Vec2(0, -1), &l);
	if (size > 3)	
		toDestroy.Add(&l);

	if (toDestroy.size > 0){
		toDestroy.push_back(myNode);
		*toDelete = &toDestroy;
		return toDelete;
	} 
	return NULL;
}

int SimpleObject::DeleteAround(NodoG* r, Vec2 dir, List<NodoG*>* l) {
	NodoG* temp;
	for (int i = 0; i < r->list.size; i++) {
		temp = r->list.get_at(i);
		if (temp) {
			if (temp->position == r->position + dir) {
				if (temp->obj->GetId() == id) {
					if(!temp->obj->willDestroy())
						l->push_back(temp);
					
					return DeleteAround(temp, dir, l) + 1;
				}
			}
		}
	}
	return 1;
}
