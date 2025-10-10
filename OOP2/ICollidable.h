#pragma once

#include "GameObject.h"

class ICollidable
{
protected:
	GameObject* gameObject;

	bool is_colliding(ICollidable* other) const;

	void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }

public:
	ICollidable() :gameObject(nullptr) {}

	virtual void onCollision(GameObject* other) {}

	void examineCollision(ICollidable* other);
};

