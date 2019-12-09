#include "EndGame.h"
EndGame::EndGame(Game* g, int score) {
	assetManager = AssetManager::getPtr();
	platform = Platform::GetPtr();
	audioManager = AudioManager::getPtr();
	assetManager->AddTexture("BackGroundOver.png", "over", 1);
	assetManager->AddTexture("Finish.png", "finish", 1);
	assetManager->AddTexture("NewHighScore.png", "nhs", 1);
	game = g;
	newHighScore = assetManager->AddNewScore(score);
	if (newHighScore)
		assetManager->SaveFileScores();
	scoreText1 = new Text(Vec2(200, 400), "Your score", "med", { 255,255,255 });
	scoreText2 = new Text(Vec2(300, 450), std::to_string(score), "med", { 255, 255, 255 });

}
void EndGame::Input() {
	Vector<int> input;
	platform->CheckEvent(&input, &mouseData);
	for (int i = 0; i < input.GetSize(); i++) {
		if (input.GetAt(i) == SDLK_ESCAPE) {
			state = false;
			game->Init();
		}
	}
	mouseData.ResetClicks();
}
void EndGame::Update() {

}
void EndGame::Draw() {
	platform->RenderClear();
	platform->RenderImage(&backGround, Vec2(0, -70));
	platform->RenderImage(&finish, Vec2(200, 250));
	if(newHighScore)
		platform->RenderImage(&highScore, Vec2(50,100));
	scoreText1->Draw();
	scoreText2->Draw();
	platform->RenderPresent();
}
void EndGame::Init() {
	backGround.LoadImage("over");
	audioManager->PlayMusic("gameOver");
	highScore.LoadImage("nhs");
	finish.LoadImage("finish");
}
void EndGame::Close() {

}
EndGame::~EndGame() {

}