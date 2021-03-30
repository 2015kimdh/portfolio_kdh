#pragma once

#define AMOUNT 3000



enum STATE
{
	sunny = 0,
	rainny,
	snowy
};

class c_weather
{
public:
	c_weather();
	~c_weather();

	void DrawWeather();
	void update();
	void init();
public:
	float Object[AMOUNT][2][3];

	float fallingSpeed [AMOUNT][2] = {0.0};

	bool dropping[AMOUNT][2] = { false };

	float rainScale{ 50.0 };
	float snowScale;

	int state;
private:
	const int x = 0;
	const int y = 1;
	const int z = 2;

	const int snow = 0;
	const int rain = 1;

	int startPoint = 700;
};

