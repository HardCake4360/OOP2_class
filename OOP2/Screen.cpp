
#include <cstdio>
#include <cstring>
#include <Windows.h>
#include "Screen.h"
#include "GameObject.h"
#include "Utils.h"


Screen::~Screen()
{
	this->size = 0;
	if (this->canvas)
		delete[] this->canvas;
	this->canvas = nullptr;
}

void Screen::clear()
{
	memset(this->canvas, '#', this->size);
	this->canvas[this->size] = '\0';
	for (int h = 0; h < height; h++)
		this->canvas[h * (width + 1) + width] = '\n';
	this->canvas[this->size] = '\0';
}

void Screen::draw(int pos, const char* shape, int width_to_draw)
{
	int canvas_x = pos % (width + 1);
	int canvas_y = pos / (width + 1);
	if (canvas_y < 0 || canvas_y >= height) return;
	
	for (int i = 0; i < width_to_draw; i++) {
		if (canvas_x + i < 0 || canvas_x + i >= width) continue;
		this->canvas[pos + i] = shape[i];
	}
}

void Screen::draw(const Vector2& position, const Dimension& dimension, const char* shape)
{
	int screen_x = (int)position.x;
	int screen_y = (int)position.y;
	for (int h = 0; h < dimension.height; h++) {
		int canvas_pos = (screen_y + h) * (width + 1) + screen_x;
		int shape_pos = h * dimension.width;
		draw(canvas_pos, (const char*)(shape + shape_pos), dimension.width);
	}
}


void Screen::draw(const GameObject* obj)
{
	if (obj == nullptr) return;
	draw((int)obj->get_pos(), obj->get_shape(), strlen(obj->get_shape()) );
}

void Screen::render()
{
	this->canvas[this->size] = '\0';
	GotoXY(0, 0);
	printf("%s", this->canvas);
	GotoXY(0, height);
	printf("[%d]", GameObject::GetNumOfActiveObjects());
	
	Sleep(1000 / this->n_frames_per_second);
}
