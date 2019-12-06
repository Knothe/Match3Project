#include "Image.h"
#include "Platform.h"
#include "AssetManager.h"

/*
Loads a simple image
@param n: name of the image file
*/
void Image::LoadImage(std::string id) {
	try {
		image = AssetManager::getPtr()->GetTextureData(id, size, totalFrames);
	}
	catch (MessageException e) {
		std::cout << "Image LoadImage() exception: " << e.what() << std::endl;
	}
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