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
	GLubyte *pBytes; // �����͸� ����ų ������
	BITMAPINFO *info; // ��Ʈ�� ��� ������ ��
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

