#include "Button.h"

Button::Button() {
	platform = Platform::GetPtr();
	int size = platform->GetScale();
	position.x = 0;
	position.y = 0;
}

Button::Button(std::string imageLoc1, std::string imageLoc2, Vec2 pos) {
	platform = Platform::GetPtr();
	int s = platform->GetScale();
	plainImage.LoadImage(imageLoc1);
	hoverImage.LoadImage(imageLoc2);
	size = plainImage.GetSize() * s;
	position = pos;
}

void Button::Init(std::string imageLoc1, std::string imageLoc2, Vec2 pos) {
	int s = platform->GetScale();
	plainImage.LoadImage(imageLoc1);
	hoverImage.LoadImage(imageLoc2);
	size = plainImage.GetSize() * s;
	position = pos;
}

bool Button::Update(MouseData* mouseData) {
	if (mouseData->position > position&& mouseData->position < position + size) {
		if (mouseData->leftButton)	return true;
		isOver = true;
	}
	else	isOver = false;

	return false;
}

void Button::Draw() {
	if(isOver)	platform->RenderImage(&hoverImage, position);
	else		platform->RenderImage(&plainImage, position);
}

void Button::SetPos(Vec2 pos) {
	position = pos;
}


Button::~Button() {

}