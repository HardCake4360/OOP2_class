#include <cstdlib>
#include <ctype.h>
#include "Boss.h"
#include "Player.h"


void Boss::move_toward_player()
{
	Player* player = nullptr;
	for (int i = 0; i < MaxGameObjects; i++)
	{
		if (GameObjects[i] == nullptr || GameObjects[i]->is_active() == false) continue;
		player = dynamic_cast<Player*>(GameObjects[i]);
		if (player != nullptr) break;
	}
	if (player == nullptr) return;
	float player_pos = player->get_pos();
	float boss_pos = get_pos();
	if (fabs(player_pos - boss_pos) < 1.0f) return;
	if (boss_pos < player_pos) {
		move(get_speed() * 2);
	}
	else {
		move(-get_speed() * 2);
	}
}

void Boss::update(const Screen* screen)
{
	const char* enemy_shape_normal = "(+ ~ +/)";
	const char* enemy_shape_on_hit = "(T _ T/)";
	const int n_frames_per_second = 10;
	const int max_crying_animation_frames = 3 * n_frames_per_second;

	Enemy::update(screen);
	if (this->n_remaining_frames_for_current_pattern > 0) {
		this->n_remaining_frames_for_current_pattern--;
		if (this->n_remaining_frames_for_current_pattern > 0) {
			if (current_pattern == 1) {
				//move_toward_player();
			}
			return;
		}
		if (current_pattern == 0) {
			fire();
		}
		else if (current_pattern == 2) {
			(void)Add(new Enemy(enemy_shape_normal, enemy_shape_on_hit, max_crying_animation_frames, rand() % 80));
			(void)Add(new Enemy(enemy_shape_normal, enemy_shape_on_hit, max_crying_animation_frames, rand() % 80));
		}
	}

	if (get_hp() <= 50.0f) {
		current_pattern = 2;
	}
	else {
		current_pattern = rand() % 2;
	}

	switch (current_pattern) {
	case 0:
		n_remaining_frames_for_current_pattern = 2 * 30;
		break;

	case 1:
		n_remaining_frames_for_current_pattern = 5 * 30;
		break;

	case 2:
		n_remaining_frames_for_current_pattern = 10 * 30;
		break;
	}
}

