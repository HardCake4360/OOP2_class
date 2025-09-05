#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Particle.h"


void Bullet::set_fire(int pos, int direction)
{
	set_pos((float)pos);
	set_direction(direction);
}

void Bullet::onCollision(GameObject* other)
{
	if (!other) return;

	Player* player = dynamic_cast<Player*>(other);
	if (player) {
		player->take_damage(1.0f);
		this->set_active(false);
		return;
	}
	Enemy* enemy = dynamic_cast<Enemy*>(other);
	if (enemy) {
		enemy->take_damage(1.0f);
		Particle::SpawnParticles((int)get_pos(), get_direction() * -1);
		this->set_active(false);
		return;
	}
	Bullet* bullet = dynamic_cast<Bullet*>(other);
	if (bullet) {
		this->set_active(false);
		return;
	}
}

void Bullet::update(const Screen* screen)
{

	if (!screen) return;
	int pos = (int)get_pos();
	if (pos < 0 || pos >= screen->length()) {
		this->set_active(false);
		return;
	}

	move(0.5f * get_direction());
}

