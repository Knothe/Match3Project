#include "Menu.h"
Menu::Menu() {

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
}

void Menu::Draw() {
	platform->RenderClear();
	for (int i = 0; i < points.GetSize(); i++)
		platform->DrawPoint(points.GetAt(i));
	platform->RenderPresent();
}

void Menu::Init() {
	platform = Platform::GetPtr();
}

void Menu::Close() {
	state = false;
}

Menu::~Menu() {

}