#include "stdafx.h"
#include "WinApi+Assembler.h"
#include <string>
#include<iostream>
#include <cmath>
using namespace std;
#define MAX_LOADSTRING 100
// Global Variables:
HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                
WCHAR szWindowClass[MAX_LOADSTRING];           
struct Num {
	string Number;
	BOOL Hex;
	BOOL Bin;
	BOOL Dec;
	
	Num()
	{
		Number = "0";
		Hex = FALSE;
		Bin = FALSE;
		Dec = FALSE;

	}
	Num SetNumber(string N) {
		Number = N;
		Hex = TRUE;
		Bin = FALSE;
		Dec = FALSE;
		return *this;
	}
	Num SetNotationHex() {
		Hex = TRUE;
		Bin = FALSE;
		Dec = FALSE;
		return *this;
	}
	Num SetNotationBin() {
		Hex = FALSE;
		Bin = TRUE;
		Dec = FALSE;
		return *this;
	}
	Num SetNotationDec() {
		Hex = FALSE;
		Bin = FALSE;
		Dec = TRUE;
		return *this;
	}

};
int FromBinToHex(int *mas,int s) {
	int Sum = 0;
	_asm
	{
		lea eax, mas
		mov edi, s
		mov esi, -1
		_start:

		inc esi
			cmp esi, s
			je _end
			mov edi, s
			dec edi
			sub edi, esi

			mov ecx, 1


			mov edx, -1
			_imulling:
		inc edx
			cmp edx, edi
			je _finish_imulling
			imul ecx, 2
			jmp _imulling

			_finish_imulling :

		mov ebx, [eax][esi * 4]
			imul ecx, ebx
			mov edx, Sum
			add edx, ecx
			mov Sum, edx
			jmp _start



			_end :


	}
	return Sum;
}
long double left_range;
long double right_range;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Converter(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Calculator(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Graph(HWND, UINT, WPARAM, LPARAM);
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
    LoadStringW(hInstance, IDC_WINAPIASSEMBLER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIASSEMBLER));

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




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIASSEMBLER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIASSEMBLER);
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

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		
		switch (wmId)
		{
		case ID_START_CONVERTING:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_CONVERTER), hWnd, Converter);
			break;
		case ID_START_CALCULATING:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_CALCULATOR), hWnd, Calculator);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
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
INT_PTR CALLBACK Converter(HWND hCon, UINT message, WPARAM wParam, LPARAM lParam)
{
	static string Num_Str;
	static int length;
	static BOOL Wrong_Input = FALSE;
	
	switch (message)
	{
	case WM_INITDIALOG:
	{
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hCon, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		switch (LOWORD(wParam)) {
		case IDC_INPUT:
		{
			switch (HIWORD(wParam))
			{
			case EN_KILLFOCUS:
			{
				length = SendMessage((HWND)lParam, WM_GETTEXTLENGTH,0,0);
				char *buffer = new char[length];
				SendMessage((HWND)lParam,WM_GETTEXT,(WPARAM)(length+1),(LPARAM)buffer);
				string temp_num_str(buffer);
				Num_Str = temp_num_str;
				

				
				
				break;
			}


			
			}
			break;
		}
		case IDC_DEC:
		{
			break;
		}
		case IDC_BIN:
		{
			break;
		}
		case IDC_HEXDEC:
		{
			break;
		}
		case IDC_BIN_DEC:
		{
			Wrong_Input = FALSE;
			CheckDlgButton(hCon, IDC_BIN, TRUE);
			CheckDlgButton(hCon, IDC_DEC, FALSE);
			CheckDlgButton(hCon, IDC_HEXDEC, FALSE);

			
			for (string::iterator i = Num_Str.begin(); i != Num_Str.end(); i++) {
				if ((*i) != '0' && (*i) !='1' ) {
					MessageBox(hCon, "Wrong Input Number (This is not Binary!)", "Error", NULL);
					Wrong_Input = TRUE;
					break;
				}
				else Wrong_Input = FALSE;
			}
			if (Wrong_Input == FALSE) {
				int mas[50];
				int k = 0;

				for (string::iterator i = Num_Str.begin(); i != Num_Str.end(); i++) {
					mas[k++] = (*i) - 48;
				}
				int s = Num_Str.size();
				int Sum = 0;
				_asm
				{
					lea eax, mas
					mov edi, s
					mov esi, -1
					_start:

					inc esi
						cmp esi, s
						je _end
						mov edi, s
						dec edi
						sub edi, esi

						mov ecx, 1


						mov edx, -1
						_imulling:
					inc edx
						cmp edx, edi
						je _finish_imulling
						imul ecx, 2
						jmp _imulling

						_finish_imulling :

					mov ebx, [eax][esi * 4]
						imul ecx, ebx
						mov edx, Sum
						add edx, ecx
						mov Sum, edx
						jmp _start



						_end :


				}
				SendMessageW(GetDlgItem(hCon, IDC_OUTPUT), WM_SETTEXT, 0, (LPARAM)to_wstring(Sum).c_str());

			}
			break;
		}
		case IDC_BIN_HEX:
		{
			Wrong_Input = FALSE;
			CheckDlgButton(hCon, IDC_BIN, TRUE);
			CheckDlgButton(hCon, IDC_DEC, FALSE);
			CheckDlgButton(hCon, IDC_HEXDEC, FALSE);

			for (string::iterator i = Num_Str.begin(); i != Num_Str.end(); i++) {
				if ((*i) != '0' && (*i) != '1') {
					MessageBox(hCon, "Wrong Input Number (This is not Binary!)", "Error", NULL);
					Wrong_Input = TRUE;
					break;
				}
				else Wrong_Input = FALSE;
			}
			if (Wrong_Input == FALSE) {
				int mas[50];
				int k = 0;

				for (string::reverse_iterator i = Num_Str.rbegin(); i != Num_Str.rend(); i++) {
					mas[k++] = (*i) - 48;
				}
				k = Num_Str.size();
				int mas_reversed_copy[50];
				while (k % 4 != 0) {
					mas[k] = 0;
					k++;
				}
				int j = 0;
				for (int i = k-1; i >= 0; i--) {
					mas_reversed_copy[j++] = mas[i];
				}
			
				int tetraeds[4];
				int *Hex_Mas = new int[k / 4];
				j = 0;
				int index_for_hex=0;
				for (int i = 0; i < k; i++) {
					
					tetraeds[j++] = mas_reversed_copy[i];
					if ((i + 1) % 4 == 0) {
						j = 0;
						int s = 4;
						int Sum = 0;
						_asm
						{
							lea eax, tetraeds
							mov edi, s
							mov esi, -1
							_start_:

							inc esi
								cmp esi, s
								je _end_
								mov edi, s
								dec edi
								sub edi, esi

								mov ecx, 1


								mov edx, -1
								_imulling_:
							inc edx
								cmp edx, edi
								je _finish_imulling_
								imul ecx, 2
								jmp _imulling_

								_finish_imulling_ :

							mov ebx, [eax][esi * 4]
								imul ecx, ebx
								mov edx, Sum
								add edx, ecx
								mov Sum, edx
								jmp _start_



								_end_ :


						}
						Hex_Mas[index_for_hex++] = Sum;

					}
				}
				string Hex_Output;
				for (int i = 0; i < index_for_hex; i++) {
					if (Hex_Mas[i] >= 0 && Hex_Mas[i] <= 9) Hex_Output += to_string(Hex_Mas[i]).c_str();

					else if (Hex_Mas[i] == 10)  Hex_Output += "A";

					else if (Hex_Mas[i] == 11)  Hex_Output += "B";

					else if (Hex_Mas[i] == 12)  Hex_Output += "C";

					else if (Hex_Mas[i] == 13)  Hex_Output += "D";

					else if (Hex_Mas[i] == 14)  Hex_Output += "E";

					else if (Hex_Mas[i] == 15)  Hex_Output += "F";



				}

				SendMessage(GetDlgItem(hCon, IDC_OUTPUT), WM_SETTEXT, 0, (LPARAM)((Hex_Output).c_str()));






		}
		



			break;
		}
		case IDC_DEC_BIN:
		{
			Wrong_Input = FALSE;
			CheckDlgButton(hCon, IDC_BIN,FALSE);
			CheckDlgButton(hCon, IDC_DEC, TRUE);
			CheckDlgButton(hCon, IDC_HEXDEC, FALSE);

			for (string::iterator i = Num_Str.begin(); i != Num_Str.end(); i++) {
				if ((*i) < '0' || (*i) > '9') {
					MessageBox(hCon, "Wrong Input Number (This is not Decimal!)", "Error", NULL);
					Wrong_Input = TRUE;
					break;
				}
				else Wrong_Input = FALSE;
			}
			if (Wrong_Input == FALSE) {

				int Bin_Mas[50];
				int Dec_Num = atoi(Num_Str.c_str());
				int num_of_bin = 0;
				int *Bin_Mas_Reversed = new int[num_of_bin];
				int two = 2;
				int j = 0;
				_asm 
				{
					lea ebx, Bin_Mas
					mov esi,-1
					mov eax,Dec_Num
						_lets_start:
					cdq
						idiv two
					cmp eax,0
					je _finita
					inc esi
					mov [ebx][esi*4],edx
						jmp _lets_start 
					

						_finita:
					inc esi
					mov[ebx][esi * 4], edx
					mov num_of_bin,esi
				}
				for (int i = num_of_bin; i >= 0; i--) {
					Bin_Mas_Reversed[j++] = Bin_Mas[i];
				}
				string Output_Str;
				for (int i = 0; i <= num_of_bin; i++) {

					Output_Str += to_string(Bin_Mas_Reversed[i]).c_str();
				}

				SendMessage(GetDlgItem(hCon, IDC_OUTPUT), WM_SETTEXT, 0, (LPARAM)((Output_Str).c_str()));


			}

			break;
		}
		case IDC_HEX_BIN:
		{
			Wrong_Input = FALSE;
			CheckDlgButton(hCon, IDC_BIN, FALSE);
			CheckDlgButton(hCon, IDC_DEC, FALSE);
			CheckDlgButton(hCon, IDC_HEXDEC, TRUE);

			for (string::iterator i = Num_Str.begin(); i != Num_Str.end(); i++) {
				if (!(((*i) >= '0' && (*i) <= '9')||((*i) >= 'A' && (*i) <= 'F'))) {
					MessageBox(hCon, "Wrong Input Number (This is not HexDecimal!)", "Error", NULL);
					Wrong_Input = TRUE;
					break;
				}
				else Wrong_Input = FALSE;
			}
			if (Wrong_Input == FALSE) {
				int Hex_Dec_Mas[50];
				int num_of_elem = 0;
				for (string::iterator i = Num_Str.begin(); i != Num_Str.end(); i++) {
					if ((*i) >= '0' && (*i) <= '9') Hex_Dec_Mas[num_of_elem++] = *i - 48;
					else if ((*i) >= 'A' && (*i) <= 'F') Hex_Dec_Mas[num_of_elem++] = *i - 65 + 10;
				}

				int tetra[4];
				int j = 0;
				int tetranum = 0;
				int two = 2;
				string out_dec;
				for (int i = 0; i < num_of_elem; i++)
				{
					int tetra_reverse[4];
					int imul_this = Hex_Dec_Mas[i];
					_asm
					{
						lea ebx, tetra
						mov esi, -1
						mov eax, imul_this
						_lets_start_ :
						cdq
							idiv two
							cmp eax, 0
							je _finita_
							inc esi
							mov[ebx][esi * 4], edx
							jmp _lets_start_


							_finita_ :
						inc esi
							mov[ebx][esi * 4], edx
							mov tetranum,esi
					}
					while ((tetranum + 1) % 4 != 0) {
						tetra[tetranum +1] = 0;
						tetranum++;
					}


					int k = 0;
					for (int j = 3; j >= 0; j--) {
						
						tetra_reverse[k++] = tetra[j];
					}
					for (int j = 0; j < 4; j++) {
						out_dec += (to_string(tetra_reverse[j]).c_str());
					}


				}
			
				SendMessage(GetDlgItem(hCon, IDC_OUTPUT), WM_SETTEXT, 0, (LPARAM)((out_dec).c_str()));






			}




			break;
		}

		}
		break;
		
	}
	break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK Calculator(HWND hClc , UINT message, WPARAM wParam, LPARAM lParam)
{
	static string Num_Str_Cos;
	static string Num_Str_Ln;
	static string Num_Str_L_Range;
	static string Num_Str_R_Range;
	static long double num_cos;
	static long double num_ln;
	static int length_cos;
	static int length_ln;
	static int length_l;
	static int length_r;
	static BOOL Wrong_Input = FALSE;
	static long double	_1_8_0_ = 180;
	
	switch (message)
	{
	case WM_INITDIALOG:
	{
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hClc, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		switch (LOWORD(wParam)) {
		case IDC_COS_INPUT:
		{
			switch (HIWORD(wParam))
			{
			case EN_KILLFOCUS:
			{
				length_cos = SendMessage((HWND)lParam, WM_GETTEXTLENGTH, 0, 0);
				char *buffer = new char[length_cos];
				SendMessage((HWND)lParam, WM_GETTEXT, (WPARAM)(length_cos + 1), (LPARAM)buffer);
				string temp_num_str(buffer);
				Num_Str_Cos = temp_num_str;




				break;
			}



			}
			break;
		}
		case IDC_EQUAL_COS:
		{
			num_cos = atof(Num_Str_Cos.c_str());
			_asm {
				finit
				fldpi
				fmul num_cos
				fdiv _1_8_0_
				fcos
				fstp num_cos

			}
			SendMessageW(GetDlgItem(hClc, IDC_COS_OUTPUT), WM_SETTEXT, 0, (LPARAM)to_wstring(num_cos).c_str());

			break;
		}
		case IDC_LN_INPUT:
		{
			switch (HIWORD(wParam))
			{
			case EN_KILLFOCUS:
			{
				length_ln = SendMessage((HWND)lParam, WM_GETTEXTLENGTH, 0, 0);
				char *buffer = new char[length_ln];
				SendMessage((HWND)lParam, WM_GETTEXT, (WPARAM)(length_ln + 1), (LPARAM)buffer);
				string temp_num_str(buffer);
				Num_Str_Ln = temp_num_str;




				break;
			}


			break;
			}
			break;

		}
		case IDC_EQUAL_LN:
		{
			num_ln = atof(Num_Str_Ln.c_str());
			_asm
			{
				finit
				fldln2
				fld num_ln
				fyl2x
				fstp num_ln
			}
			SendMessageW(GetDlgItem(hClc, IDC_LN_OUTPUT), WM_SETTEXT, 0, (LPARAM)to_wstring(num_ln).c_str());


			break;
		}
		case IDC_L_RANGE:
		{
			switch (HIWORD(wParam))
			{
			case EN_KILLFOCUS:
			{
				length_l = SendMessage((HWND)lParam, WM_GETTEXTLENGTH, 0, 0);
				char *buffer = new char[length_l];
				SendMessage((HWND)lParam, WM_GETTEXT, (WPARAM)(length_l + 1), (LPARAM)buffer);
				string temp_num_str(buffer);
				Num_Str_L_Range = temp_num_str;




				break;
			}

			}
			break;
		}
		case IDC_R_RANGE:
		{
			switch (HIWORD(wParam))
			{
			case EN_KILLFOCUS:
			{
				length_r = SendMessage((HWND)lParam, WM_GETTEXTLENGTH, 0, 0);
				char *buffer = new char[length_r];
				SendMessage((HWND)lParam, WM_GETTEXT, (WPARAM)(length_r + 1), (LPARAM)buffer);
				string temp_num_str(buffer);
				Num_Str_R_Range = temp_num_str;




				break;
			}

			}
			break;
		}
		case IDC_CALCULATE:
		{
			left_range = atof(Num_Str_L_Range.c_str());
			right_range = atof(Num_Str_R_Range.c_str());
			DialogBox(hInst, MAKEINTRESOURCE(IDD_GRAPH), hClc, Graph);
			break;
		}
		}
		break;
	}
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK Graph(HWND hGrh, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT Center;
	static RECT Rect;
	static HDC hdc;
	static int scale = 20;
	static int line_size = 5;
	static long double n = 100;
	static long double step = (right_range - left_range) / n;
	static long double x, y;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		GetClientRect(hGrh, &Rect);
		Center.x = (Rect.right - Rect.left) / 2;
		Center.y = (Rect.bottom - Rect.top) / 2;
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{


		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hGrh, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	case WM_PAINT:
	{
		
		PAINTSTRUCT ps;
		hdc = BeginPaint(hGrh, &ps);
		SetBkMode(hdc, TRANSPARENT);
		MoveToEx(hdc, 0, Center.y, NULL);
		LineTo(hdc, 2 * Center.x, Center.y);
		MoveToEx(hdc, Center.x, 0, NULL);
		LineTo(hdc, Center.x, 2 * Center.y);

		int accum = Center.x;
		for (int count = 0; count < 20; count++) {
			MoveToEx(hdc, accum, Center.y - line_size, NULL);
			LineTo(hdc, accum, Center.y + line_size);
			accum += scale;
		}
		accum = Center.x;
		for (int count = 20; count > 0; count--) {
			MoveToEx(hdc, accum, Center.y - line_size, NULL);
			LineTo(hdc, accum, Center.y + line_size);
			accum -= scale;
		}
		accum = Center.y;
		for (int count = 20; count > 0; count--) {
			MoveToEx(hdc, Center.x-line_size, accum, NULL);
			LineTo(hdc, Center.x+line_size, accum);
			accum -= scale;
		}
		accum = Center.y;
		for (int count = 0; count < 20; count++) {
			MoveToEx(hdc, Center.x - line_size, accum, NULL);
			LineTo(hdc, Center.x + line_size, accum);
			accum += scale;
		}
		long double k = 0;
		x = left_range;
		MoveToEx(hdc, Center.x + left_range*scale , Center.y - scale*(sin(left_range)+left_range*left_range), NULL);
		while (x < right_range) {
			x = left_range + step*k;
			k++;
			y = sin(x) + x * x;
			LineTo(hdc, x*scale + Center.x, Center.y - y*scale);
			HPEN Pen_line = CreatePen(10, 1, RGB(0, 250, 154));
			SelectObject(hdc, Pen_line);
			LineTo(hdc, x*scale + Center.x, Center.y);
			MoveToEx(hdc, x*scale + Center.x, Center.y - y*scale, NULL);
			DeleteObject(Pen_line);
		}
	
		
		k = 1;
		long double buf = 0;
		long double result_accum = 0;
		long double result = 0;
		long double one = 1;
		long double two = 2;
		n = n - 1;
		k = k - 1;
		_asm
		{
			finit
			_beg_ :
			fld k
				fadd one
				fstp k
				fld step
				fmul k
				fadd left_range
				fst result

				fsin
				fstp buf
				fld result
				fmul result
				fadd buf
				fstp buf
				fld result_accum
				fadd buf
				fstp result_accum
				fld k
				fld n

				fcompp
				fstsw ax
				sahf
				jne _beg_

				fld result_accum
				fmul two
				fst buf
				fld left_range

				fsin
				fst result
				fld left_range
				fmul left_range
				fadd result
				fst result
				fld right_range
				fsin
				fadd result
				fst result
				fld right_range



				fmul right_range
				fadd result
				fadd buf
				fmul step
				fdiv two
				fst result
		}
		string result_str = "Definite Integral = " + to_string(result);
		TextOut(hdc, Center.x + 50, Center.y + 50, result_str.c_str(), strlen(result_str.c_str()));
		n = n + 1;
		k = 1;
		EndPaint(hGrh, &ps);
		break;
	}
	}
	return (INT_PTR)FALSE;
}