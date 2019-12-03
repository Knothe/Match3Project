#include <iostream>
#include <string>
#include <SDL.h>
#undef main
#include "SDL_image.h"

int main()
{
	int width;
	int height;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::string name;
	name = "prueba";
	width = 864; //27 
	//16 x 54
	height = 640; //20
	//16 x 40
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_INIT";
		return 0;
	}

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "CreateWindow";
		SDL_Quit();
		return 0;
	}


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "CreateRenderer";
		SDL_Quit();
		return 0;
	}

	while (true) {
		SDL_RenderPresent(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	}
}
