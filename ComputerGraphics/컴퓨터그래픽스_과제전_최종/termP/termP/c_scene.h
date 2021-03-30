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
	GLubyte *pBytes; // �����͸� ����ų ������
	BITMAPINFO *info; // ��Ʈ�� ��� ������ ��
	BITMAPINFO *texture;
	c_texture Texture;

private:

};

