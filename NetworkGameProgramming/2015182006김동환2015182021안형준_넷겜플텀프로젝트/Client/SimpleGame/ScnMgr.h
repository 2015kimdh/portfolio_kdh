#pragma once
#include "Globals.h"
#include "Renderer.h"
#include "Object.h"


#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "Player.h"


class ScnMgr
{
public:
	ScnMgr();
	~ScnMgr();

	void ReadTexture();

	void WoodRender(int i, int j);
	void IronRender(int i, int j);
	void BombRender(int i, int j);
	void EmptyRender(int i, int j);
	void OnemorebombRender(int i, int j);
	void SpeedUpRender(int i, int j);
	void FireRender(int i, int j);
	void PowerUpRender(int i, int j);


	void RenderScene();

	void Update(float elpasedTimeInSecond);


	void KeyDownInputHero(int key, int x, int y);
	void KeyUpInputHero(int key, int x, int y);


	void KeyInfoGathering(char *key);
	void err_quit(char *msg);

	// 소켓 함수 오류 출력
	void err_display(char *msg);


	SOCKET sock;
	SOCKADDR_IN serveraddr;

	float player1_xpos, player1_ypos;
	float player2_xpos, player2_ypos;


	char recv_map[18][18];
	char map[20][20];

	float player_pos[6];

private:
	Renderer * m_Renderer = NULL;

	Player *Hero = NULL;

	int retval;
	char buffer[BUFSIZE];
	int recvbuffer[INTBUFSIZE];

	char KeyInfo[5];

	bool m_KeyW = false;
	bool m_KeyS = false;
	bool m_KeyA = false;
	bool m_KeyD = false;

	bool m_KeyUp = false;
	bool m_KeyDown = false;
	bool m_KeyLeft = false;
	bool m_KeyRight = false;
	enum
	{
		off = 0,
		on
	};

	int inputTexture;
	int Player1_Texture[2];
	int Player2_Texture[2];

	int WinScene_Texture[2];
	int Map_Texture[8];

	bool Player1_Alive = true;
	bool Player2_Alive = true;
	
};

