#pragma once

class GameObject;
#include "Utils.h"

class Screen
{
	int n_frames_per_second;
	int size;
	int width;
	int height;
	char* canvas;

public:
	Screen(int width, int height, int n_frames_per_second)
		: n_frames_per_second(n_frames_per_second),
		height(height),
		width(width),
		size( (width+1)*height),
		canvas(new char[size]) {
		clear();
	}
	~Screen();

	int		length() const { return size; }
	void	clear();
	void	draw(int pos, const char* shape, int width_to_draw);
	void	draw( const Vector2& position, const Dimension& dimension, const char* shape);
	void	draw(const GameObject* obj);
	void	render();
};


