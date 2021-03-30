#include <gl/freeglut.h>
#include <random>
#include <time.h>
#include <math.h>


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct Triangle {
	int angle = 0;
	bool select = false;
	int x = -400;
	int y = 250;
};

struct Sliced {
	int status = 0;
	double x,y = 0;
	double angle = 0;
	int targetx = 0;
	int targety = 0;
	float target_angle = 0;
	double pro = 0;
};

struct Trash {
	double x = 0;
	double y = 0;
	int stack = 0;
};

struct Star {
	bool qu = false;
	int angle = 0;
	bool select = false;
	int x = 0;
	int y = 0;
	int tx = 0;
	int ty = 0;
	int size = 30;
	float grow = 0;
	int up = 0;
	float timer = 0;
	float r,g,b = 0;
};

struct Square {
	int type = 0;
	int x = 0;
	int y = 0;
};

Triangle tri[10];
Star star[50];
Square sq[2];
Trash tr[13][3];
Sliced sli[6];

bool star_select = FALSE;
bool tri_select = FALSE;
int star_num = 0;
int mx, my = 0;
int sx, sy = 0;
int rx, ry = 0;
bool mdown, rdown = FALSE;
int timer = 100 / 6;
void TimerFunction(int value);
bool left_button;
bool right_button;

void Merge_star()
{
	int cx, cy = 0;
	if (star_select == TRUE)
	{
		star[star_num].x = rx;
		star[star_num].y = ry;
		for (int i = 0; i < 50; i += 1)
		{
			if (i != star_num && star[i].qu == true)
			{
				cx = pow(star[i].x - rx, 2);
				cy = pow(star[i].y - ry, 2);
				if (cx + cy < 1000)
				{
					star[i].size += star[star_num].size/2;
					star[i].r += star[star_num].r;
					star[i].g += star[star_num].g;
					star[i].b += star[star_num].b;
					star[star_num].size = 30;
					star[star_num].qu = false;
					
				}
			}
		}
	}
	star_select = FALSE;
}

void Pick_star()
{
	int cx, cy = 0;
	if (star_select == FALSE)
	{
		for (int i = 0; i < 50; i += 1)
		{
			if (star[i].qu == true)
			{
				cx = pow(star[i].x - rx, 2);
				cy = pow(star[i].y - ry, 2);
				if (cx + cy < 900)
				{
					star[i].select = true;
					star_select = TRUE;
					star_num = i;
					break;
				}
			}
		}
	}
	if (star_select == TRUE)
	{
		star[star_num].x = rx;
		star[star_num].y = ry;
	}
}

void Make_Star()
{
	int cx, cy = 0;
	for (int i = 0; i < 10; i += 1)
	{
		cx = pow(tri[i].x - rx, 2);
		cy = pow(tri[i].y - ry, 2);
		if (cx + cy < 900)
		{
			for (int j = 0; j < 6; j += 1)
			{
				if (sli[j].status == 3)
				{
					sli[j].status = 0;
					sli[j].x = 0;
					sli[j].pro = 0;
					tri_select = FALSE;
					tri[i].select = true;
					for (int k = 0; k < 50; k += 1)
					{
						if (star[k].qu == false)
						{
							star[k].qu = true;
							star[k].x = rx;
							star[k].y = ry;
							star[k].tx = (rand() % 700) - 350;
							star[k].ty = (rand() % 400) - 200;
							star[k].timer = 0;
							break;
						}
					}
				}
			}
		}
	}
}

