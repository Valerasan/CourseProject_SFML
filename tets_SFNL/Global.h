#pragma once

#include <array>
#include <SFML/Graphics.hpp>


constexpr unsigned char BASE_SIZE = 16;
constexpr unsigned char ENEMY_BULLET_SPEED = 2;

constexpr unsigned short SCREEN_HEIGHT = 600;
constexpr unsigned short SCREEN_WIDTH = 600;

struct Bullet
{
	bool dead;

	//float real_x;
	float real_y;
	//float step_x;
	float step_y;

	short x;
	short y;

	//We also use this struct in the Player class. But the player's bullets don't have a tail. So it may seem a bit redundant. But I'm too lazy to fix it.
	std::array<short, 3> previous_x;
	std::array<short, 3> previous_y;

	//Bullet(float i_step_x, float i_step_y, short i_x, short i_y) :
	Bullet(float i_step_y, short i_x, short i_y) :
		dead(0),
		//real_x(i_x),
		real_y(i_y),
		//step_x(i_step_x),
		step_y(i_step_y),
		x(i_x),
		y(i_y)
	{
		//previous_x.fill(x);
		previous_y.fill(y);
	}

	void update()
	{
		if (0 == dead)
		{
			//I hate using floats, so we'll change real_x and _y and work only with integer values.
			//real_x += step_x;
			real_y += step_y;

			for (unsigned char a = 0; a < previous_x.size() - 1; a++)
			{
				//previous_x[a] = previous_x[1 + a];
				previous_y[a] = previous_y[1 + a];
			}

			//previous_x[previous_x.size() - 1] = x;
			previous_y[previous_y.size() - 1] = y;

			//x = round(real_x);
			y = round(real_y);
			
			if ( 0 >= y )
			{
				
				dead = 1;
			}
		}
	}

	sf::IntRect get_hitbox() const
	{
		//Smaller hitboxes make the game so much better!
		return sf::IntRect(x + 0.375f * BASE_SIZE, y + 0.375f * BASE_SIZE, 0.25f * BASE_SIZE, 0.25f * BASE_SIZE);
	}
};