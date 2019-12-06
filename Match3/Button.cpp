#include "Button.h"
/*
Initializes Button variables
*/
Button::Button() {
	platform = Platform::GetPtr();
	position.x = 0;
	position.y = 0;
}
/*
Initializes variables and textures
@param imageLoc1: image when mouse isn't over the button
@param imageLoc2: image when mouse is over the button
@param pos: position of the button
*/
Button::Button(std::string imageId1, std::string imageId2, Vec2 pos) {
	platform = Platform::GetPtr();
	int s = platform->GetScale();
	plainImage.LoadImage(imageId1);
	hoverImage.LoadImage(imageId2);
	size = plainImage.GetSize() * s;
	position = pos;
}
/*
Initializes variables and textures
@param imageLoc1: image when mouse isn't over the button
@param imageLoc2: image when mouse is over the button
@param pos: position of the button
*/
void Button::Init(std::string imageId1, std::string imageId2, Vec2 pos) {
	
	int s = platform->GetScale();
	plainImage.LoadImage(imageId1);
	hoverImage.LoadImage(imageId2);
	size = plainImage.GetSize() * s;
	position = pos;
	
}
/*
Updates the button and checks mouse inputs
@param mouseData: pointer to mouse data
*/
bool Button::Update(MouseData* mouseData) {
	if (mouseData->position > position&& mouseData->position < position + size) {
		if (mouseData->leftButton)	return true;
		isOver = true;
	}
	else	isOver = false;

	return false;
}
/*
Draws the button
*/
void Button::Draw() {
	if(isOver)	platform->RenderImage(&hoverImage, position);
	else		platform->RenderImage(&plainImage, position);
}
/*
Changes button position
@param pos: new button position
*/
void Button::SetPos(Vec2 pos) {
	position = pos;
}


Button::~Button() {

}