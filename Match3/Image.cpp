#include "Image.h"
#include "Platform.h"
#include "SDL_image.h"

/*
Loads the image with various frames
@param n: name of the image file
@param widthFrame: number of Frames long
@param heightFrame: number of Frames height
*/
void Image::LoadImage(std::string n, int widthFrame, int heightFrame) {
	name = "Assets/Images/" + n;
	SDL_Surface* loadedSurface = IMG_Load(name.c_str());
	size.x = loadedSurface->w / widthFrame;
	size.y = loadedSurface->h / heightFrame;
	image = SDL_CreateTextureFromSurface(Platform::renderer, loadedSurface);
	totalFrames = widthFrame * heightFrame;
	actualFrame = 0;
}
/*
Loads a simple image
@param n: name of the image file
*/
void Image::LoadImage(std::string n) {
	name = "Assets/Images/" + n;
	SDL_Surface* loadedSurface = IMG_Load(name.c_str());
	size.x = loadedSurface->w;
	size.y = loadedSurface->h;
	image = SDL_CreateTextureFromSurface(Platform::renderer, loadedSurface);
	totalFrames = 0;
	actualFrame = 0;
}
/*
@return texture of the image
*/
SDL_Texture* Image::GetTexture() {
	return image;
}
/*
@return height of the texture
*/
int Image::GetHeight() {
	return size.y;
}
/*
@return lenght of the texture
*/
int Image::GetWidth() {
	return size.x;
}
/*
@return current frame
*/
int Image::GetFrame() {
	return actualFrame;
}
/*
Moves animation to the next frame
*/
void Image::NextFrame() {
	actualFrame++;
	if (actualFrame == totalFrames)
		actualFrame = 0;
}
/*
@return vector with the size of the texture
*/
Vec2 Image::GetSize() {
	return size;
}