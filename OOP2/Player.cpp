#include <cstdlib>
#include <ctype.h>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

void Player::onCollision(GameObject* other)
{
	if (!other) return;

	Enemy* enemy = dynamic_cast<Enemy*>(other);
	if (enemy != nullptr) {
		enemy->take_damage(0.1f);
	}
}


void Player::fire() const
{
	// find the closest enemy from my location
	Vector2 player_center = { position.x + dimension.width / 2.0f, position.y + dimension.height / 2.0f };
	Enemy* closest = nullptr;
	float distToClosest = FLT_MAX;
	for (int i = 0; i < MaxGameObjects; i++)
	{
		if (GameObjects[i] == nullptr || GameObjects[i]->is_active() == false) continue;

		Enemy* enemy = dynamic_cast<Enemy*>(GameObjects[i]);
		if (enemy == nullptr) continue;

		Vector2 enemy_center = enemy->get_center();
		float distToEnemy = player_center.distance(enemy_center);

		if (closest == nullptr || distToEnemy < distToClosest) {
			closest = enemy;
			distToClosest = distToEnemy;
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
		start_pos += get_dimension().width + 1;
		direction = 1;
	}
	bullet->set_fire( { (float)start_pos, position.y }, { (float)direction, 0.0f } );
}

void Player::update(const Screen* screen)
{
	if (this->n_remaining_frames_for_hp_bar > 0) {
		this->n_remaining_frames_for_hp_bar--;
		if (this->n_remaining_frames_for_hp_bar == 0) {
			recover_shape();
		}
		else {
			set_hp_shape();
		}
	}
	if (this->hp <= 0.0f) {
		set_active(false);
		return;
	}
}

void Player::process_input(int major, int minor) {
	switch (tolower(major)) {
	case 'a': 
		position.x--; 
		break;
	case 'd': 
		position.x++; 
		break;
	case 'w':
		position.y--;
		break;
	case 's':
		position.y++;
		break;

	case ' ': fire(); break;
	case 'i': show_hp_bar(); break;
	}
}
