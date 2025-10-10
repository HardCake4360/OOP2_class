#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Particle.h"

void Bullet::set_fire(const Vector2& position, const Vector2& direction)
{
	this->position = position;
	set_pos(position.x);
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
		//Particle::SpawnParticles((int)get_pos(), get_direction() * -1);
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
	int pos = (int)position.x;
	if (pos < 0 || pos >= screen->length()) {
		this->set_active(false);
		return;
	}

	position = { position.x + direction.x * 0.5f, position.y + direction.y * 0.5f };
	GotoXY(0, 24);
	printf("bullet pos: %2.0f %2.0f, direction = %2.0f %2.0f", position.x, position.y, direction.x, direction.y);
	set_pos(position.x);
}

