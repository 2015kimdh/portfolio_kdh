#pragma once

enum
{
	OBJ_NORMAL,
	OBJ_BUlLET
};

class Object
{
public:
	Object();
	~Object();

	void SetPos(float x, float y, float z);
	void GetPos(float *x, float *y, float *z);

	void SetVol(float x, float y, float z);
	void GetVol(float *x, float *y, float *z);

	void SetVel(float x, float y, float z);
	void GetVel(float *x, float *y, float *z);

	void SetAcc(float x, float y, float z);
	void GetAcc(float *x, float *y, float *z);

	void SetColor(float r, float g, float b, float a);
	void GetColor(float *r, float *g, float *b, float *a);

	void SetMass(float mass);
	void GetMass(float *mass);

	void SetFricCoef(float coef);
	void GetFricCoef(float *coef);

	void SetType(int type);
	void GetType(int *type);

	void SetTex(int ID);
	void GetTex(int *ID);

	void AddForce(float x, float y, float z, float elapsedTime);

	void InitThis();
	void Update(float elpasedTimeInSecond);

	bool CanshootBullet();
	void ResetBulletCoolTime();

private:
	float	m_r, m_g, m_b, m_a;		// color
	float	m_posX, m_posY, m_posZ;	// position
	float	m_velX, m_velY, m_velZ;	// velocity
	float	m_accX, m_accY, m_accZ;	// acceleration
	float	m_volX, m_volY, m_volZ;	// volume
	float	m_mass;					// mass
	float	m_fricCoef;				// fricition coeffcient	
	int		m_type;					// obj_type

	float m_remaininingBulletCoolTime;
	float m_bulletcooltime;

	int m_TexID = -1;
};

