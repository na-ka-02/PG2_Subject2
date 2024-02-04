#include "Enemy.h"
#include "Novice.h"

void Enemy::Initalize() {
	this->enemyPos_.x = 640.0f;
	this->enemyPos_.y = 20.0f;
	this->enemySpeed_.x = 3.0f;
	this->enemySpeed_.y = 0.0f;
	this->enemyRadius_ = 16.0f;
	this->deathFrame_ = 0;
	this->isEnemyAlive_ = true;
}

void Enemy::OnCollision() { isEnemyAlive_ = false; }

void Enemy::ReturnAlive() { isEnemyAlive_ = true; }

void Enemy::Update() {
	enemyPos_.x += enemySpeed_.x;
	if (enemyPos_.x >= 1265) {
		enemySpeed_.x *= -1;
	}
	if (enemyPos_.x <= 15) {
		enemySpeed_.x *= -1;
	}
}

void Enemy::Draw() {
	if (isEnemyAlive_ == true) {
		Novice::DrawEllipse(
		    int(enemyPos_.x), int(enemyPos_.y), int(enemyRadius_), int(enemyRadius_), 0.0f, RED,
		    kFillModeSolid);
	}
}

void Enemy::SetSpeed(Vector2 speed) {
	enemySpeed_.x = speed.x;
	enemySpeed_.y = speed.y;
}
