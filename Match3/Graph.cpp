#include "Graph.h"
#include <time.h>
#include <stdlib.h>
#include "SimpleObject.h"
#include "DestroyLine.h"
#include "DestroySame.h"

Graph::Graph() {
	platform = Platform::GetPtr();
	isVisitedCheck = true;
	insertNodes(8, 8);
	sprites.PushBack("bow");
	sprites.PushBack("sword");
	sprites.PushBack("gem");
	sprites.PushBack("rupee");
	sprites.PushBack("coin");
	sprites.PushBack("wand");
	srand(time(NULL));
	fillEmpty(root);
	isVisitedCheck = !isVisitedCheck;
	isMoving = true;
	isPlayable = false;
	board.LoadImage("board");
	boardPos.x = platform->GetWitdth() - 512;
	boardPos.y = (platform->GetHeight() / 2) - 237;
	onSelect.LoadImage("select");
}

Graph::~Graph() {

}

void Graph::insertNodes(int x, int y) {
	Vector<Vector<NodoG*>*> nodes;
	for (int i = 0; i < x; i++) {
		nodes.PushBack(new Vector<NodoG*>(y));
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			nodes.GetAt(i)->PushAt(j, new NodoG(Vec2(i, j)));
			if (i > 0)		connectNodes(nodes.GetAt(i - 1)->GetAt(j), nodes.GetAt(i)->GetAt(j));
			if (i < x - 1)	connectNodes(nodes.GetAt(i + 1)->GetAt(j), nodes.GetAt(i)->GetAt(j));
			if (j > 0)		connectNodes(nodes.GetAt(i)->GetAt(j - 1), nodes.GetAt(i)->GetAt(j));
			if (j < y - 1)	connectNodes(nodes.GetAt(i)->GetAt(j + 1), nodes.GetAt(i)->GetAt(j));
		}
	}
	root = nodes.GetAt(0)->GetAt(0);
}

void Graph::connectNodes(NodoG* node1, NodoG* node2) {
	try {
		if (node1 && node2) {
			node1->list.push_back(node2);
			node2->list.push_back(node1);
		}
	}
	catch (std::exception e) {
		std::cout << "Error Graph connect Nodes: " << e.what() << std::endl;
	}
	
}

void Graph::fillEmpty(NodoG* r) {
	if (r->visited == isVisitedCheck)
		return;
	int v = rand() % sprites.GetSize();
	r->obj = new SimpleObject(v, sprites.GetAt(v), r->position - Vec2(0, 10), r->position, r);
	r->visited = isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		fillEmpty(r->list.get_at(i));
	}
}

void Graph::Draw() {
	destroyed = 0;
	Draw(root);
	isVisitedCheck = !isVisitedCheck;
	platform->RenderImage(&board, boardPos);
	if (isDestroying && destroyed == toDestroy)	
		isDestroying = false;
	if (!isPlayable && !isMoving && !isDestroying)
		reFill();
}

void Graph::Draw(NodoG* r) {
	if (r->visited == isVisitedCheck)
		return;
	bool isSelected = selectedList.find(r);
	if (r->obj->Draw(isSelected)) 
		destroyed++;
	else if (isSelected)
		platform->RenderImage(&onSelect, r->obj->GetPos());
	r->visited = isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		Draw(r->list.get_at(i));
	}
}

void Graph::Input(MouseData* mouseData) {
	if (!isMoving && !isDestroying)
		isPlayable = true;
	if (isPlayable) {
		Input(root, mouseData);
		isVisitedCheck = !isVisitedCheck;
	}
	
}

void Graph::Input(NodoG* r, MouseData* mouseData) {
	if (r->visited == isVisitedCheck)
		return;
	if (r->obj->Input(mouseData)) {
		if (!selectedList.find(r))
			selectedList.push_back(r);
	}
	r->visited = isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		Input(r->list.get_at(i), mouseData);
	}
}

void Graph::Update() {
	if (isPlayable) {
		if (selectedList.size == 2) {
			if (canSwap()) {
				isMoving = true;
				isPlayable = false;
				swapObjects(selectedList.first->value, selectedList.last->value);
			}else	selectedList.clear();
		}
	}
	else {
		if (isMoving) {
			if (hasFinishedMoving()) {
				addToDestroy();
				if (destroyList.size > 0)	isDestroying = true;
				else		isPlayable = true;
				isMoving = false;
			}
		}
	}
	//Update(root);
	//isVisitedCheck = !isVisitedCheck;
	
}

void Graph::addToDestroy() {
	toDestroy = 0;
	if (selectedList.first) {
		NodeL<NodoG*>* it;
		it = selectedList.first;
		while (it) {
			if (it->value->CreateListObject()) {
				destroyList.push_back(it->value);
				toDestroy += it->value->toDelete->GetSize();
			}
			it = it->next;
		}
		selectedList.clear();
	}
	else {
		addToDestroy(root);
		isVisitedCheck = !isVisitedCheck;
	}

}

