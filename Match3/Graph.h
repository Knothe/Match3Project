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
	bool isMoving = false;
	bool isDestroying = false;
	bool isPlayable = true;
	int toDestroy;
	int destroyed;

	List<NodoG*> selectedList;
	List<NodoG*> destroyList;
	Image onSelect;

	void insertNodes(int x, int y);
	void connectNodes(NodoG* node1, NodoG* node2);
	void fillEmpty(NodoG* r);
	void Draw(NodoG* r);
	void Input(NodoG* r, MouseData* mouseData);
	void Update(NodoG* r);
	bool canSwap();
	void swapObjects(NodoG* n1, NodoG* n2);
	bool hasFinishedMoving();
	bool hasFinishedMoving(NodoG* r);
	void addToDestroy();
	void addToDestroy(NodoG* r);
	void resetVisited(NodoG* r);
	void reFill();
	void orderNodes(List<NodoG*>* l);
	void fillUp(NodoG* n, int b);
	NodoG* searchObj(NodoG* n);
};

