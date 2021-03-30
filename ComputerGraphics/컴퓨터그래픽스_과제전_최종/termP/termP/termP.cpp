
//은면제거, 컬링, 카메라 적용 됨


#include"pch.h"
#include"TextureManager.h"



#define WWIDTH 1600
#define WHEIGHT 800
#define DEPTH 400
#define LENGTH 200



GLvoid drawScene(GLvoid);
void TotalSetup();
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
//void doKeyboard(unsigned char keyPressed, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Keyboardup(unsigned char key, int x, int y);
void Keyboard2(unsigned char key, int x, int y);


void TotalSetup();



Camera<float3> m_Camera((float)WHEIGHT / (float)WWIDTH);

Camera<float3> m_Camera1((float)WHEIGHT / (float)WWIDTH);

Camera<float3> m_Camera2((float)WHEIGHT / (float)WWIDTH);

c_background background;
c_ship ship1;
c_ship ship2;
c_missile missile1;
c_missile missile2;
c_texture TXTR;
CSound sound;
c_weather weather;

c_ship* pTestShip = new c_ship[4];


c_light light;

c_ui ui1;
c_ui ui2;
c_scene scene;

int state;


// 플레이할 모델의 종류를 잠시 저장.
int tempModelType[2];
bool isReady[2];


int selectSceneDegree[2] { TYPE::model1 };
float selectSceneAutoRotation = 0;

void main(int argc, char *argv[]) {

	srand((unsigned)time(NULL));

	//tempModelType[0] = 0;
	//tempModelType[1] = 0;

	//state = ENUM_SCENE::SCENE_START;

	state = ENUM_SCENE::SCENE_START;

	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 	// 디스플레이 모드 설정
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 			// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);							// 윈도우의 위치지정 
	glutInitWindowSize(WWIDTH, WHEIGHT); 						// 윈도우의 크기 지정 
	glutCreateWindow("Example"); 								// 윈도우 생성 (윈도우 이름)

	//SetupRC();//초기화 함수

	glutDisplayFunc(drawScene); 								// 출력 함수의 지정 
	glutReshapeFunc(Reshape);									// 다시 그리기 함수의 지정 
	

	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(Keyboardup);
	glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);

	glutTimerFunc(100, TimerFunction, 1);




	TotalSetup();


	glutMainLoop();

}

float degreeX = 0;
float degreeY = 0;
float degreeZ = 0;


