#pragma once
#include <cstdio>
#include <cstring>
#include <Windows.h>

#include "Screen.h"
#include "GameObject.h"

class GameObject
{
	char* shape;
	float	pos;
	bool	active;

public:
	GameObject(const char* shape, float pos);
	virtual ~GameObject();

	void set_active(bool active = true) { this->active = active; }
	bool is_active() const { return this->active; }

	void set_shape(const char* shape);
	const char* get_shape() const { return shape; }
	int get_shape_size() const { return (int)strlen(shape); }

	void set_pos(float pos) { this->pos = pos; }
	float get_pos() const { return pos; }

	void move(float delta) { set_pos(get_pos() + delta); }

	virtual void draw(Screen* screen) const;
	virtual void process_input(int major, int minor) {}

	virtual void update(const Screen* screen) {}
	virtual bool is_colliding(const GameObject* other) const;

private:
	static void DestroyUnusedObjects()
	{
		for (int i = 0; i < MaxGameObjects; i++) {
			if (GameObjects[i] && GameObjects[i]->is_active() == false) {
				delete GameObjects[i];
				GameObjects[i] = nullptr;
			}
		}
	}

protected:
	static int MaxGameObjects;
	static GameObject** GameObjects;

public:

	static void Initialize();
	static void Deinitialize();
	static bool Add(GameObject* newGameObject)
	{
		for (int i = 0; i < MaxGameObjects; i++) {
			if (GameObjects[i] != nullptr) continue;

			GameObjects[i] = newGameObject;
			return true;
		}
		return false;
	}
	static int GetNumOfActiveObjects()
	{
		int count = 0;
		for (int i = 0; i < MaxGameObjects; i++) {
			if (GameObjects[i] && GameObjects[i]->is_active()) count++;
		}
		return count;
	}

	static void ProcessInput(bool* exit_flag);
	static void Draw(Screen* screen)
	{
		DestroyUnusedObjects();
		for (int i = 0; i < MaxGameObjects; i++) {
			if (GameObjects[i] == nullptr || GameObjects[i]->is_active() == false) continue;
			GameObjects[i]->draw(screen);
		}
	}
	static void Update(Screen* screen);
};