#pragma once

#include "c_ship.h" 

class c_ui
{
public:
	c_ui();
	~c_ui();

	void drawGear();
	void drawNiddle();

public:
	c_ship* ship;
	int length = 250;

	int niddleHeight = 200 / 2;
	int niddleWidth = 20;
	float niddleDegree;

};

