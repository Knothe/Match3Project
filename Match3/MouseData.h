#pragma once
#include "Vec2.h"

struct MouseData {
	bool leftButton;
	bool rightButton;
	Vec2 position;
	MouseData() {
		leftButton = false;
		rightButton = false;
	}
};