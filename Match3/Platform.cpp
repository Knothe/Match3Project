#include "Platform.h"

Platform* Platform::ptr;
 SDL_Renderer* Platform::renderer;


Platform* Platform::GetPtr() {
	if (!ptr)
		ptr = new Platform();
	return ptr;
}

Platform::Platform() {
	std::string name = "Match3";
	width = 864; //27 
	//16 x 54
	height = 640; //20
	//16 x 40
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_INIT";
		return;
	}

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "CreateWindow";
		SDL_Quit();
		return;
	}


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "CreateRenderer";
		SDL_Quit();
		return;
	}
}

void Platform::DrawRect(int x, int y, int w, int h) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderDrawRect(renderer, &rect);
}

void Platform::RenderClear() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Platform::RenderPresent() {
	SDL_RenderPresent(renderer);
}

void Platform::RenderImage() {
	//TODO: RenderTexture
}

void Platform::RenderTexture() {

}

void Platform::CheckEvent() {
	SDL_Event e;
}

Platform::~Platform() {

}