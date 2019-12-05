#include "Vec2.h"
Vec2::Vec2() {
	x = 0;
	y = 0;
}
Vec2::Vec2(int x, int y) {
	this->x = x;
	this->y = y;
}

bool Vec2::operator<(const Vec2 other) {
	if (x < other.x && y < other.y)
		return true;
	return false;
}
bool Vec2::operator>(const Vec2 other) {
	if (x > other.x && y > other.y)
		return true;
	return false;
}
Vec2 Vec2::operator+(const Vec2 other) {
	Vec2 v;
	v.x = x + other.x;
	v.y = y + other.y;
	return v;
}

Vec2 Vec2::operator*(int n) {
	Vec2 v;
	v.x = x * n;
	v.y = y * n;
	return v;
}

void Vec2::operator=(const Vec2 other) {
	x = other.x;
	y = other.y;
}

Vec2::~Vec2() {

}