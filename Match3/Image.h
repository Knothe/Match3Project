#pragma once
#include <iostream>
#include <SDL.h>
#undef main
#include "Vec2.h"


class Image
{
private:
	SDL_Texture* image;
	std::string name; // ?
	Vec2 size;
	int totalFrames;
	int actualFrame;

public:
	void LoadImage(std::string id);
	SDL_Texture* GetTexture();
	int GetWidth();
	int GetHeight();
	int GetFrame();
	void NextFrame();
	Vec2 GetSize();
};

