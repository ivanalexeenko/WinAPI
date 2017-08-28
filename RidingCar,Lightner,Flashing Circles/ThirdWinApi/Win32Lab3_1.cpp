#define _CRT_SECURE_NO_WARNINGS
#define PI 3.1415926535897
#undef UNICODE
#include<windows.h>
#include"resource.h"
#include <stdio.h>
#include<cmath>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
const int Displace = 380;
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "RIDING CAR";
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	if (!hPrevInstance)
	{
		if (!InitApplication(hInstance))
			return (FALSE);
	}
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return (msg.wParam);
}
BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS  wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE - 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	return RegisterClass(&wc);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow(
		szClassName,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)    return (FALSE);
	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);
	return (TRUE);
}
void DrawFirstWheel(HDC hdc,int x,int y,int WheelBRad,int WheelSRad) {
	SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
	SelectObject(hdc, CreatePen(10, 1, RGB(0, 0, 0)));
	Ellipse(hdc, x / 25 - WheelBRad, y / 1.1 - WheelBRad, x / 25 + WheelBRad, y / 1.1 + WheelBRad);
	SelectObject(hdc, CreateSolidBrush(RGB(192, 192, 192)));
	Ellipse(hdc, x / 25 - WheelSRad, y / 1.1 - WheelSRad, x / 25 + WheelSRad, y / 1.1 + WheelSRad);
	SelectObject(hdc, CreatePen(10, 7, RGB(128, 128, 128)));
	MoveToEx(hdc, x / 25, y / 1.1, NULL);
	LineTo(hdc, x / 23, y / 1.15);
	MoveToEx(hdc, x / 25, y / 1.1, NULL);
	LineTo(hdc, x / 17, y / 1.12);
	MoveToEx(hdc, x / 25, y / 1.1, NULL);
	LineTo(hdc, x / 18, y / 1.07);
	MoveToEx(hdc, x / 25, y / 1.1, NULL);
	LineTo(hdc, x / 32, y / 1.06);
	MoveToEx(hdc, x / 25, y / 1.1, NULL);
	LineTo(hdc, x / 46, y / 1.12);
}
void DrawSecondWheel(HDC hdc,int x,int y,int WheelBRad,int WheelSRad,int Displace) {
	SelectObject(hdc, CreatePen(10, 1, RGB(0, 0, 0)));
	SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
	Ellipse(hdc, x / 25 - WheelBRad + Displace, y / 1.1 - WheelBRad, x / 25 + WheelBRad + Displace, y / 1.1 + WheelBRad);
	SelectObject(hdc, CreateSolidBrush(RGB(192, 192, 192)));
	Ellipse(hdc, x / 25 - WheelSRad + Displace, y / 1.1 - WheelSRad, x / 25 + WheelSRad + Displace, y / 1.1 + WheelSRad);
	SelectObject(hdc, CreatePen(10, 7, RGB(128, 128, 128)));
	MoveToEx(hdc, x / 25 + Displace, y / 1.1, NULL);
	LineTo(hdc, x / 23 + Displace, y / 1.15);
	MoveToEx(hdc, x / 25 + Displace, y / 1.1, NULL);
	LineTo(hdc, x / 17 + Displace, y / 1.12);
	MoveToEx(hdc, x / 25 + Displace, y / 1.1, NULL);
	LineTo(hdc, x / 18 + Displace, y / 1.07);
	MoveToEx(hdc, x / 25 + Displace, y / 1.1, NULL);
	LineTo(hdc, x / 32 + Displace, y / 1.06);
	MoveToEx(hdc, x / 25 + Displace, y / 1.1, NULL);
	LineTo(hdc, x / 46 + Displace, y / 1.12);
}
void DrawCabine(HDC hdc,POINT *Triangle) {
	SelectObject(hdc, CreateSolidBrush(RGB(255, 215, 0)));
	SelectObject(hdc, CreatePen(10, 3, RGB(220, 20, 60)));
	Polygon(hdc, Triangle, 3);
}
void DrawCar(HDC hdc,HBITMAP hBmp,BITMAP bm,int x,int y) {
	HDC hCarMemDC = CreateCompatibleDC(hdc);
	SelectObject(hCarMemDC, hBmp);
	SaveDC(hdc);
	TransparentBlt(hdc, x-80, y-bm.bmHeight/1.5, bm.bmWidth+Displace, bm.bmHeight+50, hCarMemDC, 0, 0, bm.bmWidth, bm.bmHeight,RGB(255,255,255));
	RestoreDC(hdc, -1);
	DeleteObject(hCarMemDC);
}
void DrawBitmapWheel(HWND hWnd,HDC hdc,HBITMAP hBmp,BITMAP bm,float x,float y,int alpha) {
	XFORM xForm;
	HRGN hRgn;
	HDC hWheelMemDC = CreateCompatibleDC(hdc);
	SelectObject(hWheelMemDC, hBmp);
	// Задаем область отсечения
	hRgn = CreateEllipticRgn(x, y, x + bm.bmWidth, y + bm.bmHeight);
	SelectClipRgn(hdc,hRgn);
	// Мировые преобразования для вращения и перемещения мяча
	xForm.eM11 = (FLOAT) cos(alpha*2*(PI)/360);
	xForm.eM12 = (FLOAT) sin(alpha * 2 * (PI) / 360);
	xForm.eM21 = (FLOAT) -sin(alpha * 2 * (PI) / 360);
	xForm.eM22 = (FLOAT) cos(alpha * 2 * (PI) / 360);
	xForm.eDx = x + bm.bmWidth / 2;
	xForm.eDy = y + bm.bmHeight / 2;
	// Вывод колеса
	SaveDC(hdc);
	BOOL ret = SetWorldTransform(hdc,&xForm);
	TransparentBlt(hdc,-bm.bmWidth/2,-bm.bmHeight/2,bm.bmWidth,bm.bmHeight,hWheelMemDC,0,0, bm.bmWidth, bm.bmHeight,RGB(255,255,255));
	RestoreDC(hdc, -1);
	SelectClipRgn(hdc, NULL);
	DeleteObject(hRgn);
	DeleteObject(hWheelMemDC);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	PAINTSTRUCT ps;
	RECT Rect;
	RECT WheelRect;
	const int WheelBRad=50;
	const int WheelSRad = 40;
	
	HBITMAP BackGround;
	static HBRUSH BrushBackGround;
	static HBITMAP BackWheel;
	static BITMAP bm;
	static int x, y;
	static HBITMAP Car;
	static BITMAP bitmap;
	
	
	static float WheelX=0, WheelY=0;
	static float dx, dy;
	static int alpha = 0;
	static int frequency = 100;

	switch (message)
	{
	case WM_CREATE: {
		hdc = GetDC(hWnd);
		GetClientRect(hWnd, &Rect);
		x = Rect.right;
		y = Rect.bottom;
		dx = Rect.right / 50;
		//dy = Rect.bottom / 50;
		SetTimer(hWnd, 1, frequency, NULL);

		BackGround = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_BG));
		BrushBackGround = CreatePatternBrush(BackGround);
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)BrushBackGround);
		BackWheel = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_WHEEL));
		GetObject(BackWheel, sizeof(bm), LPSTR(&bm));
		Car = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_BITMAP4));
		GetObject(Car, sizeof(BITMAP), &bitmap);
		SetGraphicsMode(hdc, GM_ADVANCED);
		SetBkMode(hdc, TRANSPARENT);
		break;

	}
	case WM_TIMER: {
		GetClientRect(hWnd, &Rect);
		SetRect(&WheelRect, (int)WheelX, (int)WheelY, (int)WheelX + bm.bmWidth, (int)WheelY + bm.bmHeight);
		FillRect(hdc, &WheelRect, BrushBackGround);
		SetRect(&WheelRect, (int)WheelX + Displace, (int)WheelY, (int)WheelX + Displace + bm.bmWidth, (int)WheelY + bm.bmHeight);
		FillRect(hdc, &WheelRect, BrushBackGround);
		SetRect(&WheelRect, WheelX - 80, WheelY - bitmap.bmHeight / 1.5, bitmap.bmWidth, bitmap.bmHeight);
		FillRect(hdc, &Rect, BrushBackGround);
		
		WheelX += dx;
		WheelY = Rect.bottom - bm.bmHeight;
		alpha += 10;
		if (alpha > 360) alpha = 0;
		if (WheelX-80 > Rect.right ) WheelX = -(Displace+bm.bmWidth+80);
		//if (WheelY + bm.bmHeight >= Rect.bottom || WheelY < 0) dy = -dy;
		DrawCar(hdc, Car, bitmap,WheelX,WheelY);

		DrawBitmapWheel(hWnd, hdc, BackWheel, bm, WheelX, WheelY, alpha);

		DrawBitmapWheel(hWnd, hdc, BackWheel, bm, WheelX + Displace, WheelY, alpha);
		break;

	}

	case WM_KEYDOWN: {
		if (wParam == VK_UP) {
			KillTimer(hWnd,1);
			SetTimer(hWnd, 1, frequency-=5, NULL);
			
		}
		else if(wParam == VK_DOWN) {
			KillTimer(hWnd, 1);
			SetTimer(hWnd, 1, frequency += 5, NULL);
		}
		break;
	}
	
	case WM_DESTROY: 
		KillTimer(hWnd, 1);
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break; 
	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
