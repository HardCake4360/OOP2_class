#include <stdio.h>
#include <cstring>
#include "Screen.h"
#include "GameObject.h"

Screen::~Screen()
{
	this->size = 0;
	if (this->canvas)
		delete[] this->canvas;
	this->canvas = nullptr;
}

void Screen::clear()
{
	memset(this->canvas, ' ', this->size);
	this->canvas[this->size] = '\0';
}

void Screen::draw(int pos, const char* shape)
{
	for (int i = 0; i < (int)strlen(shape); i++) {
		if (pos + i < 0 || pos + i >= this->size) continue;
		this->canvas[pos + i] = shape[i];
	}
}

void Screen::draw(const GameObject* obj)
{
	if (obj == nullptr) return;
	draw((int)obj->get_pos(), obj->get_shape());
}

void Screen::render()
{
	this->canvas[this->size] = '\0';
	printf("%s\r", this->canvas);
	printf("[%2d]\r", GameObject::GetNumOfActiveObjects());
	Sleep(1000 / this->n_frames_per_second);
}