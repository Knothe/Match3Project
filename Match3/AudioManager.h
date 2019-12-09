#pragma once
#include "AssetManager.h"

class AudioManager
{
private:
	AudioManager();
	~AudioManager();
	static AudioManager* ptr;
	AssetManager* assetManager;
public:
	static AudioManager* getPtr();

	void PlayMusic(string id, int loops = -1);
	void PauseMusice();
	void ResumeMusic();
	int VolumeMusic(int vol);
	void PlaySFX(string id, int loops = 0, int channel = 0);
};

