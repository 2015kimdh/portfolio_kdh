#include "pch.h"
#include "c_ship.h"
#include "math.h"
#include "c_missile.h"
#include "camera.h"
#include "TextureManager.h"

c_ship::c_ship()
{
	//backGround = new c_background();
}


c_ship::~c_ship()
{

}

void c_ship::update()
{
	shipSpeed();
	shipAngle();

	position[y] = backGround->seaPoints[25][25][y];


	//=================
	AimPoint[x] = position[x] + (cos(AimPointAngle) * AimPointDistance);
	AimPoint[y] = 80;
	AimPoint[z] = position[z] + (sin(AimPointAngle) * AimPointDistance);
	//=================





	enemyposition[x] = enemyship->position[x];
	enemyposition[y] = enemyship->position[y];
	enemyposition[z] = enemyship->position[z];

	float arc = atan2f((enemyship->position[x]) - position[x], (enemyship->position[z]) - position[z]);
	enemyangle = (arc * 180 / 3.1415f) - 180;

	wheel = wheel % 360 + 10;

	position[z] += cos(Radian)*speed;
	position[x] -= sin(Radian)*speed;

	if (position[x] >= 1200)
	{
		position[x] += sin(Radian) * 30;
	}
	else if (position[x] <= -1200)
	{
		position[x] += sin(Radian) * 30;
	}
	if (position[z] >= 1200)
	{
		position[z] -= cos(Radian) * 30;
	}
	else if (position[z] <= -1200)
	{
		position[z] -= cos(Radian) * 30;
	}

	Collideland();
}



void c_ship::Collideland()
{
	float cx, cz = 0;
	for (int i = 0; i < backGround->landamount; i++)
	{
		for (int j = 0; j < backGround->landsubamount; j++)
		{
			cx = pow(position[x] - backGround->land[i][j].position[x] + 25, 2);
			cz = pow(position[z] - backGround->land[i][j].position[z] + 25, 2);
			if (cx + cz <= 5000)
			{
				position[z] -= cos(Radian)*20;
				position[x] += sin(Radian)*20;
			}
		}
	}
	cx = pow(position[x] - enemyship->position[x] + 50, 2);
	cz = pow(position[z] - enemyship->position[z] + 50, 2);
	if (cx + cz <= 5000)
	{
		position[z] -= cos(Radian) * 25;
		position[x] += sin(Radian) * 25;
	}
}

void c_ship::shipModelUposit()
{
	glPushMatrix();
	{

		glColor3f(1.0, 1.0, 1.0);
		glTranslated(position[x], position[y], position[z]);
		glRotatef(leanAngle, 0, -1, 0);

		model_shipBody();
		glPushMatrix();
		{
			glTranslatef(0, 10, -20);
			glRotatef(wheel, 1, 0, 0);
			model_shipWheel();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(0, 0, 30);
			glRotatef(leanAngle, 0, 1, 0);
			glRotatef(-180 * AimPointAngle / 3.14f - 90, 0, 1, 0);
			model_cannonBody();
			model_cannonHead();
		}
		glPopMatrix();

	}
	glPopMatrix();


}

void c_ship::fire(float Angle, float Distance)
{
	if (missile->state == false && missile->reload == 50)
		missile->init(Angle, Distance);
}



