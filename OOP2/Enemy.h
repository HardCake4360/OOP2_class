#pragma once

#include "GameObject.h"
#include "ICollidable.h"

class Enemy :
    public GameObject, public ICollidable
{
	Vector2 position;
	Dimension dimension;

	int max_frames_crying_on_hit;
	const char* shape_in_normal;
	const char* shape_on_hit;
	int current_n_remaining_frames_on_hit;

	float hp;
	float speed;

protected:

	void fire() const;

public:

	Enemy(const char* shape_in_normal, 
		const char* shape_on_hit, 
		int max_frames_crying_on_hit, 
		const Vector2& position, const Dimension& dimension);
	~Enemy();

	void onCollision(GameObject* other) override;

	void set_hp(float hp) { this->hp = hp; }

	float get_hp() const { return hp; }

	Vector2 get_position() const { return position; }

	Dimension get_dimension() const { return dimension; }

	Vector2 get_center() const { return { position.x + dimension.width / 2.0f, position.y + dimension.height / 2.0f }; }

	float get_speed() const { return speed; }

	void take_damage(float damage)
	{
		cry();
		hp -= damage;
		if (hp <= 0.0f) {
			set_active(false);
		}
	}

	void process_input(int major, int minor) override;

	void	cry();
	void	decry();
	void	update(const Screen* screen) override;

	void draw(Screen* screen) const override {
		screen->draw(position, dimension, get_shape());
	}


};

