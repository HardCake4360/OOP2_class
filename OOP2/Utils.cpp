
#include "Utils.h"
#include <cmath>

Vector2 Vector2::Left	{ -1.0f, 0.0f };
Vector2 Vector2::Right	{ 1.0f, 0.0f };
Vector2 Vector2::Up		{ 0.0f, -1.0f };
Vector2 Vector2::Down	{ 0.0f, 1.0f };
Vector2 Vector2::Zero	{ 0.0f, 0.0f };
Vector2 Vector2::One	{ 1.0f, 1.0f };

Vector2 operator+(const Vector2& one, const Vector2& another) {
	return { one.x + another.x,one.y + another.y };
}

void GotoXY(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, COORD{ static_cast<SHORT>(x), static_cast<SHORT>(y) });
}
