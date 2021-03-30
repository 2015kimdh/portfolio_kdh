#include <windows.h>
#include<stdio.h>
#include<string>
#include<time.h>
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include "resource.h"

#define H 800
#define W 800

#define BIT 101

struct Captain
{
	char x;
	char y;
	char status = -1;
	char side;
	char bot;
	char move = 0;
};
int tempx = 0;
int tempy = 0;
int speed = 400;
int h = 12;
int w = 10;
int r = 0;
int Over = 0;
Captain sq[24][20];
HINSTANCE g_hInst;
LPCTSTR lpszClass = "ParentClass";

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
	WndClass.hbrBackground =
		(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow
	(lpszClass, "그아아앗",
		WS_OVERLAPPED | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		0, 0, W + 0, H + 0,
		NULL, (HMENU)NULL,
		hInstance, NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
void CALLBACK TimerProc(HWND hwnd, UINT iMessage, WPARAM idEvent, DWORD dwTime);

void Bomb(int ckx, int cky, int orx, int ory, int tempx, int tempy)
{
	if (sq[cky][ckx].status == 0)
	{
		if (ckx == 0)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky][ckx + 1].status == 0 || sq[cky][ckx + 1].status == 2 || sq[cky][ckx + 1].status == 3)
				{
					tempx = ckx;
					sq[cky][ckx].status = 7;
					ckx += 1;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
			}
			else if (tempx == ckx + 1)
			{
				if (sq[ory][orx].side == 1 || sq[ory][orx].bot == 1)
				{
					sq[cky][ckx].status = 7;
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					return;
				}
			}
		}
		else if (ckx < w - 1)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky][ckx + 1].status == 0 || sq[cky][ckx + 1].status == 2 || sq[cky][ckx + 1].status == 3)
				{
					sq[cky][ckx].status = 7;
					tempx = ckx;
					ckx += 1;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
			}
			else
			{
				if (tempx != ckx + 1)
				{
					if (sq[cky][ckx + 1].status == 0 || sq[cky][ckx + 1].status == 2 || sq[cky][ckx + 1].status == 3)
					{
						sq[cky][ckx].status = 7;
						tempx = ckx;
						ckx += 1;
						Bomb(ckx, cky, orx, ory, tempx, tempy);
					}
				}
				else
				{
					if (sq[cky][ckx - 1].status == 0 || sq[cky][ckx - 1].status == 4 || sq[cky][ckx - 1].status == 5)
					{
						sq[cky][ckx].status = 7;
						tempx = ckx;
						ckx -= 1;
						Bomb(ckx, cky, orx, ory, tempx, tempy);
					}
				}
			}
		}
		else if (ckx == w - 1)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky][ckx - 1].status == 0 || sq[cky][ckx - 1].status == 4 || sq[cky][ckx - 1].status == 5)
				{
					sq[cky][ckx].status = 7;
					tempx = ckx;
					ckx -= 1;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
			}
			else if (tempx == ckx - 1)
			{
				if (sq[ory][orx].side == 1 || sq[ory][orx].bot == 1)
				{
					sq[cky][ckx].status = 7;
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					return;
				}
			}
		}
	}
	else if (sq[cky][cky].status == 1)//2번 블록
	{
		if (cky == h - 1)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky - 1][ckx].status == 1 || sq[cky - 1][ckx].status == 2 || sq[cky - 1][ckx].status == 5)
				{
					sq[cky][ckx].status = 7;
					tempy = cky;
					cky -= 1;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
			}
			else
			{
				if (sq[ory][orx].side == 1 || sq[ory][orx].bot == 1)
				{
					sq[cky][ckx].status = 7;
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					return;
				}
			}
		}
		else if (cky < h - 1)
		{
			if (cky - 1 == ory && ckx == orx)
			{
				if (sq[cky - 1][ckx].status == 1 || sq[cky - 1][ckx].status == 2 || sq[cky - 1][ckx].status == 5)
				{
					
					ckx = orx;
					cky = ory;
					sq[cky][ckx].status = 7;
					tempx = orx;
					tempy = ory;
					return;
				}
			}
			else if (cky + 1 == ory && ckx == orx)
			{
				if (sq[cky + 1][ckx].status == 1 || sq[cky + 1][ckx].status == 3 || sq[cky + 1][ckx].status == 4)
				{
					
					ckx = orx;
					cky = ory;
					sq[cky][ckx].status = 7;
					tempx = orx;
					tempy = ory;
					return;
				}

			}
			else if (cky - 1 != tempy)///////////////
			{
				if (sq[cky - 1][ckx].status == 1 || sq[cky - 1][ckx].status == 2 || sq[cky - 1][ckx].status == 5)
				{
					sq[cky][ckx].status = 7;
					tempy = cky;
					cky -= 1;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
			}
			else
			{
				if (sq[cky + 1][ckx].status == 1 || sq[cky + 1][ckx].status == 3 || sq[cky + 1][ckx].status == 4)
				{
					sq[cky][ckx].status = 7;
					tempy = cky;
					cky += 1;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
			}
		}
	}
	else if (sq[cky][cky].status == 2)/////////////////////////2번 블록////////////////////////////////
	{
	
		if (ckx == 0)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky + 1][ckx].status == 1 || sq[cky + 1][ckx].status == 3 || sq[cky + 1][ckx].status == 4)
				{
					sq[cky][ckx].status = 7;
					tempy = cky;
					cky += 1;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
			}
			else
			{
				if (sq[ory][orx].side == 1 || sq[ory][orx].bot == 1)
				{
					sq[cky][ckx].status = 7;
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					return;
				}
			}
		}
		else if (ckx < w - 1 && cky < h - 1)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky][ckx - 1].status == 0 || sq[cky][ckx - 1].status == 4 || sq[cky][ckx - 1].status == 5)
				{
					sq[cky][ckx].status = 7;
					tempx = ckx;
					ckx -= 1;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
			}
			else if (tempx != ckx - 1)
			{
				if (ckx - 1 == orx && cky == ory)
				{
					if (sq[cky][ckx - 1].status == 0 || sq[cky][ckx - 1].status == 4 || sq[cky][ckx - 1].status == 5)
					{
						sq[cky][ckx].status = 7;
						ckx = orx;
						cky = ory;
						tempx = orx;
						tempy = ory;
						return;
					}
				}
				else if (sq[cky][ckx - 1].status == 0 || sq[cky][ckx - 1].status == 4 || sq[cky][ckx - 1].status == 5)
				{
					sq[cky][ckx].status = 7;
					tempx = ckx;
					ckx -= 1;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
			}
			else
			{
				if (ckx == orx && cky + 1 == ory)
				{
					if (sq[cky + 1][ckx].status == 1 || sq[cky + 1][ckx].status == 3 || sq[cky + 1][ckx].status == 4)
					{
						sq[cky][ckx].status = 7;
						ckx = orx;
						cky = ory;
						tempx = orx;
						tempy = ory;
						return;
					}
				}
				else if (sq[cky + 1][ckx].status == 1 || sq[cky + 1][ckx].status == 3 || sq[cky + 1][ckx].status == 4)
				{
					sq[cky][ckx].status = 7;
					tempy = cky;
					cky -= 1;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
			}
		}
		else if (ckx == 0 && cky < h - 1)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky + 1][ckx].status == 1 || sq[cky + 1][ckx].status == 3 || sq[cky + 1][ckx].status == 4)
				{
					sq[cky][ckx].status = 7;
					tempy = cky;
					cky += 1;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
			}
			else
			{
				if (sq[ory][orx].side == 1 || sq[ory][orx].bot == 1)
				{
					sq[cky][ckx].status = 7;
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					return;
				}
			}
		}
	}
}

