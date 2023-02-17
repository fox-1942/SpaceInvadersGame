#pragma once

#include <paddle.h>
#include <bullet.h>
#include <vector>

class Scene
{
public:
	Paddle paddle;
	std::vector<Bullet> bullets;
	std::vector<Element> blocks;
	std::vector<Element> bunkers;

	bool gameStarted;
	bool toRight;
	bool toDown;
	Vector2 centerOfBlocks;

	friend void act(float dt);
	friend void draw();
	friend void handleButtons();

	Scene() {}

	Scene(Paddle _paddle, std::vector<Bullet> _bullets, std::vector<Element> _blocks, std::vector<Element> _bunkers)
		:paddle(_paddle),
		bullets(_bullets),
		blocks(_blocks),
		bunkers(_bunkers),
		gameStarted(false),
		toRight(true),
		toDown(true),
		centerOfBlocks(300, 160)
	{

		Element el = Element(Vector3(0, 255, 0));

		el.setMin(Vector2(centerOfBlocks.x, centerOfBlocks.y));
		el.setMax(Vector2(centerOfBlocks.x + 10, centerOfBlocks.y + 10));

		blocks.push_back(el);
	}

	void shiftPaddleToLeft() {
		if (paddle.getMin().x - 8 > 0) {

			paddle.setMinX(-6);
			paddle.setMaxX(-6);
		}
	}

	void shiftPaddleToRight() {
		if (paddle.getMax().x + 8 < SCREEN_WIDTH)
		{
			paddle.setMinX(6);
			paddle.setMaxX(6);
		}
	}


	void moveSpritesRight(float distance) {
		
		if (centerOfBlocks.x + 200 >= SCREEN_WIDTH)
		{
			toRight = false;
			moveSpritesDown(distance * 10);
		}

		else {
			for (int i = 0; i < blocks.size(); ++i) {
				blocks.at(i).changeXcoords(distance);
		
			}

			centerOfBlocks.x += distance;
		}
	}


	void moveSpritesLeft(float distance) {
		
		if (centerOfBlocks.x - 200 <= 0)
		{
			toRight = true;
			moveSpritesDown(distance * 10);
		}

		else {
			for (int i = 0; i < blocks.size(); ++i) {
				blocks.at(i).changeXcoords(-distance);
			}

			centerOfBlocks.x -= distance;
		}
	}

	void moveSpritesDown(float distance) {
		if (centerOfBlocks.y + 300 >= SCREEN_HEIGHT)
		{
			initialize();
		}

		else {
			for (int i = 0; i < blocks.size(); ++i) {
				blocks.at(i).changeYcoords(distance);
			}
			centerOfBlocks.y += distance;
		}
	}
};
