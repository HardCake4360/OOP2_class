#include <cstdio>
#include <cstdlib>
#include <cstring> 
#include <conio.h>  // _getch, _kbhit
#include <Windows.h> // Sleep()
#include <cassert>

#include "Boss.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameObject.h"
#include "ICollidable.h"
#include "Particle.h"
#include "Player.h"
#include "Screen.h"


int main()
{
	const int screen_size = 80;
	const int max_bullets = 5;
	const int max_active_particles_per_bullet = 5;
	const int n_frames_per_second = 10;
	const int max_crying_animation_frames = 3 * n_frames_per_second;
	const int max_particle_visible_frames = 1 * n_frames_per_second;
	bool exit_flag = false;

	Screen screen(screen_size, n_frames_per_second);
	GameObject::Initialize();
	Particle::Initialize(max_particle_visible_frames, max_active_particles_per_bullet);

	while (exit_flag == false) {
		screen.clear();
		GameObject::ProcessInput(&exit_flag);
		GameObject::Draw(&screen);
		GameObject::Update(&screen);
		screen.render();
	}
	GameObject::Deinitialize();

	return 0;
}