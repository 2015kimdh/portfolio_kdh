#include <windows.h>
#include<stdio.h>
#include<string>
#include<time.h>
#include<conio.h>
#include<math.h>

#define H 800
#define W 800

struct Captain
{
	double x;
	double y;
	double size;
	int show;
};

struct Trap
{
	double x;
	double y;
	double size;
	int met;
	double engage;
	double tangle;
	int way;
};

struct Pray
{
	double x;
	double y;
	int count;
	int met;
};


struct Virus
{
	double x;
	double y;
	double size;
	int count;
	int met;
};

Pray pray[50];
Virus virus[20];
Trap trap[10];
Captain hero[20];
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
	WndClass.hbrBackground =
		(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow
	(lpszClass, "Agar.io",
		WS_OVERLAPPED | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		0, 0, W+0, H+0,
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

HDC memDC;
HBRUSH hBrush, oldBrush;
HBITMAP hBitmap;
double mx = 100;
double my = 100;
int timmer = 0;
int score = 0;
int viruscounter = 0;
int traptimer = 0;
double herosize = 0;
int conti = 2;
int view = 0;

BOOL virus_contact;
RECT rect;

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


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	
	HDC hdc;
	
	RECT rect;
	COLORREF text_color;
	COLORREF bk_color;
	
	switch (iMessage)
	{
	case WM_CREATE:
		srand((unsigned)time(NULL));
		
		hero[0].x = 400;
		hero[0].y = 400;
		hero[0].size = 1;
		hero[0].show = 1;

		for (int i = 1; i < 6; i++)
		{
			trap[i].size = 1;
			trap[i].met = 1;
		}

		for (int i = 1; i < 20; i++)
		{
			hero[i].x = rand() % 750;
			hero[i].y = rand() % 750;
			hero[i].size = 1;
			hero[i].show = 0;
		}

		virus[0].x = 100;
		virus[0].y = 100;
		virus[0].size = 1;
		virus[0].met = 0;
		for (int i = 1; i < 20; i++)
		{
			virus[i].x = rand()%750;
			virus[i].y = rand()%750;
			virus[i].size = 1;
			virus[i].met = 1;
		}

		for (int i = 0; i < 49; i++)
		{
			pray[i].x = rand() % 800;
			pray[i].y = rand() % 800;
			if (InCircle(pray[i].x, pray[i].y, hero[0].x, hero[0].y, 3))
			{
				pray[i].x = rand() % 800;
				pray[i].y = rand() % 800;
			}
			pray[i].met = 0;
			pray[i].count = 0;
		}
		virus_contact = FALSE;
		break;

	case WM_LBUTTONUP:
		hdc = GetDC(hwnd);
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (conti == 2 && my < 40 && my > 10 && mx > 300 && mx < 400)
		{
			conti = 0;
			SetTimer(hwnd, 1, 10, TimerProc);
		}
		if (conti == 0 && my < 40 && my > 10 && mx > 400 && mx < 500)
		{
			conti = 2;
			KillTimer(hwnd, 1);
		}
		if (conti == 0 && my < 40 && my > 10 && mx > 500 && mx < 600)
		{
			KillTimer(hwnd, 1);
			TCHAR str[100];
			wsprintf(str, "게임을 종료하였습니다\n 생존시간 %d", timmer);
			if (MessageBox(hwnd, str, "게임 종료", MB_OK) == IDOK)
			{
				PostQuitMessage(0);
				break;
			}
		}

		double kx;
		double ky;
		double kangle;

		for (int j = 0; j < 20; j++)
		{
			if (InCircle(mx, my, hero[j].x, hero[j].y, 10 + hero[j].size * 2) && hero[j].show == 1 && hero[j].size > 8)
			{
				for (int i = 0; i < 20; i++)
				{
					if (hero[i].show == 0)
					{
						hero[i].x = hero[j].x;
						hero[i].y = hero[j].y;

						kx = mx - hero[j].x;
						ky = my - hero[j].y;
						kangle = atan2f((float)ky, (float)kx);
						if (kx == 0 && ky <= 0)
						{
							kangle = 90;
						}
						else if (kx == 0 && ky >= 0)
						{
							kangle = 180;
						}
						else if (kx >= 0 && ky == 0)
						{
							kangle = 0;
						}
						else if (kx <= 0 && ky == 0)
						{
							kangle = 270;
						}
						hero[i].x += cos(kangle)*(hero[j].size * 8 + 10);
						hero[i].y += sin(kangle)*(hero[j].size * 8 + 10);
						hero[i].show = 1;
						hero[i].size = hero[j].size / 2;
						hero[j].size -= hero[i].size;
						break;
					}
				}
			}
		}

		InvalidateRect(hwnd, NULL, false);
		ReleaseDC(hwnd, hdc);
		break;

	case WM_RBUTTONUP:
		hdc = GetDC(hwnd);
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		for (int j = 0; j < 20; j++)
		{
			if (InCircle(mx, my, hero[j].x, hero[j].y, 10 + hero[j].size * 5) && hero[j].show == 1 && hero[j].size > 5)
			{
				for (int i = 0; i < 50; i++)
				{
					if (pray[i].met == 1)
					{
						pray[i].x = hero[j].x;
						pray[i].y = hero[j].y;
						
						kx = mx - hero[j].x;
						ky = my - hero[j].y;
						kangle = atan2f((float)ky, (float)kx);
						if (kx == 0 && ky <= 0)
						{
							kangle = 90;
						}
						else if (kx == 0 && ky >= 0)
						{
							kangle = 180;
						}
						else if (kx >= 0 && ky == 0)
						{
							kangle = 0;
						}
						else if (kx <= 0 && ky == 0)
						{
							kangle = 270;
						}
						pray[i].x += cos(kangle)*(hero[j].size*5+10);
						pray[i].y += sin(kangle)*(hero[j].size*5+10);
						pray[i].count = 0;pray[i].met = 0;
						hero[j].size--;
						break;
					}
				}
			}
		}

		InvalidateRect(hwnd, NULL, false);
		ReleaseDC(hwnd, hdc);
		break;

	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		InvalidateRect(hwnd, NULL, false);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		TCHAR str[100];
		if (conti == 2)
		{
			rect = { 300, 10, 400, 40 };
			wsprintf(str, TEXT("게임시작"), timmer);
			DrawText(hdc, str, -1, &rect, DT_CENTER);
		}
		
		if (conti == 1)
		{
			MessageBeep(MB_ICONEXCLAMATION);
			wsprintf(str, "주인공이 사망하였습니다\n 생존시간 %d", timmer);
			MessageBox(hwnd, str, "게임 오버", MB_OK);
			if (MessageBox(hwnd, str, "게임 오버", MB_OK) == IDOK)
			{
				KillTimer(hwnd, 1);
				PostQuitMessage(0);
				break;
			}
		}
		if (view == 0)
		{
			BitBlt(hdc, 0, 0, W, H, memDC, 0, 0, SRCCOPY);
		}
	
	
	DeleteDC(memDC);
	DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;

	case WM_CHAR:

		InvalidateRect(hwnd, NULL, true);
		break;

	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMessage, wParam, lParam));
}