void Draw_star()
{
	float tt, tm, t;
	for (int i = 0; i < 50; i += 1)
	{
		if (star[i].qu == true)
		{
				if (star[i].timer < 100)
				{
					tt = pow((1 - star[i].timer / 100), 2);	//(1-t)^2
					tm = (1 - star[i].timer / 100);			//(1-t)
					t = (star[i].timer / 100);					//t
					glPushMatrix();
					{
						glTranslatef(tt*star[i].x + 2 * t*tm*((star[i].x + star[i].tx) / 2)+ t * t* star[i].tx, tt*star[i].y + 2 * t*tm*((star[i].y + star[i].ty)+100) + t * t*star[i].ty, 0);
						glRotatef(star[i].angle, 0.0, 0.0, 1.0);
						glColor3f(star[i].r, star[i].g, star[i].b);
						glBegin(GL_POLYGON);
						{
							glVertex2i(0, -star[i].size - star[i].grow);
							glVertex2i(-star[i].size - star[i].grow, star[i].size / 2 + star[i].grow);
							glVertex2i(star[i].size + star[i].grow, star[i].size / 2 + star[i].grow);
						}
						glEnd();
						glBegin(GL_POLYGON);
						{
							glVertex2i(0, star[i].size + star[i].grow);
							glVertex2i(star[i].size + star[i].grow, -star[i].size / 2 + star[i].grow);
							glVertex2i(-star[i].size - star[i].grow, -star[i].size / 2 + star[i].grow);
						}
						glEnd();
					}
					glPopMatrix();

					star[i].timer += 1;
					if (star[i].timer == 100)
					{
						star[i].x = star[i].tx;
						star[i].y = star[i].ty;
					}
				}
				else
				{
					glPushMatrix();
					{
						glTranslatef(star[i].x,  star[i].y, 0);
						glRotatef(star[i].angle, 0.0, 0.0, 1.0);
						glColor3f(star[i].r, star[i].g, star[i].b);
						glBegin(GL_POLYGON);
						{
							glVertex2i(0, -star[i].size - star[i].grow);
							glVertex2i(-star[i].size - star[i].grow, (star[i].size + star[i].grow)/ 2);
							glVertex2i(star[i].size + star[i].grow, (star[i].size + star[i].grow) / 2);
						}
						glEnd();
						glBegin(GL_POLYGON);
						{
							glVertex2i(0, star[i].size + star[i].grow);
							glVertex2i(star[i].size + star[i].grow, (-star[i].size - star[i].grow)/ 2 );
							glVertex2i(-star[i].size - star[i].grow, (-star[i].size- star[i].grow) / 2 );
						}
						glEnd();
					}
					glPopMatrix();
				}
		}
		if (star[i].qu == true)
		{
			star[i].angle = (star[i].angle + 2) % 360;
			star[i].r = star[i].r + 0.02;
			star[i].g = star[i].g + 0.025;
			star[i].b = star[i].b + 0.03;
		}

		if (star[i].up == 1)
		{
			star[i].grow += 0.3;
		}
		else
		{
			star[i].grow -= 0.3;
		}

		if (star[i].grow >= 10)
		{
			star[i].up = 0;
		}
		if (star[i].grow <= 0)
		{
			star[i].up = 1;
		}

		if (star[i].r > 1)
		{
			star[i].r = 0;
		}
		if (star[i].g > 1)
		{
			star[i].g = 0;
		}
		if (star[i].b > 1)
		{
			star[i].b = 0;
		}
	}
}

void Draw_Pick()
{
	for (int i = 0; i < 6; i += 1)
	{
		if (sli[i].status == 3)
		{
			sli[i].x = rx;
			sli[i].y = ry;
			if (i % 2 == 1)
			{
				sli[i].angle = sli[i].angle + (sli[i].pro / 150) * (180 - sli[i].angle);
			}
			else
			{
				sli[i].angle = sli[i].angle + (sli[i].pro / 150) * (360 - sli[i].angle);
			}
			glPushMatrix();
			{
				glTranslatef(rx, ry, 0);
				glRotatef(sli[i].angle, 0.0, 0.0, 1.0);
				glColor3f(0.5, 0.8, 1.0);
				glBegin(GL_POLYGON);
				{
					glVertex2i(30, -30);
					glVertex2i(-30, -30);
					glVertex2i(-30, 30);
				}
				glEnd();
			}
			glPopMatrix();
		}
	}
}

void Pick_Up()
{
	float tt, t, tm = 0;
	
	float cx, cy = 0;
	for (int i = 0; i < 6; i += 1)
	{
		tt = pow((1 - sli[i].pro / 150), 2);
		tm = (1 - sli[i].pro / 150);
		t = (sli[i].pro / 150);

		if (sli[i].status == 2)
		{
			cx = pow(tt*sli[i].x + 2 * t*tm*((sli[i].x + tr[sli[i].targetx][sli[i].targety].x) / 2) + t * t*tr[sli[i].targetx][sli[i].targety].x - rx, 2);
			cy = pow(tt*sli[i].y + 2 * t*tm*((sli[i].y + tr[sli[i].targetx][sli[i].targety].y) + 400) + t * t*tr[sli[i].targetx][sli[i].targety].y - ry, 2);
			if (cx + cy < 2500 && rdown == TRUE)
			{
				sli[i].status = 3;
				tri_select = TRUE;
				break;
			}
		}
	}

}

void Cutter()
{
		glLineWidth(3.0f);
		glColor3f(1.0f, 1.0f, 0.3f);
		glBegin(GL_LINES);
		glVertex3i(mx, my, 0);
		glVertex3i(sx, sy, 0);
		glEnd();
}