void c_ship::drawAim(float r, float g, float b, float a)
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glEnable(GL_ALPHA_TEST);
		
		//if (m_id == 1)
		//	glColor4f(0.85, 0.55, 0.25, aimAlpha);
		//else if (m_id == 2)
		//	glColor4f(0.25, 0.85, 0.35, aimAlpha);


		glTranslatef(AimPoint[x], 0, AimPoint[z]);
		//glutSolidCube(50);
		glColor4f(r, g + 0.2, b + 0.2, a + 0.3);
		glutSolidSphere(40,16,16);

		//추가 막대
		glPushMatrix();
		{
			int tempScale = 200;
			glTranslatef(0, 5 * tempScale / 2, 0);
			glScalef(1, tempScale, 1);
			glutSolidCube(5);
		}
		glPopMatrix();

		
		glColor4f(r, g, b, a);
		glutSolidSphere(50, 16, 16);

		//추가 막대
		glPushMatrix();
		{
			int tempScale = 200;
			glTranslatef(0, 5 * tempScale / 2, 0);
			glScalef(1, tempScale, 1);
			glutSolidCube(10);
		}
		glPopMatrix();



		//glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void c_ship::drawEnemyPosition(float r, float g, float b, float a)
{

	glDisable(GL_LIGHTING);
	glPushMatrix();
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glScalef(1, 200, 1);
		glTranslatef(position[x], 0, position[z]);

		glColor4f(r, g, b, a + 0.3);
		//glColor4f(0.9, 0.9, 0.9, enemyPositionAlpha + 0.3);
		glutSolidSphere(40,16,16);
		//glutSolidCube(40);

		//glColor4f(0.9, 0.9, 0.9, enemyPositionAlpha);
		glColor4f(r, g, b, a);
		glutSolidSphere(70, 16, 16);
		//glutSolidCube(70);


		//glPushMatrix();
		//{
		//	glTranslatef(0,1000,0);
		//	glColor4f(r, g, b, a + 0.3);
		//	glutSolidSphere(70, 16, 16);
		//}
		//glPopMatrix();


		glDisable(GL_BLEND);
	}
	glPopMatrix();

	glEnable(GL_LIGHTING);

}

void c_ship::drawShip()
{
	shipModel();
}

void c_ship::drawShipUposit()
{
	shipModelUposit();
}



void c_ship::shipSpeed()
{
	if (w == true || eight == true)
	{
		if (gear_now < 4)
		{
			gear_now += 1;
		}
		w = false;
	}
	else if (s == true || five == true)
	{
		if (gear_now > -1)
		{
			gear_now -= 1;
		}
		s = false;
	}

	if (gear_now == 1)
	{
		if (speed < gear_1)
		{
			speed += 0.1;
		}
		else if (speed > gear_1)
		{
			speed -= 0.1;
		}
	}
	else if (gear_now == 2)
	{
		if (speed < gear_2)
		{
			speed += 0.07;
		}
		else if (speed > gear_2)
		{
			speed -= 0.1;
		}
	}
	else if (gear_now == 3)
	{
		if (speed < gear_3)
		{
			speed += 0.05;
		}
		else if (speed > gear_3)
		{
			speed -= 0.1;
		}
	}
	else if (gear_now == 4)
	{
		if (speed < gear_4)
		{
			speed += 0.03;
		}
		else if (speed > gear_4)
		{
			speed -= 0.1;
		}
	}
	else if (gear_now == -1)
	{
		if (speed < gear_R)
		{
			speed += 0.5;
		}
		else if (speed > gear_R)
		{
			speed -= 0.05;
		}
	}
	else if (gear_now == 0)
	{
		if (speed < 0)
		{
			speed += 0.05;
		}
		else if (speed > 0)
		{
			speed -= 0.1;
		}
	}

}

void c_ship::shipAngle()
{
	if (gear_now >= 0)
	{
		if (d == true || six == true)
		{
			leanAngle += 1;
			if (leanAngle > 360)
			{
				leanAngle = 0;
			}
		}
		else if (a == true || four == true)
		{
			leanAngle -= 1;
			if (leanAngle < 0)
			{
				leanAngle = 360;
			}
		}
	}
	else
	{
		if (a == true)
		{
			leanAngle += 1;
			if (leanAngle > 360)
			{
				leanAngle = 0;
			}
		}
		else if (d == true)
		{
			leanAngle -= 1;
			if (leanAngle < 0)
			{
				leanAngle = 360;
			}
		}
	}
	Radian = leanAngle * 3.1415f / 180;



	//===================================
	if (c == true)
	{
		AimPointAngle -= 0.05;
	}
	if (b == true)
	{
		AimPointAngle += 0.05;
	}
	if (f == true)
	{
		AimPointDistance += 10;
	}
	if (v == true)
	{
		AimPointDistance -= 10;
		if (AimPointDistance < 0)
			AimPointDistance = 0;
	}

	//===================================

	if (seven == true)
	{
		AimPointAngle -= 0.05;
	}
	if (nine == true)
	{
		AimPointAngle += 0.05;
	}
	if (k == true)
	{
		AimPointDistance += 10;
	}
	if (comma == true)
	{
		AimPointDistance -= 10;
		if (AimPointDistance < 0)
			AimPointDistance = 0;
	}

	//===================================
}

