#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include <Novice.h>

const char kWindowTitle[] = "Subject2";
enum SCENE {
	TITLE,
	GAMESCENE,
	GAMECLEAR,
	GAMEOVER,
};

// 当たり判定
bool Collision(Vector2 playerPos, Vector2 enemyPos, float playreRadius, float enemyRadius);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	int enterTxt = Novice::LoadTexture("./Resouces./enter.png");
	int titleTxt = Novice::LoadTexture("./Resouces./title.png");
	int keyTxt = Novice::LoadTexture("./Resouces./key.png");
	int bulletExTxt = Novice::LoadTexture("./Resouces./bulletEx.png");
	int gameoverTxt = Novice::LoadTexture("./Resouces./gameover.png");
	int gameclearTxt = Novice::LoadTexture("./Resouces./gameclear.png");

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	SCENE scene = TITLE;
	Player* player = new Player;
	Enemy* enemy = new Enemy;
	int deathEnemyFrame = 0;
	int count = 0;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		switch (scene) {
		case TITLE:
			if (keys[DIK_RETURN]) {
				scene = GAMESCENE;
				enemy->Initalize();
				player->Initalize();
			}
			break;
		case GAMESCENE:
			enemy->Update();
			player->Update(keys);
			if (Collision(
			        player->GetPos(), enemy->GetPos(), player->GetRadius(), enemy->GetRadius())) {
				player->OnCollision();
				scene = GAMEOVER;
			}
			if (Collision(
			        player->GetBulletPos(), enemy->GetPos(), player->GetRadius(),
			        enemy->GetRadius())) {
				enemy->OnCollision();
			}

			if (enemy->GetAlive() == false) {
				deathEnemyFrame++;
			}
			if (deathEnemyFrame == 120) {
				enemy->ReturnAlive();
				deathEnemyFrame = 0;
				count += 1;
			}

			if (count == 2) {
				scene = GAMECLEAR;
			}

			break;
		case GAMECLEAR:
			if (!keys[DIK_RETURN] && preKeys[DIK_RETURN]) {
				scene = TITLE;
			}
			player->Initalize();
			enemy->Initalize();
			count = 0;
			break;
		case GAMEOVER:
			if (!keys[DIK_RETURN] && preKeys[DIK_RETURN]) {
				scene = TITLE;
			}
			player->Initalize();
			enemy->Initalize();
			count = 0;
			break;
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (scene) {
		case TITLE:
			Novice::DrawSprite(200, 300, enterTxt, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(200, 100, titleTxt, 1.0f, 1.0f, 0.0f, WHITE);
			break;
		case GAMESCENE:
			enemy->Draw();
			player->Draw();
			Novice::DrawSprite(0, 500, keyTxt, 0.5f, 0.5f, 0.0f, WHITE);
			Novice::DrawSprite(0, 600, bulletExTxt, 0.7f, 0.7f, 0.0f, WHITE);
			break;
		case GAMECLEAR:
			Novice::DrawSprite(200, 100, gameclearTxt, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(200, 300, enterTxt, 1.0f, 1.0f, 0.0f, WHITE);
			break;
		case GAMEOVER:
			Novice::DrawSprite(200, 100, gameoverTxt, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(200, 300, enterTxt, 1.0f, 1.0f, 0.0f, WHITE);
			break;
			break;
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

bool Collision(Vector2 playerPos, Vector2 enemyPos, float playerRadius, float enemyRadius) {
	Vector2 distance = {};
	distance.x = playerPos.x - enemyPos.x;
	distance.y = playerPos.y - enemyPos.y;
	float dis = (distance.x * distance.x) + (distance.y * distance.y);
	float radius = float(pow(playerRadius + enemyRadius, 2) / 2);
	if (dis < radius + radius) {
		return true;
	} else {
		return false;
	}
}