void CALLBACK TimerProc(HWND hwnd, UINT iMessage, WPARAM idEvent, DWORD dwTime)
{
	if (conti == 0)
	{
		HDC hdc;
		hdc = GetDC(hwnd);

		double fx;
		double fy;
		double angle;
		timmer += 1;
		memDC = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, W, H);
		SelectObject(memDC, hBitmap);
		Rectangle(memDC, 0, 0, W, H);


		//주인공 원 움직이기
		for (int i = 0; i < 19; i++)
		{
			fx = mx - hero[i].x;
			fy = my - hero[i].y;
			angle = atan2f((float)fy, (float)fx);
			if (fx == 0 && fy <= 0)
			{
				angle = 90;
			}
			else if (fx == 0 && fy >= 0)
			{
				angle = 180;
			}
			else if (fx >= 0 && fy == 0)
			{
				angle = 0;
			}
			else if (fx <= 0 && fy == 0)
			{
				angle = 270;
			}
			hero[i].x += cos(angle)*(5 / hero[i].size * 3);
			hero[i].y += sin(angle)*(5 / hero[i].size * 3);
			for (int j = 0; j < 19; j++)
			{
				if (i != j && hero[j].show == 1 && hero[i].show == 1)
				{
					if (InCircle(hero[i].x, hero[i].y, hero[j].x, hero[j].y, 10 + hero[i].size))
					{
						hero[i].size += hero[j].size;
						hero[j].show = 0;
						hero[j].size = 1;
					}
				}
			}
		}


		if (timmer % 500 == 0)
		{
			if (viruscounter < 20)
				viruscounter++;
			else
				viruscounter = 0;
		}

		int save = 0;
		int save1 = 0;
		double vx;
		double vy;
		double vx1 = 1000;
		double vy1 = 1000;

		if (virus[viruscounter].met == 1)
		{
			virus[viruscounter].met = 0;
			virus[viruscounter].x = rand() % 600;
			virus[viruscounter].y = rand() % 600;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					if (InCircle(virus[i].x, virus[i].y, hero[j].x, hero[j].y, 10 + hero[j].size * 2) && hero[j].show == 1)
					{
						virus[viruscounter].x = rand() % 600;
						virus[viruscounter].y = rand() % 600;
					}
				}
			}
		}
		for (int i = 0; i < 20; i++)
		{
			if (virus[i].met == 0)
			{
				for (int j = 0; j < 50; j++)
				{
					if (pray[j].met == 0)
					{
						vx = LengthPts(virus[i].x, virus[i].y, pray[j].x, pray[j].y);
						if (vx < vx1)
						{
							vx1 = vx;
							save = j;
						}
					}
				}
				for (int k = 0; k < 20; k++)
				{
					if (hero[k].show == 1)
					{
						vy = LengthPts(virus[i].x, virus[i].y, hero[k].x, hero[k].y);
						if (vy < vy1)
						{
							vy1 = vy;
							save1 = k;
						}
					}
				}
				if (virus[i].size > hero[save1].size && InCircle(virus[i].x, virus[i].y, hero[save1].x, hero[save1].y, 250) && hero[save1].show == 1)
				{
					fx = hero[save1].x - virus[i].x;
					fy = hero[save1].y - virus[i].y;
					angle = atan2f((float)fy, (float)fx);
					if (fx == 0 && fy <= 0)
					{
						angle = 90;
					}
					else if (fx == 0 && fy >= 0)
					{
						angle = 180;
					}
					else if (fx >= 0 && fy == 0)
					{
						angle = 0;
					}
					else if (fx <= 0 && fy == 0)
					{
						angle = 270;
					}
					virus[i].x += cos(angle)*(5 / virus[i].size);
					virus[i].y += sin(angle)*(5 / virus[i].size);
				}
				else if (vx1 < vy1)
				{
					fx = pray[save].x - virus[i].x;
					fy = pray[save].y - virus[i].y;
					angle = atan2f((float)fy, (float)fx);
					if (fx == 0 && fy <= 0)
					{
						angle = 90;
					}
					else if (fx == 0 && fy >= 0)
					{
						angle = 180;
					}
					else if (fx >= 0 && fy == 0)
					{
						angle = 0;
					}
					else if (fx <= 0 && fy == 0)
					{
						angle = 270;
					}
					virus[i].x += cos(angle)*(5 / virus[i].size);
					virus[i].y += sin(angle)*(5 / virus[i].size);
				}
				else if (vx1 >= vy1 && virus[i].size > hero[save1].size&& hero[save1].show == 1)
				{
					fx = hero[save1].x - virus[i].x;
					fy = hero[save1].y - virus[i].y;
					angle = atan2f((float)fy, (float)fx);
					if (fx == 0 && fy <= 0)
					{
						angle = 90;
					}
					else if (fx == 0 && fy >= 0)
					{
						angle = 180;
					}
					else if (fx >= 0 && fy == 0)
					{
						angle = 0;
					}
					else if (fx <= 0 && fy == 0)
					{
						angle = 270;
					}
					virus[i].x += cos(angle)*(5 / virus[i].size);
					virus[i].y += sin(angle)*(5 / virus[i].size);
				}
				else if (vx1 >= vy1 && virus[i].size <= hero[save1].size && hero[save1].show == 1)
				{
					fx = pray[save].x - virus[i].x;
					fy = pray[save].y - virus[i].y;
					angle = atan2f((float)fy, (float)fx);
					if (fx == 0 && fy <= 0)
					{
						angle = 90;
					}
					else if (fx == 0 && fy >= 0)
					{
						angle = 180;
					}
					else if (fx >= 0 && fy == 0)
					{
						angle = 0;
					}
					else if (fx <= 0 && fy == 0)
					{
						angle = 270;
					}
					virus[i].x += cos(angle)*(5 / virus[i].size);
					virus[i].y += sin(angle)*(5 / virus[i].size);
				}
				for (int m = 0; m < 20; m++)
				{
					if (i != m && virus[m].met == 0)
					{
						if (InCircle(virus[i].x, virus[i].y, virus[m].x, virus[m].y, 10 + virus[i].size * 2) || InCircle(virus[i].x, virus[i].y, virus[m].x, virus[m].y, 10 + virus[m].size * 2))
						{
							virus[i].size += virus[m].size;
							virus[m].met = 1;
						}
					}
				}
				if (virus[i].size > 30)
				{
					for (int n = 0; n < 19; n++)
					{
						if (virus[n].met == 1)
						{
							virus[i].size = virus[i].size / 2;
							virus[n].size = 15;
							virus[n].met = 0;
							virus[n].x = virus[i].x + 100;
							break;
						}
					}
				}

				for (int n = 0; n < 20; n++)
				{
					if (InCircle(virus[i].x, virus[i].y, hero[n].x, hero[n].y, 10 + hero[n].size * 2) || InCircle(virus[i].x, virus[i].y, hero[n].x, hero[n].y, 10 + virus[i].size * 2) && virus[i].size < hero[n].size)
					{
						if (virus[i].size < hero[n].size)
						{
							hero[n].size -= virus[i].size / 3;
							virus[i].size = 1;
							virus[i].met = 1;
							break;
						}
					}
					else if (InCircle(virus[i].x, virus[i].y, hero[n].x, hero[n].y, 10 + hero[n].size * 2) || InCircle(virus[i].x, virus[i].y, hero[n].x, hero[n].y, 10 + virus[i].size * 2) && virus[i].size > hero[n].size && hero[n].show == 1)
					{
						if (virus[i].size > hero[n].size)
						{
							virus[i].size -= hero[n].size / 3;
							hero[n].size = 1;
							hero[n].show = 0;
							break;
						}
					}
				}
			}
		}

		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (InCircle(pray[i].x, pray[i].y, hero[j].x, hero[j].y, 10 + hero[j].size * 2) && pray[i].met == 0 && hero[j].show == 1 && pray[i].met == 0)
				{
					pray[i].met = 1;
					pray[i].count = 0;
					hero[j].size++;
					score++;
				}
				else
				{
					if (pray[i].count < 2500)
						pray[i].count++;
					else
					{
						pray[i].count = 0;
						pray[i].x = rand() % 800;
						pray[i].y = rand() % 800;
						for (int j = 0; j < 20; j++)
						{
							if (InCircle(pray[i].x, pray[i].y, hero[j].x, hero[j].y, 10 + hero[j].size) && hero[j].show == 1 || InCircle(pray[i].x, pray[i].y, virus[j].x, virus[j].y, 10 + virus[j].size) && virus[j].met == 0)
							{
								pray[i].x = rand() % 800;
								pray[i].y = rand() % 800;
							}
						}
					}
				}
			}
			for (int j = 0; j < 20; j++)
			{
				if (InCircle(pray[i].x, pray[i].y, virus[j].x, virus[j].y, 10 + virus[j].size * 2) && pray[i].met == 0 && virus[j].met == 0)
				{
					pray[i].met = 1;
					pray[i].count = 0;
					virus[j].size++;
				}
				else
				{
					if (pray[i].count < 2500)
						pray[i].count++;
					else
					{
						pray[i].count = 0;
						pray[i].x = rand() % 800;
						pray[i].y = rand() % 800;
						for (int j = 0; j < 20; j++)
						{
							if (InCircle(pray[i].x, pray[i].y, hero[j].x, hero[j].y, 10 + hero[j].size) && hero[j].show == 1 || InCircle(pray[i].x, pray[i].y, virus[j].x, virus[j].y, 10 + virus[j].size) && virus[j].met == 0)
							{
								pray[i].x = rand() % 800;
								pray[i].y = rand() % 800;
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < 50; i++)
		{
			if (pray[i].met == 1)
			{
				pray[i].count++;

				if (pray[i].count >= 2500)
				{
					pray[i].x = rand() % 800;
					pray[i].y = rand() % 800;
					for (int j = 0; j < 20; j++)
					{
						if (InCircle(pray[i].x, pray[i].y, hero[j].x, hero[j].y, 10 + hero[j].size) && hero[j].show == 1 || InCircle(pray[i].x, pray[i].y, virus[j].x, virus[j].y, 10 + virus[j].size) && virus[j].met == 0)
						{
							pray[i].x = rand() % 800;
							pray[i].y = rand() % 800;
						}
					}

					pray[i].met = 0;
					pray[i].count = 0;
				}
			}
		}
		int con = 0;
		for (int i = 0; i < 50; i++)
		{

			if (pray[i].met == 1)
				con += 1;
		}
		if (con > 30)
		{
			for (int i = 0; i < 50; i++)
			{

				if (pray[i].met == 1)
				{
					pray[i].x = rand() % 800;
					pray[i].y = rand() % 800;
					for (int j = 0; j < 20; j++)
					{
						if (InCircle(pray[i].x, pray[i].y, hero[j].x, hero[j].y, 10 + hero[j].size) && hero[j].show == 1 || InCircle(pray[i].x, pray[i].y, virus[j].x, virus[j].y, 10 + virus[j].size) && virus[j].met == 0)
						{
							pray[i].x = rand() % 800;
							pray[i].y = rand() % 800;
						}
					}

					pray[i].met = 0;
					pray[i].count = 0;
				}
			}
		}

		if (timmer % 500 == 0)
			traptimer = 1;
		for (int t = 0; t < 6; t++)
		{
			if (traptimer == 1 && trap[t].met == 1)
			{
				trap[t].met = 0;
				trap[t].size = 7;
				trap[t].engage = 0;
				trap[t].tangle = rand() % 360;
				trap[t].x = (rand() % 600) + 100;
				trap[t].y = (rand() % 600) + 100;
				trap[t].way = 1;
				traptimer = 0;
				break;
			}
		}

		for (int t = 0; t < 6; t++)
		{
			if (trap[t].met == 0 && trap[t].engage >= 500 && trap[t].way == 0)
			{
				if (trap[t].x >= 800 && trap[t].y < 800)
				{
					trap[t].tangle = (rand() % 160) + 90;
					trap[t].way = 1;
				}
				else if (trap[t].x >= 800 && trap[t].y >= 800)
				{
					trap[t].tangle = (rand() % 70) + 90;
					trap[t].way = 1;
				}
				else if (trap[t].x < 800 && trap[t].y >= 800)
				{
					trap[t].tangle = (rand() % 160);
					trap[t].way = 1;
				}
				else if (trap[t].x <= 0 && trap[t].y <= 0)
				{
					trap[t].tangle = (rand() % 70) + 280;
					trap[t].way = 1;
				}
				else if (trap[t].x <= 0 && trap[t].y < 800)
				{
					trap[t].tangle = (rand() % 70);
					trap[t].way = 1;
				}
				else if (trap[t].x < 800 && trap[t].y <= 0)
				{
					trap[t].tangle = (rand() % 160) + 180;
					trap[t].way = 1;
				}

			}
			else if (trap[t].met == 0 && trap[t].engage == 500 && trap[t].way == 1)
			{
				trap[t].x += cos(trap[t].tangle)*(5 / trap[t].size * 2);
				trap[t].y += sin(trap[t].tangle)*(5 / trap[t].size * 2);
				if (trap[t].x >= W || trap[t].x <= 0 || trap[t].y >= H || trap[t].y <= 0)
				{
					trap[t].way = 0;
				}
			}
		}

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (trap[i].met == 0 && trap[i].engage == 500 && InCircle(trap[i].x, trap[i].y, hero[j].x, hero[j].y, 10 + hero[j].size * 2) && hero[j].show == 1)
					if (trap[i].size < hero[j].size)
					{
						trap[i].met = 1;
						trap[i].engage = 0;
						trap[i].way = 0;
						for (int t = 0; t < 20; t++)
						{
							if (hero[t].show == 0)
							{
								double bangle;
								hero[t].x = hero[j].x;
								hero[t].y = hero[j].y;

								bangle = (rand() % 60) * 6;

								hero[t].x += cos(bangle)*(hero[j].size * 5 + 10);
								hero[t].y += sin(bangle)*(hero[j].size * 5 + 10);
								hero[t].show = 1;
								hero[t].size = hero[j].size / 4;
								hero[j].size -= hero[t].size;
								if (hero[j].size < 3)
								{
									break;
								}
							}
						}
					}
				if (trap[i].met == 0 && trap[i].engage == 500 && InCircle(trap[i].x, trap[i].y, virus[j].x, virus[j].y, 10 + virus[j].size * 2) && virus[j].met == 0)
				{
					if (trap[i].size < virus[j].size)
					{
						trap[i].met = 1;
						trap[i].engage = 0;
						trap[i].way = 0;
						for (int t = 0; t < 20; t++)
						{
							if (virus[t].met == 1)
							{
								double bangle;
								virus[t].x = virus[j].x;
								virus[t].y = virus[j].y;

								bangle = (rand() % 60) * 6;

								virus[t].x += cos(bangle)*(virus[j].size * 5 + 10);
								virus[t].y += sin(bangle)*(virus[j].size * 5 + 10);
								virus[t].met = 0;
								virus[t].size = virus[j].size / 4;
								virus[j].size -= virus[t].size;
								if (virus[j].size < 4)
								{
									break;
								}
							}
						}
					}
					else if (trap[i].size >= virus[j].size)
					{
						trap[i].met = 1;
						trap[i].engage = 0;
						trap[i].way = 0;
						
						virus[j].size = 1;
						virus[j].met = 1;
					}
				}

			}
		}
		SelectObject(memDC, oldBrush);
		hBrush = CreateSolidBrush(RGB(250, 0, 60));
		oldBrush = (HBRUSH)SelectObject(memDC, hBrush);

		for (int i = 0; i < 49; i++)
		{
			if (pray[i].met == 0)
				Ellipse(memDC, pray[i].x - 3, pray[i].y - 3, pray[i].x + 3, pray[i].y + 3);
		}
		SelectObject(memDC, oldBrush);
		DeleteObject(hBrush);

		SelectObject(memDC, oldBrush);
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(memDC, hBrush);

		for (int i = 0; i < 5; i++)
		{
			if (trap[i].met == 0)
				Ellipse(memDC, trap[i].x - 10 - trap[i].size * 2, trap[i].y - 10 - trap[i].size * 2, trap[i].x + 10 + trap[i].size * 2, trap[i].y + 10 + trap[i].size * 2);
		}

		SelectObject(memDC, oldBrush);
		DeleteObject(hBrush);

		SelectObject(memDC, oldBrush);
		hBrush = CreateSolidBrush(RGB(0, 255, 250));
		oldBrush = (HBRUSH)SelectObject(memDC, hBrush);

		for (int i = 0; i < 5; i++)
		{
			if (trap[i].met == 0 && trap[i].engage < 500)
			{
				Ellipse(memDC, (trap[i].x - 10 - trap[i].size * 2) + trap[i].engage / 100, (trap[i].y - 10 - trap[i].size * 2) + trap[i].engage / 100, (trap[i].x + 10 + trap[i].size * 2) - trap[i].engage / 100, (trap[i].y + 10 + trap[i].size * 2) - trap[i].engage / 100);
				trap[i].engage += 1;
			}
			else
				Ellipse(memDC, (trap[i].x - 10 - trap[i].size * 2) + trap[i].engage / 100, (trap[i].y - 10 - trap[i].size * 2) + trap[i].engage / 100, (trap[i].x + 10 + trap[i].size * 2) - trap[i].engage / 100, (trap[i].y + 10 + trap[i].size * 2) - trap[i].engage / 100);

		}


		SelectObject(memDC, oldBrush);
		DeleteObject(hBrush);

		SelectObject(memDC, oldBrush);
		hBrush = CreateSolidBrush(RGB(250, 100, 60));
		oldBrush = (HBRUSH)SelectObject(memDC, hBrush);

		for (int i = 0; i < 19; i++)
			if (hero[i].show == 1)
				Ellipse(memDC, hero[i].x - 10 - hero[i].size * 2, hero[i].y - 10 - hero[i].size * 2, hero[i].x + 10 + hero[i].size * 2, hero[i].y + 10 + hero[i].size * 2);

		SelectObject(memDC, oldBrush);
		DeleteObject(hBrush);

		SelectObject(memDC, oldBrush);
		hBrush = CreateSolidBrush(RGB(200, 0, 250));
		oldBrush = (HBRUSH)SelectObject(memDC, hBrush);

		for (int i = 0; i < 19; i++)
			if (virus[i].met == 0)
				Ellipse(memDC, virus[i].x - 10 - virus[i].size * 2, virus[i].y - 10 - virus[i].size * 2, virus[i].x + 10 + virus[i].size * 2, virus[i].y + 10 + virus[i].size * 2);

		SelectObject(memDC, oldBrush);
		DeleteObject(hBrush);
		TCHAR str[100];

		for (int i = 0; i < 20; i++)
		{
			if (hero[i].show == 1)
			{
				herosize += hero[i].size;
			}
		}
		if (herosize < 1)
		{
			conti = 1;
			return;
		}

		SelectObject(memDC, oldBrush);
		hBrush = CreateSolidBrush(RGB(200, 0, 250));
		oldBrush = (HBRUSH)SelectObject(memDC, hBrush);
		wsprintf(str, TEXT("Score : %d"), score);
		TextOut(memDC, 0, 0, str, lstrlen(str));
		wsprintf(str, TEXT("Time : %d Sec"), timmer);
		TextOut(memDC, 0, 20, str, lstrlen(str));
		wsprintf(str, TEXT("Size : %d"), (int)herosize);
		TextOut(memDC, 0, 40, str, lstrlen(str));
		if (conti == 0)
		{
			rect = { 400, 10, 500, 40 };
			wsprintf(str, TEXT("게임중지"), timmer);
			DrawText(memDC, str, -1, &rect, DT_CENTER);
		}
		if (conti == 0)
		{
			rect = { 500, 10, 600, 40 };
			wsprintf(str, TEXT("게임종료"), timmer);
			DrawText(memDC, str, -1, &rect, DT_CENTER);
		}

		SelectObject(memDC, oldBrush);
		DeleteObject(hBrush); herosize = 0;
		// 여기 까지 주인공 원


		InvalidateRect(hwnd, NULL, false);
		ReleaseDC(hwnd, hdc);
	}
}