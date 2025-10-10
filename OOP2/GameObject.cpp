#include <cstring>
#include <conio.h>
#include <cassert>
#include <ctype.h>
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
//#include "Boss.h"



int GameObject::MaxGameObjects = 0;
GameObject** GameObject::GameObjects = nullptr;

void GameObject::Initialize()
{
	Vector2 player_initial_pos{ 60, 10 };
	Dimension player_dimension = Dimension{ 6, 3 };
	Vector2 enemy_initial_pos = { 20, 10 };
	Dimension enemy_dimension = { 7, 3 };
	int hello[] = {1, 2, 3, 4};
	const char* player_shape = "(-  -)(+  +)( __ )";
	const char* enemy_shape_normal = "(`   ')(+   +)(  _  )";
	const char* enemy_shape_on_hit = "(` _ ')(T   T)(  _  )";
	const char* boss_shape_normal = "<(+_--_+)>";
	const char* boss_shape_on_hit = "<(T_--_T)>";
	const int n_frames_per_second = 10;
	const int max_crying_animation_frames = 3 * n_frames_per_second;

	MaxGameObjects = 100;
	GameObjects = new GameObject * [MaxGameObjects];
	for (int i = 0; i < MaxGameObjects; i++) GameObjects[i] = nullptr;

	(void)Add(new Player(player_initial_pos, player_dimension, player_shape));
	(void)Add(new Enemy(enemy_shape_normal, enemy_shape_on_hit, max_crying_animation_frames, enemy_initial_pos, enemy_dimension));
	(void)Add(new Enemy(enemy_shape_normal, enemy_shape_on_hit, max_crying_animation_frames, { 10, 5 }, { 7,3 }));
	//(void)Add(new Boss(boss_shape_normal, boss_shape_on_hit, max_crying_animation_frames, 40));
}

void GameObject::Deinitialize()
{
	for (int i = 0; i < MaxGameObjects; i++) {
		if (GameObjects[i] == nullptr) continue;
		delete GameObjects[i];
		GameObjects[i] = nullptr;
	}

	delete[] GameObjects;
	GameObjects = nullptr;
}


void GameObject::Update(Screen* screen)
{
	// check collision
	for (int i = 0; i < MaxGameObjects; i++) {
		if (GameObjects[i] == nullptr || GameObjects[i]->is_active() == false) continue;

		ICollidable* one = dynamic_cast<ICollidable*>(GameObjects[i]);
		if (one == nullptr) continue;
		for (int j = i + 1; j < MaxGameObjects; j++) {
			if (GameObjects[j] == nullptr || GameObjects[j]->is_active() == false) continue;
			ICollidable* another = dynamic_cast<ICollidable*>(GameObjects[j]);
			if (another == nullptr) continue;

			one->examineCollision(another);
		}
	}
	DestroyUnusedObjects();


	for (int i = 0; i < MaxGameObjects; i++) {
		if (GameObjects[i] == nullptr || GameObjects[i]->is_active() == false) continue;
		GameObjects[i]->update(screen);
	}
	DestroyUnusedObjects();
}

GameObject::GameObject(const char* shape, float pos) : shape(nullptr), pos(pos), active(true)
{
	assert(shape != nullptr);
	set_shape(shape);
}

GameObject::~GameObject()
{
	if (this->shape != nullptr) delete[] this->shape;
}

void GameObject::set_shape(const char* shape)
{
	if (shape == nullptr) return;

	if (this->shape != nullptr) delete[] this->shape;

	this->shape = new char[strlen(shape) + 1];
	strcpy(this->shape, shape);
}

void GameObject::draw(Screen* screen) const
{
	if (screen == nullptr) return;
	screen->draw(this);
}

bool GameObject::is_colliding(const GameObject* other) const
{
	float one_pos = get_pos();
	int one_shape_sz = get_shape_size();

	if (other == nullptr) return false;

	float other_pos = other->get_pos();
	int other_shape_sz = other->get_shape_size();

	if (one_pos >= other_pos && one_pos < other_pos + other_shape_sz) return true;
	if (other_pos >= one_pos && other_pos < one_pos + one_shape_sz) return true;

	return false;
}

void GameObject::ProcessInput(bool* exit_flag)
{
	char major, minor = -1;
	int found = -1;

	if (_kbhit() == 0) return;

	major = _getch();
	if (major == -32 || major == 0)
		minor = _getch();

	switch (tolower(major)) {
	case 'q':
		*exit_flag = true;
		return;
	}

	for (int i = 0; i < MaxGameObjects; i++)
	{
		if (GameObjects[i] == nullptr || GameObjects[i]->is_active() == false) continue;

		GameObjects[i]->process_input(major, minor);
	}
}

