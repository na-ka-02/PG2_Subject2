#pragma once
#include "Vector2.h"

class Enemy {
private:
	// メンバ変数
	Vector2 enemyPos_;   // 位置
	Vector2 enemySpeed_; // スピード
	int deathFrame_;     // 死んだときのアニメーション
	float enemyRadius_;  // 半径
	bool isEnemyAlive_;  // 生存フラグ

public:
	// メンバ関数
	void Initalize();   // 初期化
	void OnCollision(); // 当たり判定
	void ReturnAlive();
	void Update(); // 更新処理
	void Draw();   // 描画処理void Draw();
	float GetRadius() const { return enemyRadius_; }
	bool GetAlive() const { return bool(isEnemyAlive_); }
	Vector2 GetPos() const { return Vector2(enemyPos_); }
	void SetSpeed(Vector2 speed);
};