#include "AudioManager.h"
#include "MessageException.h"

AudioManager* AudioManager::ptr;

AudioManager::AudioManager() {
	assetManager = AssetManager::getPtr();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		throw MessageException("Mixer initializacion Error");
	}
}

AudioManager* AudioManager::getPtr() {
	if (!ptr)
		ptr = new AudioManager();
	return ptr;
}

void AudioManager::PlayMusic(string id, int loops) {
	Mix_PlayMusic(assetManager->GetMusic(id), loops);
}

void AudioManager::PauseMusice() {
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void AudioManager::ResumeMusic() {
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void AudioManager::PlaySFX(string id, int loops, int channel) {
	Mix_PlayChannel(channel, assetManager->GetSFX(id), loops);
}

int AudioManager::VolumeMusic(int vol) {
	return Mix_VolumeMusic(vol); // Use MIX_MAX_VOLUME as a base
}

AudioManager::~AudioManager() {
	assetManager = NULL;
	Mix_Quit();
}