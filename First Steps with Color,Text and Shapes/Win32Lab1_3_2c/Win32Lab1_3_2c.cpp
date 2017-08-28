#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#include<windows.h>
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
void DrawWeekColumn(HDC hdc,int x,int y) {
	Rectangle(hdc, 0, y / 9, x, y);
	Rectangle(hdc, 0, y / 9, x / 20, y);
	Rectangle(hdc, 0, y / 9, x / 20, y / 4);
	Rectangle(hdc, 0, y / 4, x / 20, y / 2.7);
	Rectangle(hdc, 0, y / 2.7, x / 20, y / 2);
	Rectangle(hdc, 0, y / 2, x / 20, y / 1.6);
	Rectangle(hdc, 0, y / 1.6, x / 20, y / 1.3);
	Rectangle(hdc, 0, y / 1.3, x / 20, y / 1.1);
}
RECT ChangeRectParam(RECT Rect, int l, int t, int r, int b) {
	Rect.left = l;
	Rect.top = t;
	Rect.right = r;
	Rect.bottom = b;
	return Rect;
}
void FillWeekColumn(HDC hdc, int x, int y, RECT Week) {
	Week = ChangeRectParam(Week, 0, y / 9, x / 20, y / 4 + 35);
	DrawText(hdc, "Mon", -1, &Week, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	Week = ChangeRectParam(Week, 0, y / 4, x / 20, y / 2.7 + 25);
	DrawText(hdc, "Tue", -1, &Week, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	Week = ChangeRectParam(Week, 0, y / 4, x / 20, y / 2 + 40);
	DrawText(hdc, "Wed", -1, &Week, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	Week = ChangeRectParam(Week, 0, y / 4, x / 20, y / 1.6 + 35);
	DrawText(hdc, "Thu", -1, &Week, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	Week = ChangeRectParam(Week, 0, y / 4, x / 20, y / 1.3 + 20);
	DrawText(hdc, "Fri", -1, &Week, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	Week = ChangeRectParam(Week, 0, y / 4, x / 20, y / 1.1 + 20);
	DrawText(hdc, "Sat", -1, &Week, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);

}
LOGFONT CreateInclinedFont(int esc) {
	static LOGFONT Dayz;
	Dayz.lfCharSet = DEFAULT_CHARSET;
	Dayz.lfPitchAndFamily = DEFAULT_PITCH;
	strcpy(Dayz.lfFaceName, "Infinite Stroke");
	Dayz.lfHeight = 60;
	Dayz.lfWeight = FW_NORMAL;
	Dayz.lfEscapement = esc;
	return Dayz;
}
void DrawScheduleLines(HDC hdc, int x, int y) {
	MoveToEx(hdc, 0, y / 4, NULL);
	LineTo(hdc, x, y / 4);
	MoveToEx(hdc, 0, y / 2.7, NULL);
	LineTo(hdc, x, y / 2.7);
	MoveToEx(hdc, 0, y / 2, NULL);
	LineTo(hdc, x, y / 2);
	MoveToEx(hdc, 0, y / 1.6, NULL);
	LineTo(hdc, x, y / 1.6);
	MoveToEx(hdc, 0, y / 1.3, NULL);
	LineTo(hdc, x, y / 1.3);
	MoveToEx(hdc, 0, y / 1.1, NULL);
	LineTo(hdc, x, y / 1.1);
	MoveToEx(hdc, x / 3.9, y / 9, NULL);
	LineTo(hdc, x / 3.9, y);
	MoveToEx(hdc, x / 2.2, y / 9, NULL);
	LineTo(hdc, x / 2.2, y);
	MoveToEx(hdc, x / 1.5, y / 9, NULL);
	LineTo(hdc, x / 1.5, y);
	MoveToEx(hdc, x / 1.2, y / 9, NULL);
	LineTo(hdc, x / 1.2, y);
}
void FillScheduleData(HDC hdc,int x,int y,HFONT FontForSubj,RECT Week,HBRUSH HeadBrush) {
	// Monday ;
	Rectangle(hdc, x / 20, y / 9, x / 3.9, y / 4);
	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, FontForSubj);

	Week = ChangeRectParam(Week, x / 20, y / 9, x / 3.9, y / 4);
	DrawText(hdc, "GA(lecture) 521", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 3.9, y / 9, x / 2.25, y / 4);
	DrawText(hdc, "MA(practice) 520", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 2.25, y / 9, x / 1.5, y / 4);
	DrawText(hdc, "GA(practice) 517", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	SelectObject(hdc, CreateSolidBrush(RGB(0, 255, 102)));
	Rectangle(hdc, x / 1.5, y / 9, x / 1.2, y / 4);
	Week = ChangeRectParam(Week, x / 1.5, y / 9, x / 1.2, y / 4);
	DrawText(hdc, "MA(extra) ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.2, y / 9, x, y / 4);
	DrawText(hdc, "--------- ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	// Tuesday ;
	SelectObject(hdc, HeadBrush);
	Rectangle(hdc, x / 20, y / 4, x / 3.9, y / 2.7);
	Week = ChangeRectParam(Week, x / 20, y / 4, x / 3.9, y / 2.7);
	DrawText(hdc, "MA(lecture) 605", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 3.9, y / 4, x / 2.25, y / 2.7);
	DrawText(hdc, "English 255a/b", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 2.25, y / 4, x / 1.5, y / 2.7);
	DrawText(hdc, "GA(practice) 517", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	SelectObject(hdc, CreateSolidBrush(RGB(0, 255, 102)));
	Rectangle(hdc, x / 1.5, y / 4, x / 1.2, y / 2.7);
	Rectangle(hdc, x / 1.2, y / 4, x, y / 2.7);
	Week = ChangeRectParam(Week, x / 1.5, y / 4, x / 1.2, y / 2.7);
	DrawText(hdc, "English(extra)", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.2, y / 4, x, y / 2.7);
	DrawText(hdc, "GA(extra)", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	// Wednesday ;
	SelectObject(hdc, HeadBrush);
	Rectangle(hdc, x / 20, y / 2.7, x / 3.9, y / 2);
	Week = ChangeRectParam(Week, x / 20, y / 2.7, x / 3.9, y / 2);
	DrawText(hdc, "Proga(lecture)521 ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 3.9, y / 2.7, x / 2.25, y / 2);
	DrawText(hdc, "Proga(practice)314 ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 2.25, y / 2.7, x / 1.5, y / 2);
	DrawText(hdc, "Proga(practice)334 ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.5, y / 2.7, x / 1.2, y / 2);
	DrawText(hdc, "PE ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.2, y / 2.7, x, y / 2);
	DrawText(hdc, "--------- ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	// Thursday ;
	Week = ChangeRectParam(Week, x / 20, y / 2.2, x / 3.9, y / 1.5);
	DrawText(hdc, "MA(practice)234", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Rectangle(hdc, x / 3.9, y / 2, x / 2.2, y / 1.6);
	Week = ChangeRectParam(Week, x / 3.9, y / 2, x / 2.2, y / 1.6);
	DrawText(hdc, "GA(lecture)521 ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Rectangle(hdc, x / 2.2, y / 2, x / 1.5, y / 1.6);
	Week = ChangeRectParam(Week, x / 2.2, y / 2, x / 1.5, y / 1.6);
	DrawText(hdc, "DMML(lecture)521 ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.5, y / 2, x / 1.2, y / 1.6);
	DrawText(hdc, "DMML (240) ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.2, y / 2, x, y / 1.6);
	DrawText(hdc, "--------- ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	// Friday ;
	Rectangle(hdc, x / 20, y / 1.6, x / 3.9, y / 1.3);
	Week = ChangeRectParam(Week, x / 20, y / 1.6, x / 3.9, y / 1.3);
	DrawText(hdc, "MA(lecture)605", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 3.9, y / 1.6, x / 2.25, y / 1.3);
	DrawText(hdc, "English 255a/b", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 2.25, y / 1.6, x / 1.5, y / 1.3);
	DrawText(hdc, "SP Proga 508", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.5, y / 1.6, x / 1.2, y / 1.3);
	DrawText(hdc, "PE", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.2, y / 1.6, x, y / 1.3);
	DrawText(hdc, "--------- ", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	// Saturday ;
	Rectangle(hdc, x / 20, y / 1.3, x / 3.9, y / 1.1);
	Week = ChangeRectParam(Week, x / 20, y / 1.3, x / 3.9, y / 1.1);
	DrawText(hdc, "Proga(lecture)521", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 3.9, y / 1.3, x / 2.25, y / 1.1);
	DrawText(hdc, "Proga(practice)508", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 2.25, y / 1.3, x / 1.5, y / 1.1);
	DrawText(hdc, "---------", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.5, y / 1.3, x / 1.2, y / 1.1);
	DrawText(hdc, "---------", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.2, y / 1.3, x, y / 1.1);
	DrawText(hdc, "---------", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

}
void FillTimeData(HDC hdc,int x,int y,RECT Week) {
	SetTextColor(hdc, RGB(255, 255, 255));
	Week = ChangeRectParam(Week, x / 20, y / 1.1, x / 3.9, y);
	DrawText(hdc, "8:15-9:35", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 3.9, y / 1.1, x / 2.25, y);
	DrawText(hdc, "9:45-11:05", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 2.25, y / 1.1, x / 1.5, y);
	DrawText(hdc, "11:15-12:35", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.5, y / 1.1, x / 1.2, y);
	DrawText(hdc, "13:00-14:20", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	Week = ChangeRectParam(Week, x / 1.2, y / 1.1, x, y);
	DrawText(hdc, "14:30-15:50", -1, &Week, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, hcompdc;
	PAINTSTRUCT ps;
	static RECT Rect;
	static RECT Week;
	HBRUSH BG = CreateSolidBrush(RGB(70, 130, 180));
	HBRUSH HeadBrush = CreateSolidBrush(RGB(139,0,0));
	LPCSTR Header = "FAMCS SCHEDULE  2016 / 2017 Volume 2";
	HFONT hFont;
	HFONT FontForSubj;
	HPEN hpen = CreatePen(10, 7, RGB(0, 0, 139));
	static int x, y;
	HANDLE hbitmap, holdbitmap;
	BITMAP bitmap;
	switch (message)
	{
	case WM_CREATE:
	{
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)BG); // Changing Background color ;
		break;
	}
	case WM_SIZE:
	{
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		break;
	}
	
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);

		int esc = 850;

		HFONT WeekFont = CreateFontIndirect(&CreateInclinedFont(esc));

		SetBkMode(hdc, TRANSPARENT);
		hFont = CreateFont(65, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Stranger back in the Night"));
		FontForSubj = CreateFont(60, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Infinite Stroke"));

		Rect = ChangeRectParam(Rect, 0, 0, x, y);

		SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(139, 0, 0));
		DrawText(hdc, Header, strlen(Header), &Rect, DT_CENTER);
		DeleteObject(hFont);
		SelectObject(hdc, FontForSubj);
		SelectObject(hdc, HeadBrush);
		SelectObject(hdc, hpen);

		DrawWeekColumn(hdc, x, y);

		SetTextColor(hdc, RGB(255, 255, 255));
		SelectObject(hdc, WeekFont);

		FillWeekColumn(hdc, x, y, Week);

		DeleteObject(WeekFont);
		HeadBrush = CreateSolidBrush(RGB(255, 255, 102));
		SelectObject(hdc, HeadBrush);

		DrawScheduleLines(hdc, x, y);
		
		FillScheduleData(hdc, x, y, FontForSubj, Week, HeadBrush);
	/*	
		hbitmap = LoadImage(NULL, "с:\\clock.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		GetObject(hbitmap, sizeof(BITMAP), &bitmap);
		hcompdc = CreateCompatibleDC(hdc);
		holdbitmap = SelectObject(hcompdc, hbitmap);
		GetClientRect(hWnd, &Rect);
		StretchBlt(hdc,0,0,Rect.right,Rect.bottom,hcompdc,0,0,bitmap.bmWidth,bitmap.bmHeight,NOTSRCCOPY);
		SelectObject(hcompdc,holdbitmap);
		DeleteObject(hbitmap);
		DeleteDC(hcompdc);
		*/
		DeleteObject(HeadBrush);
		FillTimeData(hdc, x, y, Week);
		SelectObject(hdc,CreateSolidBrush(RGB(255,255,255)));
		SelectObject(hdc, CreatePen(1, 4, RGB(0, 0, 0)));
		Ellipse(hdc, 0, y, x / 20, y / 1.1);
		MoveToEx(hdc,x/40,y/1.04,NULL);
		LineTo(hdc,x/40,y/1.1);
		LineTo(hdc, x / 50, y / 1.09);
		MoveToEx(hdc, x / 40, y / 1.1, NULL);
		LineTo(hdc, x / 33, y / 1.09);
		MoveToEx(hdc, x / 40, y / 1.04, NULL);
		LineTo(hdc, x / 23, y / 1.06);
		LineTo(hdc, x / 25, y / 1.05);
		MoveToEx(hdc, x / 23, y / 1.06, NULL);
		LineTo(hdc, x / 28, y / 1.055);
		EndPaint(hWnd, &ps);
		break; 
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