GLvoid drawScene(GLvoid)
{
	if (state == ENUM_SCENE::SCENE_SELECT)
	{
		if (ship1.m_CameraWheeled == true)
		{
			ship1.m_CameraWheeled = false;
			ship1.m_CameraAngle = 0;
			ship1.m_CameraUp = 0;
		}

		//은면제거

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		glEnable(GL_DEPTH_TEST | GL_CULL_FACE);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);      // 바탕색을 'blue' 로 지정 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      // 설정된 색으로 전체를 칠하기 

		//light.setLight();
		//light.setLight0();


		// ==================================== 1플레이어 선택 화면

		m_Camera.LookAtOrtho1();

		glScaled(2, 1, 2);
		//glScaled(1.7, 1.7, 1.7);
		glRotatef(ship1.leanAngle + 180, 0, 1, 0);
		glTranslatef(ship1.position[0], 0, ship1.position[2]);
		glPushMatrix();//=========================
		{
			glRotated(180, 0, 1, 0);//축이 돌아가서 돌렸음

			//glDisable(GL_LIGHTING);
			//glDisable(GL_LIGHT0);



			//glEnable(GL_LIGHTING);
			//glEnable(GL_LIGHT0);


			for (int i = 0; i < 4; ++i)
			{
				glPushMatrix();//=========================
				{
					glTranslatef(0, 0, 50);
					glRotated(selectSceneDegree[0], 0, 1, 0);	// 배 선택
					glPushMatrix();//=========================
					{
						glRotated(90 * i + 90, 0, 1, 0);
						glTranslatef(100, 0, 0);
						{
							glPushMatrix();//=========================
							{
								glRotated(selectSceneAutoRotation, 0, 1, 0);//자동회전
								{
									pTestShip[i].drawShip();
								}
							}
							glPopMatrix();//=========================
						}
					}
					glPopMatrix();//=========================

				}
				glPopMatrix();//=========================

			}

			if (isReady[0])
			{
				glPushMatrix();//=========================
				{
					glRotated(180, 0, 1, 0);//축이 돌아가서 돌렸음
					glTranslatef(0, -120, 0);
					scene.drawReady();
				}
				glPopMatrix();//=========================
			}

		}
		glPopMatrix();//=========================



		
		// ==================================== 2플레이어 화면

		m_Camera1.LookAtOrtho2();

		glScaled(2, 1, 2);
		//glScaled(1.7, 1.7, 1.7);
		glRotatef(ship2.leanAngle + 180, 0, 1, 0);
		glTranslatef(ship2.position[0], 0, ship2.position[2]);

		glPushMatrix();//=========================
		{
			glRotated(180, 0, 1, 0);//축이 돌아가서 돌렸음

			//glDisable(GL_LIGHTING);
			//glDisable(GL_LIGHT0);
			//glEnable(GL_LIGHTING);
			//glEnable(GL_LIGHT0);


			for (int i = 0; i < 4; ++i)
			{
				glPushMatrix();//=========================
				{
					glTranslatef(0, 0, 50);
					glRotated(selectSceneDegree[1], 0, 1, 0);	// 배 선택
					glPushMatrix();//=========================
					{
						glRotated(90 * i + 90, 0, 1, 0);//축이 돌아가서 돌렸음
						glTranslatef(100, 0, 0);
						{
							glPushMatrix();//=========================
							{
								glRotated(selectSceneAutoRotation, 0, 1, 0);// 자동회전
								{
									pTestShip[i].drawShip();
								}
							}
							glPopMatrix();//=========================
						}
					}
					glPopMatrix();//=========================

				}
				glPopMatrix();//=========================
			}

			if (isReady[1])
			{
				glPushMatrix();//=========================
				{
					glRotated(180, 0, 1, 0);//축이 돌아가서 돌렸음
					glTranslatef(0, -120, 0);
					scene.drawReady();
				}
				glPopMatrix();//=========================
			}


		}
		glPopMatrix();//=========================


									 // 화면에 출력하기

	//은면제거
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		//은면제거

	}
	else if (state == ENUM_SCENE::SCENE_START)
	{
		m_Camera.LookAtOrthoscene();
		auto temp = TextureInstance->EnableTextur(ENUM_TEXTURE::START_SCENE);

		scene.drawScene();

		TextureInstance->DisableTextur(ENUM_TEXTURE::START_SCENE, temp);

	}
	else if (state == ENUM_SCENE::SCENE_PLAYER1_WIN)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);


		if (ship1.m_CameraWheeled == false)
		{
			m_Camera.Rotate(ship1.m_CameraAngle, ship1.m_CameraUp);
			ship1.m_CameraWheeled = true;
			m_Camera.Rotate(0.f, 0.2f);
			m_Camera1.Rotate(0.f, 0.2f);
		}
		m_Camera.LookAtOrthoscene();
		
		auto temp = TextureInstance->EnableTextur(ENUM_TEXTURE::PLAYER1_WIN_SCENE);

		scene.drawScene();

		TextureInstance->DisableTextur(ENUM_TEXTURE::PLAYER1_WIN_SCENE, temp);

	}
	else if (state == ENUM_SCENE::SCENE_PLAYER2_WIN)
	{
		m_Camera.LookAtOrthoscene();
		auto temp = TextureInstance->EnableTextur(ENUM_TEXTURE::PLAYER2_WIN_SCENE);

		scene.drawScene();

		TextureInstance->DisableTextur(ENUM_TEXTURE::PLAYER2_WIN_SCENE, temp);

	}
	else if (state == ENUM_SCENE::SCENE_PLAYING)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);

		if (ship1.m_CameraWheeled == true)
		{
			ship1.m_CameraWheeled = false;
			ship1.m_CameraAngle = 0;
			ship1.m_CameraUp = 0;
		}

		//은면제거

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		glEnable(GL_DEPTH_TEST | GL_CULL_FACE);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);      // 바탕색을 'blue' 로 지정 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      // 설정된 색으로 전체를 칠하기 


		

		light.setLight();
		light.setLight0();


		// 1플레이어
		m_Camera.LookAtOrtho1();

		glScaled(2, 1, 2);
		glRotatef(ship1.leanAngle + 180, 0, 1, 0);
		glTranslatef(ship1.position[0], 0, ship1.position[2]);
		glPushMatrix();//=========================
		{
			glRotated(180, 0, 1, 0);//축이 돌아가서 돌렸음

			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			weather.DrawWeather();
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			background.drawSea();
			ship1.drawShip();
			ship2.drawShip();
			//ship2.drawShipUposit();
			missile1.drawMissile();
			missile2.drawMissile();
			missile1.ParticleDraw();
			missile2.ParticleDraw();
			//fill

			ship2.drawEnemyPosition(0.9, 0.9, 0.9, 0.1);
			ship1.drawAim(0.85, 0.55, 0.25, 0.7);
			ship2.drawAim(0.25, 0.85, 0.35, 0.25);

		}
		glPopMatrix();//=========================

		// 2플레이어
		m_Camera1.LookAtOrtho2();
		
		glScaled(2, 1, 2);
		//glScaled(1.7, 1.7, 1.7);
		glRotatef(ship2.leanAngle + 180, 0, 1, 0);
		glTranslatef(ship2.position[0], 0, ship2.position[2]);
		glPushMatrix();//=========================
		{
			glRotated(180, 0, 1, 0);//축이 돌아가서 돌렸음

			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			weather.DrawWeather();
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			background.drawSea();
			ship1.drawShip();
			ship2.drawShip();
			//ship2.drawShipUposit();
			missile1.drawMissile();
			missile2.drawMissile();
			missile1.ParticleDraw();
			missile2.ParticleDraw();


			ship1.drawAim(0.85, 0.55, 0.25, 0.3);
			ship1.drawEnemyPosition(0.9, 0.9, 0.9, 0.1);
			ship2.drawAim(0.25, 0.85, 0.35, 0.7);
		}
		glPopMatrix();//=========================


		m_Camera.LookAtOrthoMinimap();
		glScaled(1, 0.5, 0.5);
		glPushMatrix();//=========================
		{
			//축이 돌아가서 돌렸음
			glTranslatef(100, 0, 0);
			glRotated(90, 1.0, 0, 0);
			glTranslatef(0, -150, 0);
			background.drawSea();
			ship1.drawShip();
			ship2.drawShip();
			missile1.drawMissile();
			missile2.drawMissile();

			//fill
			ship1.drawAim(0.85, 0.55, 0.25, 1);
			ship2.drawAim(0.25, 0.85, 0.35, 1);
			ship1.drawEnemyPosition(1, 0, 0, 1);
			ship2.drawEnemyPosition(0, 1, 0, 1);

		}
		glPopMatrix();//=========================

		m_Camera.LookAtOrtho1pUI();
		glScaled(2.5, 2, 2);
		glPushMatrix();//=========================
		{

			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHTING);
			//축이 돌아가서 돌렸음
			ui1.drawGear();
			//fill

			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHTING);

		}
		glPopMatrix();//=========================

		m_Camera.LookAtOrtho2pUI();
		glScaled(2.5, 2, 2);
		glPushMatrix();//=========================
		{
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			//축이 돌아가서 돌렸음
			ui2.drawGear();
			//fill

			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHTING);
		}
		glPopMatrix();//=========================

		m_Camera.LookAtOrtho2p_2UI();
		glScaled(2.5, 2, 2);
		glPushMatrix();//=========================
		{
			//축이 돌아가서 돌렸음

			//축이 돌아가서 돌렸음
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			glPushMatrix();
			{
				glTranslatef(0, 0, 300);
				glRotatef(180, 0, 1, 0);
				glColor3f(ship2.hp / 100, 0.0f, 0.3f);
				//glutSolidCube(ship2.hp * 4);
				glBegin(GL_QUADS);
				{	
					glVertex3f(250, -250, 0);
					glVertex3f(-250, -250, 0);
					glVertex3f(-250, ship2.hp*5-250, 0);
					glVertex3f(250, ship2.hp*5-250, 0);
				}
				glEnd();
			}
			glPopMatrix();
			glColor3f(0.0f, 0.f, 0.f);
			glutSolidCube(500);
			//glBegin(GL_QUADS);
			//{
			//	glVertex3f(-100 * 4 - 50, -100, 0);
			//	glVertex3f(-100 * 4 - 50, 100, 0);
			//	glVertex3f(100 * 4 + 50, 100, 0);
			//	glVertex3f(100 * 4 + 50, -100, 0);
			//}
			//glEnd();
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHTING);
			//fill
			//fill


		}
		glPopMatrix();//=========================

		m_Camera.LookAtOrtho2p_3UI();
		glScaled(2.5, 2, 2);
		glPushMatrix();//=========================
		{
			//축이 돌아가서 돌렸음
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			glPushMatrix();
			{
				glTranslatef(0, 0, 300);
				glColor3f(1.0f, 0.3f, 0.3f);
				glRotatef(180, 0, 1, 0);
				glBegin(GL_QUADS);
				{
					glVertex3f(250, -250, 0);
					glVertex3f(-250, -250, 0);
					glVertex3f(-250, missile2.reload * 10 - 250, 0);
					glVertex3f(250, missile2.reload * 10 - 250, 0);
				}
				glEnd();
			}
			glPopMatrix();
			glColor3f(0.0f, 0.f, 0.f);
			glutSolidCube(500);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHTING);
			//fill


		}
		glPopMatrix();//=========================


		m_Camera.LookAtOrtho1p_2UI();
		glScaled(2.5, 2, 2);
		glPushMatrix();//=========================
		{
			//축이 돌아가서 돌렸음
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			glPushMatrix();
			{
				glTranslatef(0, 0, 300);

				glRotatef(180, 0, 1, 0);
				glColor3f(ship1.hp/100, 0.0f, 0.3f);
				glBegin(GL_QUADS);
				{
					glVertex3f(250, -250, 0);
					glVertex3f(-250, -250, 0);
					glVertex3f(-250, ship1.hp * 5 - 250, 0);
					glVertex3f(250, ship1.hp * 5 - 250, 0);
				}
				glEnd();
			}
			glPopMatrix();
			glColor3f(0.0f, 0.f, 0.f);
			glutSolidCube(500);
			//glBegin(GL_QUADS);
			//{
			//	glVertex3f(-100 * 4 - 50, -100, 0);
			//	glVertex3f(-100 * 4 - 50, 100, 0);
			//	glVertex3f(100 * 4 + 50, 100, 0);
			//	glVertex3f(100 * 4 + 50, -100, 0);
			//}
			//glEnd();
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHTING);
			//fill


		}
		glPopMatrix();//=========================

		m_Camera.LookAtOrtho1p_3UI();
		glScaled(2.5, 2, 2);
		glPushMatrix();//=========================
		{
			//축이 돌아가서 돌렸음
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			glPushMatrix();
			{
				glTranslatef(0, 0, 300);
				glColor3f(1.0f, 0.3f, 0.3f);
				glRotatef(180, 0, 1, 0);
				glBegin(GL_QUADS);
				{
					glVertex3f(250, -250, 0);
					glVertex3f(-250, -250, 0);
					glVertex3f(-250, missile1.reload * 10 - 250, 0);
					glVertex3f(250, missile1.reload * 10 - 250, 0);
				}
				glEnd();
			}
			glPopMatrix();
			glColor3f(0.0f, 0.f, 0.f);
			glutSolidCube(500);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHTING);

			//fill


		}
		glPopMatrix();//=========================


									 // 화면에 출력하기

	//은면제거
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		//은면제거
	}

	glutSwapBuffers(); 
}



