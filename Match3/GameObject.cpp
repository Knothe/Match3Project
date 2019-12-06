#include "GameObject.h"

GameObject::GameObject() {
	platform = Platform::GetPtr();
	frameTime = platform->GetFrameTime();
}

GameObject::GameObject(int id, string imageId) {
	platform = Platform::GetPtr();
	frameTime = platform->GetFrameTime();
	this->id = id;
	sprite.LoadImage(imageId);
	size = sprite.GetSize() * platform->GetScale();
}

GameObject::GameObject(int id, string imageId, Vec2 pos) {
	platform = Platform::GetPtr();
	frameTime = platform->GetFrameTime();
	this->id = id;
	sprite.LoadImage(imageId);
	SetPos(pos);
	size = sprite.GetSize() * platform->GetScale();
}

GameObject::~GameObject() {

}

void GameObject::Input(MouseData* mouseData) {
	MouseIsOver(mouseData);
}

void GameObject::Draw() {
	if (isOver) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), lastFrameTime + frameTime)) {
			lastFrameTime = SDL_GetTicks();
			sprite.NextFrame();
		}
		platform->RenderImage(&sprite, position);
	}
	else {
		platform->RenderImage(&sprite, position, 0);
	}
}

void GameObject::SetPos(Vec2 pos) {
	//position = pos;
	position = Vec2(pos.x * sprite.GetWidth() * platform->GetScale() + (12 * pos.x), 
		pos.y * sprite.GetHeight() * platform->GetScale() + (12 * pos.y));
	position = position + offset;
}

bool GameObject::MouseIsOver(MouseData* mouseData) {
	if (mouseData->position > position&& mouseData->position < position + size) {
		if (mouseData->leftButton)	return true;
		isOver = true;
	}
	else	isOver = false;

	return false;
}
