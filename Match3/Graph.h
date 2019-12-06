#pragma once
#include "NodoG.h"
#include "Vector.h"

class Graph
{
public:
	Graph();
	void Draw();
	void Input(MouseData* mouseData);
	~Graph();
private:
	NodoG* root;
	Vector<string> sprites;
	int count;
	bool isVisitedCheck;
	void insertNodes(int x, int y);
	void connectNodes(NodoG* node1, NodoG* node2);
	void fillEmpty(NodoG* r);
	void Draw(NodoG* r);
	void Input(NodoG* r, MouseData* mouseData);
};

