#pragma once

#include "Element.h"
#include "Engine.h"

class Bullet : public Element
{
private:
	bool north, south;
	float distance;
	
public:
	bool userBullet;

	Bullet() = default;

	Bullet(unsigned _width, unsigned _height, Vector3 _color, Element& element, bool _userBullet):
		Element(_color),
		userBullet(_userBullet)
	{

		if(userBullet)
		{
			min = Vector2((element.getMin().x + (element.getMax().x - element.getMin().x) / 2) - (_width / 2),
				SCREEN_HEIGHT - _height - 40);

			max = Vector2(min.x + _width, min.y + _height);

			north = true;
			south = false;
		}

		// shoots by enemy sprites
		else
		{
			min = Vector2((element.getMin().x + (element.getMax().x - element.getMin().x) / 2) - (_width / 2),
				element.getMin().y - 3);

			max = Vector2(min.x + _width, min.y + _height);

			north = false;
			south = true;
		}
	}

	bool isCollided(Element& other)
	{
		if (min.x < other.getMax().x &&
			max.x > other.getMin().x &&
			max.y >= other.getMin().y &&
			min.y < other.getMin().y
		)
		{
			return true;
		}

		if (min.x < other.getMax().x &&
			max.x > other.getMin().x &&
			max.y > other.getMax().y &&
			min.y <= other.getMax().y
		)
		{
			return true;
		}

		if (min.y < other.getMax().y &&
			max.y > other.getMin().y &&
			max.x >= other.getMin().x &&
			min.x < other.getMin().x)
		{
			return true;
		}

		if (min.y < other.getMax().y &&
			max.y > other.getMin().y &&
			min.x <= other.getMax().x &&
			max.x > other.getMax().x)
		{
			return true;
		}

		return false;
	}

	void set_north(bool north)
	{
		this->north = north;
	}

	void set_south(bool south)
	{
		this->south = south;
	}


	bool outOfPlayingZone(float dt)
	{
		distance = dt * 80;
		if (north)
		{
			if (min.y - distance > 0)
			{
				min.y -= distance;
				max.y -= distance;
			}

			else
			{
				return true;
			}
		}

		else
		{
			if (south)
			{
				if (max.y < SCREEN_HEIGHT)
				{
					max.y += distance;
					min.y += distance;
				}

				else
				{
					return true;
				}
			}
		}

		return false;
	}
};
