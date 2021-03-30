#include <windows.h>
#include<stdio.h>
#include<string>
#include<time.h>
#include<math.h>
#include"resource.h"
#include <fmod.h>
#include "fmod.hpp"
#include "fmod_errors.h"


#define BS 10
#define BS2 15
#define H 800
#define W 1200
#define MAPCO 112
#define MAPBK 113
#define CHCO  103
#define CHBK  114
#define MOCO  105
#define MOBK  106
#define GRBK  116
#define GRCO  115
#define BOBK  118
#define BOCO  117
#define BKBK  121
#define BKCO  120
#define BK  119
#define MENUCO 122
#define BACKCO 123
struct Hero {
	int x;
	double y;
	char air;
	char jump;
	char jt;
	char exist;
	char life;
	char shot;
	char scene;
	char command; // 1 - 오른쪽 2 - 왼쪽
	char granade = 0;
	float angle;
	char side;
	int sx;
	int sy;
	char no = 0;
	char set = 0;
};
struct Land {
	int x;
	double y;
};

struct Granade {
	int x;
	double y;
	int angle;
	float speed;
	char status;
	char exist;
	int sx;
	int sy;
	char up = 0;
	char air = 0;
	char set = 0;
};

struct Hbullet {
	float x;
	float y;
	float angle;
	char exist;
	int sx;
	int sy;
};

struct Ebullet {
	int x;
	double y;
	float angle;
	char exist;
	int sx;
	int sy;
};

struct Enemy {
	int x;
	double y;
	char air;
	char jump;
	char jt;
	char exist;
	char shot;
	char scene;
	char timmer;
	float angle;
	char command;
	char side;
	int sx;
	int sy;
	char no;
	char set = 0;
};

Land land[11000];
Hero ch[1];
Enemy em[20];
Granade gr[6];
Hbullet cb[20];
Ebullet eb[50];


BOOL START = FALSE;
BOOL QUIT = FALSE;
FMOD_SYSTEM* soundSystem;
FMOD_SOUND* soundSYSTEM[5];
FMOD_CHANNEL* soundCHANNEL[5];
void soundsetup();
void playsound(int i);
void soundoff();


float LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}

BOOL InCircle(int x, int y, int lx, int ly, int r)
{
	if (LengthPts(x, y, lx, ly) < r)
		return TRUE;
	else
		return FALSE;
}

HINSTANCE g_hInst;
LPCTSTR lpszClass = "Window Class Name";
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow
	(lpszClass, "Uganda",
		WS_OVERLAPPED | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		0, 0, W, H,
		NULL, LoadMenu(g_hInst, MAKEINTRESOURCE(101)),
		hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

void CALLBACK TimerProc(HWND hwnd, UINT iMessage, WPARAM idEvent, DWORD dwTime);
int emcounter = 0;
int emkind = 0;
int emspot = 5;
int granade = 100;
int cameramove = 0;
int cax = 1200;
int cay = 800;
char gunangle = 0;
int f = 10;
int bkx = 0;
int bkcox = 0;
int emx = 0;
int emy = 0;
int victory = 0;

int mx, my;

HDC hdc;
HDC chdc, memdc, chdc2, modc, modc2, mapdc2, grdc, grdc2, bodc, bodc2, bkdc, bkcodc, bkbkdc; HDC mapdc,menudc,backdc;
HBITMAP mapco, mapbk, chco, chbk, moco, mobk, mem, grco, grbk, boco, bobk, bk, bkco, bkbk,menuco,backco;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	

	switch (iMessage)
	{
	case WM_CREATE:

		soundsetup();
		playsound(3);
		FMOD_Channel_SetVolume(soundCHANNEL[3], 0.7);

		SetTimer(hwnd, 1, 10, TimerProc);
		ch[0].x = 100;
		ch[0].y = 400;
		ch[0].air = 1;
		ch[0].jump = 0;
		ch[0].jt = 0;
		ch[0].exist = 1;
		ch[0].life = 10;
		ch[0].shot = 0;
		ch[0].scene = 0;
		ch[0].command = 0;
		ch[0].angle = 0;
		ch[0].side = 0;
		ch[0].sx = 0;
		ch[0].sy = 0;
		for (int i = 0; i < 650; i++)
		{
			land[i].x = i;
			land[i].y = 430;
		}
		for (int i = 0; i < 200; i++)
		{
			land[i+650].x = i+650;
			land[i+650].y = 430 - (i/2);
		}
		for (int i = 850; i < 1500; i++)
		{
			land[i].x = i;
			land[i].y = 330;
		}
		land[1500].x = 1500;
		land[1500].y = 430;
		for (int i = 0; i < 400; i++)
		{
			land[i+1501].x = i+1501;
			land[i+1501].y = 430 + i/4;
		}
		land[1900].x = 1900;
		land[1900].y = 530;
		for (int i = 0; i < 2000; i++)
		{
			land[i+1901].x = i+1901;
			land[i + 1901].y = 430;
		}
		for (int i = 0; i < 1600; i++)
		{
			land[i+3901].x = i+3901;
			land[i + 3901].y = 380;
		}
		for (int i = 4700; i < 4900; i++)
		{
			land[i].x = i;
			land[i].y = 280;
		}
		for (int i = 0; i < 1000; i++)
		{
			land[i+5501].x = i+5501;
			land[i + 5501].y = 440 + i/10;
		}
		for (int i = 6500; i < 7400; i++)
		{
			land[i].x = i;
			land[i].y = 540;
		}
		for (int i = 7400; i < 9500; i++)
		{
			land[i].x = i;
			land[i].y = 440;
		}
		for (int i = 9500; i < 11000; i++)
		{
			land[i].x = i;
			land[i].y = 540;
		}
		for (int i = 9900; i < 10300; i++)
		{
			land[i].x = i;
			land[i].y = 430;
		}
		for (int i = 10000; i < 10200; i++)
		{
			land[i].x = i;
			land[i].y = 330;
		}

		mapbk = LoadBitmap(g_hInst, MAKEINTRESOURCE(MAPBK));
		mapco = LoadBitmap(g_hInst, MAKEINTRESOURCE(MAPCO));
		menuco = LoadBitmap(g_hInst, MAKEINTRESOURCE(MENUCO));
		backco = LoadBitmap(g_hInst, MAKEINTRESOURCE(BACKCO));
		mobk = LoadBitmap(g_hInst, MAKEINTRESOURCE(MOBK));
		moco = LoadBitmap(g_hInst, MAKEINTRESOURCE(MOCO));
		chco = LoadBitmap(g_hInst, MAKEINTRESOURCE(CHCO));
		chbk = LoadBitmap(g_hInst, MAKEINTRESOURCE(CHBK));
		grco = LoadBitmap(g_hInst, MAKEINTRESOURCE(GRCO));
		grbk = LoadBitmap(g_hInst, MAKEINTRESOURCE(GRBK));
		boco = LoadBitmap(g_hInst, MAKEINTRESOURCE(BOCO));
		bobk = LoadBitmap(g_hInst, MAKEINTRESOURCE(BOBK));
		bkco = LoadBitmap(g_hInst, MAKEINTRESOURCE(BKCO));
		bkbk = LoadBitmap(g_hInst, MAKEINTRESOURCE(BKBK));
		bk = LoadBitmap(g_hInst, MAKEINTRESOURCE(BK));


		for (int i = 0; i < 20; i++)
		{
			em[i].x = 0;
			em[i].y = 0;
			em[i].air = 0;
			em[i].jump = 0;
			em[i].jt = 0;
			em[i].exist = 0;
			em[i].shot = 0;
			em[i].scene = 0;
			em[i].timmer = 10;
			em[i].command = 0;
			em[i].angle = 0;
			em[i].side = 0;
			em[i].sx = 0;
			em[i].sy = 0;
		}
		for (int i = 0; i < 20; i++)
		{
			cb[i].angle = 0;
			cb[i].exist = 0;
			cb[i].x = 0;
			cb[i].y = 0;
			cb[i].sx = 0;
			cb[i].sy = 0;
		}
		for (int i = 0; i < 50; i++)
		{
			eb[i].angle = 0;
			eb[i].exist = 0;
			eb[i].x = 0;
			eb[i].y = 0;
			eb[i].sx = 0;
			eb[i].sy = 0;
		}
		for (int i = 0; i < 6; i++)
		{
			gr[i].angle = 0;
			gr[i].exist = 0;
			gr[i].status = 0;
			gr[i].x = 0;
			gr[i].y = 0;
			gr[i].sx = 0;
			gr[i].sy = 0;
		}

		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;

	case WM_CHAR:
		if (wParam == 'x')
		{
			ch[0].granade = 1;
		}
		if (wParam == 'z')
		{
			if (ch[0].jump == 0)
			{
				ch[0].jump = 1;
			}
		}
		if (wParam == 'c')
		{
			if (ch[0].shot == 0)
			{
				ch[0].shot = 1;
				playsound(1);
			}
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RIGHT)
		{
			if (ch[0].exist == 1)
			{
				if (ch[0].command == !1)
				{
					ch[0].command = 1;
					ch[0].side = 0;
					ch[0].scene = 0;
					ch[0].angle = 0;
				}
			}
		}
		else if (wParam == VK_LEFT)
		{
			if (ch[0].exist == 1)
			{
				if (ch[0].command == !2)
				{
					ch[0].command = 2;
					ch[0].side = 1;
					ch[0].scene = 0;
					ch[0].angle = 3.1415f;
				}
			}
		}
		if (wParam == VK_UP)
		{
			if (gunangle != 1)
			{
				gunangle = 1;
				if (ch[0].side == 0)
				{
					ch[0].angle = 0;
				}
				else if (ch[0].side == 1)
				{
					ch[0].angle = 3.1415f;
				}
			}
			gunangle = 1;
		}
		else if (wParam == VK_DOWN)
		{
			if (gunangle != 2)
			{
				gunangle = 2;
				if (ch[0].side == 0)
				{
					ch[0].angle = 3.1415f*2;
				}
				else if (ch[0].side == 1)
				{
					ch[0].angle = 3.1415f;
				}
			}
			gunangle = 2;
		}

		break;
	case WM_KEYUP:
		if (wParam == VK_RIGHT)
		{
			if (ch[0].exist == 1)
			{
				ch[0].command = 0;
				ch[0].scene = 0;
			}
		}
		else if (wParam == VK_LEFT)
		{
			if (ch[0].exist == 1)
			{
				ch[0].command = 0;
				ch[0].scene = 0;
			}
		}
		if (wParam == VK_UP)
		{
			gunangle = 3;
		}
		else if (wParam == VK_DOWN)
		{
			gunangle = 3;
		}
		InvalidateRect(hwnd, NULL, false);
		break;

	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (mx >= 730 && mx <= 1130 && my >= 120 && my <= 220 && START == FALSE) {
			playsound(0);
			FMOD_Channel_Stop(soundCHANNEL[3]);
			START = TRUE;
		}
		if (mx >= 730 && mx <= 1130 && my >= 240 && my <= 340 && QUIT == FALSE)
			QUIT = TRUE;

		break;


	case WM_DESTROY:
		for (int i = 0; i < 5; i++)
			FMOD_Sound_Release(soundSYSTEM[i]);
		FMOD_System_Close(soundSystem);
		FMOD_System_Release(soundSystem);

		DeleteObject(chco);
		DeleteObject(chbk);
		DeleteObject(mem); DeleteObject(memdc);
		DeleteObject(mapco);
		DeleteObject(menuco);
		DeleteObject(backco);
		DeleteObject(mapbk);
		DeleteObject(moco);
		DeleteObject(mobk);
		DeleteObject(chdc);
		DeleteObject(chdc2);
		DeleteObject(mapdc);
		DeleteObject(mapdc2);
		DeleteObject(modc);
		DeleteObject(modc2);
		DeleteObject(grdc);
		DeleteObject(grdc2);
		DeleteObject(bodc);
		DeleteObject(bodc2);
		DeleteObject(grco);
		DeleteObject(grbk);
		DeleteObject(boco);
		DeleteObject(bobk);
		DeleteObject(bkbk);
		DeleteObject(bkco);
		DeleteObject(bk);
		DeleteObject(bkbkdc);
		DeleteObject(bkdc);
		DeleteObject(bkcodc);
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMessage, wParam, lParam));
}


