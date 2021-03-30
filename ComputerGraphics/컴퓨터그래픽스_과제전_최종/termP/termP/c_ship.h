#pragma once
#include "c_background.h"
#include "texture.h"
#include "c_missile.h"
#include "camera.h"

enum TYPE {		//0712장우석
	model1,
	model2,
	model3,
	model4
};

class c_ship
{
public:
	c_ship();
	~c_ship();

	void update();
	void shipSpeed();
	void drawShip();
	void shipModel();
	void init(const int posX, const int posY, const int posZ,const int modelType, const int id);
	void shipAngle();
	void Collideland();

	//===============================


	void shipModelUposit();

	void drawShipUposit();
	void fire(float x, float z);		// 발사 1013

	void drawAim(float r, float g, float b, float a);
	void drawEnemyPosition(float r, float g, float b, float a);

	//void AimSet();
	//void AimSet2P();

	//===============================


	void model_shipBody();
	void model_shipWheel();
	void model_cannonBody();
	void model_cannonHead();


	void keybard1(unsigned char key);
	void keybard2(unsigned char key);
	void keybard1up(unsigned char key);
	void keybard2up(unsigned char key);

	void keybardInSelect1(unsigned char key);
	void keybardInSelect2(unsigned char key);

	void cube(float centerX, float centerY, float centerZ, float height);




	void ModelTypeSetup();

	void textureSetUp();

	c_texture Texture;

	int modelType = TYPE::model1;		//0712장우석


public:
	float position[3];
	float moveSpeedZ;
	float moveSpeedX;
	float leanAngle;
	int gear_now = 0;
	float speed;
	float Radian;

	bool w = false;
	bool a = false;
	bool s = false;
	bool d = false;
	bool g = false;

	//========================
	bool c = false;
	bool b = false;
	bool f = false;
	bool v = false;
	//========================

	bool five = false;
	bool eight = false;
	bool six = false;
	bool four = false;

	//========================
	bool seven = false;
	bool nine = false;
	bool k = false;
	bool comma = false;
	//========================

	float camerarotate;
	float hp = 60;
	float enemyangle = 0;
	float enemyposition[3];
	float updownangle = 0;
	int wheel = 0;

	float m_CameraAngle = 0;			// 1012 김동환 추가 수정
	float m_CameraUp = 0;
	float m_CameraWheeled = false;

	//========================
	float AimPointAngle = 90;
	float AimPointDistance = 50;
	float AimPoint[3];

	float enemyPositionAlpha = 0.1;
	float aimAlpha = 0.5;

	int m_id;
	//========================


	c_ship *enemyship;

	c_background* backGround;
	c_missile* missile;
	c_texture* p_Texture;

	Camera<float3> *Camera;

	GLuint shipTexture[4];

	GLubyte * TexBits;
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변
	BITMAPINFO *texture;


	std::vector<vec3> out_vertices;
	std::vector<vec2> out_uvs;
	std::vector<vec3> out_normals;

	std::vector<vec3> out_vertices_wheel;
	std::vector<vec2> out_uvs_wheel;
	std::vector<vec3> out_normals_wheel;

	std::vector<vec3> out_vertices_cannonBody;
	std::vector<vec2> out_uvs_cannonBody;
	std::vector<vec3> out_normals_cannonBody;

	std::vector<vec3> out_vertices_cannonHead;
	std::vector<vec2> out_uvs_cannonHead;
	std::vector<vec3> out_normals_cannonHead;

private:
	const int x = 0;
	const int y = 1;
	const int z = 2;
	const int right = -1;
	const int left = 1;
	const int nutral = 0;
	const float gear_1 = 100 / 72;
	const float gear_2 = 100 / 48;
	const float gear_3 = 100 / 36;
	const float gear_4 = 100 / 24;
	const float gear_R = -100 / 72;
	const float AngleMax = 60;
};

