#define _CRT_SECURE_NO_WARNINGS
#define IdHOT WM_USER+1
#undef UNICODE
#include<windows.h>
#include <string>
#include <iostream>
#include "stdio.h"
using namespace std;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Создание окна Windows";
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
HBRUSH BG = CreateSolidBrush(RGB(0, 128, 255));
static int FontSize = 400;

BOOL MinusPick=FALSE;
HFONT hFont = CreateFont(FontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
	CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Infinite Stroke"));
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	static HDC hdc;
	PAINTSTRUCT ps;
	static RECT Rect;
	int x, y;
	static int t=0;
	switch (message)
	{
	case WM_CHAR:
	{
		switch (wParam) {
		case '-': {
			MinusPick = TRUE;
			KillTimer(hWnd, 1);
			break;
		}
		case '+':{
			if (MinusPick) {
				SetTimer(hWnd, 1, 1000, NULL);
				MinusPick = FALSE;
			}
			

		break;
		}
		 
		}
		break;
	}
	case WM_CREATE:
	{
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)BG); // Changing Background color ;
		SetTimer(hWnd, 1, 1000, NULL);
		RegisterHotKey(hWnd, IdHOT, MOD_CONTROL, 'S');
		break;
	}
	case WM_HOTKEY: {
		if (IdHOT == (int)wParam) {
			KillTimer(hWnd, IdHOT);
			
			SetTimer(hWnd, 1, 1000, NULL);
			t = -1;
		}
		break;
	}

	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);

		GetClientRect(hWnd, &Rect);
		x = Rect.right - Rect.left;
		y = Rect.bottom - Rect.top;
		SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(255, 255, 0));
		SelectObject(hdc, CreateSolidBrush(RGB(255,255,153)));
		Ellipse(hdc, x / 3, y / 4, x / 1.5, y / 1.2);
		SetTextColor(hdc, RGB(255, 0, 0));

		TCHAR buffer[10];
		sprintf(buffer, TEXT("%d"), t);
		DrawText(hdc, buffer, -1, &Rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		EndPaint(hWnd, &ps);
		break;
	}
	
	case WM_TIMER: {
		t++;
		InvalidateRect(hWnd, NULL, TRUE);

		break;

	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}