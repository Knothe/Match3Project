#include "Pause.h"

Pause::Pause(Game* g) {
	assetManager = AssetManager::getPtr();
	platform = Platform::GetPtr();
	audioManager = AudioManager::getPtr();
	assetManager->AddTexture("BackGroundPause.png", "pause", 1);
	game = g;
}

void Pause::Input() {
	Vector<int> input;
	platform->CheckEvent(&input, &mouseData);
	for (int i = 0; i < input.GetSize(); i++) {
		if (input.GetAt(i) == SDLK_ESCAPE)	state = false;
	}
	if (hasMusic) {
		if (soundButtonOn.Update(&mouseData)) {
			audioManager->VolumeMusic(0);
			hasMusic = false;
		}
	}
	else {
		if (soundButtonOff.Update(&mouseData)) {
			audioManager->VolumeMusic(MIX_MAX_VOLUME / 4);
			hasMusic = true;
		}
	}
}

void Pause::Update() {

}

void Pause::Draw() {
	platform->RenderClear();
	game->PauseDraw();
	platform->RenderImage(&backGround, Vec2(0, 0));
	if (hasMusic)
		soundButtonOn.Draw();
	else
		soundButtonOff.Draw();
	platform->RenderPresent();
}

void Pause::Init() {
	backGround.LoadImage("pause");
	if (audioManager->VolumeMusic(-1) > 0) {
		hasMusic = true;
		audioManager->VolumeMusic(MIX_MAX_VOLUME / 4);
	}
	else
		hasMusic = false;
	soundButtonOn.Init("sn", "sf", Vec2(375, 510));
	soundButtonOff.Init("sf", "sn", Vec2(375, 510));
}

void Pause::Close() {
	if (hasMusic)
		audioManager->VolumeMusic(MIX_MAX_VOLUME);

}

Pause::~Pause() {

}