#include "GameObject.h"

GameObject::GameObject(int id, string imageId, Vec2 pos) {
	platform = Platform::GetPtr();
	frameTime = platform->GetFrameTime();
	this->id = id;
	offset.x = platform->GetWitdth() - 500;
	offset.y = (platform->GetHeight() / 2) - 228;
	sprite.LoadImage(imageId);
	onSelect.LoadImage("select");
	SetPos(pos);
	size = sprite.GetSize() * platform->GetScale();
}

GameObject::~GameObject() {

}

bool GameObject::Input(MouseData* mouseData) {
	return MouseIsOver(mouseData);
}

bool GameObject::Draw(bool s) {
	if (isDestroying) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), lastFrameTime + frameTime)) {
			if (onDestroy.GetFrame() == onDestroy.GetTotalFrames())
				return true;
			lastFrameTime = SDL_GetTicks();
			onDestroy.NextFrame();
		}
		platform->RenderImage(&onDestroy, position);
	}else if (isOver || s) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), lastFrameTime + frameTime)) {
			lastFrameTime = SDL_GetTicks();
			sprite.NextFrame();
		}
		platform->RenderImage(&sprite, position);
	}
	else 	platform->RenderImage(&sprite, position, 0);
	//if (s)	platform->RenderImage(&onSelect, position);
	return false;
}

void GameObject::SetPos(Vec2 pos) {
	//position = pos;
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
