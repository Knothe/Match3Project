#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#undef main
#include "SDL_image.h"
#include "Vector.h"


class Platform
{
private: 
	int width;
	int height;
	SDL_Window* window;
	
	Platform();
	static Platform* ptr;

	void RenderTexture();

public:
	static SDL_Renderer* renderer;
	void RenderClear();
	void RenderPresent();
	void RenderImage(); // Así por ahora
	void DrawRect(int x, int y, int w, int h);
	void CheckEvent();
	static Platform* GetPtr();
	~Platform();
};

