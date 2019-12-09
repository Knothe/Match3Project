#include "HighScoreMenu.h"

HighScoreMenu::HighScoreMenu() {
	platform = Platform::GetPtr();
	assetManager = AssetManager::getPtr();
}

void HighScoreMenu::Input() {
	Vector<int> input;
	platform->CheckEvent(&input);
	for (int i = 0; i < input.GetSize(); i++) {
		if (input.GetAt(i) == SDLK_ESCAPE) {
			state = false;
		}
	}
}

void HighScoreMenu::Update() {

}

void HighScoreMenu::Draw() {
	platform->RenderClear();
	platform->RenderImage(&backGround, Vec2(0, 0));
	title->Draw();
	for (int i = 0; i < scores.GetSize(); i++) {
		scores.GetAt(i)->Draw();
	}
	platform->RenderPresent();
}

void HighScoreMenu::Init() {
	title = new Text(Vec2(200, 100), "High Scores", "big", { 255,255,255 });
	NodeL<int>* it = assetManager->GetScoreList()->first;
	int i = 0;
	while (it) {
		scores.PushBack(new Text(Vec2( 300, 200 + (i*50)), std::to_string(it->value), "med", { 255,255,255 }));
		i++;
		it = it->next;
	}
	backGround.LoadImage("menu");

}

void HighScoreMenu::Close() {

}