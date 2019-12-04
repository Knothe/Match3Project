#include "Menu.h"
Menu::Menu() {
	bgTime = 300;
	lastBgTime = SDL_GetTicks();
}
void Menu::Input() {
	Vector<int> keysDown;
	Vector<int> keysUp;
	platform->CheckEvent(&keysDown, &keysUp, &mouseData);
	/*for (int i = 0; i < keysDown.GetSize(); i++) {
		switch (keysDown.GetAt(i)) {
		case SDLK_ESCAPE:
			state = false;
			break;
		case SDLK_RIGHT: right = true;
			break;
		case SDLK_LEFT: left = true;
			break;
		case SDLK_UP: up = true;
			break;
		case SDLK_DOWN: down = true;
			break;

		}
	}
	for (int i = 0; i < keysUp.GetSize(); i++) {
		switch (keysUp.GetAt(i)) {
		case SDLK_RIGHT: right = false;
			break;
		case SDLK_LEFT: left = false;
			break;
		case SDLK_UP: up = false;
			break;
		case SDLK_DOWN: down = false;
			break;

		}
	}*/

	if (mouseData.leftButton)
		points.PushBack(mouseData.position);

	mouseData.leftButton = false;
	mouseData.rightButton = false;
}

void Menu::Update() {
	if (SDL_TICKS_PASSED(SDL_GetTicks(), lastBgTime + bgTime))
	{
		lastBgTime = SDL_GetTicks();
		testImage->NextFrame();
	}
}

void Menu::Draw() {
	platform->RenderClear();
	for (int i = 0; i < points.GetSize(); i++)
		platform->DrawPoint(points.GetAt(i));

	platform->RenderImage(testImage, 0, 0);

	platform->RenderPresent();
}

void Menu::Init() {
	platform = Platform::GetPtr();
	testImage = new Image();
	testImage->LoadImage("Assets/Images/Arrow-Sheet.png", 4,1);
}

void Menu::Close() {
	state = false;
}

Menu::~Menu() {

}