GLvoid Reshape(int w, int h)
{
	glutPostRedisplay();
}


void TimerFunction(int value)
{
	if (state == ENUM_SCENE::SCENE_PLAYING)
	{
		weather.update();
		background.seaUpdate();
		ship1.update();
		ship2.update();
		missile1.update();
		missile2.update();
		for (int i = 0; i < 50; ++i)
			for (int j = 0; j < 50; ++j)
			{
				background.waterSplash[i][j] -= 7.0f;
				if (background.waterSplash[i][j] <= 1.0f)
					background.waterSplash[i][j] = 1.0f;
			}
	}

	else if(state == ENUM_SCENE::SCENE_SELECT)
	{
		selectSceneAutoRotation += 0.1;
	}
	//m_Camera.Rotate(0,0.1);
	
	if (ship1.hp <= 0)
	{
		state = ENUM_SCENE::SCENE_PLAYER2_WIN;
	}

	else if (ship2.hp <= 0)
	{
		state = ENUM_SCENE::SCENE_PLAYER1_WIN;
	}

	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(50, TimerFunction, 1);
}


void Keyboard_1(unsigned char keyPressed, int x, int y)
{
	switch (keyPressed)
	{
	case 'x':
		m_Camera.Rotate(0.f, 0.1f);
		break;
	case 'X':
		m_Camera.Rotate(0.f, -0.1f);
		break;
	case 'y':
		m_Camera.Rotate(0.1f, 0.f);
		break;
	case 'Y':
		m_Camera.Rotate(-0.1f, 0.f);
		break;
	case 'z':
		m_Camera.zoom(0.9f);
		break;
	case 'Z':
		m_Camera.zoom(1.1f);
		break;
	case '+':
		break;
	case '-':
		sound.Play(1);
		break;
	}
	ship1.keybard1(keyPressed);

}


