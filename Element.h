#pragma once
#include <iostream>

struct Vector3 {
	unsigned char x, y, z;

	Vector3() = default;

	Vector3(unsigned char x_, unsigned char y_, unsigned char z_) {
		x = x_;
		y = y_;
		z = z_;
	}
};

struct Vector2 {
	int x, y;

	Vector2() = default;

	Vector2(int x_, int y_) {
		x = x_;
		y = y_;
	}
};

class Element
{

protected:
	Vector2 min;
	Vector2 max;
	Vector3 colour;
	int lives;

public:


	Element() = default;

	Element(Vector3 _colour) :
		colour(_colour),
		lives(3) {

	}

	Vector2 getMin() { return min; }
	Vector2 getMax() { return max; }

	int getLives() { return lives; }
	void setLives(int _lives) { lives=_lives; }
	void reduceLife() { --lives; }


	void setMin(Vector2 _min) { min = _min; }
	void setMax(Vector2 _max) { max = _max; }

	void setMinX(int param) { min.x += param; }
	void setMaxX(int param) { max.x += param; }

	void setMinY(int param) { min.y += param; }
	void setMaxY(int param) { max.y += param; }

	void changeXcoords(float value) {
		min.x += value;
		max.x += value;

	}

	void changeYcoords(float value) {
		min.y += value;
		max.y += value;
	}


	bool isOnScreen(unsigned row, unsigned column)
	{
		if (min.x <= column && max.x >= column &&
			min.y <= row && max.y >= row)
		{
			return true;
		}
		return false;
	}

	uint32_t getColour() {
		return (colour.x << 16) | (colour.y << 8) | colour.z;
	}
};