#pragma once


enum ENUM_OBJECT
{
	SEA = 0,
	SKY,
	LAND,
	SHIP,
	BULLET
};

class c_light
{
public:
	c_light();
	~c_light();

	void init();

	void setLight();
	void setLight0();

	void update();

	void enableMaterial(ENUM_OBJECT id);
	void disableMaterial();

	void setMaterial();

public:
	GLfloat ambientLignt[4];

	GLfloat ambientLignt0[4];
	GLfloat DiffuseLight0[4];
	GLfloat SpecularLight0[4]; // 백색조명
	GLfloat lightPos0[4];

	GLfloat MaterialColor[5][4];
	GLfloat Materialspecref[5][4];

private:
	const int r = 0;
	const int g = 1;
	const int b = 2;
	const int a = 3;

	const int x = 0;
	const int y = 1;
	const int z = 2;
	const int w = 3;
};

