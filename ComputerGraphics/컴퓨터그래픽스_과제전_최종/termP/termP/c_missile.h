#pragma once
#include "c_ship.h"
#include "c_background.h"
#include "Sound.h"

class c_ship;
class c_missile
{
public:
	c_missile();
	~c_missile();

	void update();
	void init(float Angle, float Distance);

	void drawMissile();
	void missileroad();
	void Collide();
	void ParticleDraw();

public:
	float starting[3];
	float position[3];
	float enemyposition[3];
	float t;
	float slice;
	float Radianx;
	float Radianz;
	bool state;
	float distance;
	int reload;
	bool collide = false;
	bool particle = false;
	float particlepos[3];
	float partsize = 0;

	CSound *sound;
	c_background* backGround;
	c_ship* ship;
	c_ship* enemyship;
	GLubyte * TexBits;
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변
	BITMAPINFO *texture;

private:
	const int x = 0;
	const int y = 1;
	const int z = 2;
	const int delay = 500;
	const int reallyneardistance = 200;
	const int neardistance = 300;
	const int middledistance = 400;
	const int fardistance = 500;
};

