#include "GameObject.h"

GameObject::GameObject(int id, string imageId, Vec2 pos, NodoG* node) {
	platform = Platform::GetPtr();
	myNode = node;
	frameTime = platform->GetFrameTime();
	this->id = id;
	offset.x = platform->GetWitdth() - 500;
	offset.y = (platform->GetHeight() / 2) - 228;
	sprite.LoadImage(imageId);
	onSelect.LoadImage("select");
	SetPos(pos);
	size = sprite.GetSize() * platform->GetScale();
	movement = Vec2(0, 0);
}

GameObject::GameObject(int id, string imageId, Vec2 iPos, Vec2 finalPos, NodoG* node) {
	platform = Platform::GetPtr();
	myNode = node;
	frameTime = platform->GetFrameTime();
	this->id = id;
	offset.x = platform->GetWitdth() - 500;
	offset.y = (platform->GetHeight() / 2) - 228;
	sprite.LoadImage(imageId);
	onSelect.LoadImage("select");
	SetMovement(iPos, finalPos);
	size = sprite.GetSize() * platform->GetScale();
}


GameObject::~GameObject() {

}

bool GameObject::Input(MouseData* mouseData) {
	
	return MouseIsOver(mouseData);
}

bool GameObject::Update() {
	return true;
}

bool GameObject::Draw(bool s) {
	if (isDestroying) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), lastFrameTime + frameTime)) {
			if (onDestroy.GetFrame() == onDestroy.GetTotalFrames() - 1)	return true;
			lastFrameTime = SDL_GetTicks();
			onDestroy.NextFrame();
		}
		platform->RenderImage(&onDestroy, position);
	} else if (moving) {
		position = position + movement;
		if (position == finalPosition)	moving = false;
		platform->RenderImage(&sprite, position, 0);
	} else if (isOver || s) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), lastFrameTime + frameTime)) {
			lastFrameTime = SDL_GetTicks();
			sprite.NextFrame();
		}
		isOver = false;
		platform->RenderImage(&sprite, position);
	} else 	platform->RenderImage(&sprite, position, 0);
	return false;
}

void GameObject::SetPos(Vec2 pos) {
	position = Vec2(pos.x * sprite.GetWidth() * platform->GetScale() + (12 * pos.x), 
		pos.y * sprite.GetHeight() * platform->GetScale() + (12 * pos.y));
	position = position + offset;
}

bool GameObject::MouseIsOver(MouseData* mouseData) {
	if (mouseData->position > position&& mouseData->position < position + size) {
		isOver = true;
		if (mouseData->leftButton)	
			return true;
	}
	else	isOver = false;

	return false;
}

Vec2 GameObject::GetPos() {
	return position;
}

int GameObject::GetId() {
	return id;
}

void GameObject::SetMovement(Vec2 iPos, Vec2 finalPos) {
	moving = true;
	SetPos(iPos);
	finalPosition = Vec2(finalPos.x * sprite.GetWidth() * platform->GetScale() + (12 * finalPos.x),
		finalPos.y * sprite.GetHeight() * platform->GetScale() + (12 * finalPos.y));
	finalPosition = finalPosition + offset;
	movement = (finalPos - iPos).normalize();
	movement = movement * 6;
}

void GameObject::Destroy() {
	isDestroying = true;
}


bool GameObject::isMoving() {
	try {
		return moving;
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}

void GameObject::SetNewNode(NodoG* node) {
	myNode = node;
}

Vector<NodoG*>* GameObject::DeleteObjects() {
	return NULL;
}

bool GameObject::willDestroy() {
	return isDestroying;
}
