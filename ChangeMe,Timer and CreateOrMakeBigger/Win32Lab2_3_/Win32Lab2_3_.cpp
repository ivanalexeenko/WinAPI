#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include<windows.h>
#include <string>
#include <iostream>
#include<vector>
#include<deque>
#include<array>
using namespace std;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Создание окна Windows";
class Circle {
public:
	RECT Rect;
	Circle() {
		Rect.left = 0;
		Rect.top = 0;
		Rect.right = 0;
		Rect.bottom = 0;
	}
	Circle(int l, int t, int r, int b) {
		Rect.left = l;
		Rect.top = t;
		Rect.right = r;
		Rect.bottom = b;
	}
	Circle(const RECT&Rec) {
		Rect = Rec;
	}
	Circle(int x, int y, int Radius) {
		Rect.left = x - Radius;
		Rect.top = y - Radius;
		Rect.right = x + Radius;
		Rect.bottom = y + Radius;
	}
	RECT ReturnRect() {
		return this->Rect;
	}
	Circle ChangeCircle(int x,int y,int Radius,int PlusSize) {
		Rect.left = x - (Radius+PlusSize);
		Rect.top = y - (Radius+PlusSize);
		Rect.right = x + (Radius+PlusSize);
		Rect.bottom = y +( Radius+PlusSize);
		return *this;
	}
	int CenterX() {
		return (Rect.left +(Rect.right - Rect.left) / 2);
	}
	int CenterY() {
		return (Rect.top+(Rect.bottom - Rect.top) / 2);
	}
	~Circle() {};
};
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
HBRUSH BG = CreateSolidBrush(RGB(128, 255, 0));
static int FontSize = 70;
const int CircleRadius = 40;
static int CR_2 = CircleRadius;
static int RadGreater = 5;
HFONT hFont = CreateFont(FontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
	CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Infinite Stroke"));
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	static HDC hdc;
	PAINTSTRUCT ps;
	static RECT Rect;
	static RECT SizeRect;
	static Circle *Helper;
	static int x, y;
	static int a, b;
	static vector<Circle>vC;
	static int i = 0;
	static BOOL In = FALSE;
	switch (message)
	{
	case WM_CREATE:
	{
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)BG);
		break;
	}
	case WM_LBUTTONDOWN: {
			a = LOWORD(lParam);
			b = HIWORD(lParam);
			for (i =0; i != vC.size(); i++) {
				if (a >= vC[i].ReturnRect().left && a <= vC[i].ReturnRect().right &&  b >= vC[i].ReturnRect().top && b <= vC[i]. ReturnRect().bottom) {
					In = TRUE;
					break;
				}
			}
			
		break;
	}
	case WM_LBUTTONUP: {
		hdc = GetDC(hWnd);
			if (In) {
			
				//vC[i].ChangeCircle(vC[i].CenterX(), vC[i].CenterY(), CircleRadius, RadGreater);
				vC[i].Rect.left -= RadGreater;
				vC[i].Rect.top -= RadGreater;
				vC[i].Rect.right += RadGreater;
				vC[i].Rect.bottom += RadGreater;


				InvalidateRect(hWnd, NULL, TRUE);
				Ellipse(hdc, vC[i].ReturnRect().left, vC[i].ReturnRect().top, vC[i].ReturnRect().right, vC[i].ReturnRect().bottom);
				In = FALSE;
				ReleaseDC(hWnd, hdc);
				break;
			}
			else {
				
				Ellipse(hdc, a-CR_2, b-CR_2,a+CR_2, b+CR_2);
				SizeRect.left = a - CR_2;
				SizeRect.top = b - CR_2;
				SizeRect.right = a + CR_2;
				SizeRect.bottom = b + CR_2;

				Helper = new Circle(SizeRect);
				vC.push_back(*Helper);
				ReleaseDC(hWnd, hdc);
				break;
			}
		
		break;
	}

	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);

		GetClientRect(hWnd, &Rect);
		x = Rect.right - Rect.left;
		y = Rect.bottom - Rect.top;
				
		for (i=0 ; i != vC.size(); i++) {
			Ellipse(hdc, vC[i].ReturnRect().left, vC[i].ReturnRect().top, vC[i].ReturnRect().right, vC[i].ReturnRect().bottom);
		}
		EndPaint(hWnd, &ps);
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
