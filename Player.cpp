#include "Player.h"
#include <Novice.h>

// プレイヤーが初期化する情報
Player::~Player() { delete bullet_; }

void Player::OnCollision() {
	isAlive_ = false;
	if (isAlive_ == false) {
		deathFrame_++;
	}
	if (deathFrame_ == 120) {
		isAlive_ = true;
		deathFrame_ = 0;
	}
}

void Player::Initalize() {
	pos_ = {500, 500};
	radius_ = 20;
	speed_ = 4.0f;
	isAlive_ = true;
	bullet_ = new Bullet();
}

// プレイヤーが更新処理で行う情報
void Player::Update(char* keys) {
	// 移動処理
	if (keys[DIK_W] || keys[DIK_UP]) {
		pos_.y -= speed_;
	}
	if (keys[DIK_S] || keys[DIK_DOWN]) {
		pos_.y += speed_;
	}
	if (keys[DIK_A] || keys[DIK_LEFT]) {
		pos_.x -= speed_;
	}
	if (keys[DIK_D] || keys[DIK_RIGHT]) {
		pos_.x += speed_;
	}
	// 弾処理
	if (keys[DIK_SPACE] && bullet_->isShot_ == false) {
		bullet_->pos_ = pos_;
		bullet_->isShot_ = true;
	}
	if (pos_.x > 1260) {
		pos_.x = 1260;
	}
	if (pos_.x < 20) {
		pos_.x = 20;
	}
	if (pos_.y > 700) {
		pos_.y = 700;
	}
	if (pos_.y < 20) {
		pos_.y = 20;
	}

	// 弾の関数の呼び出し
	bullet_->Update();
}

void Player::Draw() {
	if (isAlive_ == true) {
		Novice::DrawEllipse(
		    int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, WHITE, kFillModeSolid);
		bullet_->Draw();
	}
}

float Player::GetSpeed() const { return speed_; }
