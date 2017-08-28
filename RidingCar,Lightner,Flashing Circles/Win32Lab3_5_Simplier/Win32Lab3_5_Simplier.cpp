#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#undef UNICODE
#define PI 3.1415926535

#include<windows.h>
#include <stdio.h>
#include <cmath>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Sinusal Ball Movement";
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
void DrawBitmapBall(HWND hWnd, HDC hdc, HBITMAP hBmp, BITMAP bm, float x, float y, int alpha) {
	XFORM xForm;
	HRGN hRgn;
	HDC hWheelMemDC = CreateCompatibleDC(hdc);
	SelectObject(hWheelMemDC, hBmp);

	hRgn = CreateEllipticRgn(x, y, x + bm.bmWidth, y + bm.bmHeight);
	SelectClipRgn(hdc, hRgn);

	xForm.eM11 = (FLOAT)cos(alpha * 2 * (PI) / 360);
	xForm.eM12 = (FLOAT)sin(alpha * 2 * (PI) / 360);
	xForm.eM21 = (FLOAT)-sin(alpha * 2 * (PI) / 360);
	xForm.eM22 = (FLOAT)cos(alpha * 2 * (PI) / 360);
	xForm.eDx = x + bm.bmWidth / 2;
	xForm.eDy = y + bm.bmHeight / 2;

	SaveDC(hdc);
	BOOL ret = SetWorldTransform(hdc, &xForm);
	BitBlt(hdc, -bm.bmWidth / 2, -bm.bmHeight / 2, bm.bmWidth, bm.bmHeight, hWheelMemDC, 0, 0, SRCCOPY);
	RestoreDC(hdc, -1);
	SelectClipRgn(hdc, NULL);
	DeleteObject(hRgn);
	DeleteObject(hWheelMemDC);
}

int j = 0;
const int NUM = 120;
POINT apt[NUM];
POINT DrawSinusGraph(HDC hdc, int x, int y, BITMAP bm, POINT *apt, const int NUM) {
	MoveToEx(hdc, 0, y / 2, NULL);
	LineTo(hdc, x, y / 2);
	MoveToEx(hdc, x / 2, 0, NULL);
	LineTo(hdc, x / 2, y);


	for (int i = 0; i <= NUM; i++) {
		apt[i].x = i*x / NUM;
		apt[i].y = (((y / 2)* (1 - sin((2 * PI*i) / NUM))))*(y - bm.bmHeight) / y + bm.bmHeight / 2;

	}
	Polyline(hdc, apt, NUM);
	return *apt;
}
void DrawBigPoint(HDC hdc, int x, int y, BITMAP bm) {
	SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
	Ellipse(hdc, x - bm.bmWidth + 20, y - bm.bmHeight + 20, x + bm.bmWidth - 20, y + bm.bmHeight - 20);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	PAINTSTRUCT ps;
	static int x, y;
	static RECT Rect;
	static HBITMAP BG;
	static HBRUSH HBBG;
	static HBITMAP Ball;
	static BITMAP bm;
	static int alpha;
	static int dx, dy;
	static int WheelX, WheelY;
	static RECT BallRect;
	static HPEN hpen;

	switch (message)
	{
	case WM_CREATE: {
	
		HBBG = CreateSolidBrush(RGB(153,255,153));
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)HBBG);

		break;
	}
	case WM_PAINT: {
		hdc = GetDC(hWnd);
		GetClientRect(hWnd, &Rect);

		x = Rect.right;
		y = Rect.bottom;

		hdc = BeginPaint(hWnd, &ps);
		
		WheelX = apt[j].x;
		WheelY = apt[j].y - 120;
		SetTimer(hWnd, 1, 50, NULL);

		hpen = CreatePen(10, 5, RGB(0, 0, 0));
		SelectObject(hdc, hpen);
		SetRect(&BallRect, (int)WheelX, (int)WheelY, (int)WheelX + bm.bmWidth, (int)WheelY + bm.bmHeight);
		FillRect(hdc, &BallRect, HBBG);


		alpha += 10;
		if (alpha > 360) alpha = 0;

		DrawBitmapBall(hWnd, hdc, Ball, bm, WheelX, WheelY, alpha);
		SelectObject(hdc, hpen);

		DrawSinusGraph(hdc, x, y, bm, apt, NUM);

		if (j == NUM) {
			j = 0;

		}
		j++;


		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER: {
		InvalidateRect(hWnd, NULL, TRUE);
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