#pragma once
#include "GameObject.h"
#include "ICollidable.h"

class Bullet :
    public GameObject, public ICollidable
{
	Vector2 position;
	Dimension dimension;
	Vector2 direction;

public:
	Bullet(const Vector2& position = Vector2::Left, const Dimension& dimension = {1, 1})
		: GameObject(" ", -1.0f), ICollidable(), direction(Vector2::Zero), position(position), dimension(dimension)
	{
		setGameObject(this);
	}
	~Bullet() {}

	void onCollision(GameObject* other) override;

	void set_direction(const Vector2& direction = Vector2::Right) { this->direction = direction; }
	Vector2  get_direction() const { return direction; }

	void	set_fire(const Vector2& pos, const Vector2& direction);
	void	update(const Screen* screen) override;

	void draw(Screen* screen) const override {
		screen->draw(position, dimension, get_shape());
	}

};

