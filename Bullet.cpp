#include "Bullet.h"
#include <Novice.h>
// 弾の情報
Bullet::Bullet() {
	pos_ = {0, 0};
	isShot_ = false;
	radius_ = 4;
	speed_ = 8;
}

// 弾の更新処理
void Bullet::Update() {
	if (isShot_ == true) {
		pos_.y -= speed_;
	}
	if (pos_.y <= -4) {
		isShot_ = false;
	}
}

void Bullet::Draw() {
	if (isShot_ == true) {
		Novice::DrawEllipse(
		    int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, BLUE, kFillModeSolid);
	}
}
