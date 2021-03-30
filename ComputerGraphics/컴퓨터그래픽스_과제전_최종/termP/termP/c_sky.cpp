#include "pch.h"
#include "c_sky.h"


c_sky::c_sky()
{
}


c_sky::~c_sky()
{
}


void c_sky::drawSky()
{

	// 텍스쳐 활성화

	float w = 50 * 50; // SEA_CUBE_SIZE * SEA_WIDTH
	float h = 2048;

	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, skyTexture[i]);

		glPushMatrix();
		{
			glRotatef(90 * i, 0, 1, 0);
			glTranslated(0.0, -20.0, -50 * 50 / 2);
			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 1.0);
			{
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-w / 2, h, 0.0);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-w / 2, 0.0, 0.0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(w / 2, 0.0, 0.0);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(w / 2, h, 0.0);
			}
			glEnd();
		}
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);


}



void c_sky::textureSetUp()
{
	glGenTextures(4, skyTexture);
	glBindTexture(GL_TEXTURE_2D, skyTexture[0]);

	//2차원상의 텍스처 이미지 정의
	TexBits = Texture.LoadDIBitmap("resource/Horizon_0.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	//=============================================================================
	glBindTexture(GL_TEXTURE_2D, skyTexture[1]);

	//2차원상의 텍스처 이미지 정의
	TexBits = Texture.LoadDIBitmap("resource/Horizon_1.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


	//=============================================================================
	glBindTexture(GL_TEXTURE_2D, skyTexture[2]);

	//2차원상의 텍스처 이미지 정의
	TexBits = Texture.LoadDIBitmap("resource/Horizon_2.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	//=============================================================================
	glBindTexture(GL_TEXTURE_2D, skyTexture[3]);

	//2차원상의 텍스처 이미지 정의
	TexBits = Texture.LoadDIBitmap("resource/Horizon_3.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

}

