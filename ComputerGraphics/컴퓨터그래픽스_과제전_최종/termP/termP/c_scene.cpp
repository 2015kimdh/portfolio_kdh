#include "pch.h"
#include "TextureManager.h"


c_scene::c_scene()
{
}


c_scene::~c_scene()
{
}

void c_scene::drawPlayer1WinScene()
{
}

void c_scene::drawPlayer2WinScene()
{
}

void c_scene::drawSelectScene()
{

	glBegin(GL_QUADS);
	{

		glVertex2f(-WWIDTH / 2, +WHEIGHT / 2);
		glVertex2f(-WWIDTH / 2, -WHEIGHT / 2);
		glVertex2f(+WWIDTH / 2, -WHEIGHT / 2);
		glVertex2f(+WWIDTH / 2, +WHEIGHT / 2);

	}
	glEnd();



}

void c_scene::drawReady()
{
	int wLength = 150;
	int hLength = 100;

	float left		= 0 - wLength;
	float right		= 0 + wLength;
	float top		= 0 + hLength;
	float bottom	= 0 - hLength;


	auto t1 = TextureInstance->EnableTextur(ENUM_TEXTURE::READY);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	{

		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(+wLength / 2, +hLength / 2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-wLength / 2, +hLength / 2);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-wLength / 2, -hLength / 2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(+wLength / 2, -hLength / 2);

	}
	glEnd();

	TextureInstance->DisableTextur(ENUM_TEXTURE::READY, t1);

}

void c_scene::drawScene()
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(-WWIDTH / 2, +WHEIGHT / 2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-WWIDTH / 2, -WHEIGHT / 2);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(+WWIDTH / 2, -WHEIGHT / 2);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(+WWIDTH / 2, +WHEIGHT / 2);
	}
	glEnd();
}
