#include "stdafx.h"
#include "Object.h"
#include <math.h>
#include <iostream>
#include <float.h>

Object::Object()
{
	m_posX = 0;
	m_posY = 0;
	m_posZ = 0;

	m_volX = 0;
	m_volY = 0;
	m_volZ = 0;

	m_r = 0;
	m_g = 0;
	m_b = 0;
	m_a = 0;

	m_accX = 0;
	m_accY = 0;
	m_accZ = 0;

	m_velX = 0;
	m_velY = 0;
	m_velZ = 0;

	m_mass = 0;
	m_fricCoef = 0.f;
}


Object::~Object()
{
}

void Object::SetPos(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

void Object::GetPos(float * x, float * y, float * z)
{
	*x = m_posX;
	*y = m_posY;
	*z = m_posZ;
}

void Object::SetVol(float x, float y, float z)
{
	m_volX = x;
	m_volY = y;
	m_volZ = z;
}

void Object::GetVol(float * x, float * y, float * z)
{
	*x = m_volX;
	*y = m_volY;
	*z = m_volZ;
}

void Object::SetVel(float x, float y, float z)
{
	m_velX = x;
	m_velY = y;
	m_velZ = z;
}

void Object::GetVel(float * x, float * y, float * z)
{
	*x = m_velX;
	*y = m_velY;
	*z = m_velZ;
}

void Object::SetAcc(float x, float y, float z)
{
	m_accX = x;
	m_accY = y;
	m_accZ = z;
}

void Object::GetAcc(float * x, float * y, float * z)
{
	*x = m_accX;
	*y = m_accY;
	*z = m_accZ;
}

void Object::SetColor(float r, float g, float b, float a)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}

void Object::GetColor(float * r, float * g, float * b, float * a)
{
	*r = m_r;
	*g = m_g;
	*b = m_b;
	*a = m_a;
}

void Object::SetMass(float mass)
{
	m_mass = mass;
}

void Object::GetMass(float * mass)
{
	*mass = m_mass;
}

void Object::SetFricCoef(float coef)
{
	m_fricCoef = coef;
}

void Object::GetFricCoef(float * coef)
{
	*coef = m_fricCoef;
}

void Object::SetType(int type)
{
	m_type = type;
}

void Object::GetType(int * type)
{
	*type = m_type;
}

void Object::SetTex(int ID)
{
	m_TexID = ID;
}

void Object::GetTex(int *ID)
{
	*ID = m_TexID;
}

void Object::InitThis()
{
	m_posX, m_posY, m_posZ = -1.f;
	m_velX, m_velY, m_velZ = -1.f;
	m_accX, m_accY, m_accZ = -1.f;
	m_volX, m_volY, m_volZ = -1.f;
	m_r, m_g, m_b = -1.f;
	m_mass = -1.f;

}

void Object::AddForce(float x, float y, float z, float elpasedTimeInSecond)
{
	float accX = x / m_mass;
	float accY = y / m_mass;
	float accZ = z / m_mass;

	m_velX = m_velX + accX * elpasedTimeInSecond;
	m_velY = m_velY + accY * elpasedTimeInSecond;
	m_velZ = m_velZ + accZ * elpasedTimeInSecond;
}

void Object::Update(float elpasedTimeInSecond)
{
	//Apply friction
	float Fn = GRAVITY * m_mass;
	float Friction = m_fricCoef * Fn;


	// normalize velocity vector for getting direction of object
	float velSize = sqrtf(
		m_velX * m_velX +
		m_velY * m_velY
	);


	//--------------------------------------------------------------

	float dirX;
	float dirY;

	if (velSize > 0.00001f)
	{
		dirX = m_velX / velSize;
		dirY = m_velY / velSize;

		// calculate friction force 
		float frictionX = -dirX * Friction;
		float frictionY = -dirY * Friction;

		// calculate friction acc
		float accX = frictionX / m_mass;
		float accY = frictionY / m_mass;

		// Update velocity by friction force
		float newVelX = m_velX + accX * elpasedTimeInSecond;
		float newVelY = m_velY + accY * elpasedTimeInSecond;

		if (newVelX * m_velX < 0.f)
		{
			m_velX = 0.f;
		}
		else
		{
			m_velX = newVelX;
		}


		if (newVelY * m_velY < 0.f)
		{
			m_velY = 0.f;
		}
		else
		{
			m_velY = newVelY;
		}


	}

	//-------------------------------------------------------------------

	// Update position
	m_posX = m_posX + m_velX * elpasedTimeInSecond;
	m_posY = m_posY + m_velY * elpasedTimeInSecond;
	m_posZ = m_posZ + m_velZ * elpasedTimeInSecond;

}

bool Object::CanshootBullet()
{
	if (m_remaininingBulletCoolTime < FLT_EPSILON) {
		return true;
	}
	return false;
}

void Object::ResetBulletCoolTime()
{
	m_remaininingBulletCoolTime = m_bulletcooltime;
}


