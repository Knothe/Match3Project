#pragma once
#include <string>
#include <SDL.h>
#undef main
#include "Tree.h"
#include "Vec2.h"
#include "SDL_mixer.h"

using std::string;

struct ImageValues {
	SDL_Texture* image;
	Vec2 size;
	int frames;
	ImageValues(SDL_Texture* img, Vec2 s, int f) : image(img), size(s), frames(f) {

	}
};

class AssetManager
{
private:
	AssetManager();
	static AssetManager* ptr;
	Tree<string, ImageValues*> textureTree;
	Tree<string, Mix_Music*> mMusic;
	Tree<string, Mix_Chunk*> mSFX;

public:
	static AssetManager* getPtr();
	void AddTexture(string fileName, string id, int frames);
	SDL_Texture* GetTextureData(string id, Vec2& size, int& frames);
	void AddMusic(string fileName, string id);
	void AddSfx(string fileName, string id);
	Mix_Music* GetMusic(string id);
	Mix_Chunk* GetSFX(string id);
	~AssetManager();
};

