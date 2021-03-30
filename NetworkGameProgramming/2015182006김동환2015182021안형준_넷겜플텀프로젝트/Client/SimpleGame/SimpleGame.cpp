/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/


#pragma comment(lib, "ws2_32")

#include "stdafx.h"
#include <iostream>


#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>


#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "ScnMgr.h"





using namespace std;

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define NAMECHECK	4




ScnMgr* g_ScnMgr = NULL;
int g_prevTimeInMillisecond = 0;
//int g_testTexture;


void err_quit(char *msg)
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

void err_display(char *msg)
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



void RenderScene(int temp)
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int elapsedTime = currentTime - g_prevTimeInMillisecond;

	g_prevTimeInMillisecond = currentTime;
	//std::cout << "elapsed time: " << elapsedTime << std::endl;

	g_ScnMgr->Update((float)elapsedTime / 1000.f /* 초로 바꿔서 넣어줄 것 */);
	g_ScnMgr->RenderScene();

	glutSwapBuffers();
	glutTimerFunc(16, RenderScene, 16);
}

void Idle(void)
{
	//RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	//RenderScene();
}


void KeyDownInputHero(int key, int x, int y)
{
	g_ScnMgr->KeyDownInputHero(key, x, y);
}

void KeyUpInputHero(int key, int x, int y)
{
	g_ScnMgr->KeyUpInputHero(key, x, y);
}



int main(int argc, char **argv)
{

	int retval;
	char IPbuf[BUFSIZE];

	cout << "서버 IP 입력 : ";
	cin >> IPbuf;	// 연결할 IP 입력


	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(IPbuf);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");





	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Game Software Engineering KPU");


	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize ScnMgr


	g_ScnMgr = new ScnMgr();
	g_ScnMgr->sock = sock;
	g_ScnMgr->serveraddr = serveraddr;

	glutDisplayFunc(Idle);
	glutIdleFunc(Idle);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(KeyDownInputHero);
	glutSpecialUpFunc(KeyUpInputHero);
	//glutSpecialFunc(SpecialKeyDownInput);
	//glutSpecialUpFunc(SpecialKeyUpInput);


	//glutKeyboardFunc(KeyDownInputHero);
	//glutKeyboardUpFunc(KeyUpInputHero);

	g_prevTimeInMillisecond = glutGet(GLUT_ELAPSED_TIME);

	glutTimerFunc(16, RenderScene, 16);

	glutMainLoop();


	return 0;
}
