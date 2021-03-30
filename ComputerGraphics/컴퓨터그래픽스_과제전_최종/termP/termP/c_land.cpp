#include "pch.h"
#include "c_land.h"


c_land::c_land()
{
}


c_land::~c_land()
{
}

void c_land::init()
{
	positionSetUp();
	textureSetUp();
	objectSetUp();
}

void c_land::drawLand()
{
	int length = 20;
	float left = position[x] - length;
	float right = position[x] + length;
	float top = position[y] + height;
	float bottom = 0.0;
	float front = position[z] - length;
	float back = position[z] + length;


	//glColor3f(0.5, 0.3, 0.1);

	glPushMatrix();//=========================
	{

		glTranslated(position[x], position[y], position[z]);

		glRotated(90 * rotate, 0, 1, 0);

		glEnable(GL_NORMALIZE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, landTexture[0]);

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



		//cube();


	}
	glPopMatrix();//=========================

}

void c_land::textureSetUp()
{
	glGenTextures(2, landTexture);
	glBindTexture(GL_TEXTURE_2D, landTexture[0]);

	//2차원상의 텍스처 이미지 정의
	TexBits = Texture.LoadDIBitmap("resource/stone2.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


}

void c_land::positionSetUp()
{
	//height = rand() % 100 + 200;
	position[x] = (rand() % 50) * 20 - 500;
	position[z] = (rand() % 50) * 20 - 500;
}

void c_land::objectSetUp()
{
	rotate = rand() % 4;
	loadOBJ("resource/land.obj", out_vertices, out_uvs, out_normals);
}


void c_land::cube()
{

	int length = 20;
	float left = -length;
	float right = +length;
	float top = +height;
	float bottom = 0.0;
	float front = -length;
	float back = +length;



	//옆면
	for (int i = 0; i < 4; i++)
	{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, landTexture[0]);
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
		glDisable(GL_TEXTURE_2D);

	}

	//	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
		//위아래
	for (int i = 0; i < 2; i++)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, landTexture[0]);
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
		glDisable(GL_TEXTURE_2D);
	}

}