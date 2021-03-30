#include "pch.h"
#include "c_background.h"
#include "c_weather.h"


c_background::c_background()
{
}


c_background::~c_background()
{
}

void c_background::textureSetUp()
{
	glGenTextures(2, seaTexture);
	glBindTexture(GL_TEXTURE_2D, seaTexture[0]);

	//2차원상의 텍스처 이미지 정의
	TexBits = Texture.LoadDIBitmap("resource/sea_tile.bmp", &texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

}

void c_background::drawSea()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, seaTexture[0]);

	for (int i = 0; i < SEA_HEIGHT; i++)
	{
		for (int j = 0; j < SEA_WIDTH; j++)
		{
			glPushMatrix();
			{
				glTranslated(seaPoints[i][j][x], seaPoints[i][j][y], seaPoints[i][j][z]);
				glScalef(1, waterSplash[i][j], 1);
				//glColor3f(0.0, 0.0, 1.0);
				//glColor3f(0.0, 0.0, 0.4);
				//glutWireCube(SEA_CUBE_SIZE+2);

				light.enableMaterial(SEA);

				glColor3f(1.0, 1.0, 1.0);

				//glutSolidCube(SEA_CUBE_SIZE);
				cube(0, 0, 0, SEA_CUBE_SIZE);

				light.disableMaterial();


			}
			glPopMatrix();
		}
	}

	glDisable(GL_TEXTURE_2D);


	for (int i = 0; i < LAND_AMOUNT; i++)
		for (int j = 0; j < LAND_SUB_AMOUNT; j++)
			land[i][j].drawLand();

	sky.drawSky();

}

void c_background::seaUpdate()
{


	for (int i = 0; i < SEA_HEIGHT; i++)
	{
		for (int j = 0; j < SEA_WIDTH; j++)
		{
			waveWid[i][j] += deltaAmplitude;
			waveHei[i][j] += deltaAmplitude;
			//waveWid[i][j] = waveWid[i][j] % (2*PI);

			seaPoints[i][j][y] = amplitude * sin(waveWid[i][j]) + amplitude * sin(waveHei[i][j]);
		}
	}


}

void c_background::init()
{

	for (int i = 0; i < LAND_AMOUNT; i++)
		//for (int i = 0; i < 1; i++)
	{
		land[i][0].init();
		for (int j = 1; j < LAND_SUB_AMOUNT; j++)
		{
			land[i][j].textureSetUp();
			land[i][j].objectSetUp();
			land[i][j].position[x] = land[i][0].position[x] + rand() % 30 * 10 - 600;
			land[i][j].position[z] = land[i][0].position[z] + rand() % 30 * 10 - 600;
			land[i][j].position[y] = land[i][0].position[y] - rand() % 10 * 30;
			//land[i][j].height = land[i][0].height - rand() % 20 * 20;
		}
	}


	for (int i = 0; i < SEA_HEIGHT; i++)
	{
		for (int j = 0; j < SEA_WIDTH; j++)
		{
			seaPoints[i][j][x] = SEA_CUBE_SIZE * j - SEA_CUBE_SIZE * SEA_WIDTH / 2;
			seaPoints[i][j][z] = SEA_CUBE_SIZE * i - SEA_CUBE_SIZE * SEA_HEIGHT / 2;
			waveWid[i][j] = 0.02 * PI * i;
			waveHei[i][j] = 0.01 * PI * j;
			seaPoints[i][j][y] = amplitude * sin(waveWid[i][j]) + amplitude * sin(waveHei[i][j]);
			waterSplash[i][j] = 1.0f;
		}
	}

	textureSetUp();
	sky.textureSetUp();
}

void c_background::cube(float centerX, float centerY, float centerZ, float length)
{

	float left = centerX - length;
	float right = centerX + length;
	float top = centerY + 10;
	float bottom = centerY - length * 2;
	float front = centerZ - length;
	float back = centerZ + length;


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