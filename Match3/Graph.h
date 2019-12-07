#pragma once
#include "NodoG.h"
#include "Vector.h"

class Graph
{
public:
	Graph();
	void Draw();
	void Input(MouseData* mouseData);
	void Update();

	~Graph();
private:
	NodoG* root;
	Vector<string> sprites;
	Image board;
	Vec2 boardPos;
	Platform* platform;
	bool isVisitedCheck;
	List<NodoG*> selectedList;
	Image onSelect;

	void insertNodes(int x, int y);
	void connectNodes(NodoG* node1, NodoG* node2);
	void fillEmpty(NodoG* r);
	void Draw(NodoG* r);
	void Input(NodoG* r, MouseData* mouseData);
	bool canSwap();
	void swapObjects(NodoG* n1, NodoG* n2);
};

