#include "pch.h"
#include "c_light.h"
#include "math.h"


c_light::c_light()
{
	init();
}


c_light::~c_light()
{
}

void c_light::init()
{
	ambientLignt[r] = 0.9;
	ambientLignt[g] = 0.8;
	ambientLignt[b] = 0.7;
	ambientLignt[a] = 0.7;


	ambientLignt0[r] = 0.4;
	ambientLignt0[g] = 0.0f;
	ambientLignt0[b] = 0.0f;
	ambientLignt0[a] = 1.0f;
	
	DiffuseLight0[r] = 1.0f;
	DiffuseLight0[g] = 0.0f;
	DiffuseLight0[b] = 0.6f;
	DiffuseLight0[a] = 1.0f;

	SpecularLight0[r] = 1.0f;
	SpecularLight0[g] = 1.0f;
	SpecularLight0[b] = 0.0f;
	SpecularLight0[a] = 1.0f;

	lightPos0[x] = 0.0;
	lightPos0[y] = 300.0;
	lightPos0[z] = 0.0;
	lightPos0[w] = 0.0;
}



void c_light::setLight()
{
	glEnable(GL_LIGHTING);	//조명 사용을 가능하게
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLignt); //전역 주변광 설정 
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);	 //반사광 각도 계산 0.0~1.0
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);		// 0이면 양면이 빛을 받는다. ????
}

void c_light::setLight0()
{
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLignt0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
}

void c_light::update()
{
	//static float temp;
	//temp += 0.1 * PI;
	//lightPos0[x] = 100 * sin(temp);
	//lightPos0[z] = -100 * cos(temp);
}

void c_light::enableMaterial(ENUM_OBJECT id)
{
	glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialColor[id]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Materialspecref[id]);
	glMateriali(GL_FRONT, GL_SHININESS, 1);
}

void c_light::disableMaterial()
{
	glDisable(GL_COLOR_MATERIAL);
}

void c_light::setMaterial()
{
	MaterialColor[SEA][r] = 0.2;
	MaterialColor[SEA][g] = 0.2;
	MaterialColor[SEA][b] = 0.2;
	MaterialColor[SEA][a] = 1.0;

	Materialspecref[SEA][r] = 1.0;
	Materialspecref[SEA][g] = 1.0;
	Materialspecref[SEA][b] = 1.0;
	Materialspecref[SEA][a] = 1.0;

}



