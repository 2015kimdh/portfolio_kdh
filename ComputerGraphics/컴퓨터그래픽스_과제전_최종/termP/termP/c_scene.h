#pragma once
#include"pch.h"



class c_scene
{
public:
	c_scene();
	~c_scene();
	void drawScene();
	void drawPlayer1WinScene();
	void drawPlayer2WinScene();
	
	void drawSelectScene();

	void drawReady();


public:
	int state = 0;

	GLuint readyTexture[2];
	GLubyte * TexBits;
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변
	BITMAPINFO *texture;
	c_texture Texture;

private:

};

