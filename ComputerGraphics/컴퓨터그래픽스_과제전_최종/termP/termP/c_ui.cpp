#include "pch.h"
#include "c_ui.h"
#include <iostream>

#include "TextureManager.h"

using namespace std;

c_ui::c_ui()
{
}


c_ui::~c_ui()
{
}

void c_ui::drawGear()
{
	int temp = 10;
	auto t1 = TextureInstance->EnableTextur(ENUM_TEXTURE::POINT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(-length / temp, +length / temp);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-length / temp, -length / temp);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(+length / temp, -length / temp);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(+length / temp, +length / temp);
		
		//cout << length / temp << endl;
	}
	glEnd();
	TextureInstance->DisableTextur(ENUM_TEXTURE::POINT, t1);


	niddleDegree = ship->speed * 32;
	glPushMatrix();
	{
		glRotated(niddleDegree, 0, 0, -1);
		glTranslatef(0.0, niddleHeight / 2, 0.0);
		drawNiddle();
	}
	glPopMatrix();



	if (ship->gear_now == 1)
	{
		auto t1 = TextureInstance->EnableTextur(ENUM_TEXTURE::GEAR1);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-length, +length);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-length, -length);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(+length, -length);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(+length, +length);
		}
		glEnd();
		TextureInstance->DisableTextur(ENUM_TEXTURE::GEAR1, t1);
	}
	else if (ship->gear_now == 2)
	{
		auto t1 = TextureInstance->EnableTextur(ENUM_TEXTURE::GEAR2);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-length, +length);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-length, -length);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(+length, -length);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(+length, +length);
		}
		glEnd();
		TextureInstance->DisableTextur(ENUM_TEXTURE::GEAR2, t1);
	}
	else if (ship->gear_now == 3)
	{
		auto t1 = TextureInstance->EnableTextur(ENUM_TEXTURE::GEAR3);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-length, +length);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-length, -length);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(+length, -length);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(+length, +length);
		}
		glEnd();
		TextureInstance->DisableTextur(ENUM_TEXTURE::GEAR3, t1);

		
	}
	else if (ship->gear_now == 4)
	{
		auto t1 = TextureInstance->EnableTextur(ENUM_TEXTURE::GEAR4);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(-length, +length);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(-length, -length);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(+length, -length);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(+length, +length);
		}
		glEnd();
		TextureInstance->DisableTextur(ENUM_TEXTURE::GEAR4, t1);
	}

	auto gear0 = TextureInstance->EnableTextur(ENUM_TEXTURE::GEAR0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-length, +length);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-length, -length);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(+length, -length);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(+length, +length);
	}
	glEnd();
	TextureInstance->DisableTextur(ENUM_TEXTURE::GEAR0, gear0);
}

void c_ui::drawNiddle()
{
	auto niddle = TextureInstance->EnableTextur(ENUM_TEXTURE::NIDDLE);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(-niddleWidth, +niddleHeight);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-niddleWidth, -niddleHeight);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(+niddleWidth, -niddleHeight);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(+niddleWidth, +niddleHeight);
	}
	glEnd();
	TextureInstance->DisableTextur(ENUM_TEXTURE::NIDDLE, niddle);
}