void Spline()
{
	float tt, t, tm = 0;
	for (int i = 0; i < 6; i += 1)
	{
		if (sli[i].status == 2)
		{
			if (sli[i].pro < 150)
			{
				tt = pow((1 - sli[i].pro / 150), 2);	//(1-t)^2
				tm = (1 - sli[i].pro / 150);			//(1-t)
				t = (sli[i].pro / 150);					//t
				glPushMatrix();
				{
					glTranslatef(tt*sli[i].x + 2 * t*tm*((sli[i].x + tr[sli[i].targetx][sli[i].targety].x) / 2) + t * t*tr[sli[i].targetx][sli[i].targety].x, tt*sli[i].y + 2 * t*tm*((sli[i].y + tr[sli[i].targetx][sli[i].targety].y)+400) + t * t*tr[sli[i].targetx][sli[i].targety].y, 0);
					if (tr[sli[i].targetx][sli[i].targety].stack == 0)
					{
						glRotatef(sli[i].angle + t*(360-sli[i].angle), 0.0, 0.0, 1.0);
						//glRotatef(sli[i].angle, 0.0, 0.0, 1.0);
					}
					if (tr[sli[i].targetx][sli[i].targety].stack == 1)
					{
						glRotatef(sli[i].angle + t*(180-sli[i].angle), 0.0, 0.0, 1.0);
						//glRotatef(sli[i].angle, 0.0, 0.0, 1.0);
					}
					glColor3f(0.5, 0.8, 0.5);
					glBegin(GL_POLYGON);
					{
						glVertex2i(30, -30);
						glVertex2i(-30, -30);
						glVertex2i(-30, 30);
					}
					glEnd();
				}
				glPopMatrix();

				sli[i].pro += 1;
				if (sli[i].pro == 150)
				{
					tr[sli[i].targetx][sli[i].targety].stack += 1;
					sli[i].pro = 0;
					sli[i].status = 0;
					sli[i].x = 0;
				}
			}
		}
	}
}

void Draw_Trash()
{
	for (int i = 0; i < 3; i += 1)
	{
		for (int j = 0; j < 13; j += 1)
		{
			if (tr[j][i].stack == 1)
			{
				glPushMatrix();
				{
					glTranslatef(tr[j][i].x, tr[j][i].y, 0);
					glColor3f(0.5, 0.5, 0.5);
					glBegin(GL_POLYGON);
					glVertex2i(30, -30);
					glVertex2i(-30, -30);
					glVertex2i(-30, 30);
					glEnd();

				}
				glPopMatrix();
			}
			if (tr[j][i].stack == 2)
			{
				glPushMatrix();
				{
					glTranslatef(tr[j][i].x, tr[j][i].y, 0);
					glColor3f(0.5, 0.5, 0.5);
					glBegin(GL_POLYGON);
					glVertex2i(30, -30);
					glVertex2i(-30, -30);
					glVertex2i(-30, 30);
					glVertex2i(30, 30);
					glEnd();

				}
				glPopMatrix();
			}
		}
	}
}

void SlashedTri()
{
	for (int i = 0; i < 6; i += 2)
	{
		if (sli[i].status == 1)
		{
				sli[i].targetx = rand() % 6;
				
			for (int k = 3; k > 0; k -= 1)
			{
				if (tr[sli[i].targetx][k].stack < 2)
				{
					sli[i].status = 2;
					
					if (tr[sli[i].targetx][k].stack == 0)
					{
						sli[i].target_angle = -135;
						sli[i].targety = k;
					}
					if (tr[sli[i].targetx][k].stack == 1)
					{
						sli[i].target_angle = -315;
						sli[i].targety = k;
					}
				}
			}
		}
		if (sli[i+1].status == 1)
		{
			sli[i + 1].targetx = (rand() % 7) + 6;

			for (int k = 3; k > 0; k -= 1)
			{
				if (tr[sli[i + 1].targetx][k].stack < 2)
				{
					sli[i + 1].status = 2;

					if (tr[sli[i + 1].targetx][k].stack == 0)
					{
						sli[i + 1].target_angle = -135;
						sli[i + 1].targety = k;
					}
					if (tr[sli[i + 1].targetx][k].stack == 1)
					{
						sli[i + 1].target_angle = -315;
						sli[i + 1].targety = k;
					}
				}
			}

		}
	}
	Spline();
}

