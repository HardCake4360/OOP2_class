#pragma once
#include "GameObject.h"

class ICollidable
{
protected:
	GameObject* gameObject;

	bool is_colliding(ICollidable* other) const {
		return gameObject->is_colliding(other->gameObject);
	}

	void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }

public:
	ICollidable() :gameObject(nullptr) {}

	virtual void onCollision(GameObject* other) {}

	void examineCollision(ICollidable* other) {
		if (gameObject->is_active() == false || other->gameObject->is_active() == false) return;
		if (is_colliding(other) == true) {
			onCollision(other->gameObject);
			other->onCollision(this->gameObject);
		}
	}
};

