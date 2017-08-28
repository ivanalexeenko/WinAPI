#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include<windows.h>
#include"resource.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "London Streets Traffic Lighter";
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
void DrawLighter(HDC hdc,HBRUSH BrushLighter,int x,int y,int a,int b) {
	SelectObject(hdc, BrushLighter);
	Rectangle(hdc, a - x / 12, b - y / 2.5, a + x / 12, b + y / 2.6);

	SelectObject(hdc, CreateSolidBrush(RGB(128, 0, 0)));
	Ellipse(hdc, a - x / 12, b - y / 2.5, a + x / 12, b - y / 8);

	SelectObject(hdc, CreateSolidBrush(RGB(153, 153, 0)));
	Ellipse(hdc, a - x / 12, b - y / 8, a + x / 12, b + y / 8);

	SelectObject(hdc, CreateSolidBrush(RGB(0, 100, 0)));
	Ellipse(hdc, a - x / 12, b + y / 8, a + x / 12, b + y / 2.6);
}
void RedON(HDC hdc,int x,int y,int a,int b) {
	SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
	Ellipse(hdc, a - x / 12, b - y / 2.5, a + x / 12, b - y / 8);

}
void YellowON(HDC hdc,int x,int y,int a,int b) {
	SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 0)));
	Ellipse(hdc, a - x / 12, b - y / 8, a + x / 12, b + y / 8);
}
void GreenON(HDC hdc,int x,int y,int a,int b) {
	SelectObject(hdc, CreateSolidBrush(RGB(0, 255, 0)));
	Ellipse(hdc, a - x / 12, b + y / 8, a + x / 12, b + y / 2.6);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	PAINTSTRUCT ps;
	static RECT Rect;
	static int x, y;
	static int a, b;
	static int lightswitcher = 0;
	HBITMAP BackGround;
	HBITMAP Lighter;
	static HBRUSH BrushLighter;
	static HBRUSH BrushBackGround;
	switch (message)
	{
	case WM_CREATE: {
		hdc = GetDC(hWnd);

		BackGround = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_TOP));
		BrushBackGround = CreatePatternBrush(BackGround);
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)BrushBackGround);

		Lighter = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_LIGHTER));
		BrushLighter = CreatePatternBrush(Lighter);
		SetTimer(hWnd, 1, 1000, NULL);
		break;

	}
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &Rect);
		x = Rect.right;
		y = Rect.bottom;
		a = (Rect.right - Rect.left) / 2;
		b = (Rect.bottom - Rect.top) / 2;
		SelectObject(hdc, CreatePen(1, 7, RGB(0,0,0)));
		DrawLighter(hdc, BrushLighter, x, y, a, b);

		if (lightswitcher == 1) {
			DrawLighter(hdc, BrushLighter, x, y, a, b);
			RedON(hdc, x, y, a, b);
		}
		if (lightswitcher == 2) {
			DrawLighter(hdc, BrushLighter, x, y, a, b);
			YellowON(hdc, x, y, a, b);
		}
		if (lightswitcher == 3) {
			DrawLighter(hdc, BrushLighter, x, y, a, b);
			GreenON(hdc, x, y, a, b);

		}
		if (lightswitcher == 4) {
			DrawLighter(hdc, BrushLighter, x, y, a, b);
			YellowON(hdc, x, y, a, b);
			lightswitcher = 0;
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER: {
		InvalidateRect(hWnd, &Rect, TRUE);
		lightswitcher++;
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