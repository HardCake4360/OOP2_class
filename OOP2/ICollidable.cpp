
#include "ICollidable.h"
#include "GameObject.h"

bool ICollidable::is_colliding(ICollidable* other) const {
	return gameObject->is_colliding(other->gameObject);
}

void ICollidable::examineCollision(ICollidable* other) {
	if (gameObject->is_active() == false || other->gameObject->is_active() == false) return;
	if (is_colliding(other) == true) {
		onCollision(other->gameObject);
		other->onCollision(this->gameObject);
	}
}