// 키보드 down
void Keyboard(unsigned char key, int x, int y)
{
	if (state == ENUM_SCENE::SCENE_PLAYING)
	{
		ship1.keybard1(key);
		ship2.keybard2(key);
	}
	else if(state == ENUM_SCENE::SCENE_SELECT)
	{
		//for (int i = 0; i < 4; ++i)
		//	pTestShip[i].keybardInSelect1(key);
		if (!isReady[0])
		{
			std::cout << "키보드 : ";
			switch (key)
			{
			case 'a':
				ship1.a = true;
				std::cout << "a 눌림" << std::endl;
				selectSceneDegree[0] += 90;

				if (selectSceneDegree[0] % 90 < 0)
					selectSceneDegree[0] = 0;

				tempModelType[0]--;
				if (tempModelType[0] < TYPE::model1)
					tempModelType[0] = TYPE::model4;
				break;
			case 'd':
				ship1.d = true;
				std::cout << "d 눌림" << std::endl;
				selectSceneDegree[0] -= 90;
				if (selectSceneDegree[0] % 90 < 0)
					selectSceneDegree[0] = 0;
				std::cout << "degree : " << selectSceneDegree << std::endl;
				tempModelType[0]++;
				if (tempModelType[0] > TYPE::model4)
					tempModelType[0] = TYPE::model1;

				break;
			case 'g':
				//ship1.g = true;
				isReady[0] = true;
				std::cout << "1Player is Ready" << std::endl;
				if (isReady[0] && isReady[1])
				{
					state = ENUM_SCENE::SCENE_PLAYING;
					ship1.init(750, 100, 750, tempModelType[0], 1);
					ship2.init(-750, 100, -750, tempModelType[1], 2);
					//delete[] pTestShip;
				}
				break;
			default:
				break;
			}
			std::cout << "model Type : " << tempModelType[0] << std::endl;
		}


		if (!isReady[1])
		{

			std::cout << "키보드 : ";
			switch (key)
			{
			case '4':
				ship1.four = true;
				std::cout << "4 눌림" << std::endl;
				selectSceneDegree[1] += 90;
				if (selectSceneDegree[1] % 90 < 0)
					selectSceneDegree[1] = 0;
				tempModelType[1]--;
				if (tempModelType[1] < TYPE::model1)
					tempModelType[1] = TYPE::model4;
				break;
			case '6':
				ship1.six = true;
				std::cout << "6 눌림" << std::endl;
				selectSceneDegree[1] -= 90;
				if (selectSceneDegree[1] % 90 < 0)
					selectSceneDegree[1] = 0;
				tempModelType[1]++;
				if (tempModelType[1] > TYPE::model4)
					tempModelType[1] = TYPE::model1;

				break;
			case 'l':
				//ship1.g = true;
				std::cout << "2Player is Ready" << std::endl;
				isReady[1] = true;
				if (isReady[0] && isReady[1])
				{
					state = ENUM_SCENE::SCENE_PLAYING;
					ship1.init(750, 0, 750, tempModelType[0], 1);
					ship2.init(-750, 0, -750, tempModelType[1], 2);
					delete[] pTestShip;
				}
				break;
			default:
				break;
			}

		}

	}

	switch (key)
	{
	case '1':
		weather.state = 0;
		break;
	case '2':
		weather.state = 1;
		break;
	case '3':
		weather.state = 2;
		break;
	case '0':
		light.ambientLignt[0] = { 1.0 };
		light.ambientLignt[1] = { 1.0 };
		light.ambientLignt[2] = { 1.0 };
		light.DiffuseLight0[0] = { 1.0 };
		light.DiffuseLight0[2] = { 1.0 };
		break;
	case '-':
		light.ambientLignt[0] = { 0.0 };
		light.ambientLignt[1] = { 0.4 };
		light.ambientLignt[2] = { 0.4 };
		light.DiffuseLight0[0] = { 0.0 };
		light.DiffuseLight0[2] = { 0.0 };
		break;
	default:
		if (state == ENUM_SCENE::SCENE_START) {
			state = ENUM_SCENE::SCENE_SELECT;
			for (int i = 0; i < 4; i++)
				pTestShip[i].init(0, 0, 0, i, 0);
			
			//pTestShip[0].init(0, 0, 0, TYPE::model1);
			//pTestShip[1].init(0, 0, 0, TYPE::model2);
			//pTestShip[2].init(0, 0, 0, TYPE::model3);
			//pTestShip[3].init(0, 0, 0, TYPE::model4);

		}
		else if (state == ENUM_SCENE::SCENE_SELECT) {
			//ship1.init(750, 100, 750);
			//ship2.init(-750, 100, -750);
 		//	state = ENUM_SCENE::SCENE_PLAYING; 
		
		}
		else if (state == ENUM_SCENE::SCENE_PLAYER1_WIN || state == ENUM_SCENE::SCENE_PLAYER2_WIN) {
			state = ENUM_SCENE::SCENE_START;
			TotalSetup();
		}
		break;
	}

}

