#include "Graph.h"
#include <time.h>
#include <stdlib.h>

Graph::Graph() {
	platform = Platform::GetPtr();
	isVisitedCheck = true;
	insertNodes(8, 8);
	sprites.PushBack("arrow");
	sprites.PushBack("sword");
	sprites.PushBack("gem");
	sprites.PushBack("rupee");
	sprites.PushBack("coin");
	srand(time(NULL));
	fillEmpty(root);
	isVisitedCheck = !isVisitedCheck;
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
	r->obj = new GameObject(v, sprites.GetAt(v), r->position);
	r->visited = isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		fillEmpty(r->list.get_at(i));
	}
}

void Graph::Draw() {
	Draw(root);
	isVisitedCheck = !isVisitedCheck;
	platform->RenderImage(&board, boardPos);
}

void Graph::Draw(NodoG* r) {
	if (r->visited == isVisitedCheck)
		return;
	bool isSelected = selectedList.find(r);
	r->obj->Draw(isSelected);
	if (isSelected)
		platform->RenderImage(&onSelect, r->obj->GetPos());
	r->visited = isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		Draw(r->list.get_at(i));
	}
}

void Graph::Input(MouseData* mouseData) {
	Input(root, mouseData);
	isVisitedCheck = !isVisitedCheck;
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
	if (selectedList.size == 2) {
		if (canSwap()) {
			swapObjects(selectedList.first->value, selectedList.last->value);
			std::cout << "Can flip" << std::endl;
		}
		else {
			std::cout << "Can't fip" << std::endl;
		}
		selectedList.clear();
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
	n1->SetNewObject(n2->obj);
	n2->SetNewObject(objTemp);
}