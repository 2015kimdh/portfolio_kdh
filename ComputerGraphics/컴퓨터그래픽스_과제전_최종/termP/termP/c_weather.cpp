#include "pch.h"
#include "c_weather.h"


c_weather::c_weather()
{
}

c_weather::~c_weather()
{
}

void c_weather::DrawWeather()
{
	for (int k = 0; k < AMOUNT; k++)
	{
		for (int i = 0; i < 2; i++)
		{
			glPushMatrix();
			{
				if (state == rainny)
				{
					glColor3f(0.3f, 0.5f, 1.0f);
					glScalef(1, rainScale, 1);
				}
				else if (state == snowy)
				{
					glColor3f(1.0f, 1.0f, 1.0f);
				}

				glTranslated(Object[k][i][x], Object[k][i][y], Object[k][i][z]);
				glutSolidCube(4);
			}
			glPopMatrix();
		}
	}
}


void c_weather::update()
{
	for (int k = 0; k < AMOUNT; k++)
	{
		if (state == STATE::sunny)
		{
			Object[k][snow][y] = startPoint;
			Object[k][rain][y] = startPoint;
		}

		else if (state == STATE::rainny)
		{
			Object[k][snow][y] = startPoint;

			if		(Object[k][rain][y] > 0)	{ Object[k][rain][y] -= (float)fallingSpeed[k][rain]; }
			else if (Object[k][rain][y] <= 0)	{ Object[k][rain][y] = startPoint; }
		}
		else if (state == STATE::snowy)
		{
			Object[k][rain][y] = startPoint;

			if		(Object[k][snow][y] > 0)	{ Object[k][snow][y] -= fallingSpeed[k][snow]; }
			else if (Object[k][snow][y] <= 0)	{ Object[k][snow][y] = startPoint; }
		}
	}

}

void c_weather::init()
{
	for (int k = 0; k < AMOUNT; k++)
	{
		for (int i = 0; i < 2; i++)
		{
			Object[k][i][x] = rand() % 2500 * 2 - 1250;
			Object[k][i][y] = startPoint;
			Object[k][i][z] = rand() % 2500 * 2 - 1250;
		}
		fallingSpeed[k][snow] = (rand() % 40 + 1) * 0.1;
		fallingSpeed[k][rain] = (rand() % 100 + 150) * 0.3;
	}

}
