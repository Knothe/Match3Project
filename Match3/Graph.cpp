#include "Graph.h"
#include <time.h>
#include <stdlib.h>
#include "SimpleObject.h"
#include "DestroyLine.h"
#include "DestroySame.h"

/*
Initializes all values in the graph
*/
Graph::Graph() {
	srand(time(NULL));
	platform = Platform::GetPtr();
	insertNodes(8, 8);
	sprites.PushBack("bow");
	sprites.PushBack("sword");
	sprites.PushBack("gem");
	sprites.PushBack("rupee");
	sprites.PushBack("coin");
	sprites.PushBack("wand");
	isVisitedCheck = true;
	fillEmpty(root);
	isVisitedCheck = !isVisitedCheck;
	board.LoadImage("board");
	boardPos = Vec2(platform->GetWitdth() - 512, (platform->GetHeight() / 2) - 237);
	onSelect.LoadImage("select");
}
/*

*/
Graph::~Graph() {

}
/*
Inserts and indicates links all nodes in the graph
@param x: size in x
@param y: size in y
*/
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
/*
Links 2 nodes toghether
*/
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
/*
Fills for the first time all of the graph
@param r: node to add an object
*/
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
/*
Checks if is playable and Updates al Objects
@param mouseData: data on the mouse status
*/
void Graph::Input(MouseData* mouseData) {
	if (!isMoving && !isDestroying)
		isPlayable = true;
	if (isPlayable) {
		Input(root, mouseData);
		isVisitedCheck = !isVisitedCheck;
	}

}
/*
Updates all game objects
@param r: pointer to the Node
@param mouseData: data on the mouse status
*/
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
/*
Updates all objects and the state of the board
*/
int Graph::Update() {
	bool updateScore;
	updateScore = checkState();
	destroyed = 0;
	Update(root);
	isVisitedCheck = !isVisitedCheck;
	if (isDestroying && destroyed == toDestroy)	isDestroying = false;
	if (!isPlayable && !isMoving && !isDestroying)	reFill();
	if (updateScore)	return toDestroy * 100;
	else		return 0;
}
/*
Updates all objects
@param r: pointer to the Node
*/
void Graph::Update(NodoG* r) {
	if (r->visited == isVisitedCheck)
		return;
	if (r->obj->Update())
		destroyed++;
	r->visited = isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		Update(r->list.get_at(i));
	}
}
/*
Starts the recursive function draw and checks the states at the end of the cycle
*/
void Graph::Draw() {
	platform->RenderImage(&board, boardPos);
	Draw(root);
	isVisitedCheck = !isVisitedCheck;
}
/*
Recursively draws everything and checks
*/
void Graph::Draw(NodoG* r) {
	if (r->visited == isVisitedCheck)
		return;
	bool isSelected = selectedList.find(r);
	r->obj->Draw(isSelected);
	if(isSelected)
		platform->RenderImage(&onSelect, r->obj->getPos());
	r->visited = isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		Draw(r->list.get_at(i));
	}
}
/*
Checks the current state of the game
@return true if player scored points
*/
bool Graph::checkState() {
	bool updateScore = false;
	if (isPlayable) {
		if (selectedList.size == 2) {
			if (canSwap()) {
				isMoving = true;
				isPlayable = false;
				swapObjects(selectedList.first->value, selectedList.last->value);
			}
			else	selectedList.clear();
		}
	}
	else {
		if (isMoving) {
			if (hasFinishedMoving()) {
				addToDestroy();
				if (destroyList.size > 0) {
					isDestroying = true;
					updateScore = true;
				}
				else		isPlayable = true;
				isMoving = false;
			}
		}
	}
	return updateScore;
}
/*
Checks if you can swap 2 objects of place
@return true if swap is posible
*/
bool Graph::canSwap() {
	NodoG* temp = selectedList.first->value;
	for (int i = 0; i < temp->list.size; i++) {
		if (temp->list.get_at(i) == selectedList.last->value)
			return true;
	}
	return false;
}
/*
Swaps 2 objects
@param n1, n2: Nodes to swap 
*/
void Graph::swapObjects(NodoG* n1, NodoG* n2) {
	GameObject* objTemp;
	objTemp = n1->obj;
	n1->SetNewObject(n2->obj, n2->position);
	n2->SetNewObject(objTemp, n1->position);
}
/*
If we have items selected, we check if those finished moving
If a lot of things are moving, we check everything
@return true if objects finished moving
*/
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
/*
Checks each object if it finished moving
@param r: node to check
@return true if objects finished moving
*/
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
/*
Adds objects to the destroyList, for destroying later
*/
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
/*
Recursively adds objects to the destroyList
*/
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
/*
Refills the entire graph
*/
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
/*
Orders all the nodes and adds new objects if needed
@param l: empty list that will carry resulting objects
*/
void Graph::orderNodes(List<NodoG*>* l) {
	NodeL<NodoG*>* it = destroyList.first;
	Vector<NodoG*> vector;
	int x;
	while (it) {
		x = it->value->obj->getId();
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
	getLowest(l, vector);
}
/*
Filters empty lowest points on the graph
@param l: empty list that will carry resulting objects
@param v: vector with the ordered deleted nodes
*/
void Graph::getLowest(List<NodoG*>* l, Vector<NodoG*> v) {
	int x = -1;
	NodoG* n;
	for (int i = 0; i < v.GetSize(); i++) {
		n = v.GetAt(i);
		if (n->obj)		break;
		if (n->position.x != x) {
			x = n->position.x;
			l->push_back(n);
		}
	}
}
/*
Refills all of the graph
@param n: Node to fill
@param b: positions away from the actual position, start with -1
*/
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
		NodoG* temp = searchObj(next);
		if (temp) {
			n->SetNewObject(temp->obj, temp->position);
			temp->obj = NULL;
			fillUp(next, -1);
			return;
		}
		b = n->position.y + 3;
	}
	int v = rand() % sprites.GetSize();
	n->obj = new SimpleObject(v, sprites.GetAt(v), n->position - Vec2(0, b), n->position, n);
	fillUp(next, b);
}
/*
Searchs an object to fall to its position
@param n: node to check
@return node if it has an object
*/
NodoG* Graph::searchObj(NodoG* n) {
	if (!n)			return NULL;
	if (n->obj)		return n;
	NodoG* next = NULL;
	for (int i = 0; i < n->list.size; i++) {
		if (n->list.get_at(i)->position.y < n->position.y) {
			next = n->list.get_at(i);
			break;
		}
	}
	return searchObj(next);
}
/*
Resets all visited places, when we didnt visited all the graph
@param r: Node to reset
*/
void Graph::resetVisited(NodoG* r) {
	if (r->visited != isVisitedCheck)		return;
	r->visited = !isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		resetVisited(r->list.get_at(i));
	}
}