void Slash()
{
	int enable = 0;

	for (int i = 0; i < 2; i += 1)
	{
		if (sq[i].type == 0)
		{
			if (mx >= sq[i].x - 25 && mx <= sq[i].x + 25 && sx >= sq[i].x - 25 && sx <= sq[i].x + 25)
			{
				if (my <= sq[i].y - 25 && sy >= sq[i].y + 25)
				{
					enable = 1;
					sq[i].type = 2;
				}

				if (sy <= sq[i].y - 25 && my >= sq[i].y + 25)
				{
					enable = 1;
					sq[i].type = 2;
				}
			}
			if (my <= sq[i].y + 25 && sy >= sq[i].y - 25)
			{
				if ((mx <= sq[i].x - 25 && sx >= sq[i].x + 25) || (sx <= sq[i].x - 25 && mx >= sq[i].x + 25))
				{
					enable = 2;
					sq[i].type = 2;
				}
			}
			if (sy <= sq[i].y + 25 && my >= sq[i].y - 25)
			{
				if ((mx <= sq[i].x - 25 && sx >= sq[i].x + 25) || (sx <= sq[i].x - 25 && mx >= sq[i].x + 25))
				{
					enable = 2;
					sq[i].type = 2;
				}
			}
		}
		if (sq[i].type == 1)
		{
			if ((sx <= sq[i].x - 25 && sy >= sq[i].y + 25 && mx >= sq[i].x + 25 && my <= sq[i].y - 25) || (mx <= sq[i].x - 25 && my >= sq[i].y + 25 && sx >= sq[i].x + 25 && sy <= sq[i].y - 25))
			{
					enable = 3;
					sq[i].type = 2;
			}
			if((sx >= sq[i].x + 25 && sy >= sq[i].y + 25 && mx <= sq[i].x - 25 && my <= sq[i].y - 25) || (mx >= sq[i].x + 25 && my >= sq[i].y + 25 && sx <= sq[i].x - 25 && sy <= sq[i].y - 25))
			{
				enable = 4;
				sq[i].type = 2;
			}
		}

		if (enable == 1)
		{
			for (int k = 0; k < 6; k += 2)
			{
				if (sli[k].status == 0)
				{
					sli[k].angle = -45;
					sli[k].y = sq[i].y;
					for (int m = 0; m < 6; m += 2)
					{
						if (sli[m+1].status == 0)
						{
							sli[m+1].angle = -225;
							sli[m+1].y = sq[i].y;
							sli[m+1].status = 1;
							break;
						}
					}
					sli[k].status = 1;
					
					enable = 0;
					break;
				}
			}
		}
		else if (enable == 2)
		{
			for (int k = 0; k < 6; k += 2)
			{
				if (sli[k].status == 0)
				{
					sli[k].angle = 45;
					sli[k].y = sq[i].y;
					
					sli[k].status = 1;
					for (int m = 0; m < 6; m += 2)
					{
						if (sli[m+1].status == 0)
						{
							sli[m+1].angle = 225;
							sli[m+1].y = sq[i].y;
							sli[m+1].status = 1;
							break;
						}
					}
					enable = 0;
					break;
				}
			}
		}
		else if (enable == 3)
		{
			for (int k = 0; k < 6; k += 2)
			{
				if (sli[k].status == 0)
				{
					sli[k].angle = 0;
					sli[k].y = sq[i].y;
					
					sli[k].status = 1;
					for (int m = 0; m < 6; m += 2)
					{
						if (sli[m+1].status == 0)
						{
							sli[m+1].angle = 180;
							sli[m+1].y = sq[i].y;
							sli[m+1].status = 1;
							break;
						}
					}
					enable = 0;
					break;
				}
			}
		}
		else if (enable == 4)
		{
			for (int k = 0; k < 6; k += 2)
			{
				if (sli[k].status == 0)
				{
					sli[k].angle = -90;
					sli[k].y = sq[i].y;
					sli[k].status = 1;
					for (int m = 0; m < 6; m += 2)
					{
						if (sli[m+1].status == 0)
						{	
							sli[m+1].angle = -270;
							sli[m+1].y = sq[i].y;
							sli[m+1].status = 1;
							break;
						}
					}
					enable = 0;
					break;
				}
			}
		}
	}
}

