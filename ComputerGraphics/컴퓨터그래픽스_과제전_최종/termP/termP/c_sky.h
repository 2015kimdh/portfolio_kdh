#pragma once

#include "texture.h"


class c_sky
{
public:
	c_sky();
	~c_sky();

	void drawSky();
	void textureSetUp();


	c_texture Texture;

public:
	GLuint skyTexture[4];

	GLubyte * TexBits;
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변
	BITMAPINFO *texture;
};

