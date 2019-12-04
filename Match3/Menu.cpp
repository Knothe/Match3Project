#include "Menu.h"
Menu::Menu() {
	posX = 0;
	posY = 100;
	right = false;
	left = false;
	down = false;
	up = false;
}
void Menu::Input() {
	Vector<int> keysDown;
	Vector<int> keysUp;
	platform->CheckEvent(&keysDown, &keysUp);
	for (int i = 0; i < keysDown.GetSize(); i++) {
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
	}
}

void Menu::Update() {
	if (right)
		posX += 2;
	if (left)
		posX -= 2;
	if (up)
		posY -= 2;
	if (down)
		posY += 2;
}

void Menu::Draw() {
	platform->RenderClear();
	platform->DrawRect(posX, posY, 100, 100);
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