#include "GameObject.h"
/*
Initializes the object
@param id: id of the object
@param imageId: id of the image
@param pos: position in graph
@param node: node that will save it
*/
GameObject::GameObject(int id, string imageId, Vec2 pos, NodoG* node) {
	platform = Platform::GetPtr();
	myNode = node;
	frameTime = platform->GetFrameTime();
	this->id = id;
	offset.x = platform->GetWitdth() - 500;
	offset.y = (platform->GetHeight() / 2) - 228;
	sprite.LoadImage(imageId);
	onSelect.LoadImage("select");
	setPos(pos);
	size = sprite.GetSize() * platform->GetScale();
	movement = Vec2(0, 0);
}
/*
Initializes the object
@param id: id of the object
@param imageId: id of the image
@param iPos: initial position relative to graph
@param finalPos: position in graph
@param node: node that will save it
*/
GameObject::GameObject(int id, string imageId, Vec2 iPos, Vec2 finalPos, NodoG* node) {
	platform = Platform::GetPtr();
	myNode = node;
	frameTime = platform->GetFrameTime();
	this->id = id;
	offset.x = platform->GetWitdth() - 500;
	offset.y = (platform->GetHeight() / 2) - 228;
	sprite.LoadImage(imageId);
	onSelect.LoadImage("select");
	setMovement(iPos, finalPos);
	size = sprite.GetSize() * platform->GetScale();
}

GameObject::~GameObject() {

}
/*
Checks the input in the object
@param mouseData: data with mouse status
*/
bool GameObject::Input(MouseData* mouseData) {
	return MouseIsOver(mouseData);
}
/*
Updates positions and frames of objects
@return true if the object will destroy
*/
bool GameObject::Update() {
	if (moving) {
		position = position + movement;
		if (position == finalPosition)
			moving = false;
	}
	else if (isDestroying) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), lastFrameTime + frameTime)) {
			if (onDestroy.GetFrame() == onDestroy.GetTotalFrames() - 1)
				return true;
			lastFrameTime = SDL_GetTicks();
			onDestroy.NextFrame();
		}
	}
	return false;
}
/*
Draws something depending in the status of the object
@param s: if the object is selected
*/
void GameObject::Draw(bool s) {
	onDraw(s);
	if (isDestroying) {
		platform->RenderImage(&onDestroy, position);
	} else if (isOver || s) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), lastFrameTime + frameTime)) {
			lastFrameTime = SDL_GetTicks();
			sprite.NextFrame();
		}
		isOver = false;
		platform->RenderImage(&sprite, position);
	} else 	platform->RenderImage(&sprite, position, 0);
	return;
}
/*
Does something if the object draws
@param s: if the object is selected
*/
void GameObject::onDraw(bool s) {

}
/*
Sets position of the object on screen
@param pos: position on graph
*/
void GameObject::setPos(Vec2 pos) {
	position = Vec2(pos.x * sprite.GetWidth() * platform->GetScale() + (12 * pos.x), 
		pos.y * sprite.GetHeight() * platform->GetScale() + (12 * pos.y));
	position = position + offset;
}
/*
Sets movement variable and needed variables for moving the objects from point a to b
@param iPos: initial position of the object
@param finalPos: finalPosition of the object
*/
void GameObject::setMovement(Vec2 iPos, Vec2 finalPos) {
	moving = true;
	setPos(iPos);
	finalPosition = Vec2(finalPos.x * sprite.GetWidth() * platform->GetScale() + (12 * finalPos.x),
		finalPos.y * sprite.GetHeight() * platform->GetScale() + (12 * finalPos.y));
	finalPosition = finalPosition + offset;
	movement = (finalPos - iPos).normalize();
	movement = movement * 6;
}
/*
Sets new node for the object
@param node: new node for the object
*/
void GameObject::setNewNode(NodoG* node) {
	myNode = node;
}
/*
@return id of the object
*/
int GameObject::getId() {
	return id;
}
/*
return position of the object
*/
Vec2 GameObject::getPos() {
	return position;
}
/*
return moving variable
*/
bool GameObject::isMoving() {
	try {
		return moving;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}
/*
return isDestroying
*/
bool GameObject::willDestroy() {
	return isDestroying;
}
/*
Sets is detroying to true
*/
void GameObject::destroy() {
	isDestroying = true;
}
/*
@return true if mouse is over the object
*/
bool GameObject::MouseIsOver(MouseData* mouseData) {
	if (mouseData->position > position&& mouseData->position < position + size) {
		isOver = true;
		if (mouseData->leftButton)
			return true;
	}
	else	isOver = false;

	return false;
}
