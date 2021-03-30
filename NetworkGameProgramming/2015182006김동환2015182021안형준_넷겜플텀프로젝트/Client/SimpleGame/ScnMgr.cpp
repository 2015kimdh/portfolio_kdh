#include "stdafx.h"
#include "ScnMgr.h"
#include "Dependencies\freeglut.h"


//int g_testTexture;

ScnMgr::ScnMgr()
{
	// Initialize Renderer
	m_Renderer = new Renderer(1000, 1000);

	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < HEIGHT; ++j)
		{
			if (i == 0 || i == WIDTH - 1 || j == 0 || j == HEIGHT - 1)
			{
				map[i][j] = IRON_TILE;
			}
		}
	}

	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	ReadTexture();

	Hero = new Player();
}


ScnMgr::~ScnMgr()
{
}

void ScnMgr::ReadTexture()
{

	Player1_Texture[0] = m_Renderer->GenPngTexture("./Texture/1pplayer.png");
	Player1_Texture[1] = m_Renderer->GenPngTexture("./Texture/1pplayer_1.png");
	Player2_Texture[0] = m_Renderer->GenPngTexture("./Texture/2pplayer.png");
	Player2_Texture[1] = m_Renderer->GenPngTexture("./Texture/2pplayer_1.png");

	Map_Texture[0] = m_Renderer->GenPngTexture("./Texture/stone.png");
	Map_Texture[1] = m_Renderer->GenPngTexture("./Texture/wood.png");
	Map_Texture[2] = m_Renderer->GenPngTexture("./Texture/empty.png");
	Map_Texture[3] = m_Renderer->GenPngTexture("./Texture/speedup.png");
	Map_Texture[4] = m_Renderer->GenPngTexture("./Texture/onemorebomb.png");
	Map_Texture[5] = m_Renderer->GenPngTexture("./Texture/bombpower.png");
	Map_Texture[6] = m_Renderer->GenPngTexture("./Texture/bomb.png");
	Map_Texture[7] = m_Renderer->GenPngTexture("./Texture/bombtrail.png");

	WinScene_Texture[0] = m_Renderer->GenPngTexture("./Texture/1pwin.png");
	WinScene_Texture[1] = m_Renderer->GenPngTexture("./Texture/2pwin.png");
}

void ScnMgr::WoodRender(int i, int j)
{
	m_Renderer->DrawTextureRect(MAPSIZE / 2 - WINDOWSIZE / 2 + i * MAPSIZE, MAPSIZE / 2 - WINDOWSIZE / 2 + j * MAPSIZE, 0, MAPSIZE, MAPSIZE, 1, 1, 1, 1, 1, Map_Texture[1]);
}

void ScnMgr::IronRender(int i, int j)
{
	m_Renderer->DrawTextureRect(MAPSIZE / 2 - WINDOWSIZE / 2 + i * MAPSIZE, MAPSIZE / 2 - WINDOWSIZE / 2 + j * MAPSIZE, 0, MAPSIZE, MAPSIZE, 1, 1, 1, 1, 1, Map_Texture[0]);
}

void ScnMgr::BombRender(int i, int j)
{
	m_Renderer->DrawTextureRect(MAPSIZE / 2 - WINDOWSIZE / 2 + i * MAPSIZE, MAPSIZE / 2 - WINDOWSIZE / 2 + j * MAPSIZE, 0, MAPSIZE, -MAPSIZE, 1, 1, 1, 1, 1, Map_Texture[6]);
}

void ScnMgr::EmptyRender(int i, int j)
{
	m_Renderer->DrawTextureRect(MAPSIZE / 2 - WINDOWSIZE / 2 + i * MAPSIZE, MAPSIZE / 2 - WINDOWSIZE / 2 + j * MAPSIZE, 0, MAPSIZE, MAPSIZE, 1, 1, 1, 1, 1, Map_Texture[2]);
}

void ScnMgr::OnemorebombRender(int i, int j)
{
	m_Renderer->DrawTextureRect(MAPSIZE / 2 - WINDOWSIZE / 2 + i * MAPSIZE, MAPSIZE / 2 - WINDOWSIZE / 2 + j * MAPSIZE, 0, MAPSIZE, -MAPSIZE, 1, 1, 1, 1, 1, Map_Texture[4]);
}

void ScnMgr::SpeedUpRender(int i, int j)
{
	m_Renderer->DrawTextureRect(MAPSIZE / 2 - WINDOWSIZE / 2 + i * MAPSIZE, MAPSIZE / 2 - WINDOWSIZE / 2 + j * MAPSIZE, 0, MAPSIZE, -MAPSIZE, 1, 1, 1, 1, 1, Map_Texture[3]);
}

void ScnMgr::FireRender(int i, int j)
{
	m_Renderer->DrawTextureRect(MAPSIZE / 2 - WINDOWSIZE / 2 + i * MAPSIZE, MAPSIZE / 2 - WINDOWSIZE / 2 + j * MAPSIZE, 0, MAPSIZE, MAPSIZE, 1, 1, 1, 1, 1, Map_Texture[7]);
}