void c_ship::model_shipBody()
{

	glPushMatrix();
	{

		glColor3f(1.0, 1.0, 1.0);

		glEnable(GL_NORMALIZE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, shipTexture[0]);

		glBegin(GL_TRIANGLES);
		{
			for (int i = 0; i < out_vertices.size(); i++)
			{
				glTexCoord2f(out_uvs[i].x, out_uvs[i].y);
				glNormal3f(out_normals[i].x, out_normals[i].x, out_normals[i].x);
				glVertex3f(out_vertices[i].x, out_vertices[i].y, out_vertices[i].z);
			}
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_NORMALIZE);

	}
	glPopMatrix();


}

void c_ship::model_shipWheel()
{
	glPushMatrix();
	{

		glColor3f(1.0, 1.0, 1.0);

		glEnable(GL_NORMALIZE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, shipTexture[0]);	//0712장우석 1 -> 0

		glBegin(GL_TRIANGLES);
		{
			for (int i = 0; i < out_vertices_wheel.size(); i++)
			{
				glTexCoord2f(out_uvs_wheel[i].x, out_uvs_wheel[i].y);
				glNormal3f(out_normals_wheel[i].x, out_normals_wheel[i].y, out_normals_wheel[i].z);
				glVertex3f(out_vertices_wheel[i].x, out_vertices_wheel[i].y, out_vertices_wheel[i].z);
			}
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_NORMALIZE);


		//glutSolidCube(100);
	}
	glPopMatrix();
}

void c_ship::model_cannonBody()
{
	glPushMatrix();
	{

		glColor3f(1.0, 1.0, 1.0);

		glEnable(GL_NORMALIZE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, shipTexture[0]);	//0712장우석 2 -> 0

		glBegin(GL_TRIANGLES);
		{
			for (int i = 0; i < out_vertices_cannonBody.size(); i++)
			{
				glTexCoord2f(out_uvs_cannonBody[i].x, out_uvs_cannonBody[i].y);
				glNormal3f(out_normals_cannonBody[i].x, out_normals_cannonBody[i].y, out_normals_cannonBody[i].z);
				glVertex3f(out_vertices_cannonBody[i].x, out_vertices_cannonBody[i].y, out_vertices_cannonBody[i].z);
			}
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_NORMALIZE);


		//glutSolidCube(100);
	}
	glPopMatrix();
}

void c_ship::model_cannonHead()
{
	glPushMatrix();
	{

		glColor3f(1.0, 1.0, 1.0);

		glEnable(GL_NORMALIZE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, shipTexture[0]);	//0712장우석 3 -> 0

		glBegin(GL_TRIANGLES);
		{ 
			for (int i = 0; i < out_vertices_cannonHead.size(); i++)
			{
				glTexCoord2f(out_uvs_cannonHead[i].x, out_uvs_cannonHead[i].y);
				glNormal3f(out_normals_cannonHead[i].x, out_normals_cannonHead[i].y, out_normals_cannonHead[i].z);
				glVertex3f(out_vertices_cannonHead[i].x, out_vertices_cannonHead[i].y, out_vertices_cannonHead[i].z);
			}
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_NORMALIZE);

	}
	glPopMatrix();
}

void c_ship::shipModel()
{

	glPushMatrix();
	{

		glColor3f(1.0, 1.0, 1.0);
		glTranslated(position[x], position[y], position[z]);
		glRotatef(leanAngle, 0, -1, 0);

		model_shipBody();
		glPushMatrix();
		{
			glTranslatef(0, 10, -20);
			glRotatef(wheel, 1, 0, 0);
			model_shipWheel();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(0, 0, 30);
			glRotatef(leanAngle, 0, 1, 0);
			glRotatef(-180 * AimPointAngle / 3.14f - 270, 0, 1, 0);
			model_cannonBody();
			model_cannonHead();
		}
		glPopMatrix();

	}
	glPopMatrix();
	
}

