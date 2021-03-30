#pragma once

#include "Dependencies\freeglut.h"


class Player
{
public:
	Player();
	~Player();

	void KeyDownInput(int key, int x, int y);
	void KeyUpInput(int key, int x, int y);

public:
	bool FirstPlayer = false;

	int direction;

	bool key_up = false;
	bool key_down = false;
	bool key_left = false;
	bool key_right = false;
	bool key_shift = false;
};

