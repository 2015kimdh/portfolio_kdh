#pragma once
#include <GL/freeglut.h>
#include"pch.h"
//#include "../../import/GL/glut.h"
#include <cmath>
#include "float3.h"


#define WWIDTH 1600
#define WHEIGHT 800
#define DEPTH 400

template<typename Vector3>
float Length(Vector3&& vec) { return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z); }
#define PI 3.14
template<typename Vector3>
Vector3 Normalize(Vector3&& vec)
{
	float fLength = Length(vec);
	if (fLength == 0) return Vector3{ 0, 0, 0 };
	return Vector3{ vec.x / fLength, vec.y / fLength, vec.z / fLength };
}

template <typename Vector3>
class Camera
{
	Vector3 m_at{ 0.f, 0.f, 0.f };
	Vector3 m_up{ 0.f, 1.f, 0.f };


	float m_distance{ 0 };

	float m_vertical{ 3.14f*0.5f };
	float m_horizontal{ 0 };
	
	

	float m_aspect{ 0 };
	float m_near{ 0.f };
	float m_far{ 1.f };
	float m_fovy{ 0 };

public:
	Camera()
		// ī�޶� ���� �� ���� 1ȸ�� aspect�� �ڵ����� �����Ѵ�.
		: m_aspect{ glutGet(GLUT_WINDOW_WIDTH) / static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) }
	{
	}
	Camera(float aspect)
		// ī�޶� ���� �� ���� 1ȸ�� aspect�� �ڵ����� �����Ѵ�.
		: m_aspect{ aspect }
	{
	}

	~Camera() = default;

	void Initialize(const Vector3 & pos, float distance, float zNear, float zFar, float fov)
	{
		m_fovy = fov;
		m_near = zNear;
		m_far = zFar;
		m_distance = distance;
		m_at = pos;
	}

	void SetAspect(float aspect) { m_aspect = aspect; }
	Vector3 GetPosition()   const { return m_at; }

	void SetAt(const Vector3& pos) { m_at = pos; LookAt(); }
	//void SetAt(Vector3&& pos)   noexcept { m_at = std::move(pos); LookAt(); }
	void Move(const Vector3& pos)   noexcept { SetAt(m_at + pos); }
	//void Move(Vector3&& pos)      noexcept { SetPosition(m_at + std::move(pos)); }

	void SetDistance(const float& d) { m_distance = fmax(d, m_near); }
	float GetDistance() const { return m_distance; }


	void zoom(float per) {m_distance = m_distance * per; }

	void Rotate(float v, float h)
	{
		m_vertical += v;
		if (-PI * 0.5f <= m_horizontal + h && m_horizontal + h <= PI * 0.5f)
			m_horizontal += h;
	}

	void LookAt() const
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		Vector3 vEye{ eye() };

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluPerspective(m_fovy, m_aspect, m_near, m_far);

		gluLookAt(
			vEye.x, vEye.y, vEye.z,      //ī�޶��� ��ġ
			m_at.x, m_at.y, m_at.z,   //(����)�ٶ󺸴°�
			m_up.x, m_up.y, m_up.z      //������
		);
	}

	void LookAtOrtho() const
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		Vector3 vEye{ eye() };
		
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		glOrtho(-WWIDTH / 2, WWIDTH/2, -WHEIGHT/2, WHEIGHT/2, 5, 6000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(
			vEye.x, vEye.y, vEye.z,      //ī�޶��� ��ġ
			m_at.x, m_at.y, m_at.z,		//�ٶ󺸴°�
			m_up.x, m_up.y, m_up.z      //������
		);

	}

	void LookAtOrtho1() const
	{
		glViewport(50,30, WWIDTH/2-75, WHEIGHT -00);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		Vector3 vEye{ eye() };
		
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		//glOrtho(-WWIDTH/4, WWIDTH/4, -WHEIGHT/2, WHEIGHT/2, -2000, 6000);
		gluPerspective(60.0, WWIDTH / WHEIGHT, 1.0, 6000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//gluLookAt(
		//	vEye.x, vEye.y, vEye.z,      //ī�޶��� ��ġ
		//	m_at.x, m_at.y, m_at.z,		//�ٶ󺸴°�
		//	m_up.x, m_up.y, m_up.z      //������
		//);

		gluLookAt(
			vEye.x, vEye.y, vEye.z,      //ī�޶��� ��ġ
			m_at.x, m_at.y, m_at.z,		//�ٶ󺸴°�
			m_up.x, m_up.y, m_up.z      //������
		);

	}

	void LookAtOrtho2() const
	{
		glViewport(WWIDTH/2, 30, WWIDTH/2-75, WHEIGHT-00);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		Vector3 vEye{ eye() };
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		//glOrtho(-WWIDTH/4, WWIDTH/4, -WHEIGHT/2, WHEIGHT/2, -2000, 6000);
		gluPerspective(60.0, WWIDTH / WHEIGHT, 1.0, 6000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(
			vEye.x, vEye.y, vEye.z,      //ī�޶��� ��ġ
			m_at.x, m_at.y, m_at.z,		//�ٶ󺸴°�
			m_up.x, m_up.y, m_up.z      //������
		);
	}

	void LookAtOrthoMinimap() const
	{
		glViewport(WWIDTH / 2 -125, 600, 200, 200);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		glOrtho(-WWIDTH, WWIDTH, -WHEIGHT, WHEIGHT, -2000, 6000);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		

	}

	void LookAtOrtho1pUI() const
	{
		glViewport(0, 0, 200, 200);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		glOrtho(-WWIDTH, WWIDTH, -WHEIGHT, WHEIGHT, -2000, 6000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


	}

	void LookAtOrtho1p_2UI() const	// hp
	{
		glViewport(WWIDTH / 4 - 100-10, WHEIGHT/2, 50, 200);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		glOrtho(-WWIDTH, WWIDTH, -WHEIGHT, WHEIGHT, -2000, 6000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


	}

	void LookAtOrtho1p_3UI() const		//�Ѿ�
	{
		glViewport(WWIDTH/4+100-10, WHEIGHT / 2, 50, 200);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		glOrtho(-WWIDTH, WWIDTH, -WHEIGHT, WHEIGHT, -2000, 6000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


	}

	void LookAtOrtho2pUI() const
	{
		glViewport(WWIDTH / 2 - 40, 0, 200, 200);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		glOrtho(-WWIDTH, WWIDTH, -WHEIGHT, WHEIGHT, -2000, 6000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


	}

	void LookAtOrtho2p_2UI() const
	{
		glViewport(WWIDTH * 3 / 4 - 100 - 60, WHEIGHT / 2, 50, 200);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		glOrtho(-WWIDTH, WWIDTH, -WHEIGHT, WHEIGHT, -2000, 6000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


	}

	void LookAtOrtho2p_3UI() const
	{
		glViewport(WWIDTH * 3/ 4 + 100 - 50, WHEIGHT / 2, 50, 200);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		glOrtho(-WWIDTH, WWIDTH, -WHEIGHT, WHEIGHT, -2000, 6000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


	}

	void LookAtOrthoscene() const
	{
		glViewport(0, -20, WWIDTH, WHEIGHT+50);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		Vector3 vEye{ eye() };
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		glOrtho(-WWIDTH / 2, WWIDTH / 2, -WHEIGHT / 2, WHEIGHT / 2, 5, 6000);
		

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(
			vEye.x, vEye.y, vEye.z,      //ī�޶��� ��ġ
			m_at.x, m_at.y, m_at.z,		//�ٶ󺸴°�
			m_up.x, m_up.y, m_up.z      //������
		);

	}

	void LookAtSelectscene() const
	{
		glViewport(WWIDTH / 2, 200, WWIDTH / 2 - 50, WHEIGHT - 200);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		Vector3 vEye{ eye() };
		// ������ ����� ���缭 ���Ƿ� �ٲ�
		//glOrtho(-WWIDTH/4, WWIDTH/4, -WHEIGHT/2, WHEIGHT/2, -2000, 6000);
		gluPerspective(60.0, WWIDTH / WHEIGHT, 1.0, 6000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(
			vEye.x, vEye.y, vEye.z,      //ī�޶��� ��ġ
			m_at.x, m_at.y, m_at.z,		//�ٶ󺸴°�
			m_up.x, m_up.y, m_up.z      //������
		);
	}


	Vector3 GetLookVector() const
	{
		return Normalize(Vector3
			{
			   cos(m_horizontal) * cos(m_vertical),
			   sin(m_horizontal),
			   cos(m_horizontal) * sin(m_vertical)
			});
	}

	Vector3 eye() const { return GetPosition() - GetLookVector() * m_distance; }
};