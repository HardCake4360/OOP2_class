#pragma once
#include "GameObject.h"
class Particle :
    public GameObject
{
	float speed;
	int	n_remaining_frames;

public:
	Particle() : GameObject("+", 0.0f), speed(0.0f), n_remaining_frames(0) {}
	~Particle();

	void	update(const Screen* screen) override;
	void	spawn(int n_remaining_frames, float pos, float speed);

private:
	static int MaxFramesParticlesVisible;
	static int MaxActiveParticlesPerBullet;

public:
	static void	SpawnParticles(int pos, int direction);
	static void Initialize(int max_particle_visible_frames, int max_active_particles_per_bullet)
	{
		MaxFramesParticlesVisible = max_particle_visible_frames;
		MaxActiveParticlesPerBullet = max_active_particles_per_bullet;
	}

};

