#pragma once
#include "GameObject.h"
#include "ICollidable.h"

class Enemy : public GameObject, public ICollidable {

	int max_frames_crying_on_hit;
	const char* shape_in_normal;
	const char* shape_on_hit;
	int current_n_remaining_frames_on_hit;

	float hp;
	float speed;

protected:

	void fire() const;

public:

	Enemy(const char* shape_in_normal, const char* shape_on_hit, int max_frames_crying_on_hit, int pos) :
		GameObject(shape_in_normal, (float)pos),
		max_frames_crying_on_hit(max_frames_crying_on_hit),
		shape_in_normal(shape_in_normal), shape_on_hit(shape_on_hit),
		current_n_remaining_frames_on_hit(0), ICollidable(), hp(10.0f), speed(0.1f)
	{
		setGameObject(this);
	}
	~Enemy();

	void onCollision(GameObject* other) override;

	void set_hp(float hp) { this->hp = hp; }

	float get_hp() const { return hp; }

	float get_speed() const { return speed; }

	void take_damage(float damage)
	{
		cry();
		hp -= damage;
		if (hp <= 0.0f) {
			set_active(false);
		}
	}

	void process_input(int major, int minor) override {
		switch (tolower(major)) {
		case -32: // arrow key
			if (minor == 75) {
				move(-1 * speed);
			}
			else if (minor == 77) {
				move(1 * speed);
			}
			break;
		case 13:
			fire();
			break;
		}
	}

	void	cry();
	void	decry();
	void	update(const Screen* screen) override;
};
