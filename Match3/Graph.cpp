#include "Graph.h"
#include <time.h>
#include <stdlib.h>

Graph::Graph() {
	isVisitedCheck = true;
	insertNodes(8, 8);
	sprites.PushBack("as");
	sprites.PushBack("r");
	sprites.PushBack("s");
	sprites.PushBack("g");
	fillEmpty(root);
	isVisitedCheck = !isVisitedCheck;
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
}

void Graph::Draw(NodoG* r) {
	if (r->visited == isVisitedCheck)
		return;
	r->obj->Draw();
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
	r->obj->Input(mouseData);
	r->visited = isVisitedCheck;
	for (int i = 0; i < r->list.size; i++) {
		Input(r->list.get_at(i), mouseData);
	}
}