void CALLBACK TimerProc(HWND hwnd, UINT iMessage, WPARAM idEvent, DWORD dwTime)
{
	hdc = GetDC(hwnd);
	
	memdc = CreateCompatibleDC(hdc);
	mem = CreateCompatibleBitmap(hdc, 1200, 800);
	SelectObject(memdc, mem);
	Rectangle(memdc, 0, 0, 1200, 800);
	chdc = CreateCompatibleDC(memdc);
	chdc2 = CreateCompatibleDC(memdc);
	mapdc = CreateCompatibleDC(memdc);
	menudc = CreateCompatibleDC(memdc);
	backdc = CreateCompatibleDC(memdc);
	mapdc2 = CreateCompatibleDC(memdc);
	modc = CreateCompatibleDC(memdc);
	modc2 = CreateCompatibleDC(memdc);
	grdc = CreateCompatibleDC(memdc);
	grdc2 = CreateCompatibleDC(memdc);
	bodc = CreateCompatibleDC(memdc);
	bodc2 = CreateCompatibleDC(memdc);
	bkbkdc = CreateCompatibleDC(memdc);
	bkdc = CreateCompatibleDC(memdc);
	bkcodc = CreateCompatibleDC(memdc);

	SelectObject(chdc, chco);
	SelectObject(chdc2, chbk);
	SelectObject(grdc, grco);
	SelectObject(grdc2, grbk);
	SelectObject(mapdc, mapco);
	SelectObject(menudc, menuco);
	SelectObject(backdc, backco);

	SelectObject(bkdc, bk);
	SelectObject(bkbkdc, bkbk);
	SelectObject(bkcodc, bkco);

	SelectObject(bodc, boco);
	SelectObject(bodc2, bobk);
	SelectObject(mapdc2, mapbk);
	SelectObject(modc, moco);
	SelectObject(modc2, mobk);


	if(START==TRUE)
	{
	if (gunangle == 1)
	{
		if (ch[0].side == 0)
		{
	
			if (ch[0].angle < 3.1415f/2 - 0.5 && ch[0].angle >= 0)
			{
				ch[0].angle += 3.1415f/12;
			}
		}
		else if (ch[0].side == 1)
		{
			if (ch[0].angle > 3.1415f/2 + 0.5 && ch[0].angle <= 3.1415f)
			{
				ch[0].angle -= 3.1415f / 12;
			}
		}
	}
	else if (gunangle == 2)
	{
		if (ch[0].side == 0)
		{
			if (ch[0].angle <= 2*3.1415f && ch[0].angle > 3*3.1415f/2 + 0.5)
			{
				ch[0].angle -= 3.1415f / 12;
			}
		}
		else if (ch[0].side == 1)
		{
			if (ch[0].angle >= 3.1415f/2 && ch[0].angle < 3 * 3.1415f / 2 - 0.5)
			{
				ch[0].angle += 3.1415f / 12;
			}
		}
	}
	else if (gunangle == 3)
	{
		if (ch[0].side == 0)
		{
			if (ch[0].angle > 0  && ch[0].angle <= 3.1415f/2)
			{
				ch[0].angle -= 3.1415f/12;
			}
			else if (ch[0].angle >= 3*3.1415f/2 && ch[0].angle < 2*3.1415f)
			{
				ch[0].angle += 3.1415f / 12;
			}
		}
		else if (ch[0].side == 1)
		{
			if (ch[0].angle < 3.1415f && ch[0].angle >= 3.1415f / 2)
			{
				ch[0].angle += 3.1415f / 12;
			}
			else if (ch[0].angle > 3.1415f && ch[0].angle <= 3*3.1415f/2 )
			{
				ch[0].angle -= 3.1415f / 12;
			}
		}
	}
	if (ch[0].command == 0)
	{
		if (ch[0].exist == 1)
		{
			if (ch[0].shot == 1)
			{
				ch[0].sx = 20;
				ch[0].sy = 145;
				ch[0].scene = 0;
			}
			else if (ch[0].granade == 0)
			{
				if (ch[0].scene == 0)
				{
					ch[0].sx = 10;
					ch[0].sy = 0;
				}
			}
			else if (ch[0].granade == 1)
			{
				if (ch[0].scene == 0)
				{
					ch[0].sx = 15;
					ch[0].sy = 272;
					ch[0].scene = 1;
				}
				else if (ch[0].scene == 1)
				{
					ch[0].sx = 20;
					ch[0].sy = 410;
					ch[0].scene = 0;
					ch[0].granade = 0;
				}
			}
		}
		else if (ch[0].exist == 2)
		{
			if (ch[0].scene == 0)
			{
				ch[0].sx = 20;
				ch[0].sy = 545;
				ch[0].set += 1;
				if (ch[0].set == 7)
				{
					ch[0].set = 0;
					ch[0].scene = 1;
				}
			}
			else if (ch[0].scene == 1)
			{
				ch[0].sx = 135;
				ch[0].sy = 545;
				ch[0].set += 1;
				if (ch[0].set == 7)
				{
					ch[0].set = 0;
					ch[0].scene = 2;
				}
			}
			else if (ch[0].scene == 2)
			{
				ch[0].sx = 258;
				ch[0].sy = 545;
				ch[0].set += 1;
				if (ch[0].set == 7)
				{
					ch[0].set = 0;
					ch[0].scene = 3;
				}
			}
			else if (ch[0].scene == 3)
			{
				ch[0].sx = 383;
				ch[0].sy = 545;
				ch[0].set += 1;
				if (ch[0].set == 7)
				{

					if (ch[0].life > 0)
					{
						ch[0].set = 0;
						ch[0].life -= 1;
						ch[0].exist = 1;
						ch[0].scene = 0;
						ch[0].y -= 150;
					}
				}
			}
		}
	}
	else if (ch[0].command == 1)
	{
			if (ch[0].scene == 0)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 22;
					ch[0].sy = 145;
					ch[0].scene = 1;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 15;
					ch[0].sy = 270;
					ch[0].scene = 1;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 15;
					ch[0].sy = 405;
					ch[0].scene = 1;
					ch[0].granade = 0;
				}
				else if(ch[0].granade == 0)
				{
					ch[0].sx = 10;
					ch[0].sy = 0;
					ch[0].scene = 1;
				}
			}
			else if (ch[0].scene == 1)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 135;
					ch[0].sy = 145;
					ch[0].scene = 2;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 135;
					ch[0].sy = 270;
					ch[0].scene = 2;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 135;
					ch[0].sy = 405;
					ch[0].scene = 2;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 125;
					ch[0].sy = 0;
					ch[0].scene = 2;
				}
			}
			else if (ch[0].scene == 2)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 255;
					ch[0].sy = 145;
					ch[0].scene = 3;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 255;
					ch[0].sy = 270;
					ch[0].scene = 3;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 255;
					ch[0].sy = 405;
					ch[0].scene = 3;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 250;
					ch[0].sy = 0;
					ch[0].scene = 3;
				}
			}
			else if (ch[0].scene == 3)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 370;
					ch[0].sy = 145;
					ch[0].scene = 4;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 368;
					ch[0].sy = 270;
					ch[0].scene = 4;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 365;
					ch[0].sy = 405;
					ch[0].scene = 4;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 360;
					ch[0].sy = 0;
					ch[0].scene = 4;
				}
			}
			else if (ch[0].scene == 4)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 480;
					ch[0].sy = 145;
					ch[0].scene = 5;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 480;
					ch[0].sy = 270;
					ch[0].scene = 5;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 480;
					ch[0].sy = 405;
					ch[0].scene = 5;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 470;
					ch[0].sy = 0;
					ch[0].scene = 5;
				}
			}
			else if (ch[0].scene == 5)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 370;
					ch[0].sy = 145;
					ch[0].scene = 6;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 368;
					ch[0].sy = 270;
					ch[0].scene = 6;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 365;
					ch[0].sy = 405;
					ch[0].scene = 6;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 360;
					ch[0].sy = 0;
					ch[0].scene = 6;
				}
			}
			else if (ch[0].scene == 6)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 255;
					ch[0].sy = 145;
					ch[0].scene = 0;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 255;
					ch[0].sy = 270;
					ch[0].scene = 0;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 255;
					ch[0].sy = 405;
					ch[0].scene = 0;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 250;
					ch[0].sy = 0;
					ch[0].scene = 0;
				}
			}

	}
	else if (ch[0].command == 2)
	{
		if (ch[0].scene == 0)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 22;
					ch[0].sy = 145;
					ch[0].scene = 1;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 15;
					ch[0].sy = 270;
					ch[0].scene = 1;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 15;
					ch[0].sy = 405;
					ch[0].scene = 1;
					ch[0].granade = 0;
				}
				else if(ch[0].granade == 0)
				{
					ch[0].sx = 10;
					ch[0].sy = 0;
					ch[0].scene = 1;
				}
			}
			else if (ch[0].scene == 1)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 135;
					ch[0].sy = 145;
					ch[0].scene = 2;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 135;
					ch[0].sy = 270;
					ch[0].scene = 2;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 135;
					ch[0].sy = 405;
					ch[0].scene = 2;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 125;
					ch[0].sy = 0;
					ch[0].scene = 2;
				}
			}
			else if (ch[0].scene == 2)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 255;
					ch[0].sy = 145;
					ch[0].scene = 3;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 255;
					ch[0].sy = 270;
					ch[0].scene = 3;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 255;
					ch[0].sy = 405;
					ch[0].scene = 3;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 250;
					ch[0].sy = 0;
					ch[0].scene = 3;
				}
			}
			else if (ch[0].scene == 3)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 370;
					ch[0].sy = 145;
					ch[0].scene = 4;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 368;
					ch[0].sy = 270;
					ch[0].scene = 4;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 365;
					ch[0].sy = 405;
					ch[0].scene = 4;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 360;
					ch[0].sy = 0;
					ch[0].scene = 4;
				}
			}
			else if (ch[0].scene == 4)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 480;
					ch[0].sy = 145;
					ch[0].scene = 5;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 480;
					ch[0].sy = 270;
					ch[0].scene = 5;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 480;
					ch[0].sy = 405;
					ch[0].scene = 5;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 470;
					ch[0].sy = 0;
					ch[0].scene = 5;
				}
			}
			else if (ch[0].scene == 5)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 370;
					ch[0].sy = 145;
					ch[0].scene = 6;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 368;
					ch[0].sy = 270;
					ch[0].scene = 6;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 365;
					ch[0].sy = 405;
					ch[0].scene = 6;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 360;
					ch[0].sy = 0;
					ch[0].scene = 6;
				}
			}
			else if (ch[0].scene == 6)
			{
				if (ch[0].shot == 1)
				{
					ch[0].sx = 255;
					ch[0].sy = 145;
					ch[0].scene = 0;
				}
				else if (ch[0].granade == 1)
				{
					ch[0].sx = 255;
					ch[0].sy = 270;
					ch[0].scene = 0;
					ch[0].granade = 2;
				}
				else if (ch[0].granade == 2)
				{
					ch[0].sx = 255;
					ch[0].sy = 405;
					ch[0].scene = 0;
					ch[0].granade = 0;
				}
				else if (ch[0].granade == 0)
				{
					ch[0].sx = 250;
					ch[0].sy = 0;
					ch[0].scene = 0;
				}
			}
	}
	
	if (ch[0].jump > 0)
	{
		ch[0].jump += 1;
		ch[0].y -= 5;
		if (ch[0].jump == 25)
		{
			ch[0].jump = 0;
			ch[0].air = 1;
		}
	}

	if (ch[0].x >= 500 && emspot == 5)
	{
		emspot -= 1;
		emcounter = 10;
		emkind = 0;
		for (int i = 0; i < 20; i++)
		{
			if (em[i].exist == 0)
			{
				em[i].x = 500 + rand()%1500;
				em[i].y = 200;
				em[i].exist = 1;
				em[i].jt = emkind;
					em[i].timmer = 6000;
				em[i].command = 1;
				em[i].side = 1;
				em[i].air = 1;
				em[i].jump = 0;
				em[i].no = 0;
				emcounter -= 1;
				em[i].scene = 0;
				if (emcounter == 0)
				{
					break;
				}
			}
		}
	}
	if (ch[0].x >= 2500 && emspot == 4)
	{
		emspot -= 1;
		emcounter = 20;
		emkind = 0;
		for (int i = 0; i < 20; i++)
		{
			if (em[i].exist == 0)
			{
				em[i].x = 3000 + rand() % 1500;
				em[i].y = 200;
				em[i].exist = 1;
				em[i].jt = emkind;
				em[i].timmer = 6000;
				em[i].command = 1;
				em[i].side = 1;
				em[i].air = 1;
				em[i].jump = 0;
				em[i].no = 0;
				emcounter -= 1;
				em[i].scene = 0;
				if (emcounter == 0)
				{
					break;
				}
			}
		}
	}
	if (ch[0].x >= 3500 && emspot == 3)
	{
		emspot -= 1;
		emcounter = 10;
		emkind = 0;
		for (int i = 0; i < 20; i++)
		{
			if (em[i].exist == 0)
			{
				em[i].x = 4500 + rand() % 1500;
				em[i].y = 200;
				em[i].exist = 1;
				em[i].jt = emkind;
				em[i].timmer = 6000;
				em[i].command = 1;
				em[i].side = 1;
				em[i].air = 1;
				em[i].jump = 0;
				em[i].no = 0;
				emcounter -= 1;
				em[i].scene = 0;
				if (emcounter == 0)
				{
					break;
				}
			}
		}
	}
	if (ch[0].x >= 6000 && emspot == 2)
	{
		emspot -= 1;
		emcounter = 30;
		emkind = 0;
		for (int i = 0; i < 20; i++)
		{
			if (em[i].exist == 0)
			{
				em[i].x = 7000 + rand() % 1500;
				em[i].y = 200;
				em[i].exist = 1;
				em[i].jt = emkind;
				em[i].timmer = 6000;
				em[i].command = 1;
				em[i].side = 1;
				em[i].air = 1;
				em[i].jump = 0;
				em[i].no = 0;
				emcounter -= 1;
				em[i].scene = 0;
				if (emcounter == 0)
				{
					break;
				}
			}
		}
	}
	if (ch[0].x >= 8000 && emspot == 1)
	{
		emspot -= 1;
		emcounter = 40;
		emkind = 0;
		for (int i = 0; i < 20; i++)
		{
			if (em[i].exist == 0)
			{
				em[i].x = 9000 + rand() % 1500;
				em[i].y = 200;
				em[i].exist = 1;
				em[i].jt = emkind;
				em[i].timmer = 6000;
				em[i].command = 1;
				em[i].side = 1;
				em[i].air = 1;
				em[i].jump = 0;
				em[i].no = 0;
				emcounter -= 1;
				em[i].scene = 0;
				if (emcounter == 0)
				{
					break;
				}
			}
		}
	}
	if (ch[0].x >= 10000 && emspot == 0)
	{
		if (emcounter == 0)
		{
			emcounter = 40;
		}
		emkind = 0;
		for (int i = 0; i < 20; i++)
		{
			if (em[i].exist == 0)
			{
				em[i].x = 10500 + rand() % 1500;
				em[i].y = 200;
				em[i].exist = 1;
				em[i].jt = emkind;
				em[i].timmer = 6000;
				em[i].command = 1;
				em[i].side = 1;
				em[i].air = 1;
				em[i].jump = 0;
				em[i].no = 0;
				emcounter -= 1;
				em[i].scene = 0;
				if (emcounter == 0)
				{
					emspot -= 1;
					break;
				}
			}
		}
	}


	for (int i = 0; i < 20; i++)
	{
		if (em[i].exist == 1)
		{
			if (em[i].x - ch[0].x <= 0)
			{
				em[i].command = 1;
				em[i].side = 1;
			}
			else if(em[i].x - ch[0].x > 0)
			{
				em[i].command = 2;
				em[i].side = 0;
			}
			if (em[i].jt == 0)
			{
				if (ch[0].exist == 1)
				{
					if (em[i].exist == 1)
					{
						if (InCircle(em[i].x, em[i].y, ch[0].x, ch[0].y, 500) == TRUE)
						{
							em[i].shot = 1;
							em[i].command = 0;
							em[i].timmer -= 1;
							if (em[i].shot == 0)
								em[i].scene = 0;
						}
						else
						{
							em[i].shot = 0;

						}
					}
				}
				else
				{
					em[i].shot = 0;

				}
			}
			
			if (em[i].command == 1)
			{
				if (em[i].y <= land[em[i].x].y)
				{
					if (land[em[i].x].y - em[i].y < 10)
					{
						if (em[i].jump == 0)
						{
							em[i].y = land[em[i].x].y;
							em[i].no = 0;
						}
					}
					else if (land[em[i].x].y - em[i].y > 10)
					{
						if (em[i].jump == 0)
						{
							em[i].air = 1;
						}
						em[i].no = 0;
					}
					if (em[i].air == 1)
					{
						em[i].y += 7;
						if (em[i].y >= land[em[i].x].y)
						{
							em[i].y = land[em[i].x].y;
							em[i].air = 0;
						}
						em[i].no = 0;
					}
				}
				else if (em[i].y >= land[em[i].x].y)
				{
					if (em[i].y - land[em[i].x].y < 10)
					{
						if (em[i].jump == 0)
						{
							em[i].y = land[em[i].x].y;
						}
						em[i].no = 0;
					}
					else if (em[i].y - land[em[i].x].y > 10)
					{
						em[i].no = 1;
					}
				}
			}
			if (em[i].command == 1)
			{
				if (em[i].x < 11000)
				{
					if (em[i].no == 0)
						em[i].x += 3;
				}
			}
			if (em[i].command == 2)
		{
			if (em[i].y <= land[em[i].x].y)
			{
				if (land[em[i].x].y - em[i].y < 10)
				{
					if (em[i].jump == 0)
					{
						em[i].y = land[em[i].x].y;
						em[i].no = 0;
					}
				}
				else if (land[em[i].x].y - em[i].y > 10)
				{
					if (em[i].jump == 0)
					{
						em[i].air = 1;
					}
					em[i].no = 0;
				}
				if (em[i].air == 1)
				{
					em[i].y += 10;
					if (em[i].y >= land[em[i].x].y)
					{
						em[i].y = land[em[i].x].y;
						em[i].air = 0;
					}
					em[i].no = 0;
				}
			}
			else if (em[i].y >= land[em[i].x].y)
			{
				if (em[i].y - land[em[i].x].y < 10)
				{
					if (em[i].jump == 0)
					{
						em[i].y = land[em[i].x].y;
					}
					em[i].no = 0;
				}
				else if (em[i].y - land[em[i].x].y > 10)
				{
					em[i].no = 1;
				}
			}
			if (em[i].command == 2)
			{
				if (em[i].x > 10)
				{
					if (em[i].no == 0)
						em[i].x -= 3;

				}
			}
			
		}


		}
		if (em[i].command == 0)
		{
			if (em[i].y <= land[em[i].x].y)
			{
				if (land[em[i].x].y - em[i].y < 10)
				{
					if (em[i].jump == 0)
					{
						em[i].y = land[em[i].x].y;
						em[i].no = 0;
					}
				}
				else if (land[em[i].x].y - em[i].y > 10)
				{
					if (em[i].jump == 0)
					{
						em[i].air = 1;
					}
					em[i].no = 0;
				}
				if (em[i].air == 1)
				{
					em[i].y += 10;
					if (em[i].y >= land[em[i].x].y)
					{
						em[i].y = land[em[i].x].y;
						em[i].air = 0;
					}
					em[i].no = 0;
				}
			}
			else if (em[i].y >= land[em[i].x].y)
			{
				if (em[i].y - land[em[i].x].y < 10)
				{
					if (em[i].jump == 0)
					{
						em[i].y = land[em[i].x].y;
					}
					em[i].no = 0;
				}
				else if (em[i].y - land[em[i].x].y > 10)
				{
					em[i].no = 1;
				}
			}
		}
	}
	
	
	for (int i = 0; i < 20; i++)
	{
		if (em[i].exist == 1)
		{
			if (em[i].command == 0 && em[i].timmer > 0 && em[i].shot == 1 && em[i].jt == 0)
			{
				if (em[i].scene == 0)
				{
					em[i].set += 1;
					em[i].sx = 445;
					em[i].sy = 0;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 1;
					}
				}
				else if (em[i].scene == 1)
				{
					em[i].set += 1;
					em[i].sx = 480;
					em[i].sy = 0;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 2;
					}
				}
				else if (em[i].scene == 2)
				{
					em[i].set += 1;
					em[i].sx = 549;
					em[i].sy = 0;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 3;
					}
				}
				else if (em[i].scene == 3)
				{
					em[i].set += 1;
					em[i].sx = 620;
					em[i].sy = 0;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 4;
					}
				}
				else if (em[i].scene == 4)
				{
					em[i].set += 1;
					em[i].sx = 690;
					em[i].sy = 0;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 5;
					}
				}
				else if (em[i].scene == 5)
				{
					em[i].set += 1;
					em[i].sx = 788;
					em[i].sy = 0;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 6;
					}
				}
				else if (em[i].scene == 6)
				{
					em[i].set += 1;
					em[i].sx = 690;
					em[i].sy = 0;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 0;
					}
				}
				if (em[i].timmer == 1)
				{
					em[i].scene = 0;
				}
			}
			else if (em[i].command == 0 && em[i].timmer <= 0 && em[i].shot == 1 && em[i].jt == 0 && em[i].exist == 1)
			{
				if (em[i].scene == 0)
				{
					em[i].set += 1;
					em[i].sx = 260;
					em[i].sy = 52;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 1;
					}
				}
				else if (em[i].scene == 1)
				{
					em[i].set += 1;
					em[i].sx = 296;
					em[i].sy = 52;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 2;
					}
				}
				else if (em[i].scene == 2)
				{
					em[i].set += 1;
					em[i].sx = 332;
					em[i].sy = 52;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 3;
					}
				}
				else if (em[i].scene == 3)
				{
					em[i].set += 1;
					em[i].sx = 370;
					em[i].sy = 52;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 4;
					}
				}
				else if (em[i].scene == 4)
				{
					em[i].set += 1;
					em[i].sx = 408;
					em[i].sy = 52;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 5;
					}
				}
				else if (em[i].scene == 5)
				{
					em[i].set += 1;
					em[i].sx = 457;
					em[i].sy = 45;
					for (int j = 0; j < 50; j++)
					{
						if (eb[j].exist == 0)
						{
							emx = ch[0].x - em[i].x;
							emy =  em[i].y- ch[0].y ;
							eb[j].angle = atan2f((float)emy, (float)emx);
							if (em[i].side == 0)
							{
								eb[j].x = em[i].x + 70;
							}
							else if (em[j].side == 1)
							{
								eb[j].x = em[i].x;
							}
							eb[j].y = em[i].y - 30;
							eb[j].exist = 1;
							break;
						}
					}
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 6;
					}
				}
				else if (em[i].scene == 6)
				{
					em[i].set += 1;
					em[i].sx = 522;
					em[i].sy = 45;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 7;
					}
				}
				else if (em[i].scene == 7)
				{
					em[i].set += 1;
					em[i].sx = 588;
					em[i].sy = 45;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].scene = 8;
					}
				}
				else if (em[i].scene == 8)
				{
					em[i].set += 1;
					em[i].sx = 657;
					em[i].sy = 45;
					if (em[i].set == 7)
					{
						em[i].set = 0;
						em[i].shot = 0;
						em[i].timmer = 9000;
						em[i].scene = 0;
					}
				}
			}
		}
	}

	
	for (int i = 0; i < 20; i++)
	{
		if (em[i].exist == 1)
		{
			if ((em[i].command == 1 || em[i].command == 2) && em[i].jt == 0)
			{
				if (em[i].scene == 0)
				{
					em[i].set += 1;
					em[i].sx = 32;
					em[i].sy = 0;
					if (em[i].set == 6)
					{
						em[i].set = 0;
						em[i].scene = 1;
					}
				}
				else if (em[i].scene == 1)
				{
					em[i].set += 1;
					em[i].sx = 68;
					em[i].sy = 0;
					if (em[i].set == 6)
					{
						em[i].set = 0;
						em[i].scene = 2;
					}
				}
				else if (em[i].scene == 2)
				{
					em[i].set += 1;
					em[i].sx = 100;
					em[i].sy = 0;
					if (em[i].set == 6)
					{
						em[i].set = 0;
						em[i].scene = 3;
					}
				}
				else if (em[i].scene == 3)
				{
					em[i].set += 1;
					em[i].sx = 132;
					em[i].sy = 0;
					if (em[i].set == 6)
					{
						em[i].set = 0;
						em[i].scene = 4;
					}
				}
				else if (em[i].scene == 4)
				{
					em[i].set += 1;
					em[i].sx = 200;
					em[i].sy = 0;
					if (em[i].set == 6)
					{
						em[i].set = 0;
						em[i].scene = 5;
					}
				}
				else if (em[i].scene == 5)
				{
					em[i].set += 1;
					em[i].sx = 230;
					em[i].sy = 0;
					if (em[i].set == 6)
					{
						em[i].set = 0;
						em[i].scene = 6;
					}
				}
				else if (em[i].scene == 6)
				{
					em[i].set += 1;
					em[i].sx = 294;
					em[i].sy = 0;
					if (em[i].set == 6)
					{
						em[i].set = 0;
						em[i].scene = 7;
					}
				}
				else if (em[i].scene == 7)
				{
					em[i].set += 1;
					em[i].sx = 330;
					em[i].sy = 0;
					if (em[i].set == 6)
					{
						em[i].set = 0;
						em[i].scene = 8;
					}
				}
				else if (em[i].scene == 8)
				{
					em[i].set += 1;
					em[i].sx = 366;
					em[i].sy = 0;
					if (em[i].set == 6)
					{
						em[i].set = 0;
						em[i].scene = 0;
					}
				}

			}
		}
	}
	for (int i = 0; i < 20; i++)
	{
		if (em[i].no == 1)
			em[i].jump = 1;
		if (em[i].jump > 0)
		{
			em[i].jump += 1;
			em[i].y -= 7;
			if (em[i].jump == 15)
			{
				em[i].jump = 0;
				em[i].air = 1;
			}
		}
	}

	
	// 움직임 알고리즘
	if (ch[0].exist == 1)
	{
		if (ch[0].command == 1)
		{
			if (ch[0].y <= land[ch[0].x + 1].y)
			{
				if (land[ch[0].x + 1].y - ch[0].y < 10)
				{
					if (ch[0].jump == 0)
					{
						ch[0].y = land[ch[0].x + 1].y;
						ch[0].no = 0;
					}
				}
				else if (land[ch[0].x + 1].y - ch[0].y > 10)
				{
					if (ch[0].jump == 0)
					{
						ch[0].air = 1;
					}
					ch[0].no = 0;
				}
				if (ch[0].air == 1)
				{
					ch[0].y += 7;
					if (ch[0].y >= land[ch[0].x + 1].y)
					{
						ch[0].y = land[ch[0].x + 1].y;
						ch[0].air = 0;
					}
					ch[0].no = 0;
				}
			}
			else if (ch[0].y >= land[ch[0].x + 1].y)
			{
				if (ch[0].y - land[ch[0].x + 1].y < 10)
				{
					if (ch[0].jump == 0)
					{
						ch[0].y = land[ch[0].x + 1].y;
					}
					ch[0].no = 0;
				}
				else if (ch[0].y - land[ch[0].x + 1].y > 10)
				{
					ch[0].no = 1;
				}
			}
		}
		else if (ch[0].command == 2)
		{
			if (ch[0].y <= land[ch[0].x - 1].y)
			{
				if (land[ch[0].x - 1].y - ch[0].y < 10)
				{
					if (ch[0].jump == 0)
					{
						ch[0].y = land[ch[0].x - 1].y;
						ch[0].no = 0;
					}
				}
				else if (land[ch[0].x - 1].y - ch[0].y > 10)
				{
					if (ch[0].jump == 0)
					{
						ch[0].air = 1;
					}
					ch[0].no = 0;
				}
				if (ch[0].air == 1)
				{
					ch[0].y += 10;
					if (ch[0].y >= land[ch[0].x - 1].y)
					{
						ch[0].y = land[ch[0].x - 1].y;
						ch[0].air = 0;
					}
					ch[0].no = 0;
				}
			}
			else if (ch[0].y >= land[ch[0].x - 1].y)
			{
				if (ch[0].y - land[ch[0].x - 1].y < 10)
				{
					if (ch[0].jump == 0)
					{
						ch[0].y = land[ch[0].x - 1].y;
					}
					ch[0].no = 0;
				}
				else if (ch[0].y - land[ch[0].x - 1].y > 10)
				{
					ch[0].no = 1;
				}
			}
		}
		else if (ch[0].command == 0)
		{
			if (ch[0].air == 1)
			{
				ch[0].y += 10;
				if (ch[0].y >= land[ch[0].x - 1].y)
				{
					ch[0].y = land[ch[0].x - 1].y;
					ch[0].air = 0;
				}
				ch[0].no = 0;
			}
		}
	

	if (ch[0].granade == 2 || ch[0].granade == 1)
	{
		for (int i = 0; i < 6; i++)
		{
			if (gr[i].exist == 0 && granade > 0)
			{
				granade -= 1;
				gr[i].exist = 1;
				gr[i].x = ch[0].x;
				gr[i].y = ch[0].y - 30;
				gr[i].status = 0;
				gr[i].up = 1;

				if (ch[0].side == 0 && ch[0].command == 0)
				{
					gr[i].angle = 3.1415f / 4;
					gr[i].speed = 5;
				}
				else if (ch[0].side == 1 && ch[0].command == 0)
				{
					gr[i].angle = 3*3.1415f / 4;
					gr[i].speed = -5;
				}
				else if (ch[0].command == 1)
				{
					gr[i].angle = 3.1415f / 3;
					gr[i].speed = 10;
				}
				else if (ch[0].command == 2)
				{
					gr[i].angle = 5*3.1415f / 3;
					gr[i].speed = -10;
				}
				break;
			}
		}
	}
	if (ch[0].shot == 1)
	{
		for (int i = 0; i < 20; i++)
		{
			if (cb[i].exist == 0)
			{
				cb[i].angle = ch[0].angle;
				cb[i].y = ch[0].y - 30;
				if (ch[0].side == 0)
				{
					cb[i].x = ch[0].x + 70;
				}
				else if (ch[0].side == 1)
				{
					cb[i].x = ch[0].x;
				}
				cb[i].exist = 1;
				ch[0].shot = 0;
				break;
			}
			
		}
	}
}
	//움직임

	if (ch[0].command == 1)
	{
		if (ch[0].x < 10900)
		{
			if(ch[0].no == 0)
			ch[0].x += 5;
		}
	}
	else if (ch[0].command == 2)
	{
		if (ch[0].x > 10)
		{
			if(ch[0].no == 0)
			ch[0].x -= 5;

		}
	}
	if (cameramove == 0)
	{
		if (ch[0].x < cax - 900)
		{
			cax -= 5;
			bkcox -= 5;
			bkx -= 3;
		}
		else if (ch[0].x > cax - 400)
		{
			cax += 5;
			bkcox += 5;
			bkx += 3;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (gr[i].exist == 1)
		{
			
			gr[i].x += gr[i].speed;
			if (gr[i].up > 0 && gr[i].up <= 30)
			{
				gr[i].up += 1;
				if (gr[i].speed > 0)
				{
					gr[i].y -= gr[i].speed*3/4;
					gr[i].speed -= 0.1;
				}
				else
				{
					gr[i].y += gr[i].speed * 3 / 4;
					gr[i].speed += 0.1;
				}

			
			}
			else if (gr[i].up >= 30)
			{
				gr[i].air = 1;
				gr[i].up = 0;
			}

			if (gr[i].air == 1)
			{
				if (gr[i].speed > 0)
				{
					gr[i].y += gr[i].speed * 3 / 4;
					gr[i].speed += 0.1;
				}
				else
				{
					gr[i].y -= gr[i].speed * 3 / 4;
					gr[i].speed += 0.1;
				}
			}
			
			if (gr[i].status == 0)
			{
				gr[i].sx = 54;
				gr[i].sy = 92;
				gr[i].status = 1;
			}
			else if (gr[i].status == 1)
			{
				gr[i].sx = 54;
				gr[i].sy = 92;
				gr[i].status = 2;
			}
			else if (gr[i].status == 2)
			{
				gr[i].sx = 54;
				gr[i].sy = 92;
				gr[i].status = 3;
			}
			else if (gr[i].status == 3)
			{
				gr[i].sx = 54;
				gr[i].sy = 185;
				gr[i].status = 4;
			}
			else if (gr[i].status == 4)
			{
				gr[i].sx = 54;
				gr[i].sy = 185;
				gr[i].status = 5;
			}
			else if (gr[i].status == 5)
			{
				gr[i].sx = 218;
				gr[i].sy = 30;
				gr[i].status = 6;
			}
			else if (gr[i].status == 6)
			{
				gr[i].sx = 218;
				gr[i].sy = 30;
				gr[i].status = 7;
			}
			else if (gr[i].status == 7)
			{
				gr[i].sx = 218;
				gr[i].sy = 30;
				gr[i].status = 8;
			}
			else if (gr[i].status == 8)
			{
				gr[i].sx = 209;
				gr[i].sy = 128;
				gr[i].status = 9;
			}
			else if (gr[i].status == 9)
			{
				gr[i].sx = 209;
				gr[i].sy = 128;
				gr[i].status = 10;
			}
			else if (gr[i].status == 10)
			{
				gr[i].sx = 209;
				gr[i].sy = 128;
				gr[i].status = 11;
			}
			else if (gr[i].status == 11)
			{
				gr[i].sx = 218;
				gr[i].sy = 91;
				gr[i].status = 12;
			}
			else if (gr[i].status == 12)
			{
				gr[i].sx = 218;
				gr[i].sy = 91;
				gr[i].status = 13;
			}
			else if (gr[i].status == 13)
			{
				gr[i].sx = 218;
				gr[i].sy = 91;
				gr[i].status = 14;
			}
			else if (gr[i].status == 14)
			{
				gr[i].sx = 208;
				gr[i].sy = 185;
				gr[i].status = 15;
			}
			else if (gr[i].status == 15)
			{
				gr[i].sx = 208;
				gr[i].sy = 185;
				gr[i].status = 16;
			}
			else if (gr[i].status == 16)
			{
				gr[i].sx = 208;
				gr[i].sy = 185;
				gr[i].status = 0;
			}
		}
	}


	for (int i = 0; i < 6; i++)
	{
		if (gr[i].exist == 2)
		{
			if (gr[i].status == 0)
			{
				for (int j = 0; j < 20; j++)
				{
					if (em[j].exist == 1)
					{
						playsound(2);
						if (InCircle(gr[i].x, gr[i].y, em[j].x, em[j].y-30, 80) == TRUE)
						{
							
							em[j].exist = 2;
							em[j].scene = 0;
						}
					}
				}
				
				gr[i].sx = 0;
				gr[i].sy = 0;
				gr[i].status = 1;
			}
			else if (gr[i].status == 1)
			{
				gr[i].sx = 96;
				gr[i].sy = 0;
				gr[i].set += 1;
				if (gr[i].set == 10)
				{
					gr[i].set = 0;
					gr[i].status = 2;
				}
			}
			else if (gr[i].status == 2)
			{
				gr[i].sx = 192;
				gr[i].sy = 0;
				gr[i].set += 1;
				if (gr[i].set == 10)
				{
					gr[i].set = 0;
					gr[i].status = 3;
				}
			}
			else if (gr[i].status == 3)
			{
				gr[i].sx = 288;
				gr[i].sy = 0;
				gr[i].set += 1;
				if (gr[i].set == 10)
				{
					gr[i].set = 0;
					gr[i].status = 4;
				}
			}
			else if (gr[i].status == 4)
			{
				gr[i].sx = 384;
				gr[i].sy = 0;
				gr[i].set += 1;
				if (gr[i].set == 10)
				{
					gr[i].set = 0;
					gr[i].status = 5;
				}
			}
			else if (gr[i].status == 4)
			{
				gr[i].sx = 384;
				gr[i].sy = 0;
				gr[i].set += 1;
				if (gr[i].set == 10)
				{
					gr[i].set = 0;
					gr[i].status = 5;
				}
			}
			else if (gr[i].status == 5)
			{
				gr[i].sx = 0;
				gr[i].sy = 96;
				gr[i].set += 1;
				if (gr[i].set == 10)
				{
					gr[i].set = 0;
					gr[i].status = 6;
				}
			}
			else if (gr[i].status == 6)
			{
				gr[i].sx = 188;
				gr[i].sy = 96;
				gr[i].set += 1;
				if (gr[i].set == 10)
				{
					gr[i].set = 0;
					gr[i].status = 7;
				}
			}
			else if (gr[i].status == 7)
			{
				gr[i].sx = 384;
				gr[i].sy = 96;
				gr[i].set += 1;
				if (gr[i].set == 10)
				{
					gr[i].set = 0;
					gr[i].status = 8;
				}
			}
			else if (gr[i].status == 8)
			{
				gr[i].sx = 0;
				gr[i].sy = 192;
				gr[i].set += 1;
				if (gr[i].set == 10)
				{
					gr[i].set = 0;
					gr[i].status = 9;
				}
			}
			else if (gr[i].status == 9)
			{
				gr[i].sx = 192;
				gr[i].sy = 192;
				gr[i].set += 1;
				if (gr[i].set == 10)
				{
					gr[i].set = 0;
					gr[i].status = 10;
				}
			}
			else if (gr[i].status == 10)
			{
				gr[i].sx = 384;
				gr[i].sy = 192;
				gr[i].set += 1;
				if (gr[i].set == 10)
				{
					gr[i].set = 0;
					gr[i].status = 0;
					gr[i].exist = 0;
				}
			}

		}
	}


	for (int j = 0; j < 6; j++)
	{
		if (gr[j].exist == 1)
		{
			for (int i = (int)gr[j].x - 10; i < (int)gr[j].x + 10; i++)
			{
				if (InCircle((int)gr[j].x, (int)gr[j].y, (int)land[i].x, (int)land[i].y, f) == TRUE)
				{
					
					gr[j].exist = 2;
					gr[j].air = 0;
					gr[j].up = 0;
					gr[j].status = 0;
					gr[j].sx = 0;
					gr[j].sy = 0;
				}
				else
				{
					if ((int)gr[j].y >(int)land[i].y)
					{
						gr[j].exist = 2;
						gr[j].air = 0;
						gr[j].up = 0;
						gr[j].status = 0;
						gr[j].sx = 0;
						gr[j].sy = 0;
					}
				}
			}
		}
	}
	for (int j = 0; j < 20; j++)
	{
		if (cb[j].exist == 1)
		{
			for (int i = (int)cb[j].x - 10; i < (int)cb[j].x + 10; i++)
			{
				if (InCircle((int)cb[j].x, (int)cb[j].y, (int)land[i].x, (int)land[i].y, f) == TRUE)
				{
					
					cb[j].exist = 2;
				}
				else
				{
					if ((int)cb[j].y > (int)land[i].y)
					{
						cb[j].exist = 2;
					}
				}

			}
			for (int i = 0; i < 20; i++)
			{
				if (em[i].exist == 1)
				{
					if (InCircle((int)cb[j].x, (int)cb[j].y, (int)em[i].x + 20, (int)em[i].y - 30, 30) == TRUE)
					{
						playsound(2);
						cb[j].exist = 2;
						em[i].exist = 2;
						em[i].timmer = 6000;
						em[i].shot = 0;
						em[i].scene = 0;
						break;
					}
				}
			}
			if (cb[j].x >= ch[0].x+1200 || cb[j].x <= ch[0].x - 500 || cb[j].x >= 11000 || cb[j].y >= 800 || cb[j].y <= 100)
			{
				cb[j].exist = 2;
				cb[j].sx = 742;
				cb[j].sy = 70;
			}
			if (cb[j].exist == 1)
			{
				cb[j].x += cos((float)cb[j].angle)*(10);
				cb[j].y -= sin((float)cb[j].angle)*(10);
				cb[j].sx = 727;
				cb[j].sy = 70;
			}
		}
		if (cb[j].exist == 2)
		{
			cb[j].exist = 0;
		}

	}
	for (int j = 0; j < 50; j++)
	{
		if (eb[j].exist == 1)
		{
			for (int i = (int)eb[j].x - 10; i < (int)eb[j].x + 10; i++)
			{
				if (InCircle((int)eb[j].x, (int)eb[j].y, (int)land[i].x, (int)land[i].y, f) == TRUE)
				{
					eb[j].exist = 2;
				}
				else
				{
					if ((int)eb[j].y >(int)land[i].y)
					{
						eb[j].exist = 2;
					}
				}
				
			}
			if (eb[j].x >= ch[0].x + 1200 || eb[j].x <= ch[0].x - 500 || eb[j].x >= 11000 || eb[j].y >= 800 || eb[j].y <= 100)
			{
				eb[j].exist = 2;
				eb[j].sx = 742;
				eb[j].sy = 86;
			}
			if (eb[j].exist == 1)
			{
				eb[j].x += cos((float)eb[j].angle)*(4);
				eb[j].y -= sin((float)eb[j].angle)*(4);
				eb[j].sx = 727;
				eb[j].sy = 86;
			}
				
		}
		if (eb[j].exist == 1)
				{
					if (InCircle(eb[j].x, eb[j].y, ch[0].x + 35, ch[0].y - 35, 30) == TRUE)
					{
						eb[j].exist = 2;
						if (ch[0].exist == 1)
						{
							ch[0].exist = 2;
							ch[0].scene = 0;
							ch[0].command = 0;
						}
					}
				}
		if (eb[j].exist == 2)
		{
			eb[j].exist = 0;
		}

	}

	for (int i = 0; i < 20; i++)
	{
		if (em[i].exist == 2)
		{
			em[i].shot = 0;
			if (em[i].scene == 0)
			{
				em[i].set += 1;
				em[i].sx = 35;
				em[i].sy = 490;
				if (em[i].set == 6)
				{
					em[i].set = 0;
					em[i].scene = 1;
				}
			}
			else if (em[i].scene == 1)
			{
				em[i].set += 1;
				em[i].sx = 110;
				em[i].sy = 490;
				if (em[i].set == 6)
				{
					em[i].set = 0;
					em[i].scene = 2;
				}
			}
			else if (em[i].scene == 2)
			{
				em[i].set += 1;
				em[i].sx = 155;
				em[i].sy = 490;
				if (em[i].set == 6)
				{
					em[i].set = 0;
					em[i].scene = 3;
				}
			}
			else if (em[i].scene == 3)
			{
				em[i].set += 1;
				em[i].sx = 200;
				em[i].sy = 490;
				if (em[i].set == 6)
				{
					em[i].set = 0;
					em[i].scene = 4;
				}
			}
			else if (em[i].scene == 4)
			{
				em[i].set += 1;
				em[i].sx = 300;
				em[i].sy = 490;
				if (em[i].set == 6)
				{
					em[i].set = 0;
					em[i].scene = 5;
				}
			}
			else if (em[i].scene == 5)
			{
				em[i].set += 1;
				em[i].sx = 355;
				em[i].sy = 490;
				if (em[i].set == 6)
				{
					em[i].set = 0;
					em[i].scene = 6;
				}
			}
			else if (em[i].scene == 6)
			{
				em[i].set += 1;
				em[i].sx = 410;
				em[i].sy = 490;
				if (em[i].set == 6)
				{
					em[i].set = 0;
					em[i].scene = 7;
				}
			}
			else if (em[i].scene == 7)
			{
				em[i].set += 1;
				em[i].sx = 470;
				em[i].sy = 490;
				if (em[i].set == 6)
				{
					em[i].set = 0;
					em[i].scene = 8;
				}
			}
			else if (em[i].scene == 8)
			{
				em[i].set += 1;
				em[i].sx = 590;
				em[i].sy = 490;
				if (em[i].set == 6)
				{
					em[i].set = 0;
					em[i].scene = 9;
				}
			}
			else if (em[i].scene == 9)
			{
				em[i].set += 1;
				em[i].sx = 705;
				em[i].sy = 490;
				if (em[i].set == 6)
				{
					em[i].set = 0;
					em[i].scene = 0;
					em[i].exist = 0;
					em[i].timmer = 0;
					em[i].command = 0;
				}
			}
		}
	}
	StretchBlt(memdc, 0, 0, 1200, 800, bkdc, bkx+150, 0, 1200, 800, SRCCOPY);
	StretchBlt(memdc, 0,0, 1200, 800, bkbkdc, bkcox, 0, 1200, 800, SRCAND);
	StretchBlt(memdc, 0, 0, 1200, 800, bkcodc, bkcox, 0, 1200, 800, SRCPAINT);

		StretchBlt(memdc, 0, 0, 1200, 800, mapdc2, cax - 1200, 0, 1200, 800, SRCAND);
		StretchBlt(memdc, 0, 0, 1200, 800, mapdc, cax - 1200, 0, 1200, 800, SRCPAINT);

		for (int i = 0; i < 20; i++)
		{
			if (em[i].exist == 1 && em[i].jt == 0 && em[i].shot == 1 && em[i].timmer > 0)
			{
				if (em[i].side == 0)
				{
					StretchBlt(memdc, em[i].x - cax + 1200, em[i].y, 70, 70, modc2, em[i].sx, em[i].sy, 30, 40, SRCAND);
					StretchBlt(memdc, em[i].x - cax + 1200, em[i].y, 70, 70, modc, em[i].sx, em[i].sy, 30, 40, SRCPAINT);
				}
				else if (em[i].side == 1)
				{
					StretchBlt(memdc, em[i].x - cax + 1200+70, em[i].y, -70, 70, modc2, em[i].sx, em[i].sy, 30, 40, SRCAND);
					StretchBlt(memdc, em[i].x - cax + 1200+70, em[i].y, -70, 70, modc, em[i].sx, em[i].sy, 30, 40, SRCPAINT);
				}
			}
			else if (em[i].exist == 1 && em[i].jt == 0 && em[i].shot == 1 && em[i].timmer <= 0)
			{
				if (em[i].scene >= 0 && em[i].scene < 5)
				{
					if (em[i].side == 0)
					{
						StretchBlt(memdc, em[i].x - cax + 1200, em[i].y, 70, 70, modc2, em[i].sx, em[i].sy, 40, 40, SRCAND);
						StretchBlt(memdc, em[i].x - cax + 1200, em[i].y, 70, 70, modc, em[i].sx, em[i].sy, 40, 40, SRCPAINT);
					}
					else if (em[i].side == 1)
					{
						StretchBlt(memdc, em[i].x - cax + 1200 + 70, em[i].y, -70, 70, modc2, em[i].sx, em[i].sy, 40, 40, SRCAND);
						StretchBlt(memdc, em[i].x - cax + 1200 + 70, em[i].y, -70, 70, modc, em[i].sx, em[i].sy, 40, 40, SRCPAINT);
					}
				}
				else if (em[i].scene >= 5 && em[i].scene < 9)
				{
					if (em[i].side == 0)
					{
						StretchBlt(memdc, em[i].x - cax + 1200, em[i].y-15, 120, 90, modc2, em[i].sx, em[i].sy, 70, 50, SRCAND);
						StretchBlt(memdc, em[i].x - cax + 1200, em[i].y-15, 120, 90, modc, em[i].sx, em[i].sy, 70, 50, SRCPAINT);
					}
					else if (em[i].side == 1)
					{
						StretchBlt(memdc, em[i].x - cax + 1200 + 100, em[i].y-15, -120, 90, modc2, em[i].sx, em[i].sy, 70, 50, SRCAND);
						StretchBlt(memdc, em[i].x - cax + 1200 + 100, em[i].y-15, -120, 90, modc, em[i].sx, em[i].sy, 70, 50, SRCPAINT);
					}
				}
			}
			else if (em[i].exist == 1 && em[i].jt == 0 && em[i].shot == 0)
			{
				if (em[i].side == 0)
				{
					StretchBlt(memdc, em[i].x - cax + 1200, em[i].y, 70, 70, modc2, em[i].sx, em[i].sy, 30, 40, SRCAND);
					StretchBlt(memdc, em[i].x - cax + 1200, em[i].y, 70, 70, modc, em[i].sx, em[i].sy, 30, 40, SRCPAINT);
				}
				else if (em[i].side == 1)
				{
					StretchBlt(memdc, em[i].x - cax + 1200 + 70, em[i].y, -70, 70, modc2, em[i].sx, em[i].sy, 30, 40, SRCAND);
					StretchBlt(memdc, em[i].x - cax + 1200 + 70, em[i].y, -70, 70, modc, em[i].sx, em[i].sy, 30, 40, SRCPAINT);
				}
			}
			else if (em[i].exist == 2)
			{
				if (em[i].scene >= 0 && em[i].scene < 4)
				{
					if (em[i].side == 0)
					{
						StretchBlt(memdc, em[i].x - cax + 1200, em[i].y, 70, 70, modc2, em[i].sx, em[i].sy, 40, 50, SRCAND);
						StretchBlt(memdc, em[i].x - cax + 1200, em[i].y, 70, 70, modc, em[i].sx, em[i].sy, 40, 50, SRCPAINT);
					}
					else if (em[i].side == 1)
					{
						StretchBlt(memdc, em[i].x - cax + 1200 + 70, em[i].y, -70, 70, modc2, em[i].sx, em[i].sy, 40, 50, SRCAND);
						StretchBlt(memdc, em[i].x - cax + 1200 + 70, em[i].y, -70, 70, modc, em[i].sx, em[i].sy, 40, 50, SRCPAINT);
					}
				}
				else if (em[i].scene >= 4 && em[i].scene <= 9)
				{
					if (em[i].side == 0)
					{
						StretchBlt(memdc, em[i].x - cax + 1200, em[i].y, 70, 70, modc2, em[i].sx, em[i].sy, 60, 50, SRCAND);
						StretchBlt(memdc, em[i].x - cax + 1200, em[i].y, 70, 70, modc, em[i].sx, em[i].sy, 60, 50, SRCPAINT);
					}
					else if (em[i].side == 1)
					{
						StretchBlt(memdc, em[i].x - cax + 1200 + 70, em[i].y, -70, 70, modc2, em[i].sx, em[i].sy, 60, 50, SRCAND);
						StretchBlt(memdc, em[i].x - cax + 1200 + 70, em[i].y, -70, 70, modc, em[i].sx, em[i].sy, 60, 50, SRCPAINT);
					}
				}
			}
		}

		for (int i = 0; i < 20; i++)
		{
			if (cb[i].exist == 1 || cb[i].exist == 2)
			{
				if (cb[i].angle <= 180)
				{
					StretchBlt(memdc, cb[i].x - cax + 1200, cb[i].y+50, 20, 20, modc2, cb[i].sx, cb[i].sy, 12, 12, SRCAND);
					StretchBlt(memdc, cb[i].x - cax + 1200, cb[i].y+50, 20, 20, modc, cb[i].sx, cb[i].sy, 12, 12, SRCPAINT);
				}
				else if (cb[i].angle > 180)
				{
					StretchBlt(memdc, cb[i].x - cax + 1200, cb[i].y+50, -20, 20, modc2, cb[i].sx, cb[i].sy, 12, 12, SRCAND);
					StretchBlt(memdc, cb[i].x - cax + 1200, cb[i].y+50, -20, 20, modc, cb[i].sx, cb[i].sy, 12, 12, SRCPAINT);
				}
			}

		}
		for (int i = 0; i < 50; i++)
		{
			if (eb[i].exist == 1 || eb[i].exist == 2)
			{
				
					StretchBlt(memdc, eb[i].x - cax + 1200, eb[i].y + 50, 20, 20, modc2, eb[i].sx, eb[i].sy, 12, 12, SRCAND);
					StretchBlt(memdc, eb[i].x - cax + 1200, eb[i].y + 50, 20, 20, modc, eb[i].sx, eb[i].sy, 12, 12, SRCPAINT);
			}

		}

		for (int i = 0; i < 6; i++)
		{
			if (gr[i].exist == 1 || gr[i].exist == 2)
			{
				if (gr[i].exist == 1)
				{
					if (gr[i].status >= 0 && gr[i].status <= 2)
					{
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 30, 20, grdc2, gr[i].sx, gr[i].sy, 45, 35, SRCAND);
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 30, 20, grdc, gr[i].sx, gr[i].sy, 45, 35, SRCPAINT);
					}
					else if (gr[i].status >= 3 && gr[i].status <= 4)
					{
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 30, 33, grdc2, gr[i].sx, gr[i].sy, 50, 57, SRCAND);
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 30, 33, grdc, gr[i].sx, gr[i].sy, 50, 57, SRCPAINT);
					}
					else if (gr[i].status >= 5 && gr[i].status <= 7)
					{
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 20, 30, grdc2, gr[i].sx, gr[i].sy, 35, 57, SRCAND);
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 20, 30, grdc, gr[i].sx, gr[i].sy, 35, 57, SRCPAINT);
					}
					else if (gr[i].status >= 8 && gr[i].status <= 10)
					{
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 30, 33, grdc2, gr[i].sx, gr[i].sy, 50, 57, SRCAND);
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 30, 33, grdc, gr[i].sx, gr[i].sy, 50, 57, SRCPAINT);
					}
					else if (gr[i].status >= 11 && gr[i].status <= 13)
					{
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 30, 20, grdc2, gr[i].sx, gr[i].sy, 50, 35, SRCAND);
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 30, 20, grdc, gr[i].sx, gr[i].sy, 50, 35, SRCPAINT);
					}
					else if (gr[i].status >= 14 && gr[i].status <= 16)
					{
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 30, 33, grdc2, gr[i].sx, gr[i].sy, 55, 57, SRCAND);
						StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y + 50, 30, 33, grdc, gr[i].sx, gr[i].sy, 55, 57, SRCPAINT);
					}
				}
				else if (gr[i].exist == 2)
				{
					StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y-75, 150, 150, bodc2, gr[i].sx, gr[i].sy, 96, 96, SRCAND);
					StretchBlt(memdc, gr[i].x - cax + 1200, gr[i].y-75, 150, 150, bodc, gr[i].sx, gr[i].sy, 96, 96, SRCPAINT);
				}
			}
		}

		if (ch[0].exist == 1)
		{
			if (ch[0].side == 0)
			{
				StretchBlt(memdc, ch[0].x - cax + 1200, ch[0].y, 70, 70, chdc2, ch[0].sx, ch[0].sy, 110, 130, SRCAND);
				StretchBlt(memdc, ch[0].x - cax + 1200, ch[0].y, 70, 70, chdc, ch[0].sx, ch[0].sy, 110, 130, SRCPAINT);
			}
			else if (ch[0].side == 1)
			{
				StretchBlt(memdc, ch[0].x + 70 - cax + 1200, ch[0].y, -70, 70, chdc2, ch[0].sx, ch[0].sy, 110, 130, SRCAND);
				StretchBlt(memdc, ch[0].x + 70 - cax + 1200, ch[0].y, -70, 70, chdc, ch[0].sx, ch[0].sy, 110, 130, SRCPAINT);
			}
		}
		else if (ch[0].exist == 2)
		{
			if (ch[0].side == 0)
			{
				StretchBlt(memdc, ch[0].x - cax + 1200, ch[0].y, 70, 80, chdc2, ch[0].sx, ch[0].sy, 130, 130, SRCAND);
				StretchBlt(memdc, ch[0].x - cax + 1200, ch[0].y, 70, 80, chdc, ch[0].sx, ch[0].sy, 130, 130, SRCPAINT);
			}
			else if (ch[0].side == 1)
			{
				StretchBlt(memdc, ch[0].x + 70 - cax + 1200, ch[0].y, -70, 80, chdc2, ch[0].sx, ch[0].sy, 130, 130, SRCAND);
				StretchBlt(memdc, ch[0].x + 70 - cax + 1200, ch[0].y, -70, 80, chdc, ch[0].sx, ch[0].sy, 130, 130, SRCPAINT);
			}
		}
		}
	char str[30];
	wsprintf(str, "GRANADE %d 개", granade);
	TextOut(memdc, 100, 10, str, strlen(str));
	wsprintf(str, "LIFE %d 개", ch[0].life);
	TextOut(memdc, 10, 10, str, strlen(str));

	if (START == FALSE) {
		StretchBlt(memdc, 0, 0, 1200,800, backdc, 0, 0, 1200,800, SRCCOPY);
		StretchBlt(memdc,730, 120, 400,100, menudc, 550, 305, 220, 110, SRCCOPY);
		StretchBlt(memdc,730, 240, 400, 100, menudc, 550, 533, 220, 110, SRCCOPY);
	}

	
	StretchBlt(hdc, 0, 0, 1200, 800, memdc,0, 0, 1200, 800, SRCCOPY);
	
	for (int i = 0; i < 20; i++)
	{
		int k = 0;
		if (em[i].exist == 1)
		{
			k += 1;
		}
		if (k == 0 && ch[0].x >= 10500 && emcounter == 0)
		{
			victory = 1;
			ch[0].command = 0;
		}
	}
	if (victory == 1)
	{
		wsprintf(str, "VICTORY");
		TextOut(hdc, 600, 300, str, strlen(str));
	}

	if (QUIT == TRUE)
		DestroyWindow(hwnd);

	ReleaseDC(hwnd, hdc);
	DeleteObject(memdc);
	DeleteObject(mem);
	DeleteObject(chdc);
	DeleteObject(chdc2);
	DeleteObject(mapdc);
	DeleteObject(menudc);
	DeleteObject(backdc);
	DeleteObject(mapdc2);
	DeleteObject(modc);
	DeleteObject(modc2);
	DeleteObject(grdc);
	DeleteObject(grdc2);
	DeleteObject(bodc);
	DeleteObject(bodc2);
	DeleteObject(bkdc);
	DeleteObject(bkbkdc);
	DeleteObject(bkcodc);
	InvalidateRect(hwnd, NULL, false);
}


void soundsetup()
{
	char str[128];

	FMOD_System_Create(&soundSystem);
	FMOD_System_Init(soundSystem, 5, FMOD_INIT_NORMAL, NULL);
	for (int i = 0; i < 5; i++)
	{
		wsprintf(str, "sound\\sound%d.mp3", i + 1);
		FMOD_System_CreateSound(soundSystem, str, FMOD_DEFAULT, 0, &soundSYSTEM[i]);
	}
}
void soundoff()
{
	for (int i = 0; i < 5; i++)
		FMOD_Channel_Stop(soundCHANNEL[i]);
}

void playsound(int i)
{
	FMOD_System_PlaySound(soundSystem, soundSYSTEM[i], NULL, 0, &soundCHANNEL[i]);
	
}
