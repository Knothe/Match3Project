#pragma once
#include "State.h"
#include "Stack.h"

class State;

class GameManager
{
private:
	Stack<State*> statesStack;
	Platform* platform;
	GameManager();
	static GameManager* ptr;
public:
	static GameManager* getPtr();
	void SetState(State* state);
	void GameLoop();
	void ReleaseState();
	~GameManager();
};

