#pragma once

class GameObject;

class Screen
{
	int n_frames_per_second;
	int size;
	char* canvas;

public:
	Screen(int size, int n_frames_per_second) : n_frames_per_second(n_frames_per_second), size(size), canvas(new char[size + 1]) {}
	~Screen();

	int		length() const { return size; }
	void	clear();
	void	draw(int pos, const char* shape);
	void	draw(const GameObject* obj);
	void	render();
};
