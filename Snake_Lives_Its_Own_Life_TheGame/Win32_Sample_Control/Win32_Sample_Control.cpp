#define _CRT_SECURE_NO_WARNINGS
#include"stdafx.h"
#include <string>
#include "Win32_Sample_Control.h"
#include <windows.h>
#include<vector>
#include<fstream>
#include <map>
#include <algorithm>
#include<functional>
#define MAX_LOADSTRING 100
using namespace std;
// Global Variables:
HINSTANCE hInst;                               
WCHAR szTitle[MAX_LOADSTRING];                
WCHAR szWindowClass[MAX_LOADSTRING];       
int Width;
int Height;
int Dim;
int RectSide = 40;
RECT Helper;

LPCWSTR Buffer;
BOOL smth;
HBRUSH SquareColor = CreateSolidBrush(RGB(105, 105, 105));
HBRUSH WormColor = CreateSolidBrush(RGB(255, 0, 0));
HBRUSH BoarderColor= CreateSolidBrush(RGB(0, 0, 0));
HBRUSH TraceColor;
COLORREF Color;
vector<RECT> vR;
vector<RECT> vR_19;
vector <BOOL> Worm;
vector <BOOL> Worm_19;
map<int, int> HistRes;
vector<int> NumStep_11;
vector<int> NumStep_19;
BOOL Init_11 = TRUE;
BOOL Init_19 = TRUE;
int NumberOfMoves_11;
int NumberOfMoves_19;
int Random;
int Mover;
int numberofiter;
BOOL ShouldSave;
ifstream fin("History.txt",std::ios::app);
ofstream fout("History.txt", std::ios::app);
bool InRect(int a,int b,RECT&Rect) {
	if ((a >= Rect.left) && (a <= Rect.right) && (b >= Rect.top) && (b <= Rect.bottom)) return true;
	else return false;
}
void DrawPlaces(HDC hdc,POINT Center,int Space) {
	SetTextColor(hdc, RGB(255, 215, 0));
	TextOut(hdc, Center.x*1.6, Space * 2, L"First Place (Golden)", strlen("First Place (Golden)"));
	SetTextColor(hdc, RGB(192, 192, 192));
	TextOut(hdc, Center.x*1.6, Space * 3, L"Second Place (Silver)", strlen("Second Place (Silver)"));
	SetTextColor(hdc, RGB(205, 127, 50));
	TextOut(hdc, Center.x*1.6, Space * 4, L"Third Place (Bronze)", strlen("Third Place (Bronze)"));
	SetTextColor(hdc, RGB(166, 128, 100));
	TextOut(hdc, Center.x*1.6, Space * 5, L"Fourth Place (Wooden)", strlen("Fourth Place (Wooden)"));
	SetTextColor(hdc, RGB(79, 79, 79));
	TextOut(hdc, Center.x*1.6, Space * 6, L"Fifth Place (Rubber)", strlen("Fifth Place (Rubber)"));
}
void DrawRankings(HDC hdc,POINT Center,int Space,int l,map<int,int>::reverse_iterator i) {
	SetTextColor(hdc, RGB(200, 0, 0));
	TextOut(hdc, Center.x, Space*l, L"Type :", sizeof("Type :"));
	TextOut(hdc, Center.x*1.1, Space*l, to_wstring(i->second).c_str(), strlen(to_string(i->second).c_str()));
	TextOut(hdc, Center.x*1.13, Space*l, L"X", strlen("X"));
	TextOut(hdc, Center.x*1.17, Space*l, to_wstring(i->second).c_str(), strlen(to_string(i->second).c_str()));
	TextOut(hdc, Center.x*1.25, Space*l, L"Number of Steps =", strlen("Number of Steps ="));
	TextOut(hdc, Center.x*1.5, Space*l, to_wstring(i->first).c_str(), strlen(to_string(i->first).c_str()));
};
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Square(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Cells(HWND, UINT, WPARAM,LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32_SAMPLE_CONTROL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32_SAMPLE_CONTROL));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32_SAMPLE_CONTROL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32_SAMPLE_CONTROL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, SW_MAXIMIZE);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static CHOOSECOLOR cc;
	static COLORREF acrCustClr[16];
	static BOOL Move = FALSE;
	static BOOL App = FALSE;
	static HDC hdc;
	static POINT Center;
	static RECT Rect;
	static HFONT hFont;
	static int Space = 60;
	static int WhereToStart;
	static int x;
	static PAINTSTRUCT ps;
	static int y;
	static char buff[50];
	static int a, b;
	static int l = 1;
    switch (message)
    {
	case WM_CREATE:
	{
		SetBkMode(hdc, TRANSPARENT);
		hFont = CreateFont(40, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Infinite Stroke"));
		while(!fin.eof())
		{
			fin >> a >> b;
			HistRes.insert( pair<int,int >(b,a));
		}
		
	
		
		SetTimer(hWnd, 1, 100, NULL);
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hWnd;
		cc.lpCustColors = (LPDWORD)acrCustClr;
		cc.Flags == CC_FULLOPEN | CC_SOLIDCOLOR;
		break;

	}
    case WM_COMMAND:
    {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case ID_PARAMETERS_SETSQUARESIZE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SQUARE), hWnd, Square);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_PARAMETERS_SETSQUARECOLOR:
				if (ChooseColor(&cc) == TRUE)
				{
					Color = cc.rgbResult;
					
				}
				else
				{
					Color = NULL;
				}
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_PARAMETERS_SETCELLSNUMBER:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Cells);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
			break;
        }
	case WM_TIMER:
	{
	
		if (Dim == 11) {
			for (int k = 1; k < Dim; k++) {
				if ((WhereToStart >= 0 && WhereToStart <= Dim - 1) || (WhereToStart >= Dim*Dim - Dim && WhereToStart <= Dim*Dim - 1) || WhereToStart%Dim == 0) {
					Move = FALSE;
					
					
				}
				if (WhereToStart== Dim*k - 1) {
					Move = FALSE;
					
				}
				
			}

			if (App == TRUE&&Move == TRUE) {
				
				Random = rand() % 3 + 1;
				
				if (Random == 1) {
					Worm[WhereToStart += Dim] = TRUE;
					Mover = WhereToStart;
					NumStep_11.push_back(WhereToStart);
				}
				else if (Random == 2) {
					Worm[WhereToStart++] = TRUE;
					Mover = WhereToStart;
					NumStep_11.push_back(WhereToStart);
				}
				else if (Random == 3) {
					Worm[WhereToStart -= Dim] = TRUE;
					Mover = WhereToStart;
					NumStep_11.push_back(WhereToStart);
				}

				
				InvalidateRect(hWnd, NULL, FALSE);
				NumberOfMoves_11++;
			}

		}
		else if (Dim == 19) {
			for (int k = 1; k < Dim; k++) {
				if ((WhereToStart >= 0 && WhereToStart <= Dim - 1) || (WhereToStart >= Dim*Dim - Dim && WhereToStart <= Dim*Dim - 1) || WhereToStart%Dim == 0) {
					Move = FALSE;
				}
				if (WhereToStart == Dim*k - 1) {
					Move = FALSE;
				}
			}
			if (App == TRUE&&Move == TRUE) {
				Random = rand() % 3 + 1;
				if (Random == 1) {
					WhereToStart = Mover - Dim;
					Mover = WhereToStart;
					NumStep_19.push_back(WhereToStart);
				}
				else if (Random == 2) {
					WhereToStart = Mover + 1;
					Mover = WhereToStart;
					NumStep_19.push_back(WhereToStart);
				}
				else if (Random == 3) {
					WhereToStart = Mover + Dim;
					Mover = WhereToStart;
					NumStep_19.push_back(WhereToStart);
				}

				Worm_19[WhereToStart] = TRUE;
				InvalidateRect(hWnd, NULL, FALSE);
				NumberOfMoves_19++;
			}
		}
		break;
	}
    case WM_PAINT:
	{

		hdc = BeginPaint(hWnd, &ps);

		TraceColor = CreateSolidBrush(Color);
		SelectObject(hdc, SquareColor);
		GetClientRect(hWnd, &Rect);

		Center.x = (Rect.right - Rect.left) / 2;
		Center.y = (Rect.bottom - Rect.top) / 2;
		SelectObject(hdc, hFont);

		TextOut(hdc, Center.x*1.2,0, L"Top 5 Game Results :", strlen("Top 5 Game Results :"));
		if (HistRes.size() > 5) {
			DrawPlaces(hdc, Center, Space);
				for (map<int, int>::reverse_iterator i = HistRes.rbegin(); i != HistRes.rend()&&numberofiter!=5; i++) {
					numberofiter++;
					l++;
					DrawRankings(hdc, Center, Space, l, i);

				
			}
			l = 1;
			numberofiter = 0;
		}
		else if(HistRes.size() <= 5&&HistRes.size()>=1)
		{
			DrawPlaces(hdc, Center, Space);
			for (map<int, int>::reverse_iterator i = HistRes.rbegin(); i != HistRes.rend(); i++) {
				l++;
				DrawRankings(hdc, Center, Space, l, i);

			}
			l = 1;
		}
		if (Dim == 11 ) {
			for (int i = 0; i < Dim*Dim; i++) {
				if ((i>=0&&i<=Dim-1)||(i>=Dim*Dim-Dim&&i<=Dim*Dim-1)||(i%Dim==0)) {
					SelectObject(hdc, BoarderColor);
					Rectangle(hdc, vR[i].left, vR[i].top, vR[i].right, vR[i].bottom);
				for(int k=1;k<Dim;k++)
				{
					SelectObject(hdc, BoarderColor);
					Rectangle(hdc, vR[Dim*k-1].left, vR[Dim*k-1].top, vR[Dim*k-1].right, vR[Dim*k-1].bottom);
				}
				}

				else {
					SelectObject(hdc, SquareColor);
					Rectangle(hdc, vR[i].left, vR[i].top, vR[i].right, vR[i].bottom);
				}
				
			}
			
			for (int i = 0; i < NumStep_11.size(); i++) {
				SelectObject(hdc, TraceColor);
				Rectangle(hdc, vR[NumStep_11[i]].left, vR[NumStep_11[i]].top, vR[NumStep_11[i]].right, vR[NumStep_11[i]].bottom);
			}

			for (int i = 0; i < Dim*Dim; i++) {
				if (Worm[i] == TRUE) {
					SelectObject(hdc, WormColor);
					Rectangle(hdc, vR[WhereToStart].left, vR[WhereToStart].top, vR[WhereToStart].right, vR[WhereToStart].bottom);
					

				}
			}
			
		}
		else if (Dim == 19) {
			for (int i = 0; i < Dim*Dim; i++) {
				if ((i >= 0 && i <= Dim - 1) || (i >= Dim*Dim - Dim && i <= Dim*Dim - 1) || (i % Dim == 0)) {
					SelectObject(hdc, BoarderColor);
					Rectangle(hdc, vR_19[i].left, vR_19[i].top, vR_19[i].right, vR_19[i].bottom);
					for (int k = 1; k<Dim; k++)
					{
						SelectObject(hdc, BoarderColor);
						Rectangle(hdc, vR_19[Dim*k - 1].left, vR_19[Dim*k - 1].top, vR_19[Dim*k - 1].right, vR_19[Dim*k - 1].bottom);
					}
				}
				else 
				{
					SelectObject(hdc, SquareColor);
					Rectangle(hdc, vR_19[i].left, vR_19[i].top, vR_19[i].right, vR_19[i].bottom);
				}
			}
			for (int i = 0; i < NumStep_19.size(); i++) {
				SelectObject(hdc, TraceColor);
				Rectangle(hdc, vR_19[NumStep_19[i]].left, vR_19[NumStep_19[i]].top, vR_19[NumStep_19[i]].right, vR_19[NumStep_19[i]].bottom);
			}
			for (int i = 0; i < Dim*Dim; i++) {
				if (Worm_19[i] == TRUE) {
					SelectObject(hdc, WormColor);
					Rectangle(hdc, vR_19[WhereToStart].left, vR_19[WhereToStart].top, vR_19[WhereToStart].right, vR_19[WhereToStart].bottom);
				

				}
			}
		}

		
            EndPaint(hWnd, &ps);
			break;
        }
	case WM_LBUTTONDOWN:
	{	
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		if (App == FALSE&&Move == FALSE && (Dim == 11)) {
			for (int i = 0; i < Dim*Dim; i++) {
				if (InRect(x, y, vR[i])) {
					App = TRUE;
					Move = TRUE;
					WhereToStart = i;
					NumStep_11.push_back(WhereToStart);
					Mover = i;
					Worm[Mover] = TRUE;
					break;
				}
			}

			InvalidateRect(hWnd, &vR[WhereToStart], TRUE);

		}
		else if (App == FALSE&&Move == FALSE && (Dim == 19)) {
			for (int i = 0; i < Dim*Dim; i++) {
				if (InRect(x, y, vR_19[i])) {
					App = TRUE;
					Move = TRUE;
					WhereToStart = i;
					Mover = i;
					NumStep_19.push_back(WhereToStart);
					Worm_19[Mover] = TRUE;
					break;
				}
			}

			InvalidateRect(hWnd, &vR_19[WhereToStart], TRUE);
		}
		break;
	}
    case WM_DESTROY:
		KillTimer(hWnd, 1);
		if (Dim == 11&&ShouldSave==TRUE) {
			//fout << "Type :" << Dim << " * " << Dim << " Number of moves = " << NumberOfMoves_11 << endl;
			fout << Dim << " " << NumberOfMoves_11 << endl;
		}
		else if (Dim == 19&&ShouldSave==TRUE) {
			//fout << "Type :" << Dim << " * " << Dim << " Number of moves = " << NumberOfMoves_19 << endl;
			fout << Dim << " " << NumberOfMoves_19 << endl;
		}
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
INT_PTR CALLBACK Square(HWND hSqu, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDC_HEIGHT:
		{
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
			{
				Height = GetDlgItemInt(hSqu, IDC_HEIGHT, &smth, TRUE);
				//SendMessage(GetDlgItem(hSqu, IDC_STATIC), WM_SETTEXT, 0, (LPARAM)to_wstring(Height).c_str());
				break;
			}
			break;
			}
			break;
			
		}
		case IDC_WIDTH:
		{
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
			{
				Width = GetDlgItemInt(hSqu, IDC_WIDTH, &smth, TRUE);

				break;
			}
			break;
			}
			break;
		}

		}

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hSqu, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	break;

	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK Cells(HWND hCel, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDC_SAVER: {
			BOOL checked = IsDlgButtonChecked(hCel, 1);
			if (checked) {
				CheckDlgButton(hCel, 1, BST_UNCHECKED);
				ShouldSave = FALSE;
			}
			else {
				CheckDlgButton(hCel, 1, BST_CHECKED);
				ShouldSave = TRUE;
			}
		
		

			break;
		}
		case IDC_RADIO1:
		{
			Dim = 11;
			if (Dim == 11&&Init_11==TRUE) {
				for (int i = 0; i < Dim; i++) {
					for (int k = 0; k < Dim; k++) {

						SetRect(&Helper, k * 50, i * 50, k * 50 + RectSide, i * 50 + RectSide);
						vR.push_back(Helper);
					}


				}
				for (int i = 0; i < Dim*Dim; i++) {
					Worm.push_back(FALSE);
				}

				Init_11 = FALSE;
			}
			
			break;

		}
		case IDC_RADIO2:
		{
			Dim = 19;
			if (Dim == 19&& Init_19==TRUE) {
				for (int i = 0; i < Dim; i++) {
					for (int k = 0; k < Dim; k++) {

						SetRect(&Helper, k * 50, i * 50, k * 50 + RectSide, i * 50 + RectSide);
						vR_19.push_back(Helper);
					}


				}
				for (int i = 0; i < Dim*Dim; i++) {
					Worm_19.push_back(FALSE);
				}

				Init_19 = FALSE;
			}

			break;

		}

		}

		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hCel, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	break;

	}
	return (INT_PTR)FALSE;
}