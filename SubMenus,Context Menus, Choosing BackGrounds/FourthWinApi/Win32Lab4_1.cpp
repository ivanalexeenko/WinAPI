#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include<windows.h>
#include "resource.h"
#include<vector>
using namespace std;
HBRUSH HBBG;
HBITMAP BG1;
HBITMAP BG2;
HBITMAP BG3;
HWND hWnd;
int Width_1 = 3;
int Width_2 = 3;
int Width_3 = 3;

const int W1 = Width_1;
const int W2 = Width_2;
const int W3 = Width_3;

BOOL CALLBACK Param(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK About(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
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
	Circle(int x1, int y1, int rad, COLORREF col) {
		x = x1;
		y = y1;
		radius = rad;
		color = col;
	}

};
void DrawCircle(HDC hdc, Circle C, HBRUSH FirstCircle,int W) {
	SelectObject(hdc, CreatePen(10, W, RGB(51, 255, 153)));
	SelectObject(hdc, FirstCircle);
	Ellipse(hdc, C.x - C.radius, C.y - C.radius, C.x + C.radius, C.y + C.radius);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	if (!hPrevInstance)
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
		wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
		wc.lpszClassName = szClassName;
		if (!RegisterClass(&wc))
			return (FALSE);
	}

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

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateAccelerator(hWnd, hAccel, &msg);
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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
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

BOOL CALLBACK About(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HWND hWnd;
	static HDC hdc;
	static RECT Rect;
	static PAINTSTRUCT ps;
	switch (msg) {
	case WM_INITDIALOG:
	{
		return FALSE;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDOK:
		{
			EndDialog(hDlg, 0);
			return TRUE;
		}
		
		
		}

		

	}
	case WM_DESTROY:
	{
		EndDialog(hDlg, 0);
		return TRUE;
	}

	}
	return FALSE;
}

