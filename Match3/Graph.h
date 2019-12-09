#pragma once
#include "NodoG.h"
#include "Vector.h"

class Graph
{
public:
	Graph();

	void Input(MouseData* mouseData);
	int Update();
	void Draw();
	~Graph();
private:
	Platform* platform;

	NodoG* root;

	Vector<string> sprites;

	Image board;

	Vec2 boardPos;

	bool isVisitedCheck;
	bool isMoving = true;
	bool isDestroying = false;
	bool isPlayable = false;

	int toDestroy;
	int destroyed;

	List<NodoG*> selectedList;
	List<NodoG*> destroyList;

	Image onSelect;

	void insertNodes(int x, int y);
	void connectNodes(NodoG* node1, NodoG* node2);
	void fillEmpty(NodoG* r);

	void Input(NodoG* r, MouseData* mouseData);
	void Update(NodoG* r);
	void Draw(NodoG* r);
	
	bool checkState();
	bool canSwap();
	void swapObjects(NodoG* n1, NodoG* n2);

	bool hasFinishedMoving();
	bool hasFinishedMoving(NodoG* r);

	void addToDestroy();
	void addToDestroy(NodoG* r);

	void reFill();
	void orderNodes(List<NodoG*>* l);
	void getLowest(List<NodoG*>* l, Vector<NodoG*> v);
	void fillUp(NodoG* n, int b);

	NodoG* searchObj(NodoG* n);
	void resetVisited(NodoG* r);
};