void ScnMgr::PowerUpRender(int i, int j)
{
	m_Renderer->DrawTextureRect(MAPSIZE / 2 - WINDOWSIZE / 2 + i * MAPSIZE, MAPSIZE / 2 - WINDOWSIZE / 2 + j * MAPSIZE, 0, MAPSIZE, -MAPSIZE, 1, 1, 1, 1, 1, Map_Texture[5]);
}


void ScnMgr::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < HEIGHT; ++j)
		{
			if (map[i][j] == EMPTY_TILE)
			{
				EmptyRender(i, j);
			}
			else if (map[i][j] == WOOD_TILE)
			{
				WoodRender(i, j);

			}
			else if (map[i][j] == IRON_TILE)
			{
				IronRender(i, j);
			}
			else if (map[i][j] == BOMB_TILE)
			{
				EmptyRender(i, j);
				BombRender(i, j);
			}
			else if (map[i][j] == FIRE_TILE)
			{
				FireRender(i, j);
			}
			else if (map[i][j] == BOMB_UP_TILE)
			{
				EmptyRender(i, j);
				OnemorebombRender(i, j);
			}
			else if (map[i][j] == RANGE_UP_TILE)
			{
				EmptyRender(i, j);
				PowerUpRender(i, j);
			}
			else if (map[i][j] == SPEED_UP_TILE)
			{
				EmptyRender(i, j);
				SpeedUpRender(i, j);
			}
		}
	}

	if (inputTexture <= 10)
	{
		m_Renderer->DrawTextureRect(player1_xpos, player1_ypos, 1, 30, 30, 30, 1, 1, 1, 1, Player1_Texture[0]);
		m_Renderer->DrawTextureRect(player2_xpos, player2_ypos, 1, 30, 30, 30, 1, 1, 1, 1, Player2_Texture[0]);
		inputTexture += 1;
	}
	else {
			m_Renderer->DrawTextureRect(player1_xpos, player1_ypos, 1, 30, 30, 30, 1, 1, 1, 1, Player1_Texture[1]);
			m_Renderer->DrawTextureRect(player2_xpos, player2_ypos, 1, 30, 30, 30, 1, 1, 1, 1, Player2_Texture[1]);
			if (inputTexture == 20)
			{
				inputTexture = 0;
			}
			inputTexture += 1;
		}

	if (Player1_Alive != true || Player2_Alive != true)
	{
		if (Player1_Alive != true)
			m_Renderer->DrawTextureRect(0, 0, 2, WINDOWSIZE, -WINDOWSIZE, 1, 1, 1, 1, 1, WinScene_Texture[0]);
		else
			m_Renderer->DrawTextureRect(0, 0, 2, WINDOWSIZE, -WINDOWSIZE, 1, 1, 1, 1, 1, WinScene_Texture[1]);
	}

}

void ScnMgr::KeyDownInputHero(int key, int x, int y)
{
	Hero->KeyDownInput(key, x, y);
}

void ScnMgr::KeyUpInputHero(int key, int x, int y)
{
	Hero->KeyUpInput(key, x, y);
}

void ScnMgr::KeyInfoGathering(char *key)
{
	if (Hero->key_up)
	{
		key[UP] = on;
	}
	if (Hero->key_down)
	{
		key[DOWN] = on;
	}
	if (Hero->key_left)
	{
		key[LEFT] = on;
	}
	if (Hero->key_right)
	{
		key[RIGHT] = on;
	}

	if (Hero->key_shift)
	{
		key[SHIFT] = on;
	}
}

void ScnMgr::err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void ScnMgr::err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}



void ScnMgr::Update(float elapsedTime)
{

	KeyInfoGathering(KeyInfo);
	
	memcpy(buffer, KeyInfo, sizeof(KeyInfo));

	for (int i = 0; i < KEY_AMOUNT; ++i)
	{
		KeyInfo[i] = off;
	}
	// 보낸다

	if (Player1_Alive != true || Player2_Alive != true)
	{
		for (int i = 0; i < KEY_AMOUNT; ++i)
		{

		
			if (buffer[i] == on)
			{
				glutDestroyWindow(glutGetWindow());
				
			}
		}

	}
	else {

		retval = send(sock, (char *)&buffer, sizeof(buffer), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
		}

		// 받을 파일의 이름을 서버에게 보냄

		ZeroMemory(&buffer, sizeof(buffer));

		// 받는다
		retval = recv(sock, (char *)&recv_map, sizeof(recv_map), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
		}
		else if (retval == 0);

		retval = recv(sock, (char *)&player_pos, sizeof(player_pos), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
		}
		else if (retval == 0);

		for (int i = 1; i < WIDTH - 1; ++i)
		{
			for (int j = 1; j < HEIGHT - 1; ++j)
			{
				map[i][j] = recv_map[i - 1][j - 1];
			}
		}

		player1_xpos = player_pos[0];
		player1_ypos = player_pos[1];
		player2_xpos = player_pos[2];
		player2_ypos = player_pos[3];

		Player1_Alive = (bool)player_pos[4];
		Player2_Alive = (bool)player_pos[5];	//float 형으로 넘어오는 값을 받기 위해 형변환
	}
}