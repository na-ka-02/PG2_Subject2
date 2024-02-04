#pragma once
#include "Bullet.h"

class Player {
private:
	// メンバ変数
	Vector2 pos_;
	int radius_;
	int deathFrame_;
	float speed_;
	bool isAlive_;
	// 包含
	Bullet* bullet_;

public:
	//// コンストラクタ(初期化する)
	// Player();
	//  デストラクタ(消す)
	~Player();
	void OnCollision();
	void Initalize();
	void Update(char* keys);
	void Draw();
	Vector2 GetPos() const { return Vector2(pos_); }
	Vector2 GetBulletPos() { return Vector2(bullet_->pos_); }
	float GetRadius() const { return float(radius_); }
	float GetSpeed() const;
};