void c_ship::ModelTypeSetup()
{

	switch (modelType)	//0712장우석
	{
		std::cout << "모델 : " << modelType << std::endl;
	case TYPE::model1:
		loadOBJ("resource/ship/ship1/ship001.obj", out_vertices, out_uvs, out_normals);
		loadOBJ("resource/ship/ship1/ship001_wheel.obj", out_vertices_wheel, out_uvs_wheel, out_normals_wheel);
		loadOBJ("resource/ship/ship1/ship001_cannon_body.obj", out_vertices_cannonBody, out_uvs_cannonBody, out_normals_cannonBody);
		loadOBJ("resource/ship/ship1/ship001_cannon_head.obj", out_vertices_cannonHead, out_uvs_cannonHead, out_normals_cannonHead);
		break;
	case TYPE::model2:
		loadOBJ("resource/ship/ship2/ship002.obj", out_vertices, out_uvs, out_normals);
		loadOBJ("resource/ship/ship2/ship002_wheel.obj", out_vertices_wheel, out_uvs_wheel, out_normals_wheel);
		loadOBJ("resource/ship/ship2/ship002_cannon_body.obj", out_vertices_cannonBody, out_uvs_cannonBody, out_normals_cannonBody);
		loadOBJ("resource/ship/ship2/ship002_cannon_head.obj", out_vertices_cannonHead, out_uvs_cannonHead, out_normals_cannonHead);
		break;
	case TYPE::model3:
		loadOBJ("resource/ship/ship3/ship003.obj", out_vertices, out_uvs, out_normals);
		loadOBJ("resource/ship/ship3/ship003_wheel.obj", out_vertices_wheel, out_uvs_wheel, out_normals_wheel);
		loadOBJ("resource/ship/ship3/ship003_cannon_body.obj", out_vertices_cannonBody, out_uvs_cannonBody, out_normals_cannonBody);
		loadOBJ("resource/ship/ship3/ship003_cannon_head.obj", out_vertices_cannonHead, out_uvs_cannonHead, out_normals_cannonHead);
		break;
	case TYPE::model4:
		loadOBJ("resource/ship/ship4/ship004.obj", out_vertices, out_uvs, out_normals);
		loadOBJ("resource/ship/ship4/ship004_wheel.obj", out_vertices_wheel, out_uvs_wheel, out_normals_wheel);
		loadOBJ("resource/ship/ship4/ship004_cannon_body.obj", out_vertices_cannonBody, out_uvs_cannonBody, out_normals_cannonBody);
		loadOBJ("resource/ship/ship4/ship004_cannon_head.obj", out_vertices_cannonHead, out_uvs_cannonHead, out_normals_cannonHead);
		break;
	default:
		std::cout << "모델어느거 할거냐" << std::endl;
		break;
	}
}


void c_ship::init(const int posX, const int posY, const int posZ,const int type, const int id)
{
	modelType = type;

	//0712 장우석 주석처리했음
	textureSetUp();
	ModelTypeSetup();

	position[x] = posX;
	position[y] = posY;
	position[z] = posZ;

	m_id = id;

	//position[x] = 750;
	//position[y] = 100;
	//position[z] = 750;

}

void c_ship::keybard1(unsigned char keyPressed)
{
	switch (keyPressed)
	{
	case 'w':
		w = true;
		
		break;
	case 'a':
		a = true;

		break;
	case 's':
		s = true;
		break;
	case 'd':
		d = true;
		break;
	case 'g':
		fire(AimPointAngle, AimPointDistance);
		break;
	case 'f':
		f = true;
		break;
	case 'v':
		v = true;
		break;
	case 'c':
		c = true;
		break;
	case 'b':
		b = true;
		break;
	}
}