void Graph::addToDestroy(NodoG* r) {
	if (r->visited == isVisitedCheck)		return;
	r->visited = isVisitedCheck;
	if (r->CreateListObject()) {
		destroyList.push_back(r);
		toDestroy += r->toDelete->GetSize();
	}
	for (int i = 0; i < r->list.size; i++) {
		addToDestroy(r->list.get_at(i));
	}
}

bool Graph::hasFinishedMoving() {
	if (selectedList.first) {
		NodeL<NodoG*>* it;
		it = selectedList.first;
		while (it) {
			if (it->value->obj->isMoving())
				return false;
			it = it->next;
		}
		return true;
	}
	else {
		bool b = hasFinishedMoving(root);
		resetVisited(root);
		return b;
	}
	
}

bool Graph::hasFinishedMoving(NodoG* r) {
	if (r->visited == isVisitedCheck)
		return true;
	r->visited = isVisitedCheck;
	if (r->obj) {
		if (r->obj->isMoving()) 	return false;
	}
	else
		std::cout << "Aiuda" << std::endl;
		
	for (int i = 0; i < r->list.size; i++) {
		if (!hasFinishedMoving(r->list.get_at(i)))
			return false;
	}
	return true;
}

void Graph::resetVisited(NodoG* r) {
	if (r->visited != isVisitedCheck)		return;
	r->visited = !isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		resetVisited(r->list.get_at(i));
	}
}

void Graph::reFill() {
	List<NodoG*>* list = new List<NodoG*>();
	orderNodes(list);
	NodeL<NodoG*>* it = list->first;
	while (it) {
		fillUp(it->value, -1);
		it = it->next;
	}
	isMoving = true;
	isPlayable = false;
	destroyList.clear();
}

void Graph::fillUp(NodoG* n, int b){
	if (!n) return;
	NodoG* next = NULL;
	for (int i = 0; i < n->list.size; i++) {
		if (n->list.get_at(i)->position.y < n->position.y) {
			next = n->list.get_at(i);
			break;
		}
	}
	if (b == -1) {
		NodoG* temp = NULL;
		temp = searchObj(next);
		if (temp) {
			n->SetNewObject(temp->obj, temp->position);
			temp->obj = NULL;
			fillUp(next, -1);
			return;
		}
		else	b = n->position.y + 3;
	}
	int v = rand() % sprites.GetSize();
	n->obj = new SimpleObject(v, sprites.GetAt(v), n->position - Vec2(0, b), n->position, n);
	fillUp(next, b);
}

NodoG* Graph::searchObj(NodoG* n) {
	if (!n)
		return NULL;
	if (n->obj)
		return n;
	NodoG* next = NULL;
	for (int i = 0; i < n->list.size; i++) {
		if (n->list.get_at(i)->position.y < n->position.y) {
			next = n->list.get_at(i);
			break;
		}
	}
	return searchObj(next);
}

void Graph::orderNodes(List<NodoG*>* l) {
	Vector<NodoG*> vector;
	NodeL<NodoG*>* it = destroyList.first;
	int x;
	while (it) {
		x = it->value->obj->GetId();
		for (int i = 0; i < it->value->toDelete->GetSize(); i++)
			it->value->toDelete->GetAt(i)->obj = NULL;
		if (x < 6) {
			if (it->value->toDelete->GetSize() == 5)
				it->value->obj = new DestroyLine(it->value->position, it->value);
			if (it->value->toDelete->GetSize() > 5)
				it->value->obj = new DestroySame(it->value->position, it->value, &isVisitedCheck);
		}
		
		
		vector + it->value->toDelete;
		it = it->next;
	}
	vector.order();
	x = -1;
	NodoG* n;
	for (int i = 0; i < vector.GetSize(); i++) {
		n = vector.GetAt(i);
		if (n->obj) 
			break;
		if (n->position.x != x) {
			x = n->position.x;
			l->push_back(n);
		}
	}
}

void Graph::Update(NodoG* r) {
	if (r->visited == isVisitedCheck)
		return;
	r->obj->Update();
	r->visited = isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		Update(r->list.get_at(i));
	}
}

bool Graph::canSwap() {
	NodoG* temp = selectedList.first->value;
	for (int i = 0; i < temp->list.size; i++) {
		if (temp->list.get_at(i) == selectedList.last->value)
			return true;
	}
	return false;
}

void Graph::swapObjects(NodoG* n1, NodoG* n2) {
	GameObject* objTemp;
	objTemp = n1->obj;
	n1->SetNewObject(n2->obj, n2->position);
	n2->SetNewObject(objTemp, n1->position);
}