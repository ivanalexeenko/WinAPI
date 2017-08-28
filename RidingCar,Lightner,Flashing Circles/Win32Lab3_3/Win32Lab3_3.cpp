#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include<windows.h>
#include "resource.h"
#include<vector>
using namespace std;


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Создание окна Windows";
struct Circle {
	int x;
	int y;
	int radius;
	COLORREF color;
	Circle(int x1,int y1,int rad,COLORREF col) {
		x = x1;
		y = y1;
		radius = rad;
		color = col;
	}

};
void DrawCircle(HDC hdc,Circle C,HBRUSH FirstCircle) {
	SelectObject(hdc, FirstCircle);
	Ellipse(hdc, C.x - C.radius, C.y - C.radius,C.x + C.radius,C.y + C.radius);
}
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
 vector<Circle> vC;
 vector <BOOL>vB;
 Circle*c1, *c2, *c3;
 static COLORREF FromHex(int hex)
 {
	 auto r = (hex & 0xFF0000) >> 16;
	 auto g = (hex & 0x00FF00) >> 8;
	 auto b = (hex & 0x0000FF) >> 0;
	 return RGB(r, g, b);
 }
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	PAINTSTRUCT ps;
	static RECT Rect;
	static int x, y;
	static HBRUSH HBBG;
	static HBITMAP BG;
	static const int MinRadius = 20;
	static const int RadChanger = 10;
	static const int MaxRadius = 120;
	static int a, b;
	BOOL In = TRUE;
	
	
	static HBRUSH FirstCircle;
	static HBRUSH SecondCircle;
	static HBRUSH ThirdCircle;

	switch (message)
	{
	case WM_CREATE: {
		GetClientRect(hWnd, &Rect);
		SetTimer(hWnd, 1, 50, NULL);
		BG = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_BG));
		HBBG = CreatePatternBrush(BG);
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)HBBG);
		if (In == TRUE) {
			for (int i = 0; i < 3; i++) {
				vB.push_back(FALSE);
			}
			
			c1 = new Circle(500, 800, MinRadius, RGB(51, 51, 255));
			vC.push_back(*c1);
			c2 = new Circle(850, 300, MinRadius, RGB(204, 0, 0));
			vC.push_back(*c2);
			c3 = new Circle(200, 450, MinRadius, RGB(0, 255, 255));
			vC.push_back(*c3);
			FirstCircle = CreateSolidBrush(vC[0].color);
			SecondCircle = CreateSolidBrush(vC[1].color);
			ThirdCircle = CreateSolidBrush(vC[2].color);
			In = FALSE;
		}
		break;
	}
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &Rect);
		x = Rect.right;
		y = Rect.bottom;
		
		SelectObject(hdc, CreatePen(10, 7, RGB(0, 0, 0)));
		
		DrawCircle(hdc, vC[0], FirstCircle);
		DrawCircle(hdc, vC[1], SecondCircle);
		DrawCircle(hdc, vC[2], ThirdCircle);

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER: {
		for (int i = 0; i != vC.size(); i++) {
			if (vB[i]) {
				if (vC[i].radius < MaxRadius&&vB[i]) {
					vC[i].radius += RadChanger;

				}
				else if (vC[i].radius >= MaxRadius&&vB[i]) {
					vC[i].radius = MinRadius;
				}
			}
			
		}
		InvalidateRect(hWnd, &Rect, TRUE);
		break;
	}
	case WM_LBUTTONDOWN: {
		hdc = GetDC(hWnd);
		a = LOWORD(lParam);
		b = HIWORD(lParam);
		auto ab = GetPixel(hdc, a, b);
		for (int i = 0; i != vC.size(); i++) {
			if (ab ==(COLORREF) (vC[i].color)) {
				vB[i] = TRUE;
			}
			
			
			}
			
		
		
		InvalidateRect(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_RBUTTONDOWN: {
		hdc = GetDC(hWnd);
		a = LOWORD(lParam);
		b = HIWORD(lParam);
		auto ba = GetPixel(hdc, a, b);
		for (int i = 0; i != vC.size(); i++) {

			if (ba== vC[i].color&&vB[i]==TRUE) {
				vB[i] = FALSE;
			}
			}

		
		InvalidateRect(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hdc);
		break;
	}

		
	case WM_DESTROY: {
		KillTimer(hWnd, 1);
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break; 
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}