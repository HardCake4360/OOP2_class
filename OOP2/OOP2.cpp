#include <cstdio>
#include <cstdlib>
#include <cstring> 
#include <conio.h>  // _getch, _kbhit
#include <Windows.h> // Sleep()
#include <cassert>

#include "Screen.h"
#include "GameObject.h"
#include "Particle.h"

int main()
{
	const int screen_width = 80;
	const int screen_height = 20;
	const int max_bullets = 5;
	const int max_active_particles_per_bullet = 5;
	const int n_frames_per_second = 10;
	const int max_crying_animation_frames = 3 * n_frames_per_second;
	const int max_particle_visible_frames = 1 * n_frames_per_second;
	bool exit_flag = false;

	Vector2 pos1 = { 2, 2 };
	Vector2 pos2 = { 1, 3 };

	Vector2 pos3 = pos1 + pos2;//{3,5}
	Vector2 pos3_2 = pos1.operator+(pos2);//{3,5}
	Vector2 pos4 = pos3 - pos1;//{1,3}
	if (pos2 == pos4) {
		printf("two Vectors are identical");
	}
	if (pos2.equalApproximately(pos4)) {
		printf("two Vectors are approximately equal");
	}
	Vector2 pos5 = pos4 * 2.0f; // {2,6} 정수, float, double 연산 가능
	Vector2 pos6 = 2.0 * pos5; //{4,12}
	Vector2 pos7 = pos6 / 2.0f; //{4,12}
	Vector2 pos8 = pos7.unit();
	float sqrMag = pos8.sqrMagnitude(); // x*x + y*y
	float mag = pos8.magnitude(); // sqrt(x*x + y*y)




	Screen screen(screen_width, screen_height, n_frames_per_second);
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