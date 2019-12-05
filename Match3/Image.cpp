#include "Image.h"
#include "Platform.h"
#include "SDL_image.h"

void Image::LoadImage(std::string n, int widthFrame, int heightFrame) {
	name = "Assets/Images/" + n;
	SDL_Surface* loadedSurface = IMG_Load(name.c_str());
	size.x = loadedSurface->w / widthFrame;
	size.y = loadedSurface->h / heightFrame;
	image = SDL_CreateTextureFromSurface(Platform::renderer, loadedSurface);
	totalFrames = widthFrame * heightFrame;
	actualFrame = 0;
}

void Image::LoadImage(std::string n) {
	name = "Assets/Images/" + n;
	SDL_Surface* loadedSurface = IMG_Load(name.c_str());
	size.x = loadedSurface->w;
	size.y = loadedSurface->h;
	image = SDL_CreateTextureFromSurface(Platform::renderer, loadedSurface);
	totalFrames = 0;
	actualFrame = 0;
}

SDL_Texture* Image::GetTexture() {
	return image;
}

int Image::GetHeight() {
	return size.y;
}

int Image::GetWidth() {
	return size.x;
}

int Image::GetFrame() {
	return actualFrame;
}

void Image::NextFrame() {
	actualFrame++;
	if (actualFrame == totalFrames)
		actualFrame = 0;
}

Vec2 Image::GetSize() {
	return size;
}