// 키보드 up
void Keyboardup(unsigned char key, int x, int y)
{
	if (state == ENUM_SCENE::SCENE_PLAYING)
	{
		ship1.keybard1up(key);
		ship2.keybard2up(key);
	}
	else if (state == ENUM_SCENE::SCENE_SELECT)
	{
		switch (key)
		{
		case 'a':
			ship1.a = false;
			std::cout << "a 뗌" << std::endl;
			break;
		case 'd':
			ship1.d = false;
			std::cout << "d 뗌" << std::endl;
			break;
		}

		switch (key)
		{
		case '4':
			ship1.four = false;
			std::cout << "4 뗌" << std::endl;
			break;
		case '6':
			ship1.six = false;
			std::cout << "6 뗌" << std::endl;
			break;
		}
	}
}

void Keyboard2(unsigned char key, int x, int y)
{
	switch (key)
	{


	case 'x':
		m_Camera.Rotate(0.f, 0.1f);
		break;
	case 'X':
		m_Camera.Rotate(0.f, -0.1f);
		break;
	case 'y':
		m_Camera.Rotate(0.1f, 0.f);
		break;
	case 'Y':
		m_Camera.Rotate(-0.1f, 0.f);
		break;
	case 'z':
		m_Camera.zoom(0.9f);
		break;
	case 'Z':
		m_Camera.zoom(1.1f);
		break;
	case '+':
		break;
	case '-':
		sound.Play(1);
		break;
	}
	ship2.keybard2(key);
}