void c_ship::keybard2(unsigned char keyPressed)
{
	switch (keyPressed)
	{
	case '8':
		eight = true;
		std::cout << "8 눌렸다" << std::endl;
		break;
	case '5':
		five = true;
		break;
	case '4':
		four = true;
		break;
	case '6':
		six = true;
		break;
	case 'l':
		fire(AimPointAngle, AimPointDistance);
		break;
	case 'k':
		k = true;
		break;
	case ',':
		comma = true;
		break;
	case 'm':
		seven = true;
		break;
	case '.':
		nine = true;
		break;
	}
}

void c_ship::keybard1up(unsigned char keyPressed)
{
	switch (keyPressed)
	{
	case 'w':
		w = false;

		break;
	case 'a':
		a = false;

		break;
	case 's':
		s = false;
		break;
	case 'd':
		d = false;

		break;
	case 'c':
		c = false;

		break;

	case 'b':
		b = false;

		break;
	case 'f':
		f = false;
		break;
	case 'v':
		v = false;
	}
}

void c_ship::keybard2up(unsigned char keyPressed)
{
	switch (keyPressed)
	{
	case '8':
		eight = false;
		break;
	case '5':
		five = false;
		break;
	case '4':
		four = false;
		break;
	case '6':
		six = false;
		break;

	case 'm':
		seven = false;

		break;
	case '.':
		nine = false;

		break;
	case 'k':
		k = false;
		break;
	case ',':
		comma = false;
	}
}

void c_ship::keybardInSelect1(unsigned char keyPressed)
{
	/*
	std::cout << "키보드 : ";
	switch (keyPressed)
	{
	case 'a':
		std::cout << "a 눌림" << std::endl;
		tempModelType[0]++;
		if (tempModelType[0] > TYPE::model4)
			tempModelType[0] = TYPE::model1;
		break;
	case 'd':
		std::cout << "d 눌림" << std::endl;
		tempModelType[0]--;
		if (tempModelType[0] < TYPE::model1)
			tempModelType[0] = TYPE::model4;
		break;
	case 'g':
		break;

	default:
		std::cout << "안 눌림" << std::endl;
		break;
	}
	std::cout << "model Type : " << modelType << std::endl;
	init(0,0,0,TYPE::model1);
	*/
}

void c_ship::keybardInSelect2(unsigned char key)
{
}

void c_ship::cube(float centerX, float centerY, float centerZ, float length)
{
	float left		= centerX - length;
	float right		= centerX + length;
	float top		= centerY + length;
	float bottom	= centerY - length;
	float front		= centerZ - length;
	float back		= centerZ + length;


	//glBindTexture(GL_TEXTURE_2D, p_Texture->texture_object[0]);
	//옆면
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();//=========================
		{
			glRotatef(90 * i, 0, 1, 0);
			glTranslatef(0.0, 0.0, back);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(right, top, 0);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(left, top, 0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(left, bottom, 0);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(right, bottom, 0);
			}
			glEnd();
		}
		glPopMatrix();//=========================
	}

//	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	//위아래
	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();//=========================
		{
			glRotatef(180 * i, 1, 0, 0);
			glTranslatef(0.0, top, 0.0);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(left, 0, front);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(left, 0, back);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(right, 0, back);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(right, 0, front);
			}
			glEnd();
		}
		glPopMatrix();//=========================
	}

}

void c_ship::textureSetUp()
{
	glGenTextures(3, shipTexture);
	//glBindTexture(GL_TEXTURE_2D, shipTexture[0]);

	glBindTexture(GL_TEXTURE_2D, shipTexture[0]);
	
	switch (modelType)	//0712장우석
	{
		std::cout << "텍스쳐 : "<<modelType << std::endl;
	case TYPE::model1:
		TexBits = Texture.LoadDIBitmap("resource/ship/ship1/ship01.BMP", &texture);
		break;
	case TYPE::model2:
		TexBits = Texture.LoadDIBitmap("resource/ship/ship2/ship02.BMP", &texture);
		break;
	case TYPE::model3:
		TexBits = Texture.LoadDIBitmap("resource/ship/ship3/ship03.BMP", &texture);
		break;
	case TYPE::model4:
		TexBits = Texture.LoadDIBitmap("resource/ship/ship4/ship04.BMP", &texture);
		break;
	default:
		std::cout << "텍스쳐 어느거 할거냐" << std::endl;
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


}