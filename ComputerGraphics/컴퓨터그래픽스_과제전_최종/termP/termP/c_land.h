#pragma once

#include "texture.h"

#include "objloader.h"

class c_land
{
public:
	c_land();
	~c_land();

	void init();
	void drawLand();

	void textureSetUp();
	void positionSetUp();
	void objectSetUp();
	void cube();

public:
	int height;
	int position[3];




	c_texture Texture;

	GLuint landTexture[2];
	GLubyte * TexBits;
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변
	BITMAPINFO *texture;


	std::vector<vec3> out_vertices;
	std::vector<vec2> out_uvs;
	std::vector<vec3> out_normals;
	float rotate;

private:
	const int x = 0;
	const int y = 1;
	const int z = 2;
};