void Mouse(int button, int state, int x, int y)
{
	float mouseX = WWIDTH / 2 - x;
	float mouseY = -(y - WHEIGHT / 2);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}


}

void Motion(int x, int y)
{
	float mouseX = WWIDTH / 2 - x;
	float mouseY = -(y - WHEIGHT / 2);

}


void TotalSetup()
{
	//카메라
	m_Camera.Initialize(float3{ 0,0,0 }, 300, 1, 1000, 120);
	m_Camera1.Initialize(float3{ 0,0,0 }, 300, 1, 1000, 120);

	m_Camera.Rotate(0.f, -0.2f);
	m_Camera1.Rotate(0.f, -0.2f);

	sound.Play(0);
	sound.Play(1);

	background.init();
	weather.state = rand() % 3;
	weather.init();

	ship1.hp = 100;
	ship2.hp = 100;
	ship1.Camera = &m_Camera;
	ship2.Camera = &m_Camera1;
	missile1.sound = &sound;
	missile2.sound = &sound;
	ship1.backGround = &background;
	ship2.backGround = &background;
	ship1.missile = &missile1;
	ship2.missile = &missile2;
	ship1.enemyship = &ship2;
	ship2.enemyship = &ship1;
	missile1.ship = &ship1;
	missile2.ship = &ship2;
	missile1.enemyship = &ship2;
	missile2.enemyship = &ship1;
	missile1.backGround = &background;
	missile2.backGround = &background;
	//ship1.p_Texture = &TXTR;
	//ship1.init1();

	//ship1.init(0,0,0, TYPE::model1);
	//ship2.init(0,0,0, TYPE::model1);

	ui1.ship = &ship1;
	ui2.ship = &ship2;
}
