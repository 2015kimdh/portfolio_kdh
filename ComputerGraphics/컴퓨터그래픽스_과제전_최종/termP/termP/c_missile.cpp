#include "pch.h"
#include "c_missile.h"
#include "c_ship.h"
#include "math.h"
#include "c_background.h"
#include "Sound.h"
#include "TextureManager.h"

c_missile::c_missile()
{
}


c_missile::~c_missile()
{
}

void c_missile::init(float Angle, float Distance)
{
	starting[x] = ship->position[x];
	starting[y] = 80;
	starting[z] = ship->position[z];

	sound->Play(2);
	collide = false;
	reload = 0;
	t = 0;
	position[x] = ship->position[x];
	position[y] = 80;
	position[z] = ship->position[z];


	enemyposition[x] = position[x] + (cos(Angle) * Distance);
	enemyposition[y] = 80;
	enemyposition[z] = position[z] + (sin(Angle) * Distance);

	Radianx = atan2(starting[x], enemyposition[x]);
	Radianz = atan2(starting[z], enemyposition[z]);
	state = true;

	float cx, cz;
	cx = pow(ship->position[x] - enemyship->position[x], 2);
	cz = pow(ship->position[z] - enemyship->position[z], 2);
	
	if (cx + cz <= 400)
	{
		slice = reallyneardistance/20;
	}
	else if (cx + cz > 400 && cx + cz <= 900)
	{
		slice = neardistance/20;
	}
	else if (cx + cz > 900 && cx + cz <= 1600)
	{
		slice = middledistance/20;
	}
	else if (cx + cz > 1600)
	{
		slice = fardistance/20;
	}
}

void c_missile::ParticleDraw()
{
	if (particle > 0)
	{
		auto explotion = TextureInstance->EnableTextur(ENUM_TEXTURE::EXPLOTION);
		glPushMatrix();
		{
			glTranslatef(particlepos[x], particlepos[y], particlepos[z]);
			glPushMatrix();
			{
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(partsize/2, partsize / 2, 0.0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(partsize / 2, -partsize / 2, 0.0);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-partsize / 2, -partsize / 2, 0.0);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-partsize / 2, partsize / 2, 0.0);
				glEnd();

			}
			glPopMatrix();
			glPushMatrix();
			{
				glRotated(180, 0, 1, 0);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(partsize / 2, partsize / 2, 0.0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(partsize / 2, -partsize / 2, 0.0);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-partsize / 2, -partsize / 2, 0.0);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-partsize / 2, partsize / 2, 0.0);
				glEnd();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glRotated(90, 0, 1, 0);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(partsize / 2, partsize / 2, 0.0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(partsize / 2, -partsize / 2, 0.0);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-partsize / 2, -partsize / 2, 0.0);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-partsize / 2, partsize / 2, 0.0);
				glEnd();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glRotated(-90, 0, 1, 0);
				glEnable(GL_TEXTURE_2D);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(partsize / 2, partsize / 2, 0.0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(partsize / 2, -partsize / 2, 0.0);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-partsize / 2, -partsize / 2, 0.0);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-partsize / 2, partsize / 2, 0.0);
				glEnd();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glPushMatrix();
				{
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 1.0f);
					glVertex3f(partsize / 2, 0.0, partsize / 2);
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(partsize / 2, 0.0, -partsize / 2);
					glTexCoord2f(1.0f, 0.0f);
					glVertex3f(-partsize / 2, 0.0, -partsize / 2);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(-partsize / 2, 0.0, partsize / 2);
					glEnd();
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glRotated(90, 1, 0, 0);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(partsize / 2, partsize / 2, 0.0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(partsize / 2, -partsize / 2, 0.0);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(-partsize / 2, -partsize / 2, 0.0);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-partsize / 2, partsize / 2, 0.0);
				glEnd();
			}
			glPopMatrix();
		}
		glPopMatrix();
		TextureInstance->DisableTextur(ENUM_TEXTURE::EXPLOTION, explotion);
	}
	partsize -= 30;
	if (partsize == 0)
	{
		particle = false;
	}
}

void c_missile::Collide()
{
	float cx, cz = 0;
	for (int i = 0; i < backGround->landamount; i++)
	{
		for (int j = 0; j < backGround->landsubamount; j++)
		{
			cx = pow(position[x] - backGround->land[i][j].position[x]+25, 2);
			cz = pow(position[z] - backGround->land[i][j].position[z]+25, 2);
			if (cx + cz <= 4000)
				//if (cx + cz <= 4900)
			{
				collide = true;
			}
		}
	}
}

void c_missile::missileroad()
{
	position[x] = ((1-t/slice)*starting[x] + t/ slice *enemyposition[x]);
	position[y] = ((1 - t/ slice)*(1 - t/ slice)*starting[y] + 2 * t/ slice *(1 - t/ slice)*((starting[y] + enemyposition[y] + slice*20) / 2) + t/slice * t/ slice *enemyposition[y]);
	position[z] = ((1 - t / slice)*starting[z] + t / slice * enemyposition[z]);
	//position[z] = ((1 - t)*(1 - t)*starting[x] + 2 * t*(1 - t)*((starting[x] + enemyposition[x]) / 2) + t * t*enemyposition[x]);
}

void c_missile::update()
{
	t += 1;
	if (t >= slice && state == true)
	{
		for (int i = 0; i < 50; ++i)
			for (int j = 0; j < 50; ++j)
				if ((backGround->seaPoints[i][j - 1][x] <= enemyposition[x] && enemyposition[x] <= backGround->seaPoints[i][j + 1][x]) &&
					(backGround->seaPoints[i - 1][j][z] <= enemyposition[z]  && enemyposition[z] <= backGround->seaPoints[i + 1][j][z])){
					backGround->waterSplash[i][j] = 50.0f;
				}



		state = false;
		particle = true;
		partsize = 300;
		particlepos[x] = position[x];
		particlepos[y] = position[y];
		particlepos[z] = position[z];

		sound->Play(3);
		float cx, cz = 0;
		cx = pow(position[x] - enemyship->position[x], 2);
		cz = pow(position[z] - enemyship->position[z], 2);
		if (cx + cz <= 10000)
			//if (cx + cz <= 9000)
		{
			if (cx + cz <= 8000)
				//if (cx + cz <= 6000)
			{
				enemyship->hp -= 20;
				//enemyship->hp -= enemyship->hp / 4;
			}
			else
			{
				enemyship->hp -= 10;
				//enemyship->hp -= enemyship->hp / 6;
			}

		}
	}
	else if(t < slice && state == true)
	{
		missileroad();
		
	}
	if (reload < 50)
	{
		reload += 1;
	}
	if (state == true)
	{
		Collide();
		if (collide == true)
		{
			state = false;
			particle = true;
			partsize = 300;
			particlepos[x] = position[x];
			particlepos[y] = position[y];
			particlepos[z] = position[z];

			sound->Play(3);

		}
	}
}

void c_missile::drawMissile()
{
	if (state == true)
	{
		glPushMatrix();
		{
			glTranslatef(position[x], position[y], position[z]);
			glutSolidSphere(10, 6, 6);
		}
		glPopMatrix();
	}
}