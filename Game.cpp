#include "scene.h"

Scene scene;

// initialize game data in this function
void initialize()
{
	std::vector<Element> blocks;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			blocks.push_back(Element(Vector3(0, 130, 0)));
			blocks[(i * 3) + j].setMin(Vector2(i * 80 + 150, j * 60 + 100));
			blocks[(i * 3) + j].setMax(Vector2(blocks[(i * 3) + j].getMin().x + 60,
				blocks[(i * 3) + j].getMin().y + 40));
		}
	}

	std::vector<Bullet> bullets;
	std::vector<Element> bunkers;

	for (int j = 0; j < 3; ++j)
	{
		bunkers.push_back(Element(Vector3(130, 130, 0)));
		bunkers[j].setLives(5);
		bunkers[j].setMin(Vector2(j * 100 + 170, 670));
		bunkers[j].setMax(Vector2(bunkers[j].getMin().x + 60,
			bunkers[j].getMin().y + 40));
	}


	scene = Scene(Paddle(60, 30, Vector3(255, 0, 0)), bullets, blocks, bunkers);
}

void draw()
{
	// clear backbuffer
	memset(buffer, 200, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));


	// Querying the colour into the buffer.
	for (int i = 0; i < SCREEN_HEIGHT; ++i)
	{
		for (int j = 0; j < SCREEN_WIDTH; ++j)
		{
			if (scene.paddle.isOnScreen(i, j))
			{
				buffer[i][j] = scene.paddle.getColour();
			}

			for (size_t k = 0; k < scene.bullets.size(); ++k)
			{
				if (scene.bullets.at(k).isOnScreen(i, j))
				{
					buffer[i][j] = scene.bullets.at(k).getColour();
				}
			}

			for (size_t m = 0; m < scene.blocks.size(); ++m)
			{
				if (scene.blocks[m].isOnScreen(i, j))
					buffer[i][j] = scene.blocks[m].getColour();
			}

			for (size_t m = 0; m < scene.bunkers.size(); ++m)
			{
				if (scene.bunkers[m].isOnScreen(i, j))
					buffer[i][j] = scene.bunkers[m].getColour();
			}

		}
	}
}


void checkCollisions() {
	for (auto it = scene.bullets.begin(); it != scene.bullets.end();)
	{
   		if ((*it).userBullet == false && (*it).isCollided(scene.paddle))
		{
			scene.paddle.reduceLife();
			it = scene.bullets.erase(it);
		}
		++it;
	}

	for (auto itBunker = scene.bunkers.begin(); itBunker != scene.bunkers.end();)
	{
		for (auto it = scene.bullets.begin(); it != scene.bullets.end();)
		{
			if ((*it).isCollided(*itBunker))
			{
				it = scene.bullets.erase(it);
				(*itBunker).reduceLife();
				
			}

			else {	++it; }
		}

		if ((*itBunker).getLives() <= 0)
		{
			itBunker = scene.bunkers.erase(itBunker);
		}

		else { ++itBunker; }

	}


	for (auto itBlock = scene.blocks.begin(); itBlock != scene.blocks.end();)
	{
		for (auto it = scene.bullets.begin(); it != scene.bullets.end();)
		{
			if ((*it).userBullet && (*it).isCollided(*itBlock))
			{
				it = scene.bullets.erase(it);
				(*itBlock).reduceLife();

			}
			else { ++it; }
		}

		if ((*itBlock).getLives() <= 0)
		{
			itBlock = scene.blocks.erase(itBlock);
		}

		else { ++itBlock; }

	}
}

void finalize()
{
	clear_buffer();
}

void handleButtons()
{
	if (is_key_pressed(VK_ESCAPE)) { schedule_quit_game(); }

	if (is_key_pressed(VK_LEFT)) { scene.paddle.leftShift = true; }
	else { scene.paddle.leftShift = false; }

	if (is_key_pressed(VK_RIGHT)) { scene.paddle.rightShift = true; }
	else { scene.paddle.rightShift = false; }

	if (is_key_pressed(VK_UP)) { scene.gameStarted = true; }

	if (is_key_pressed(VK_SPACE))
	{
		scene.gameStarted = true;

		if (_Xtime_get_ticks() % 3 == 0)
		{
			Bullet bullet = Bullet(5, 20, Vector3(200, 50, 0), scene.paddle, true);
			bullet.set_north(true);
			scene.bullets.push_back(bullet);
		}
	}

}


void moveSprites(float dt)
{
	float distance = dt * 70;

	if (scene.toRight) {
		scene.moveSpritesRight(distance);
	}

	else {
		scene.moveSpritesLeft(distance);
	}

}

void shootBySprites()
{
	if (_Xtime_get_ticks() % 20 == 0)
	{
		int randomChoosenSprite = (rand() % scene.blocks.size()) + 0;

		Bullet bullet = Bullet(7, 7, Vector3(500, 50, 0), scene.blocks.at(randomChoosenSprite), false);
		bullet.set_north(false);
		bullet.set_south(true);

		scene.bullets.push_back(bullet);
	}
}


void act(float dt)
{
	if (is_window_active())
	{
		handleButtons();

		if (scene.gameStarted)
		{
			shootBySprites();
			moveSprites(dt);
			checkCollisions();

			for (auto it = scene.bullets.begin(); it != scene.bullets.end(); ) {
				if ((*it).outOfPlayingZone(dt))
				{
					it = scene.bullets.erase(it);
				}
				else {
					++it;
				}
			}


			if (scene.paddle.getLives() <= 0 || scene.blocks.empty())
			{
				initialize();
			}
		}

		if (scene.paddle.leftShift) { scene.shiftPaddleToLeft(); }
		if (scene.paddle.rightShift) { scene.shiftPaddleToRight(); }
	}
}
