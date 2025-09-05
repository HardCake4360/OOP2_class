#include <math.h>

#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"

Enemy::~Enemy()
{
	this->max_frames_crying_on_hit = 0;
	this->shape_in_normal = nullptr;
	this->shape_on_hit = nullptr;
	this->current_n_remaining_frames_on_hit = 0;
}

void Enemy::fire() const
{
	// find the closest enemy from my location
	Player* closest = nullptr;
	for (int i = 0; i < MaxGameObjects; i++)
	{
		if (GameObjects[i] == nullptr || GameObjects[i]->is_active() == false) continue;

		Player* player = dynamic_cast<Player*>(GameObjects[i]);
		if (player == nullptr) continue;

		if (closest == nullptr) {
			closest = player;
			continue;
		}
		if (fabs(closest->get_pos() - get_pos()) > fabs(player->get_pos() - get_pos())) {
			closest = player;
		}
	}

	// if found, shoot a bullet.

	Bullet* bullet = new Bullet;
	if (Add(bullet) == false) {
		delete bullet;
		return;
	}

	int start_pos = (int)get_pos() - 1;
	int direction = -1;
	if (closest == nullptr) {
		direction = rand() % 2 == 0 ? -1 : 1;
	}
	if ((closest != nullptr && get_pos() < closest->get_pos()) || direction == 1) {
		start_pos += get_shape_size() + 1;
		direction = 1;
	}
	bullet->set_fire(start_pos, direction);
}



void Enemy::onCollision(GameObject* other)
{
	if (!other) return;

	Player* player = dynamic_cast<Player*>(other);
	if (player != nullptr) {
		player->take_damage(0.1f);
	}
}

void Enemy::cry()
{
	set_shape(this->shape_on_hit);
	this->current_n_remaining_frames_on_hit = this->max_frames_crying_on_hit;
}

void Enemy::decry()
{
	set_shape(this->shape_in_normal);
	this->current_n_remaining_frames_on_hit = 0;
}

void Enemy::update(const Screen* screen)
{
	if (this->current_n_remaining_frames_on_hit == 0) return;

	// enemy is crying now

	this->current_n_remaining_frames_on_hit--;
	if (this->current_n_remaining_frames_on_hit == 0) {
		this->decry();
	}
}