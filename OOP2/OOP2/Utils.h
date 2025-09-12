#pragma once

#include <windows.h>
#include <iostream>

struct Vector2 {
	int x;
	int y;
	
	Vector2(int x,int y):x(x),y(y){}
};
void GotoXY(int x, int y);
