#include "Text.h"
#include "Platform.h"
#include "MessageException.h"
/*
Initializes variables
@param pos: position of this text
@param t: message of the text
@param id: id of the font
@param colour: colour of the text
*/
Text::Text(Vec2 pos, string t, string id, SDL_Color colour) :
	text(t), font(id), textColour(colour)
{
	position.x = pos.x;
	position.y = pos.y;
	SetSurface();
}
/*
Sets the surface (SDL_RECT)
*/
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
/*
Draws the text
*/
void Text::Draw() {
	SDL_RenderCopy(Platform::renderer, labelTexture, nullptr, &position);
}