void CheckBlock(int ckx, int cky, int orx, int ory, int tempx, int tempy)
{
	if (sq[cky][ckx].status == 0) // 0번 블록
	{
		if (ckx == 0)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky][ckx + 1].status == 0 || sq[cky][ckx + 1].status == 2 || sq[cky][ckx + 1].status == 3)
				{
					tempx = ckx;
					ckx += 1;
					CheckBlock(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
			else if (tempx == ckx + 1)
			{
				if (sq[ory][orx].side == 1 || sq[ory][orx].bot == 1)
				{
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
		}
		else if (ckx < w - 1)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky][ckx + 1].status == 0 || sq[cky][ckx + 1].status == 2 || sq[cky][ckx + 1].status == 3)
				{
					tempx = ckx;
					ckx += 1;
					CheckBlock(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
			else
			{
				if (tempx != ckx + 1)
				{
					if (ckx + 1 == orx && cky == ory)
					{
						if (sq[cky][ckx + 1].status == 0 || sq[cky][ckx + 1].status == 2 || sq[cky][ckx + 1].status == 3)
						{
							ckx = orx;
							cky = ory;
							tempx = orx;
							tempy = ory;
							Bomb(ckx, cky, orx, ory, tempx, tempy);
						}
						else
						{
							tempx = 0;
							tempy = 0;
							return;
						}
					}
					else if (sq[cky][ckx + 1].status == 0 || sq[cky][ckx + 1].status == 2 || sq[cky][ckx + 1].status == 3)
					{
						tempx = ckx;
						ckx += 1;
						CheckBlock(ckx, cky, orx, ory, tempx, tempy);
					}
					else
					{
						tempx = 0;
						tempy = 0;
						return;
					}
						
				}
				else
				{
					if (ckx - 1 == orx && cky == ory)
					{
						if (sq[cky][ckx - 1].status == 0 || sq[cky][ckx - 1].status == 2 || sq[cky][ckx - 1].status == 3)
						{
							ckx = orx;
							cky = ory;
							tempx = orx;
							tempy = ory;
							Bomb(ckx, cky, orx, ory, tempx, tempy);
						}
						else
						{
							tempx = 0;
							tempy = 0;
							return;
						}
					}
					else if (sq[cky][ckx - 1].status == 0 || sq[cky][ckx - 1].status == 4 || sq[cky][ckx - 1].status == 5)
					{
						tempx = ckx;
						ckx -= 1;
						CheckBlock(ckx, cky, orx, ory, tempx, tempy);
					}
					else
					{
						tempx = 0;
						tempy = 0;
						return;
					}
				}
			}
		}
		else if (ckx == w - 1)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky][ckx - 1].status == 0 || sq[cky][ckx - 1].status == 4 || sq[cky][ckx - 1].status == 5)
				{
					tempx = ckx;
					ckx -= 1;
					CheckBlock(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
			else if (tempx == ckx - 1)
			{
				if (sq[ory][orx].side == 1 || sq[ory][orx].bot == 1)
				{
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
		}
	}
	else if (sq[cky][cky].status == 1)//2번 블록
	{
		if (cky == h - 1)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky - 1][ckx].status == 1 || sq[cky - 1][ckx].status == 2 || sq[cky - 1][ckx].status == 5)
				{
					tempy = cky;
					cky -= 1;
					CheckBlock(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
			else
			{
				if (sq[ory][orx].side == 1 || sq[ory][orx].bot == 1)
				{
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
		}
		else if (cky < h-1)
		{
			if (cky - 1 == ory && ckx == orx)
			{
				if (sq[cky - 1][ckx].status == 1 || sq[cky - 1][ckx].status == 2 || sq[cky - 1][ckx].status == 5)
				{
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}

			}
			else if (cky + 1 == ory && ckx == orx)
			{
				if (sq[cky + 1][ckx].status == 1 || sq[cky + 1][ckx].status == 3 || sq[cky + 1][ckx].status == 4)
				{
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}

			}
			else if (cky-1 != tempy)///////////////
			{
				if (sq[cky - 1][ckx].status == 1 || sq[cky - 1][ckx].status == 2 || sq[cky - 1][ckx].status == 5)
				{
					tempy = cky;
					cky -= 1;
					CheckBlock(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
			else
			{
				if (sq[cky + 1][ckx].status == 1 || sq[cky + 1][ckx].status == 3 || sq[cky + 1][ckx].status == 4)
				{
					tempy = cky;
					cky += 1;
					CheckBlock(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
		}
	}
	else if (sq[cky][cky].status == 2)/////////////////////////2번 블록////////////////////////////////
	{
		if (ckx == 0)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky+1][ckx].status == 1 || sq[cky + 1][ckx].status == 3 || sq[cky + 1][ckx].status == 4)
				{
					tempy = cky;
					cky += 1;
					CheckBlock(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
			else
			{
				if (sq[ory][orx].side == 1 || sq[ory][orx].bot == 1)
				{
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
		}
		else if(ckx < w-1 && cky < h-1)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky][ckx - 1].status == 0 || sq[cky][ckx - 1].status == 4 || sq[cky][ckx - 1].status == 5)
				{
					tempx = ckx;
					ckx -= 1;
					CheckBlock(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
			else if (tempx != ckx - 1)
			{
				if (ckx - 1 == orx && cky == ory)
				{
					if (sq[cky][ckx - 1].status == 0 || sq[cky][ckx - 1].status == 4 || sq[cky][ckx - 1].status == 5)
					{
						ckx = orx;
						cky = ory;
						tempx = orx;
						tempy = ory;
						Bomb(ckx, cky, orx, ory, tempx, tempy);
					}
					else
					{
						tempx = 0;
						tempy = 0;
						return;
					}
				}
				else if (sq[cky][ckx - 1].status == 0 || sq[cky][ckx - 1].status == 4 || sq[cky][ckx - 1].status == 5)
				{
					tempx = ckx;
					ckx -= 1;
					CheckBlock(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
			else
			{
				if (ckx == orx && cky + 1 == ory)
				{
					if (sq[cky+1][ckx].status == 1 || sq[cky+1][ckx].status == 3|| sq[cky+1][ckx].status == 4)
					{
						ckx = orx;
						cky = ory;
						tempx = orx;
						tempy = ory;
						Bomb(ckx, cky, orx, ory, tempx, tempy);
					}
					else
					{
						tempx = 0;
						tempy = 0;
						return;
					}
				}
				else if (sq[cky + 1][ckx].status == 1 || sq[cky + 1][ckx].status == 3 || sq[cky + 1][ckx].status == 4)
				{
					tempy = cky;
					cky -= 1;
					CheckBlock(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
		}
		else if (ckx == 0 && cky < h-1)
		{
			if (ckx == orx && cky == ory)
			{
				if (sq[cky+1][ckx].status == 1 || sq[cky+1][ckx].status == 3|| sq[cky+1][ckx].status == 4)
				{
					tempy = cky;
					cky += 1;
					CheckBlock(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
			else
			{
				if (sq[ory][orx].side == 1 || sq[ory][orx].bot == 1)
				{
					ckx = orx;
					cky = ory;
					tempx = orx;
					tempy = ory;
					Bomb(ckx, cky, orx, ory, tempx, tempy);
				}
				else
				{
					tempx = 0;
					tempy = 0;
					return;
				}
			}
		}
	}
}
HDC hdc;
HDC memDC, memdc1;
HBITMAP bit, hbitmap;
HBRUSH hBrush, oldBrush;
HPEN hPen, oldPen;
char art = 0;
int sero = 0;
int garo = 5;
char command = 0;
char pouse = 0;
int timer = 0;
int ckx = 0;
int cky = 0;
int orx = 0;
int ory = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HWND child_hwnd;
	RECT rect;
	COLORREF text_color;
	COLORREF bk_color;

	switch (iMessage)
	{
	case WM_CREATE:
		srand((unsigned)time(NULL));
		SetTimer(hwnd, 1, speed, TimerProc);
		
		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				sq[i][j].x = 0;
				sq[i][j].y = 0;
				sq[i][j].status = -1;
				sq[i][j].side = 0;
				sq[i][j].bot = 0;
				sq[i][j].move = 0;
			}
		}

		break;
	
	case WM_CHAR:
		if (wParam == 'z')
		{
			command = 0;
			h = 12;
			w = 10;
			garo = 5;
			sero = 0;
			art = 0;
			timer = 0;
			for (int i = 0; i < 24; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					sq[i][j].status = -1;
				}
			}
			speed = 400;
			timer = 0;
			Over = 0;
		}
		else if (wParam == 'x')
		{
			command = 1;
			h = 18;
			w = 15;
			garo = 5;
			sero = 0;
			art = 0;
			timer = 0;
			for (int i = 0; i < 24; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					sq[i][j].status = -1;
				}
			}
			speed = 400;
			timer = 0;
			Over = 0;
		}
		else if (wParam == 'c')
		{
			command = 2;
			h = 24;
			w = 20;
			garo = 5;
			sero = 0;
			art = 0;
			timer = 0;
			for (int i = 0; i < 24; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					sq[i][j].status = -1;
				}
			}
			speed = 400;
			timer = 0;
			Over = 0;
		}
		else if (wParam == 'r')
		{
			
				if (sq[sero][garo].move == 1)
				{
					if (sq[sero][garo].status == 0)
					{
						sq[sero][garo].status = 1;
						sq[sero][garo].x = 10;
						sq[sero][garo].y = 0;
					}
					else if (sq[sero][garo].status == 1)
					{
						sq[sero][garo].status = 0;
						sq[sero][garo].x = 0;
						sq[sero][garo].y = 0;
					}
					else if (sq[sero][garo].status == 2)
					{
						sq[sero][garo].status = 3;
						sq[sero][garo].x = 30;
						sq[sero][garo].y = 0;
					}
					else if (sq[sero][garo].status == 3)
					{
						sq[sero][garo].status = 4;
						sq[sero][garo].x = 40;
						sq[sero][garo].y = 0;
					}
					else if (sq[sero][garo].status == 4)
					{
						sq[sero][garo].status = 5;
						sq[sero][garo].x = 50;
						sq[sero][garo].y = 0;
					}
					else if (sq[sero][garo].status == 5)
					{
						sq[sero][garo].status = 2;
						sq[sero][garo].x = 20;
						sq[sero][garo].y = 0;
					}
				}
		}
		else if (wParam == 's')
		{
			if (pouse == 0)
			{
				pouse = 1;
				KillTimer(hwnd, 1);
			}
			else if(pouse == 1)
			{
				pouse = 0;
				SetTimer(hwnd, 1, speed, TimerProc);
			}
		}
		else if (wParam == 'q')
		{
			DeleteObject(hPen);
			DeleteObject(memDC);
			DeleteObject(memdc1);
			DeleteObject(hPen);
			KillTimer(hwnd, 1);
			PostQuitMessage(0);
		}
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{
			if (sq[sero][garo].move == 1 && garo > 0 && sq[sero][garo - 1].status == -1)
			{
				sq[sero][garo - 1] = sq[sero][garo];
				sq[sero][garo].status = -1;
				garo -= 1;
			}
		}
		else if (wParam == VK_RIGHT)
		{
			if (sq[sero][garo].move == 1 && garo < w-1 && sq[sero][garo + 1].status == -1)
			{
				sq[sero][garo + 1] = sq[sero][garo];
				sq[sero][garo].status = -1;
				garo += 1;
			}
		}
		else if (wParam == VK_DOWN)
		{
			if (sq[sero][garo].move == 1 && sero < h - 1 && sq[sero+1][garo].status == -1)
			{
				sq[sero + 1][garo] = sq[sero][garo];
				sq[sero][garo].status = -1;
				sero += 1;
				if (sero == h - 1)
				{
					sq[sero][garo].move = 0;
					sero = 0;
					garo = 5;
					art = 0;
					
				}
			}
		}
		InvalidateRect(hwnd, NULL, false);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		BitBlt(hdc, 0, 0, 500, 600, memDC, 0, 0, SRCCOPY);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		DeleteObject(memDC);
		DeleteObject(memdc1);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		DeleteObject(hPen);
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMessage, wParam, lParam));
}

void CALLBACK TimerProc(HWND hwnd, UINT iMessage, WPARAM idEvent, DWORD dwTime)
{
	hdc = GetDC(hwnd);
	memDC = CreateCompatibleDC(hdc);
	memdc1 = CreateCompatibleDC(hdc);
	bit = CreateCompatibleBitmap(hdc, 500, 600);
	SelectObject(memDC, bit);
	SelectObject(memdc1, bit);
	Rectangle(memDC, 0, 0, 500, 600);
	if (sero == 0 && sq[sero + 1][garo].status != -1)
	{
		TextOut(memDC, 10, 400, "Game Set", 8);
		Over = 1;
		art = 1;
	}
	else if (Over == 0)
	{
		if (art == 0) {
			art = 1;
			sq[0][5].side = 0;
			sq[0][5].move = 1;
			if (r == 0)
			{
				sq[0][5].status = 0;
				sq[0][5].x = 0;
				sq[0][5].y = 0;
			}
			else if (r == 1)
			{
				sq[0][5].status = 1;
				sq[0][5].x = 10;
				sq[0][5].y = 0;
			}
			else if (r == 2)
			{
				sq[0][5].status = 2;
				sq[0][5].x = 20;
				sq[0][5].y = 0;
			}
			else if (r == 3)
			{
				sq[0][5].status = 3;
				sq[0][5].x = 30;
				sq[0][5].y = 0;
			}
			else if (r == 4)
			{
				sq[0][5].status = 4;
				sq[0][5].x = 40;
				sq[0][5].y = 0;
			}
			else if (r == 5)
			{
				sq[0][5].status = 5;
				sq[0][5].x = 40;
				sq[0][5].y = 0;
			}
			else if (r == 6)
			{
				sq[0][5].status = 6;
				sq[0][5].x = 50;
				sq[0][0].y = 0;
			}
			r = rand() % 5;
		}
		else if (art == 1)
		{
			for (int i = 0; i < h; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (i < h - 1 && i != sero && w != garo)
					{
						if (sq[i + 1][j].status == -1)
						{
							sq[i + 1][j] = sq[i][j];
							sq[i][j].status = -1;
						}
						else
						{

						}
						if (sq[i][j].move == 1 && sq[i + 1][j].status != 1)
						{
							sq[i][j].move = 0;

						}
					}
				}
			}
		}

		if (sq[sero + 1][garo].status == -1 && sq[sero][garo].move == 1)
		{
			sq[sero + 1][garo] = sq[sero][garo];
			sq[sero][garo].status = -1;
			sero += 1;
			if (sero == h - 1)
			{
				sq[sero][garo].move = 0;
				art = 0;
				sero = 0;
				garo = 5;
			}
		}
		else if (sq[sero + 1][garo].status != -1 && sq[sero][garo].move == 1)
		{
			sq[sero][garo].move = 0;
			sero = 0;
			garo = 5;
			art = 0;
		}

		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				sq[i][j].side = 0;
				sq[i][j].bot = 0;
			}
		}

		for (int i = 0; i < h; i++)
		{
			if (sq[i][0].status == 0 || sq[i][0].status == 2 || sq[i][0].status == 3)
			{
				sq[i][0].side = 1;
			}
			if (sq[i][w - 1].status == 4 || sq[i][w - 1].status == 5 || sq[i][0].status == 0)
			{
				sq[i][w - 1].side = 1;
			}
		}
		for (int i = 0; i < w; i++)
		{
			if (sq[h - 1][i].status == 1 || sq[h - 1][i].status == 2 || sq[h - 1][i].status == 5)
			{
				sq[h - 1][i].bot = 1;
			}
		}
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				orx = j;
				ory = i;
				ckx = j;
				cky = i;
				CheckBlock(ckx, cky, orx, ory, tempx, tempy);
			}
		}
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (sq[i][j].status == 7)
				{
					sq[i][j].x = 0;
					sq[i][j].y = 10;
					sq[i][j].status = 6;
				}
				else if (sq[i][j].status == 6)
				{
					sq[i][j].x = 10;
					sq[i][j].y = 10;
					sq[i][j].status = -1;
				}
			}
		}
	}

		hbitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(BIT));
		SelectObject(memdc1, hbitmap);
		if (command == 0)
		{
			for (int i = 0; i < h; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (sq[i][j].status != -1)
					{
						StretchBlt(memDC, j * 50, i * 50, 50, 50, memdc1, sq[i][j].x, sq[i][j].y, 10, 10, SRCCOPY);
					}
				}
			}
		}
		else if (command == 1)
		{
			for (int i = 0; i < h; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (sq[i][j].status != -1)
					{
						StretchBlt(memDC, j * 33, i * 33, 33, 33, memdc1, sq[i][j].x, sq[i][j].y, 10, 10, SRCCOPY);
					}
				}
			}
		}
		else if (command == 2)
		{
			for (int i = 0; i < h; i++)
			{
				for (int j = 0; j < w; j++)
				{
					if (sq[i][j].status != -1)
					{
						StretchBlt(memDC, j * 25, i * 25, 25, 25, memdc1, sq[i][j].x, sq[i][j].y, 10, 10, SRCCOPY);
					}
				}
			}
		}
		SelectObject(memdc1, hbitmap);
		StretchBlt(hdc, 600, 200, 50, 50, memdc1, r * 10, 0, 10, 10, SRCCOPY);
		if(Over == 0)
		timer += 25;
		if (timer % 2500 == 0)
		{
			if (speed < 200)
				speed -= 50;
		}
		
	char str[30];
	wsprintf(str, TEXT("Speed : %d"), speed);
	TextOut(hdc, 600, 300, str, lstrlen(str));
	wsprintf(str, TEXT("Time : %d"), timer);
	TextOut(hdc, 600, 350, str, lstrlen(str));
	DeleteObject(hbitmap);
	ReleaseDC(hwnd, hdc);
	ReleaseDC(hwnd, memdc1);
	ReleaseDC(hwnd, memDC);
	InvalidateRect(hwnd, NULL, false);
}

