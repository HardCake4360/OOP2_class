#pragma once
#include "GameObject.h"
#include "ICollidable.h"

class Bullet : public GameObject, public ICollidable {

	int direction;

public:
	Bullet() : GameObject("*", -1.0f), ICollidable(), direction(0)
	{
		setGameObject(this);
	}
	~Bullet() {}

	void onCollision(GameObject* other) override;

	void set_direction(int direction = 1) { this->direction = direction; }
	int  get_direction() const { return direction; }

	void	set_fire(int pos, int direction);
	void	update(const Screen* screen) override;
};
