#include "GameManager.h"
GameManager* GameManager::ptr;

GameManager::GameManager() {
	platform = Platform::GetPtr();
}
GameManager* GameManager::getPtr() {
	if (!ptr)
		ptr = new GameManager();
	return ptr;
}
void GameManager::SetState(State* state) {
	state->Init();
	statesStack.Push(state);
}
void GameManager::GameLoop() {
	while (true) {
		try {
			if (statesStack.GetSize() == 0)
				throw 0;
			auto estado = statesStack.Top();
			estado->Input(); // Possible Modifications
			estado->Update();
			estado->Draw();
			if (!estado->GetState())
				ReleaseState();
		} catch (int e) {
			break;
		} catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}
	}
}
void GameManager::ReleaseState() {
	State* s = statesStack.Top();
	s->Close();
	statesStack.Pop();
}
GameManager::~GameManager() {

}