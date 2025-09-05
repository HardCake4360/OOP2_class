#include "Particle.h"


int Particle::MaxFramesParticlesVisible = 0;
int Particle::MaxActiveParticlesPerBullet = 0;

Particle::~Particle()
{
	this->speed = 0.0f;
	this->n_remaining_frames = 0;
}

void Particle::update(const Screen* screen)
{
	if (this->n_remaining_frames == 0) return;

	this->n_remaining_frames--;
	if (this->n_remaining_frames == 0) {
		set_active(false);
		return;
	}
	move(this->speed);
}

void Particle::spawn(int n_remaining_frames, float pos, float speed)
{
	this->n_remaining_frames = n_remaining_frames;
	this->speed = speed;
	set_pos(pos);
}

void Particle::SpawnParticles(int pos, int direction)
{
	int current_active_particles = 0;

	for (int i = 0; i < MaxActiveParticlesPerBullet; i++) {
		Particle* particle = new Particle;
		if (Add(particle) == false) {
			delete particle;
			return;
		}
		particle->spawn(MaxFramesParticlesVisible,
			(float)pos,
			direction * (float)(rand() % 10) / 10.0f);
	}
}
