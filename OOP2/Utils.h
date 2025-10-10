#pragma once

#include <windows.h>
#include <iostream>
#include <cmath>

struct Vector2 {
	float x;
	float y;

	static Vector2 Left;
	static Vector2 Right;
	static Vector2 Up;
	static Vector2 Down;
	static Vector2 Zero;
	static Vector2 One;

	Vector2 operator-(const Vector2& another) {
		return Vector2{ this->x - another.x, this->y - another.y };
	}

	bool operator==(const Vector2& another) {
		return this->x == another.x && this->y == another.y;
	}

	Vector2 operator*(float scale) const {
		return Vector2{ this->x * scale,this->y * scale };
	}

	Vector2 operator/(float scale) const {
		if (scale == 0.0f) return *this;
		return *this * (1.0f / scale);
	}

	friend float Distance(const Vector2& one, const Vector2& another)
	{
		return sqrt((one.x - another.x) * (one.x - another.x) + (one.y - another.y) * (one.y - another.y));
	}

	float distance(const Vector2& another) const {
		return Distance(*this, another);
	}

	float sqrMagnitude() const {
		return this->x * this->x + this->y * this->y;
	}
	float magnitude() const {
		return sqrt(sqrMagnitude());
	}

	Vector2 unit()const {
		return *this / magnitude();
	}

	bool equalApproximately(const Vector2& another) const {
		float dist = Distance(*this, another);
		return dist <= 0.1f;
	}

	Vector2 operator+(const Vector2 & one) {
		return { one.x + this->x,one.y + this->y };
	}

	friend Vector2 operator+(const Vector2& one, const Vector2& another);
	friend Vector2 operator*(float scale, const Vector2& one) {
		return one * scale;
	}
};

//extern Vector2 operator+(const Vector2& one, const Vector2& another);


struct Dimension {
	int width;
	int height;
};

extern void GotoXY(int x, int y);