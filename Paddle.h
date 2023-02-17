#pragma once

#include "Engine.h"
#include "Element.h"

class Paddle : public Element
{
public:
	bool leftShift;
	bool rightShift;

	Paddle() = default;

	Paddle(unsigned int _width, unsigned int _height, Vector3 _color) : Element(_color),
		leftShift(false),
		rightShift(false)
	{
		min = Vector2((SCREEN_WIDTH / 2) - (_width / 2), SCREEN_HEIGHT - _height - 20);
		max = Vector2(min.x + _width, min.y + _height);
	}
};