#pragma once
#include "Vector2.h"
class Bullet {
public:
	// メンバ変数
	Vector2 pos_;
	int speed_;
	int radius_;
	bool isShot_;

public:
	// コンストラクタ(初期化する)
	Bullet();
	void Update();
	void Draw();
};