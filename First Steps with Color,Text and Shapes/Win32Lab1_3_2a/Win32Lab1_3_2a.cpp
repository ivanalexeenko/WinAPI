#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include<windows.h>
#include<cmath>
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT Rect1, Rect2, Rect3, Rect4;

	static RECT RectForDrawing;
	static double ClientX, ClientY;
	double a, b;
	HPEN EllipseHpen = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
	HPEN PiePen = CreatePen(PS_DASH, 5, RGB(0, 0, 255));
	HBRUSH PieBrush = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH RectangleHbrush = CreateSolidBrush(RGB(255,0,0));
	HBRUSH BG = CreateSolidBrush(RGB(0, 206 ,209));
	HFONT hFont; 

	switch (message)
	{
	case WM_CREATE:
	{
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)BG); // Changing Background color ;
		break; 
	}
	case WM_SIZE:
	{
		ClientX = LOWORD(lParam);
		ClientY = HIWORD(lParam);
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		hFont = CreateFont(60, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Parry Hotter"));
		SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);
		SetBkColor(hdc, RGB(0, 255, 255));
		a = ClientX / 2;
		b = ClientY / 2;
		// Coordinates System ;
		MoveToEx(hdc, 0, b, NULL);
		LineTo(hdc, ClientX, b);
		MoveToEx(hdc, a, 0, NULL);
		LineTo(hdc, a, ClientY);
		// Drawing Ellipse ;
		SelectObject(hdc, EllipseHpen);
		SelectObject(hdc, CreateSolidBrush(RGB(255, 106, 180)));
		Ellipse(hdc, a / 6, b / 6, a / 1.25, b / 1.5);
		Rect1.right = a;
		Rect1.bottom = b / 1.2;
		SetTextColor(hdc, RGB(255, 0, 0));
		DeleteObject(EllipseHpen);

		DrawText(hdc, "THIS IS ELLIPSE!!!", strlen("THIS IS ELLIPSE!!!"), &Rect1, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
		// Drawing Rectangle ;

		Rectangle(hdc, a*1.1, b / 7, a * 1.9, b / 1.4);
		RectForDrawing.left = a*1.1;
		RectForDrawing.top = b / 7;
		RectForDrawing.right = a*1.9;
		RectForDrawing.bottom = b / 1.4;

		FillRect(hdc, &RectForDrawing, RectangleHbrush);
		SetTextColor(hdc, RGB(0, 0, 255));
		Rect2.right = a * 2;
		Rect2.bottom = b / 1.1;
		Rect2.left = a;
		Rect2.top = 0;
		DrawText(hdc, "THIS IS RECTANGLE!!!", strlen("THIS IS RECTANGLE!!!"), &Rect2, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
		//Drawing Pie ;
		SelectObject(hdc, PiePen);
		SelectObject(hdc, PieBrush);

		Pie(hdc, 0, b*1.1, a / 1.1, b * 2, a / 1.1, b*1.55, a*1.5, b * 2 / 3);
		Rect3.right = a;
		Rect3.bottom = b*1.9;
		Rect3.left = 0;
		Rect3.top = b;
		SetTextColor(hdc, RGB(255, 0, 255));
		DrawText(hdc, "THIS IS A PIE!!!", strlen("THIS IS A PIE!!!"), &Rect3, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
		DeleteObject(PiePen);
		DeleteObject(PieBrush);
		// Drawing Diamond ;
		SelectObject(hdc, CreatePen(PS_SOLID, 7, RGB(75, 0, 130)));
		SelectObject(hdc, CreateSolidBrush(RGB(127, 255, 215)));
		const POINT PolyCord[4] = { { a*1.25,b*1.5 },{ a*1.5,b*1.2 },{ a*1.75, b*1.5 },{ a*1.5,b*1.8 } };
		Polygon(hdc, PolyCord, 4);


		SetTextColor(hdc, RGB(0, 100, 0));
		Rect4.right = a * 2;
		Rect4.bottom = b*1.9;
		Rect4.left = a;
		Rect4.top = b;
		DrawText(hdc, "THIS IS DIAMOND!!!", strlen("THIS IS DIAMOND!!!"), &Rect4, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
		DeleteObject( hFont);
		EndPaint(hWnd, &ps);
		break; 
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break; 
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}