void Grid()
{
	for (int i = 0; i < 3; i += 1)
	{
		glLineWidth(3.0f);
		glColor3f(1.0f, 0.6f, 1.0f);
		glBegin(GL_LINES);
		glVertex3i(-400, -120 - i*60, 0);
		glVertex3i(400, -120 - i * 60, 0);
		glEnd();
		for (int j = 0; j < 13; j += 1)
		{
			glLineWidth(3.0f);
			glColor3f(1.0f, 0.6f, 1.0f);
			glBegin(GL_LINES);
			glVertex3i(j * 60 - 400, -120, 0);
			glVertex3i(j * 60 - 400, -300, 0);
			glEnd();
		}
	}
}

void Squ()
{
	for (int i = 0; i < 2; i += 1)
	{
		if (sq[i].type == 0)
		{
			if (i == 0 )
			{
				glPushMatrix();
				{
					glTranslatef(sq[i].x, sq[i].y, 0);
					glRotatef(45, 0, 0, 1);
					glColor3f(0.8, 0.8, 0.8);
					glBegin(GL_POLYGON);
					{
						glVertex2i(30, -30);
						glVertex2i(-30, -30);
						glVertex2i(-30, 30);
						glVertex2i(30, 30);
					}
					glEnd();
				}
				glPopMatrix();
			}
			if (i == 1)
			{
				glPushMatrix();
				{
					glTranslatef(sq[i].x, sq[i].y, 0);
					glColor3f(0.8, 0.8, 0.8);
					glBegin(GL_POLYGON);
					{
						glVertex2i(30, -30);
						glVertex2i(-30, -30);
						glVertex2i(-30, 30);
						glVertex2i(30, 30);
					}
					glEnd();
				}
				glPopMatrix();
			}
		}
		sq[i].y += 2;
		if (sq[i].y > 500)
		{
			sq[i].type = 0;
			sq[i].y = -500;
		}
	}
}

void Move_Tri()
{
	for (int i = 0; i < 10; i += 1)
	{
		if (tri[i].select == false)
		{
			glPushMatrix();
			{
				glTranslatef(tri[i].x, tri[i].y, 0.0);
				glRotatef(tri[i].angle, 0.0, 0.0, 1.0);
				glColor3f(0.8, 0.8, 0.8);
				glBegin(GL_POLYGON);
				{
					glVertex2i(30, -30);
					glVertex2i( - 30, - 30);
					glVertex2i(0, 30);
				}
				glEnd();
			}
			glPopMatrix();
		}
		tri[i].x += 2;
		tri[i].angle += 2;
		if (tri[i].x - 20 > 400)
		{
			tri[i].x = -420;
			tri[i].angle = 0;
			tri[i].select = false;
		}
	}
}

void Draw_Upperline()
{
	glLineWidth(4.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3i(-400, 200,0);
	glVertex3i(400, 200,0);
	glEnd();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	}
}

void Mouse(int button, int state, int x, int y)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mx = x-400;
		my = -y+300;
		sx = x-400;
		sy = -y+300;
		left_button = TRUE;
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Slash();
		left_button = FALSE;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		rx = x - 400;
		ry = -y + 300;
		right_button = TRUE;
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		if (star_select == FALSE)
		{
			Make_Star();
		}
		if (tri_select == FALSE)
		{
			Merge_star();
		}
		for (int i = 0; i < 6; i += 1)
		{
			if (sli[i].status == 3)
			{
				sli[i].status = 2;
				sli[i].pro = 0;
			}
		}
		right_button = FALSE;
	}
}
void Motion(int x, int y)
{
	if (left_button == TRUE)
	{
		sx = x-400;
		sy = -y+300;
		mdown = TRUE;
	}
	else
	{
		mdown = FALSE;
	}

	if (right_button == TRUE)
	{
		rx = x - 400;
		ry = -y + 300;
		if (star_select == FALSE)
		{
			Pick_Up();
		}
		if (tri_select == FALSE)
		{
			Pick_star();
		}
		rdown = TRUE;
	}
	else
	{
		rdown = FALSE;
	}
}

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("저별내별");
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(timer, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i += 1)
	{
		tri[i].x = (i * 80)-400;
	}

	for (int i = 0; i < 2; i += 1)
	{
		sq[i].y = -(i * 500) - 350;
	}

	for (int i = 0; i < 3; i += 1)
	{
		for (int j = 0; j < 13; j += 1)
		{
			tr[j][i].x = j * 60+ 30-400;
			tr[j][i].y = -(i * 60)-30 - 120;
		}
	}
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Grid();
	
	Draw_Upperline();
	Move_Tri();
	SlashedTri();
	Draw_Trash();
	Squ();
	Draw_Pick();
	Draw_star();
	if(left_button == TRUE)
		Cutter();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400, 400, -300, 300, -1, 1);
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(timer, TimerFunction, 1);
}
