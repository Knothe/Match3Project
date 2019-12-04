#include "GameManager.h"
#include "Menu.h"
#include "MouseData.h"

int main()
{
	GameManager* gameM;
	gameM = GameManager::getPtr();
	gameM->SetState(new Menu());
	gameM->GameLoop();
}
