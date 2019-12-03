#include "Menu.h"
Menu::Menu() {

}
void Menu::Input() {

}

void Menu::Update() {

}

void Menu::Draw() {
	platform->RenderClear();
	platform->DrawRect(0, 0, 100, 100);
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