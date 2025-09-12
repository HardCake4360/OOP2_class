#include <stdio.h>
#include <cstring>
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
	for (int i = 0; i < height; i++) {
		this->canvas[i*(width+1)] = '\n';
	}
	this->canvas[this->size] = '\0';
}

void Screen::draw(int pos, const char* shape)
{
	for (int i = 0; i < (int)strlen(shape); i++) {
		if (pos + i < 0 || pos + i >= this->size) continue;
		this->canvas[pos + i] = shape[i];
	}
}

void Screen::draw(Vector2 pos, const char* shape, int shape_height, int shape_width) {
	for (int i = 0; i < (int)strlen(shape); i++) {
		if (pos.x + i < 0 || pos.x + i >= this->width) continue;
		if (pos.x + i < 0 || pos.x + i >= this->height) continue;
		this->canvas;
	}

}

void Screen::draw(const GameObject* obj)
{
	if (obj == nullptr) return;
	draw((int)obj->get_pos(), obj->get_shape());
}

void Screen::render()
{
	GotoXY(0, 0);
	this->canvas[this->size] = '\0';
	printf("%s\n", this->canvas);
	GotoXY(0, height);
	printf("[%2d]", GameObject::GetNumOfActiveObjects());
	Sleep(1000 / this->n_frames_per_second);
}