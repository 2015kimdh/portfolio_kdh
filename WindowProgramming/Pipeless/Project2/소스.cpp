#include <windows.h> 
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"

#define A_size 1200
#define B_size 800

struct Hero {
	int x;
	double y;
};

struct bod {
	int x;
	int y;
	int state;
};

Hero hero[1];
bod ground[40000];
HINSTANCE g_hInst;
LPCTSTR lpszClass = "Window Class Name";
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;  WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, "windows program1-1", WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 100, 50, A_size, B_size, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);  UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);    DispatchMessage(&Message);
	}  return Message.wParam;
}

char command = 0;
char jump = 0;
double set = 0;
int vision = 0;
BOOL jp = FALSE;
HDC hdc, memDC, memDC2; HBITMAP hBitmap, bit, bit2;
HBITMAP hBitmap2;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


	PAINTSTRUCT ps;


	switch (uMsg) {
	case WM_CREATE:
		hBitmap2 = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(102));//맵
		SetTimer(hWnd, 1, 100, TimerProc);
		hero[0].x = 10;
		hero[0].y = 400;
		for (int i = 0; i < 15000; i++) {

			ground[i].x = i;
			if (224 < i&&i < 1295) {
				set += 0.2;
				ground[i].y = 635 - set;
			}
			else
				ground[i].y = 635;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		BitBlt(hdc, 0, 0, A_size, B_size, memDC, 0, 0, SRCCOPY);
		DeleteObject(bit);
		ReleaseDC(hWnd, hdc);
		ReleaseDC(hWnd, memDC);
		ReleaseDC(hWnd, memDC2);
		DeleteDC(memDC2);
		DeleteDC(memDC);
		DeleteDC(hdc);

		EndPaint(hWnd, &ps);
		break;

	case WM_CHAR:

		break;
	case WM_KEYDOWN:
		if (wParam == VK_RIGHT)
		{
			hero[0].x += 5;
		}

		else if (wParam == VK_LEFT)
		{
			hero[0].x -= 5;
		}
		else if (wParam == VK_SPACE)
		{
			if (jp == TRUE) {
				jump = 1;
				jp = FALSE;
			}
		}

		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_KEYUP:


		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:

		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		DeleteObject(hdc);
		DeleteObject(memDC);
		DeleteObject(hBitmap);
		DeleteObject(bit);
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); // 위의 세 메시지 외의 나머지 메시지는 OS로 } 
}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	hdc = GetDC(hWnd);
	bit = CreateCompatibleBitmap(hdc, A_size, B_size);
	memDC = CreateCompatibleDC(hdc);
SelectObject(memDC, bit);
bit = CreateCompatibleBitmap(memDC, 15000, B_size);
	memDC2 = CreateCompatibleDC(memDC);
	
	SelectObject(memDC2, bit);
	Rectangle(memDC, 0, 0, A_size, B_size);
	Rectangle(memDC2, 0, 0, 15000, B_size);
	MoveToEx(memDC2, 0, 635, NULL);
	LineTo(memDC2, 1500, 635);
	MoveToEx(memDC2, 225, 635, NULL);
	LineTo(memDC2, 1295, 415);
	Rectangle(memDC2, hero[0].x, hero[0].y, hero[0].x + 30, hero[0].y + 30);

	if (jump > 0) {
		hero[0].y -= 50;
		jump++;
	}
	if (jump == 4)
		jump = 0;
	if (hero[0].y + 30 >= ground[hero[0].x].y)
		jp = TRUE;

	if (hero[0].y + 30 < ground[hero[0].x].y)
		hero[0].y += 5;
	else if (hero[0].y + 30 > ground[hero[0].x].y)
		hero[0].y = ground[hero[0].x].y - 30;
	TextOut(memDC2, 10, 400, "Game Set", 8);

	StretchBlt(memDC, 0, 0, A_size, B_size, memDC2, hero[0].x-10, 0, A_size, B_size, SRCCOPY);
	DeleteObject(bit);
	ReleaseDC(hWnd, hdc);
	ReleaseDC(hWnd, memDC2);
	ReleaseDC(hWnd, memDC);

	InvalidateRgn(hWnd, NULL, false);
}