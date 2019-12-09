#pragma once
#include "AssetManager.h"

class Text
{
private:
	SDL_Rect position;
	string text;
	string font;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
public:
	Text(Vec2 pos, string t, string id, SDL_Color colour);
	void SetSurface();
	void Draw();
};

