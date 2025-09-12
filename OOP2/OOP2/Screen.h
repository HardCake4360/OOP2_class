#pragma once
#include "Utils.h"

class GameObject;

class Screen
{
	int n_frames_per_second;
	int size;
	char* canvas;
	int width;
	int height;

public:
	Screen(int height,int width,
		int n_frames_per_second) : n_frames_per_second(n_frames_per_second),
		height(height),
		width(width),
		size((height+1)*width), canvas(new char[size + 1]) {}
	~Screen();

	int		length() const { return size; }
	void	clear();
	void	draw(int pos, const char* shape);
	void	draw(Vector2 pos, const char* shape, int shape_height, int shape_width);
	void	draw(const GameObject* obj);
	void	render();
};