BOOL CALLBACK Param(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	
	static HDC hdc;
	static RECT Rect;
	static PAINTSTRUCT ps;
	switch (msg) {
	case WM_INITDIALOG:
	{
		hdc = GetDC(hDlg);
		return FALSE;
	}

	case WM_COMMAND:
	{
		hdc = GetDC(hDlg);
		switch (LOWORD(wParam)) {
		case IDOK:
		{
			EndDialog(hDlg, 0);
			return TRUE;
		}
		case IDC_PARISBUTTON: {
			DeleteObject(HBBG);
			HBBG = CreatePatternBrush(BG1);
			return TRUE;
		}
		case IDC_BUTTONLONDON: 
		{
			DeleteObject(HBBG);
			HBBG = CreatePatternBrush(BG2);
			return TRUE;
		}
		case IDC_MINSKBUTTON:
		{
			DeleteObject(HBBG);
			HBBG = CreatePatternBrush(BG3);
			return TRUE;
		}
		case IDC_SMALL:
		{
			Width_1=3;
			Width_2=3;
			Width_3=3;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case IDC_MEDIUM:
		{
			Width_1 = 10;
			Width_2 = 10;
			Width_3 = 10;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case IDC_LARGE:
		{
			Width_1 = 20;
			Width_2 = 20;
			Width_3 = 20;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}


		break;
		}

		break;

	}
	case WM_DESTROY:
	{
		EndDialog(hDlg, 0);
		return TRUE;
	}

	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	PAINTSTRUCT ps;
	static RECT Rect;
	static int x, y;
	
	static const int MinRadius = 20;
	static const int RadChanger = 10;
	static const int MaxRadius = 120;
	static int a, b;
	BOOL In = TRUE;
	static HMENU hMenu;
	static HINSTANCE hInstance;
	static HBRUSH FirstCircle;
	static HBRUSH SecondCircle;
	static HBRUSH ThirdCircle;
	static int Num_of_Check = 0;
	POINT point;

	
	switch (message)
	{
	case WM_CREATE: {
		GetClientRect(hWnd, &Rect);
		SetTimer(hWnd, 1, 50, NULL);
		
		

		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU));
		hMenu = GetMenu(hWnd);
		hMenu = GetSubMenu(hMenu, 0);
		BG1 = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_PARIS));
		BG2= LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_BG));
		BG3 = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_MINSK));
		HBBG = CreateSolidBrush(RGB(0,0,0));
		
		if (In == TRUE) {
			vB.push_back(FALSE);
			vB.push_back(FALSE);
			vB.push_back(FALSE);
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
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)HBBG);
		x = Rect.right;
		y = Rect.bottom;

		SelectObject(hdc, CreatePen(10, 7, RGB(0, 0, 0)));

		DrawCircle(hdc, vC[0], FirstCircle,Width_1);
		DrawCircle(hdc, vC[1], SecondCircle,Width_2);
		DrawCircle(hdc, vC[2], ThirdCircle,Width_3);

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
			if (ab == (COLORREF)(vC[i].color)) {
				if (i == 2) {
					CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHAQUA, MF_BYCOMMAND | MF_CHECKED);
					Num_of_Check++;
					vB[i] = TRUE;
				}
				if (i == 1) {
					CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHRED, MF_BYCOMMAND | MF_CHECKED);
					Num_of_Check++;
					vB[i] = TRUE;
				}
				if (i == 0) {
					Num_of_Check++;
					CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHBLUE, MF_BYCOMMAND | MF_CHECKED);
					vB[i] = TRUE;
				}
				if (Num_of_Check == 3) {
					CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_CHECKED);
				}

			}


		}


		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_RBUTTONDOWN: {
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		ClientToScreen(hWnd, &point);
		TrackPopupMenu(hMenu, 0, point.x, point.y, 0, hWnd, NULL);



	
		break;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case ID_COMMANDS_LAUNCH:
		{
			if (GetMenuState(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND) == MF_UNCHECKED)
			{
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND |MF_CHECKED);
				
				 for (int i = 0; i < 3; i++) 
				 vB[i] = TRUE;
				 CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHAQUA, MF_BYCOMMAND | MF_CHECKED);

				 CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHRED, MF_BYCOMMAND | MF_CHECKED);

				 CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHBLUE, MF_BYCOMMAND | MF_CHECKED);
			}
			else  {
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHAQUA, MF_BYCOMMAND | MF_UNCHECKED);

				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHRED, MF_BYCOMMAND | MF_UNCHECKED);

				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHBLUE, MF_BYCOMMAND | MF_UNCHECKED);
				for (int i = 0; i < 3; i++)
				vB[i] = FALSE;
			}
			
			
			
		
			
			break;
		}
		case ID_COMMANDS_LAUNCHAQUA:
		{
			if (GetMenuState(hMenu, ID_COMMANDS_LAUNCHAQUA, MF_BYCOMMAND) == MF_UNCHECKED)
			{
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHAQUA, MF_BYCOMMAND | MF_CHECKED);
				Num_of_Check++;
				if (Num_of_Check == 3) {
					CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_CHECKED);
				}
				else CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_UNCHECKED);
				vB[2] = TRUE;
			}
			else 
			{
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHAQUA, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_UNCHECKED);
				Num_of_Check--;
				vB[2] = FALSE;
			}
			
			break;
		}
		case ID_COMMANDS_LAUNCHBLUE:
		{
			if (GetMenuState(hMenu, ID_COMMANDS_LAUNCHBLUE, MF_BYCOMMAND) == MF_UNCHECKED)
			{
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHBLUE, MF_BYCOMMAND | MF_CHECKED);
				Num_of_Check++;
				if (Num_of_Check == 3) {
					CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_CHECKED);
				}
				else CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_UNCHECKED);
				vB[0] = TRUE;
			}
			else
			{
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHBLUE, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_UNCHECKED);
				Num_of_Check--;
				vB[0] = FALSE;
			}
			break;
		}
		case ID_COMMANDS_LAUNCHRED: 
		{
			if (GetMenuState(hMenu, ID_COMMANDS_LAUNCHRED, MF_BYCOMMAND) == MF_UNCHECKED)
			{
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHRED, MF_BYCOMMAND | MF_CHECKED);
				Num_of_Check++;
				if (Num_of_Check == 3) {
					CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_CHECKED);
				}
				else CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_UNCHECKED);
				vB[1] = TRUE;
			}
			else
			{
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHRED, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_UNCHECKED);
				Num_of_Check--;
				vB[1] = FALSE;
			}

			break;
		}
		case ID_SETBACKGROUND_LONDON:
		{
			DeleteObject(HBBG);
			HBBG = CreatePatternBrush(BG2);
			break;
		}
		case ID_SETBACKGROUND_PARIS:
		{
			DeleteObject(HBBG);
			HBBG = CreatePatternBrush(BG1);
			break;
		}
		case ID_SETBACKGROUND_MINSK:
		{
			DeleteObject(HBBG);
			HBBG = CreatePatternBrush(BG3);
			break;
		}
		case ID_ACCELERATOR4: 
		{
			for (int i = 0; i < 3;i++) {
				vB[i] = FALSE;
			}
			CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHAQUA, MF_BYCOMMAND | MF_UNCHECKED);

			CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHRED, MF_BYCOMMAND | MF_UNCHECKED);

			CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHBLUE, MF_BYCOMMAND | MF_UNCHECKED);

			break;
		}
		case ID_ACCELERATOR1:
		{
			Width_1++;
			InvalidateRect(hWnd, NULL,TRUE) ;
			break;
		}
		case ID_ACCELERATOR2:
		{
			Width_2++;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case ID_ACCELERATOR3:
		{
			Width_3++;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		case ID_REFRESH:
		{
			Width_1= W1;
			Width_2 = W2;
			Width_3=W3;
			for (int i = 0; i < 3; i++) {
				vB[i] = FALSE;
			}
			CheckMenuItem(hMenu, ID_COMMANDS_LAUNCH, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHAQUA, MF_BYCOMMAND | MF_UNCHECKED);

			CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHRED, MF_BYCOMMAND | MF_UNCHECKED);

			CheckMenuItem(hMenu, ID_COMMANDS_LAUNCHBLUE, MF_BYCOMMAND | MF_UNCHECKED);
			for(int i=0;i<3;i++)
			{
				vC[i].radius = MinRadius;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			

			break;
		}
		case ID_INFO_INFORMATION:
		{
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUT), hWnd, About);
			break;
		}
		case ID_PARAMETERS_CHOOSEPARAMETERS:
		{
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_PARAM), hWnd, Param);
			break;
		}

		
		break;
		}
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


