#pragma once
#include <cstdio>

#include "GameObject.h"
#include "ICollidable.h"
#include "Screen.h"
#include "Utils.h"


class Player :
    public GameObject, public ICollidable
{
	float hp;
	int n_remaining_frames_for_hp_bar;
	const char* original_shape;
	char* hp_shape;
	Vector2 position;
	Dimension dimension;

	void show_hp_bar()
	{
		n_remaining_frames_for_hp_bar = 30;
		set_hp_shape();
	}

	void recover_shape()
	{
		set_shape(original_shape);
	}

	void set_hp_shape()
	{
		int sz = get_shape_size();
		hp_shape[0] = '[';
		int n_hp = (int)(sz * hp / 10.0f);
		if (n_hp <= 0) n_hp = 0;
		for (int i = 0; i < sz; i++) {
			hp_shape[1 + i] = ' ';
			if (i < n_hp) {
				hp_shape[1 + i] = '#';
			}
		}
		hp_shape[1 + sz] = ']';
		hp_shape[2 + sz] = '\0';
	}

public:
	Player(const Vector2& position, const Dimension& dimension, const char* shape) 
		: GameObject(shape, (float)position.x), ICollidable(),
		position(position),
		dimension(dimension),
		hp(10.0f),
		n_remaining_frames_for_hp_bar(0),
		original_shape(nullptr),
		hp_shape(nullptr)
	{
		setGameObject(this);
		original_shape = shape;
		int sz = get_shape_size();
		hp_shape = new char[sz + 2 + 1];
	}
	~Player() {
		delete[] hp_shape;
	}

	void onCollision(GameObject* other) override;

	void take_damage(float damage)
	{
		hp -= damage;
		show_hp_bar();
		if (hp <= 0.0f) {
			set_active(false);
		}
	}

	void process_input(int major, int minor) override;

	void	fire() const;

	Dimension get_dimension() const { return dimension; }

	void update(const Screen* screen) override;

	void draw(Screen* screen) const override {
		screen->draw( position, dimension, get_shape());
		if (n_remaining_frames_for_hp_bar > 0) {
			screen->draw((int)get_pos() - 1, hp_shape, (int)strlen(hp_shape));
		}
	}

};

