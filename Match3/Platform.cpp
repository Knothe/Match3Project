#include "Platform.h"

Platform* Platform::ptr;
SDL_Renderer* Platform::renderer;
/*
If the object isn't started, starts it
@return this pointer
*/
Platform* Platform::GetPtr() {
	if (!ptr)
		ptr = new Platform();
	return ptr;
}
/*
Sets up the Window
*/
Platform::Platform()  {
	std::string name = "Match3";
	width = 864; // 288
	height = 640; // 214 
	scale = 3;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
		std::cout << "SDL_INIT";
		return;
	}

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		std::cout << "CreateWindow";
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		std::cout << "CreateRenderer";
		SDL_Quit();
		return;
	}
}
/*
Draws an empty rectangle
@param x: position in x
@param y: position in y
@param w: width of the rect
@param h: height of the rect
*/
void Platform::DrawRect(int x, int y, int w, int h) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(renderer, &rect);
}
/*
Draws a point on screen
@param v: position
*/
void Platform::DrawPoint(Vec2 v){
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawPoint(renderer, v.x, v.y);
}
/*
Clears the Screen
*/
void Platform::RenderClear() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}
/*
Presents everything rendered on screen
*/
void Platform::RenderPresent() {
	SDL_RenderPresent(renderer);
}
/*
Translates data for RenderTexture
@param image: pointer to image to render
@param x: position in x
@param y: position in y
*/
void Platform::RenderImage(Image* image, int x, int y) {
	RenderTexture(image, x, y, image->GetFrame());
}
/*
Translates data for RenderTexture
@param image: pointer to image to render
@param pos: position
*/
void Platform::RenderImage(Image* image, Vec2 pos) {
	RenderTexture(image, pos.x, pos.y, image->GetFrame());
}
/*
Translates data for RenderTexture
@param image: pointer to image to render
@param pos: position
@param frame: frame to draw
*/
void Platform::RenderImage(Image* image, Vec2 pos, int frame) {
	RenderTexture(image, pos.x, pos.y, frame);
}
/*
Renders the texture with RenderCopyEx
@param image: pointer to image to render
@param x: position in x
@param y: position in y
@param frame: frame to draw
*/
void Platform::RenderTexture(Image* image, int x, int y, int frame) {
	SDL_Rect dstrect;
	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = image->GetWidth() * scale;
	dstrect.h = image->GetHeight() * scale;
	SDL_Rect srcrect;
	srcrect.x = frame * image->GetWidth();
	srcrect.y = 0;
	srcrect.w = image->GetWidth();
	srcrect.h = image->GetHeight();
//	SDL_RenderCopyEx(renderer, image->GetTexture(), &srcrect, &dstrect, 0, NULL, SDL_FLIP_NONE);
	SDL_RenderCopy(renderer, image->GetTexture(), &srcrect, &dstrect);
}
/*
Checks Event for keyboard and mouse
@param keysDown: pointer for vector for all the keys pressed
@param keysDown: pointer for vector for all the keys up
@param mouseData: pointer to mouse data
*/
void Platform::CheckEvent(Vector<int>* keysDown, Vector<int>* keysUp, MouseData* mouseData) {
	mouseData->ResetClicks();
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_RIGHT)		keysDown->PushBack(SDLK_RIGHT);
			if (e.key.keysym.sym == SDLK_LEFT)		keysDown->PushBack(SDLK_LEFT);
			if (e.key.keysym.sym == SDLK_UP)		keysDown->PushBack(SDLK_UP);
			if (e.key.keysym.sym == SDLK_DOWN)		keysDown->PushBack(SDLK_DOWN);
			if (e.key.keysym.sym == SDLK_ESCAPE)	keysDown->PushBack(SDLK_ESCAPE);
			break;
		case SDL_KEYUP:
			if (e.key.keysym.sym == SDLK_RIGHT)		keysUp->PushBack(SDLK_RIGHT);
			if (e.key.keysym.sym == SDLK_LEFT)		keysUp->PushBack(SDLK_LEFT);
			if (e.key.keysym.sym == SDLK_UP)		keysUp->PushBack(SDLK_UP);
			if (e.key.keysym.sym == SDLK_DOWN)		keysUp->PushBack(SDLK_DOWN);
			break;
		case SDL_MOUSEMOTION:
			mouseData->position.x = e.motion.x;
			mouseData->position.y = e.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)		mouseData->leftButton = true;
			if (e.button.button == SDL_BUTTON_RIGHT)	mouseData->rightButton = true;
			break;
		}
	}
}
/*
Checks Event for mose
@param mouseData: pointer to mouse data
*/
void Platform::CheckEvent(MouseData* mouseData) {
	SDL_Event e;
	mouseData->ResetClicks();
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_MOUSEMOTION:
			mouseData->position.x = e.motion.x;
			mouseData->position.y = e.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)		mouseData->leftButton = true;
			if (e.button.button == SDL_BUTTON_RIGHT)	mouseData->rightButton = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT)		mouseData->leftButton = false;
			if (e.button.button == SDL_BUTTON_RIGHT)	mouseData->rightButton = false;
		}
	}
}
/*
@return scale for every image
*/
int Platform::GetScale() {
	return scale;
}

Platform::~Platform() {

}