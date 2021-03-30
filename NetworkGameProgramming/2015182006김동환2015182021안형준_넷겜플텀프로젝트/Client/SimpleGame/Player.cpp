
#include "stdafx.h"
#include "Player.h"
Player::Player()
{
	direction = 1;
}

Player::~Player()
{

}

void Player::KeyDownInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		key_up = true;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		key_down = true;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		key_left = true;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		key_right = true;
	}
	else if (key == GLUT_KEY_SHIFT_L)
	{
		key_shift = true;
	}
}

void Player::KeyUpInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		key_up = false;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		key_down = false;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		key_left = false;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		key_right = false;
	}
	else if (key == GLUT_KEY_SHIFT_L)
	{
		key_shift = false;
	}
}