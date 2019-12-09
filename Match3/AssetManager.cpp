#include "SDL_image.h"
#include "AssetManager.h"
#include "Platform.h"
#include <fstream>
#include "MessageException.h"

using std::ofstream;
using std::ifstream;

AssetManager* AssetManager::ptr;

AssetManager::AssetManager() {
	if (TTF_Init())
		std::cout << "TTF_Init" << std::endl;
	ifstream savedFile;
	savedFile.open("HighScores.dat", std::ios::in);
	highScoreList.push_back(0);
	highScoreList.push_back(0);
	highScoreList.push_back(0);
	highScoreList.push_back(0);
	highScoreList.push_back(0);
	if (!savedFile.fail()) {
		int i;
		savedFile.read((char*)&i, sizeof(int));
		highScoreList.pushOrdered(i);
	}
	savedFile.close();
}
/*
If pointer is null, instanciates the object
@return pointer of this object
*/
AssetManager* AssetManager::getPtr() {
	if (!ptr)
		ptr = new AssetManager();
	return ptr;
}
/*
Adds a texture to the tree
@param fileName: name of the texture to add
@param id: id for the position in tree
@param frames: frames in the texture
*/
void AssetManager::AddTexture(string fileName, string id, int frames) {
	if (textureTree.find(id))
		return;
	string name = "Assets/Images/" + fileName;
	SDL_Surface* loadedSurface = IMG_Load(name.c_str());
	Vec2 size;
	size.x = loadedSurface->w / frames;
	size.y = loadedSurface->h;
	textureTree.insert(id, 
		new ImageValues(SDL_CreateTextureFromSurface(Platform::renderer, loadedSurface),
			size, frames));
}
/*
Sets values in the image for image use
@param id: id of the image in tree
@param size: variable for the size of the image
@param frames: variable for the number of frames
@return pointer to the texture
*/
SDL_Texture* AssetManager::GetTextureData(string id, Vec2& size, int& frames) {
	ImageValues* img = textureTree.GetValue(id);
	if (img) {
		size = img->size;
		frames = img->frames;
		return img->image;
	}
	else
		throw MessageException("Image " + id + " not loaded");
	
}
/*
@param id: id of the music in tree
@return pointer to the Music variable
*/
Mix_Music* AssetManager::GetMusic(string id) {
	Mix_Music* music = mMusic.GetValue(id);
	if (music)
		return music;
	else
		throw MessageException("Music " + id + "not loaded");
}
/*
@param id: id of the sfx in tree
@return pointer to the sfx variable
*/
Mix_Chunk* AssetManager::GetSFX(string id) {
	Mix_Chunk* sfx = mSFX.GetValue(id);
	if (sfx)
		return sfx;
	else
		throw MessageException("SFX " + id + "not loaded");
}
/*
Adds a song to the tree
@param fileName: name of the song file
@param id: id for the song in tree
*/
void  AssetManager::AddMusic(string fileName, string id) {
	if (mMusic.find(id))
		return;
	string name = "Assets/Music/" + fileName;
	Mix_Music* m = Mix_LoadMUS(name.c_str());
	if (m)
		mMusic.insert(id, Mix_LoadMUS(name.c_str()));
	else
		std::cout << Mix_GetError() << std::endl;
}
/*
Adds a sfx to the tree
@param fileName: name of the sfx file
@param id: id for the sfx in tree
*/
void  AssetManager::AddSfx(string fileName, string id) {
	if (mSFX.find(id))
		return;	
	string name = "Assets/SFX/" + fileName;
	mSFX.insert(id, Mix_LoadWAV(name.c_str()));
}
/*
Adds a font to the tree
@param fileName: Name of the file
@param id: id of the Font
@param size: Size of the font
*/
void AssetManager::AddFont(string fileName, string id, int size) {
	if (fontTree.find(id))
		return;
	string name = "Assets/TTF/" + fileName;
	TTF_Font* font = TTF_OpenFont(name.c_str() , size);
	if (font)
		fontTree.insert(id, font);
	else
		std::cout << "No cargo: " << fileName << std::endl;
}
/*
@return font
*/
TTF_Font* AssetManager::GetFont(string id) {
	TTF_Font* t = fontTree.GetValue(id);
	if (t)
		return t;
	else
		throw MessageException("Font : " + id + " didnt load");
}
/*
Saves HighScores to a .dat
*/
void AssetManager::SaveFileScores() {
	ofstream saveFile;
	saveFile.open("HighScores.dat", std::ios::out | std::ios::binary);
	NodeL<int>* temp = highScoreList.first;
	while (temp) {
		saveFile.write((char*)&temp->value, sizeof(int));
		temp = temp->next;
	}
	saveFile.close();
}
/*
Adds a score
@return true if it was added
*/
bool AssetManager::AddNewScore(int v) {
	return highScoreList.pushOrdered(v);
}
/*
@return pointer to score List
*/
List<int>* AssetManager::GetScoreList() {
	return &highScoreList;
}


AssetManager::~AssetManager() {
	TTF_Quit();
}

