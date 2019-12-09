#include "Text.h"
#include "Platform.h"
#include "MessageException.h"
Text::Text(Vec2 pos, string t, string id, SDL_Color colour) :
	text(t), font(id), textColour(colour)
{
	position.x = pos.x;
	position.y = pos.y;
	SetSurface();
}

void Text::SetSurface() {
	try {
		SDL_Surface* surf = TTF_RenderText_Blended(AssetManager::getPtr()->GetFont(font), text.c_str(), textColour);
		labelTexture = SDL_CreateTextureFromSurface(Platform::renderer, surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(labelTexture, NULL, NULL, &position.w, &position.h);
	}
	catch (MessageException e) {
		std::cout << e.what() << std::endl;
	}
}

void Text::Draw() {
	SDL_RenderCopy(Platform::renderer, labelTexture, nullptr, &position);
}