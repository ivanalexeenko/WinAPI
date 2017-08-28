// Fifth WinApi.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include<cmath>
#include "FifthWinApi.h"
#include <vector>
#include<fstream>
#define MAX_LOADSTRING 100
using namespace std;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
struct Rectangles {
	POINT Center;
	int halfside;
	Rectangles(POINT c, int h) {
		Center = c;
		halfside = h;
	}
};
struct Cell {
	BOOL Cross;
	BOOL Null;
	Cell(BOOL C, BOOL N) {
		Cross = C;
		Null = N;
	}
};
void DrawLattice(HDC hdc,POINT Center,int halfside,HPEN LinesPen) {
	// Central Dot;
	Ellipse(hdc, Center.x - 5, Center.y - 5, Center.x + 5, Center.y + 5);
	// Horizontal lines;
	SelectObject(hdc, LinesPen);
	MoveToEx(hdc, Center.x, Center.y, NULL);
	MoveToEx(hdc, Center.x + halfside, Center.y + 225, NULL);
	LineTo(hdc, Center.x + halfside, Center.y - 225);
	MoveToEx(hdc, Center.x - halfside, Center.y - 225, NULL);
	LineTo(hdc, Center.x - halfside, Center.y + 225);
	// Vertical lines;
	MoveToEx(hdc, Center.x - 225, Center.y - halfside, NULL);
	LineTo(hdc, Center.x + 225, Center.y - halfside);
	MoveToEx(hdc, Center.x - 225, Center.y + halfside, NULL);
	LineTo(hdc, Center.x + 225, Center.y + halfside);

}
vector<Rectangles> PushInVector(HDC hdc,vector<Rectangles>& vR,POINT Center,int halfside,HPEN RectPen) {
	//SelectObject(hdc, RectPen);
	//A_1_1
	vR.push_back(Rectangles({ Center.x - halfside * 2,Center.y - halfside * 2 }, halfside));
	//Rectangle(hdc, vR[0].Center.x - halfside, vR[0].Center.y - halfside, vR[0].Center.x + halfside, vR[0].Center.y + halfside);
	//A_1_2
	vR.push_back(Rectangles({ Center.x,Center.y - halfside * 2 }, halfside));
	//Rectangle(hdc, vR[1].Center.x - halfside, vR[1].Center.y - halfside, vR[1].Center.x + halfside, vR[1].Center.y + halfside);
	//A_1_3
	vR.push_back(Rectangles({ Center.x + halfside * 2,Center.y - halfside * 2 }, halfside));
	//Rectangle(hdc, vR[2].Center.x - halfside, vR[2].Center.y - halfside, vR[2].Center.x + halfside, vR[2].Center.y + halfside);
	//A_2_1
	vR.push_back(Rectangles({ Center.x - halfside * 2,Center.y }, halfside));
	//Rectangle(hdc, vR[3].Center.x - halfside, vR[3].Center.y - halfside, vR[3].Center.x + halfside, vR[3].Center.y + halfside);
	//A2_2
	vR.push_back(Rectangles({ Center.x ,Center.y }, halfside));
	//Rectangle(hdc, vR[4].Center.x - halfside, vR[4].Center.y - halfside, vR[4].Center.x + halfside, vR[4].Center.y + halfside);
	//A2_3
	vR.push_back(Rectangles({ Center.x + halfside * 2,Center.y }, halfside));
	//Rectangle(hdc, vR[5].Center.x - halfside, vR[5].Center.y - halfside, vR[5].Center.x + halfside, vR[5].Center.y + halfside);
	//A3_1
	vR.push_back(Rectangles({ Center.x - halfside * 2,Center.y + halfside * 2 }, halfside));
	//Rectangle(hdc, vR[6].Center.x - halfside, vR[6].Center.y - halfside, vR[6].Center.x + halfside, vR[6].Center.y + halfside);
	//A3_2
	vR.push_back(Rectangles({ Center.x,Center.y + halfside * 2 }, halfside));
	//Rectangle(hdc, vR[7].Center.x - halfside, vR[7].Center.y - halfside, vR[7].Center.x + halfside, vR[7].Center.y + halfside);
	//A3_3
	vR.push_back(Rectangles({ Center.x + halfside * 2,Center.y + halfside * 2 }, halfside));
	//Rectangle(hdc, vR[8].Center.x - halfside, vR[8].Center.y - halfside, vR[8].Center.x + halfside, vR[8].Center.y + halfside);
	return vR;
}
bool InRect(int a,int b,POINT Center,int halfside) {
	if ((a >= Center.x - halfside)&&(a <= Center.x + halfside)&&(b >= Center.y - halfside)&&(b <= Center.y + halfside)) return true;
	else return false;
}
int FirstPlWin(vector<Cell>&vC,bool FirstPlayer) {
	if (((vC[0].Cross&&vC[1].Cross&&vC[2].Cross)
		|| (vC[3].Cross&&vC[4].Cross&&vC[5].Cross)
		|| (vC[6].Cross&&vC[7].Cross&&vC[8].Cross)
		|| (vC[0].Cross&&vC[3].Cross&&vC[6].Cross)
		|| (vC[1].Cross&&vC[4].Cross&&vC[7].Cross)
		|| (vC[2].Cross&&vC[5].Cross&&vC[8].Cross)
		|| (vC[2].Cross&&vC[4].Cross&&vC[6].Cross)
		|| (vC[0].Cross&&vC[4].Cross&&vC[8].Cross)) )
	{
		return 1;
	}
	else if (((vC[0].Null&&vC[1].Null&&vC[2].Null)
		|| (vC[3].Null&&vC[4].Null&&vC[5].Null)
		|| (vC[6].Null&&vC[7].Null&&vC[8].Null)
		|| (vC[0].Null&&vC[3].Null&&vC[6].Null)
		|| (vC[1].Null&&vC[4].Null&&vC[7].Null)
		|| (vC[2].Null&&vC[5].Null&&vC[8].Null)
		|| (vC[2].Null&&vC[4].Null&&vC[6].Null)
		|| (vC[0].Null&&vC[4].Null&&vC[8].Null)))
	{
		return 2;
	}
	else return 0;
}
void DrawCross(HDC hdc,vector<Rectangles>&vR,int i,int halfside,HPEN RectPen) {
	SelectObject(hdc,RectPen);
	MoveToEx(hdc, vR[i].Center.x - halfside + 20, vR[i].Center.y - halfside + 20, NULL);
	LineTo(hdc, vR[i].Center.x + halfside - 20, vR[i].Center.y + halfside - 20);
	MoveToEx(hdc, vR[i].Center.x + halfside - 20, vR[i].Center.y - halfside + 20, NULL);
	LineTo(hdc, vR[i].Center.x - halfside + 20, vR[i].Center.y + halfside - 20);
}
void DrawNull(HDC hdc,vector<Rectangles>&vR,int i,int halfside,HPEN RectPen) {
	SelectObject(hdc, RectPen);
	Ellipse(hdc, vR[i].Center.x - halfside + 20, vR[i].Center.y - halfside + 20, vR[i].Center.x + halfside - 20, vR[i].Center.y + halfside - 20);
}
void DrawSwitchNull(HDC hdc,int x,int y,const int SwitcherSize,HPEN RectPen){
	SelectObject(hdc, RectPen);
	Ellipse(hdc, x / 1.35 - SwitcherSize, y / 11 - SwitcherSize, x / 1.35 + SwitcherSize, y / 11 + SwitcherSize);
}
void DrawSwitchCross(HDC hdc,int x,int y,const int SwitcherSize,HPEN RectPen) {
	SelectObject(hdc, RectPen);
	MoveToEx(hdc,x/4.5-SwitcherSize,y/12-SwitcherSize,NULL);
	LineTo(hdc, x /4.5 + SwitcherSize, y / 12 + SwitcherSize);
	MoveToEx(hdc, x / 4.5 + SwitcherSize, y / 12 - SwitcherSize, NULL);
	LineTo(hdc, x / 4.5 - SwitcherSize, y / 12 + SwitcherSize);
}
void DrawSwitchLine(HDC hdc,int x,int y,const int SwitcherSize,HPEN RectPen) {
	SelectObject(hdc, RectPen);
	MoveToEx(hdc, x / 2 - SwitcherSize, y / 12 , NULL);
	LineTo(hdc, x / 2 + SwitcherSize, y / 12 );

}
void DrawAllElements(HDC hdc,vector<Rectangles>&vR,vector<Cell>&vC,int halfside,HPEN LinesPen) {
	for (int i =0; i < vC.size(); i++) {
		if (vC[i].Cross == TRUE) {
			DrawCross(hdc, vR, i, halfside, LinesPen);
		}
		else if (vC[i].Null == TRUE) {
			DrawNull(hdc, vR, i, halfside, LinesPen);
		}
	}
}
void DrawLine(HDC hdc,int x1,int y1,int x2,int y2,HPEN RectPen) {
	SelectObject(hdc, RectPen);
	MoveToEx(hdc,x1,y1,NULL);
	LineTo(hdc,x2,y2);
}
void DefineAndCross_3_In_a_RowCrosses(HDC hdc,vector<Rectangles>&vR,vector<Cell>&vC,int halfside,HPEN RectPen) {
	if (vC[0].Cross&&vC[1].Cross&&vC[2].Cross) { DrawLine(hdc,vR[0].Center.x - halfside, vR[0].Center.y, vR[2].Center.x + halfside, vR[2].Center.y, RectPen); }// Top Line;
	else if (vC[3].Cross&&vC[4].Cross&&vC[5].Cross) { DrawLine(hdc,vR[3].Center.x - halfside, vR[3].Center.y, vR[5].Center.x + halfside,vR[5].Center.y, RectPen); }// Central Line;
	else if (vC[6].Cross&&vC[7].Cross&&vC[8].Cross) { DrawLine(hdc, vR[6].Center.x - halfside, vR[6].Center.y, vR[8].Center.x + halfside, vR[8].Center.y, RectPen); }// Bottom Line;
	else if (vC[0].Cross&&vC[3].Cross&&vC[6].Cross) { DrawLine(hdc, vR[0].Center.x, vR[0].Center.y-halfside, vR[6].Center.x, vR[6].Center.y+halfside, RectPen); }// Left Column;
	else if (vC[1].Cross&&vC[4].Cross&&vC[7].Cross) { DrawLine(hdc, vR[1].Center.x, vR[1].Center.y - halfside, vR[7].Center.x, vR[7].Center.y + halfside, RectPen); }// Central Column;
	else if (vC[2].Cross&&vC[5].Cross&&vC[8].Cross) { DrawLine(hdc, vR[2].Center.x, vR[2].Center.y - halfside, vR[8].Center.x, vR[8].Center.y + halfside, RectPen); }// Right Column;
	else if (vC[2].Cross&&vC[4].Cross&&vC[6].Cross) { DrawLine(hdc, vR[2].Center.x+halfside, vR[2].Center.y - halfside, vR[6].Center.x-halfside, vR[6].Center.y + halfside, RectPen); }//Secondary Diagonal;
	else if	(vC[0].Cross&&vC[4].Cross&&vC[8].Cross) { DrawLine(hdc, vR[0].Center.x-halfside, vR[0].Center.y - halfside, vR[8].Center.x+halfside, vR[8].Center.y + halfside, RectPen); }// Main Diagonal;
	
		
}
void DefineAndCross_3_In_a_RowNulls(HDC hdc, vector<Rectangles>&vR, vector<Cell>&vC, int halfside, HPEN RectPen) {
	if (vC[0].Null&&vC[1].Null&&vC[2].Null) { DrawLine(hdc, vR[0].Center.x - halfside, vR[0].Center.y, vR[2].Center.x + halfside, vR[2].Center.y, RectPen); }// Top Line;
	else if (vC[3].Null&&vC[4].Null&&vC[5].Null) { DrawLine(hdc, vR[3].Center.x - halfside, vR[3].Center.y, vR[5].Center.x + halfside, vR[5].Center.y, RectPen); }// Central Line;
	else if (vC[6].Null&&vC[7].Null&&vC[8].Null) { DrawLine(hdc, vR[6].Center.x - halfside, vR[6].Center.y, vR[8].Center.x + halfside, vR[8].Center.y, RectPen); }// Bottom Line;
	else if (vC[0].Null&&vC[3].Null&&vC[6].Null) { DrawLine(hdc, vR[0].Center.x, vR[0].Center.y - halfside, vR[6].Center.x, vR[6].Center.y + halfside, RectPen); }// Left Column;
	else if (vC[1].Null&&vC[4].Null&&vC[7].Null) { DrawLine(hdc, vR[1].Center.x, vR[1].Center.y - halfside, vR[7].Center.x, vR[7].Center.y + halfside, RectPen); }// Central Column;
	else if (vC[2].Null&&vC[5].Null&&vC[8].Null) { DrawLine(hdc, vR[2].Center.x, vR[2].Center.y - halfside, vR[8].Center.x, vR[8].Center.y + halfside, RectPen); }// Right Column;
	else if (vC[2].Null&&vC[4].Null&&vC[6].Null) { DrawLine(hdc, vR[2].Center.x + halfside, vR[2].Center.y - halfside, vR[6].Center.x - halfside, vR[6].Center.y + halfside, RectPen); }//Secondary Diagonal;
	else if (vC[0].Null&&vC[4].Null&&vC[8].Null) { DrawLine(hdc, vR[0].Center.x - halfside, vR[0].Center.y - halfside, vR[8].Center.x + halfside, vR[8].Center.y + halfside, RectPen); }// Main Diagonal;


}
bool IsFree(vector<Cell>&vC,int i) {
	if (vC[i].Cross==FALSE&&vC[i].Null==FALSE) return true;
	else return false;
}
int SetNullToRandomCell(vector<Cell>&vC) {
	bool aa = true;
	int random;
	while (aa)
	{
	random = rand() % 9;
	if (IsFree(vC, random))
	{
	aa = false;
	}
	}
	return random;
}
bool IsTwoFromThreeCrossesPicked(vector<Cell>&vC) {
	
		if ((vC[0].Cross == TRUE&&vC[1].Cross == TRUE)
			|| (vC[0].Cross == TRUE&&vC[2].Cross == TRUE)
			|| (vC[0].Cross == TRUE&&vC[3].Cross == TRUE)
			|| (vC[0].Cross == TRUE&&vC[4].Cross == TRUE)
			|| (vC[0].Cross == TRUE&&vC[6].Cross == TRUE)
			|| (vC[0].Cross == TRUE&&vC[8].Cross == TRUE)
			|| (vC[1].Cross == TRUE&&vC[2].Cross == TRUE)
			|| (vC[1].Cross == TRUE&&vC[4].Cross == TRUE)
			|| (vC[1].Cross == TRUE&&vC[7].Cross == TRUE)
			|| (vC[2].Cross == TRUE&&vC[4].Cross == TRUE)
			|| (vC[2].Cross == TRUE&&vC[5].Cross == TRUE)
			|| (vC[2].Cross == TRUE&&vC[6].Cross == TRUE)
			|| (vC[2].Cross == TRUE&&vC[8].Cross == TRUE)
			|| (vC[3].Cross == TRUE&&vC[4].Cross == TRUE)
			|| (vC[3].Cross == TRUE&&vC[5].Cross == TRUE)
			|| (vC[3].Cross == TRUE&&vC[6].Cross == TRUE)
			|| (vC[4].Cross == TRUE&&vC[5].Cross == TRUE)
			|| (vC[4].Cross == TRUE&&vC[6].Cross == TRUE)
			|| (vC[4].Cross == TRUE&&vC[7].Cross == TRUE)
			|| (vC[4].Cross == TRUE&&vC[8].Cross == TRUE)
			|| (vC[5].Cross == TRUE&&vC[8].Cross == TRUE)
			|| (vC[6].Cross == TRUE&&vC[7].Cross == TRUE)
			|| (vC[6].Cross == TRUE&&vC[8].Cross == TRUE)
			|| (vC[7].Cross == TRUE&&vC[8].Cross == TRUE)
			)
			return true;
		else return false;
}
int TwoFromThreeCrossesNullPos(vector<Cell>&vC) {
	if (vC[0].Cross == TRUE&&vC[1].Cross == TRUE) return 2;
	else if (vC[0].Cross == TRUE&&vC[2].Cross == TRUE) return 1;
	else if (vC[0].Cross == TRUE&&vC[3].Cross == TRUE) return 6;
	else if (vC[0].Cross == TRUE&&vC[4].Cross == TRUE) return 8;
	else if (vC[0].Cross == TRUE&&vC[6].Cross == TRUE) return 3;
	else if (vC[0].Cross == TRUE&&vC[8].Cross == TRUE) return 4;
	else if (vC[1].Cross == TRUE&&vC[2].Cross == TRUE) return 0;
	else if (vC[1].Cross == TRUE&&vC[4].Cross == TRUE) return 7;
	else if (vC[1].Cross == TRUE&&vC[7].Cross == TRUE) return 4;
	else if (vC[2].Cross == TRUE&&vC[4].Cross == TRUE) return 6;
	else if (vC[2].Cross == TRUE&&vC[5].Cross == TRUE) return 8;
	else if (vC[2].Cross == TRUE&&vC[6].Cross == TRUE) return 4;
	else if (vC[2].Cross == TRUE&&vC[8].Cross == TRUE) return 5;
	else if (vC[3].Cross == TRUE&&vC[4].Cross == TRUE) return 5;
	else if (vC[3].Cross == TRUE&&vC[5].Cross == TRUE) return 4;
	else if (vC[3].Cross == TRUE&&vC[6].Cross == TRUE) return 0;
	else if (vC[4].Cross == TRUE&&vC[5].Cross == TRUE) return 3;
	else if (vC[4].Cross == TRUE&&vC[6].Cross == TRUE) return 2;
	else if (vC[4].Cross == TRUE&&vC[7].Cross == TRUE) return 1;
	else if (vC[4].Cross == TRUE&&vC[8].Cross == TRUE) return 0;
	else if (vC[5].Cross == TRUE&&vC[8].Cross == TRUE) return 2;
	else if (vC[6].Cross == TRUE&&vC[7].Cross == TRUE) return 8;
	else if (vC[6].Cross == TRUE&&vC[8].Cross == TRUE) return 7;
	else if (vC[7].Cross == TRUE&&vC[8].Cross == TRUE) return 6;
	else return -1;
}
int WherePickNullTwoFromThree(vector<Cell>&vC) {
	int i = 0;
	int ran;
	for (i; i < vC.size(); i++) {
		if (vC[i].Null == TRUE)
			break;
	}
	if (i == 0) {
		if ((IsFree(vC, 1) && IsFree(vC, 2)) && (!IsFree(vC, 4) || !IsFree(vC, 8)) && (!IsFree(vC, 3) || !IsFree(vC, 6))) {
			ran = rand() % 2 + 1;
			return ran;
		}
		else if ((IsFree(vC, 4) && IsFree(vC, 8)) && (!IsFree(vC, 1) || !IsFree(vC, 2)) && (!IsFree(vC, 3) || !IsFree(vC, 6))) {
			ran = rand() % 2 + 1;
			if (ran == 1) return 4;
			else if (ran == 2) return 8;
		}
		else if ((IsFree(vC, 3) && IsFree(vC, 6)) && (!IsFree(vC, 1) || !IsFree(vC, 2)) && (!IsFree(vC, 4) || !IsFree(vC, 8))) {
			ran = rand() % 2 + 1;
			if (ran == 1) return 3;
			else if (ran == 2) return 6;
		}
		else if ((IsFree(vC, 1) && IsFree(vC, 2)) && (IsFree(vC, 4) && IsFree(vC, 8)) && (!IsFree(vC, 3) || !IsFree(vC, 6))) {
			ran = rand() % 4 + 1;
			if (ran == 1) return ran;
			else if (ran == 2) return ran;
			else if (ran == 3) return 4;
			else if (ran == 4) return 8;
		}
		else if ((IsFree(vC, 1) && IsFree(vC, 2)) && (IsFree(vC, 3) && IsFree(vC, 6)) && (!IsFree(vC, 4) || !IsFree(vC, 8))) {
			ran = rand() % 4 + 1;
			if (ran == 1) return ran;
			else if (ran == 2) return ran;
			else if (ran == 3) return ran;
			else if (ran == 4) return 6;
		}
		else if ((IsFree(vC, 3) && IsFree(vC, 6)) && (IsFree(vC, 4) && IsFree(vC, 8)) && (!IsFree(vC, 1) || !IsFree(vC, 2))) {
			ran = rand() % 4 + 1;
			if (ran == 1) return 3;
			else if (ran == 2) return 6;
			else if (ran == 3) return 4;
			else if (ran == 4) return 8;
		}
		else if ((IsFree(vC, 1) && IsFree(vC, 2)) && (IsFree(vC, 4) && IsFree(vC, 8)) && (IsFree(vC, 3) && IsFree(vC, 6))) {
			ran = rand() % 6 + 1;
			if (ran == 1) return ran;
			else if (ran == 2) return ran;
			else if (ran == 3) return ran;
			else if (ran == 4) return ran;
			else if (ran == 5) return 8;
			else if (ran == 6) return ran;
		}



	}
	else if (i == 1) {
		if ((IsFree(vC, 0) && IsFree(vC, 2)) && (!IsFree(vC, 4) || !IsFree(vC, 7))) {
			ran = rand() % 1;
			if (ran == 0) return ran;
			else if (ran == 1) return 2;
		}
		else if ((IsFree(vC, 4) && IsFree(vC, 7)) && (!IsFree(vC, 0) || !IsFree(vC, 2))) {
			ran = rand() % 1;
			if (ran == 0) return 4;
			else if (ran == 1) return 7;
		}
		else if ((IsFree(vC, 0) && IsFree(vC, 2)) && (IsFree(vC, 4) && IsFree(vC, 7))) {
			ran = rand() % 3;
			if (ran == 0) return ran;
			else if (ran == 1) return 7;
			else if (ran == 2) return ran;
			else if (ran == 3) return 4;

		}
	}
	else if (i == 2) {
		if ((IsFree(vC, 0) && IsFree(vC, 1)) && (!IsFree(vC, 5) || !IsFree(vC, 8)) && (!IsFree(vC, 4) || !IsFree(vC, 6))) {
			ran = rand() % 1;
			return ran;
		}
		else if ((IsFree(vC, 5) && IsFree(vC, 8)) && (!IsFree(vC, 1) || !IsFree(vC, 0)) && (!IsFree(vC, 4) || !IsFree(vC, 6))) {
			ran = rand() % 2 + 1;
			if (ran == 1) return 5;
			else if (ran == 2) return 8;
		}
		else if ((IsFree(vC, 4) && IsFree(vC, 6)) && (!IsFree(vC, 1) || !IsFree(vC, 0)) && (!IsFree(vC, 5) || !IsFree(vC, 8))) {
			ran = rand() % 2 + 1;
			if (ran == 1) return 4;
			else if (ran == 2) return 6;
		}
		else if ((IsFree(vC, 1) && IsFree(vC, 0)) && (IsFree(vC, 5) && IsFree(vC, 8)) && (!IsFree(vC, 4) || !IsFree(vC, 6))) {
			ran = rand() % 3;
			if (ran == 0) return ran;
			else if (ran == 1) return ran;
			else if (ran == 2) return 5;
			else if (ran == 3) return 8;
		}
		else if ((IsFree(vC, 1) && IsFree(vC, 0)) && (IsFree(vC, 4) && IsFree(vC, 6)) && (!IsFree(vC, 5) || !IsFree(vC, 8))) {
			ran = rand() % 3;
			if (ran == 0) return ran;
			else if (ran == 1) return ran;
			else if (ran == 2) return 6;
			else if (ran == 3) return ran;
		}
		else if ((IsFree(vC, 4) && IsFree(vC, 6)) && (IsFree(vC, 5) && IsFree(vC, 8)) && (!IsFree(vC, 1) || !IsFree(vC, 0))) {
			ran = rand() % 7 + 4;
			if (ran == 4) return ran;
			else if (ran == 5) return ran;
			else if (ran == 6) return ran;
			else if (ran == 7) return 8;
		}
		else if ((IsFree(vC, 1) && IsFree(vC, 0)) && (IsFree(vC, 5) && IsFree(vC, 8)) && (IsFree(vC, 4) && IsFree(vC, 6))) {
			ran = rand() % 5;
			if (ran == 0) return ran;
			else if (ran == 1) return ran;
			else if (ran == 2) return 8;
			else if (ran == 3) return 6;
			else if (ran == 4) return ran;
			else if (ran == 5) return ran;
		}
	}
	else if (i == 3) {
		if ((IsFree(vC, 0) && IsFree(vC, 6)) && (!IsFree(vC, 4) || !IsFree(vC, 5))) {
			ran = rand() % 1;
			if (ran == 0) return ran;
			else if (ran == 1) return 6;
		}
		else if ((IsFree(vC, 4) && IsFree(vC, 5)) && (!IsFree(vC, 0) || !IsFree(vC, 6))) {
			ran = rand() % 1;
			if (ran == 0) return 4;
			else if (ran == 1) return 5;
		}
		else if ((IsFree(vC, 0) && IsFree(vC, 6)) && (IsFree(vC, 4) && IsFree(vC, 5))) {
			ran = rand() % 3;
			if (ran == 0) return ran;
			else if (ran == 1) return 6;
			else if (ran == 2) return 4;
			else if (ran == 3) return 5;

		}

		else  return SetNullToRandomCell(vC);



	}
	else if (i == 4) {
		if ((IsFree(vC, 2) && IsFree(vC, 6)) && (!IsFree(vC, 0) || !IsFree(vC, 8)) && (!IsFree(vC, 1) || !IsFree(vC, 7)) && (!IsFree(vC, 3) || !IsFree(vC, 5))) {
			ran = rand() % 1;
			if(ran==0)return 2;
			else if (ran == 1) return 6;
		}
		else if ((IsFree(vC, 0) && IsFree(vC, 8)) && (!IsFree(vC, 2) || !IsFree(vC, 6)) && (!IsFree(vC, 1) || !IsFree(vC, 7)) && (!IsFree(vC, 3) || !IsFree(vC, 5))) {
			ran = rand() % 1;
			if (ran == 0) return ran;
			else if (ran == 1) return 8;
		}
		else if ((IsFree(vC, 1) && IsFree(vC, 7)) && (!IsFree(vC, 3) || !IsFree(vC, 5)) && (!IsFree(vC, 0) || !IsFree(vC, 8)) && (!IsFree(vC, 2) || !IsFree(vC, 6))) {
			ran = rand() % 2 + 1;
			if (ran == 1) return ran;
			else if (ran == 2) return 7;
		}
		else if ((IsFree(vC, 3) && IsFree(vC, 5)) && (!IsFree(vC, 1) || !IsFree(vC, 7)) && (!IsFree(vC, 0) || !IsFree(vC, 8)) && (!IsFree(vC, 2) || !IsFree(vC, 6))) {
			ran = rand() % 2 + 1;
			if (ran == 1) return 3;
			else if (ran == 2) return 5;
		}

		else if ((IsFree(vC, 2) && IsFree(vC, 6)) && (IsFree(vC, 0) && IsFree(vC, 8)) && (!IsFree(vC, 1) || !IsFree(vC, 7)) && (!IsFree(vC, 3) || !IsFree(vC, 5))) {
			ran = rand() % 3;
			if (ran == 0) return ran;
			else if (ran == 1) return 6;
			else if (ran == 2) return ran;
			else if (ran == 3) return 8;
		}
		else if ((IsFree(vC, 2) && IsFree(vC, 6)) && (IsFree(vC, 1) && IsFree(vC, 7)) && (!IsFree(vC, 0) || !IsFree(vC, 8)) && (!IsFree(vC, 3) || !IsFree(vC, 5))) {
			ran = rand() % 3;
			if (ran == 0) return 2;
			else if (ran == 1) return 6;
			else if (ran == 3) return 1;
			else if (ran == 4) return 7;
		}
		else if ((IsFree(vC, 2) && IsFree(vC, 6)) && (IsFree(vC, 3) && IsFree(vC, 5)) && (!IsFree(vC, 0) || !IsFree(vC, 8)) && (!IsFree(vC, 1) || !IsFree(vC, 7))) {
			ran = rand() % 7 + 4;
			if (ran == 4) return 2;
			else if (ran == 5) return 6;
			else if (ran == 6) return 3;
			else if (ran == 7) return 5;
		}
		else if ((IsFree(vC, 0) && IsFree(vC, 8)) && (IsFree(vC, 1) && IsFree(vC, 7)) && (!IsFree(vC, 2) || !IsFree(vC, 6)) && (!IsFree(vC, 3) || !IsFree(vC, 5))) {
			ran = rand() % 7 + 4;
			if (ran == 4) return 0;
			else if (ran == 5) return 1;
			else if (ran == 6) return 7;
			else if (ran == 7) return 8;
		}
		else if ((IsFree(vC, 0) && IsFree(vC, 8)) && (IsFree(vC, 3) && IsFree(vC, 5)) && (!IsFree(vC, 2) || !IsFree(vC, 6)) && (!IsFree(vC, 1) || !IsFree(vC, 7))) {
			ran = rand() % 7 + 4;
			if (ran == 4) return 0;
			else if (ran == 5) return 8;
			else if (ran == 6) return 3;
			else if (ran == 7) return 5;
		}
		else if ((IsFree(vC, 1) && IsFree(vC, 7)) && (IsFree(vC, 3) && IsFree(vC, 5)) && (!IsFree(vC, 0) || !IsFree(vC, 8)) && (!IsFree(vC, 2) || !IsFree(vC, 6))) {
			ran = rand() % 7 + 4;
			if (ran == 4) return 1;
			else if (ran == 5) return 7;
			else if (ran == 6) return 3;
			else if (ran == 7) return 5;
		}
		else if ((IsFree(vC, 2) && IsFree(vC, 6)) && (IsFree(vC, 0) && IsFree(vC, 8)) && (IsFree(vC, 1) && IsFree(vC, 7)) && (!IsFree(vC, 3) || !IsFree(vC, 5))) {
			ran = rand() % 5;
			if (ran == 0) return 2;
			else if (ran == 1) return 6;
			else if (ran == 2) return 0;
			else if (ran == 3) return 8;
			else if (ran == 4) return 1;
			else if (ran == 5) return 7;
		}

		else if ((IsFree(vC, 8) && IsFree(vC, 0)) && (IsFree(vC, 1) && IsFree(vC, 7)) && (IsFree(vC, 3) && IsFree(vC, 5)) && (!IsFree(vC, 2) || !IsFree(vC, 6))) {
			ran = rand() % 5;
			if (ran == 0) return ran;
			else if (ran == 1) return ran;
			else if (ran == 2) return 8;
			else if (ran == 3) return 7;
			else if (ran == 4) return 3;
			else if (ran == 5) return 5;
		}
		else if ((IsFree(vC, 2) && IsFree(vC, 6)) && (IsFree(vC, 3) && IsFree(vC, 5)) && (IsFree(vC, 0) && IsFree(vC, 8)) && (!IsFree(vC, 1) || !IsFree(vC, 7))) {
			ran = rand() % 5;
			if (ran == 0) return 2;
			else if (ran == 1) return 6;
			else if (ran == 2) return 0;
			else if (ran == 3) return 8;
			else if (ran == 4) return 3;
			else if (ran == 5) return 5;
		}
		else if ((IsFree(vC, 2) && IsFree(vC, 6)) && (IsFree(vC, 1) && IsFree(vC, 7)) && (IsFree(vC, 3) && IsFree(vC, 5)) && (!IsFree(vC, 0) || !IsFree(vC, 8))) {
			ran = rand() % 5;
			if (ran == 0) return 2;
			else if (ran == 1) return 6;
			else if (ran == 2) return 1;
			else if (ran == 3) return 7;
			else if (ran == 4) return 3;
			else if (ran == 5) return 5;
		}

	}
	else if (i == 5) {
		if ((IsFree(vC, 2) && IsFree(vC, 8)) && (!IsFree(vC, 4) || !IsFree(vC, 3))) {
			ran = rand() % 1;
			if (ran == 0) return 8;
			else if (ran == 1) return 2;
		}
		else if ((IsFree(vC, 4) && IsFree(vC, 3)) && (!IsFree(vC, 8) || !IsFree(vC, 2))) {
			ran = rand() % 1;
			if (ran == 0) return 4;
			else if (ran == 1) return 3;
		}
		else if ((IsFree(vC, 8) && IsFree(vC, 2)) && (IsFree(vC, 4) && IsFree(vC, 3))) {
			ran = rand() % 3;
			if (ran == 0) return 2;
			else if (ran == 1) return 8;
			else if (ran == 2) return 3;
			else if (ran == 3) return 4;

		}
	}
	else if (i == 6) {
		if ((IsFree(vC, 0) && IsFree(vC, 3)) && (!IsFree(vC, 7) || !IsFree(vC, 8)) && (!IsFree(vC, 4) || !IsFree(vC, 2))) {
			ran = rand() % 1;
			if(ran==0) return ran;
			else if (ran == 1) return 3;
		}
		else if ((IsFree(vC, 7) && IsFree(vC, 8)) && (!IsFree(vC, 3) || !IsFree(vC, 0)) && (!IsFree(vC, 4) || !IsFree(vC, 2))) {
			ran = rand() % 2 + 1;
			if (ran == 1) return 7;
			else if (ran == 2) return 8;
		}
		else if ((IsFree(vC, 4) && IsFree(vC, 2)) && (!IsFree(vC, 3) || !IsFree(vC, 0)) && (!IsFree(vC, 7) || !IsFree(vC, 8))) {
			ran = rand() % 2 + 1;
			if (ran == 1) return 4;
			else if (ran == 2) return 2;
		}
		else if ((IsFree(vC, 3) && IsFree(vC, 0)) && (IsFree(vC, 7) && IsFree(vC, 8)) && (!IsFree(vC, 4) || !IsFree(vC, 2))) {
			ran = rand() % 3;
			if (ran == 0) return ran;
			else if (ran == 1) return 3;
			else if (ran == 2) return 7;
			else if (ran == 3) return 8;
		}
		else if ((IsFree(vC, 3) && IsFree(vC, 0)) && (IsFree(vC, 4) && IsFree(vC, 2)) && (!IsFree(vC, 7) || !IsFree(vC, 8))) {
			ran = rand() % 3;
			if (ran == 0) return ran;
			else if (ran == 1) return 4;
			else if (ran == 2) return ran;
			else if (ran == 3) return ran;
		}
		else if ((IsFree(vC, 7) && IsFree(vC, 8)) && (IsFree(vC, 2) && IsFree(vC, 4)) && (!IsFree(vC, 3) || !IsFree(vC, 0))) {
			ran = rand() % 7 + 4;
			if (ran == 4) return 7;
			else if (ran == 5) return 8;
			else if (ran == 6) return 2;
			else if (ran == 7) return 4;
		}
		else if ((IsFree(vC, 3) && IsFree(vC, 0)) && (IsFree(vC, 7) && IsFree(vC, 8)) && (IsFree(vC, 4) && IsFree(vC, 2))) {
			ran = rand() % 5;
			if (ran == 0) return ran;
			else if (ran == 1) return 3;
			else if (ran == 2) return 7;
			else if (ran == 3) return 8;
			else if (ran == 4) return 2;
			else if (ran == 5) return 4;
		}
	}
	else if (i == 7) {
		if ((IsFree(vC, 6) && IsFree(vC, 8)) && (!IsFree(vC, 4) || !IsFree(vC, 1))) {
			ran = rand() % 1;
			if (ran == 0) return 6;
			else if (ran == 1) return 8;
		}
		else if ((IsFree(vC, 4) && IsFree(vC, 1)) && (!IsFree(vC, 6) || !IsFree(vC, 8))) {
			ran = rand() % 1;
			if (ran == 0) return 4;
			else if (ran == 1) return ran;
		}
		else if ((IsFree(vC, 6) && IsFree(vC, 8)) && (IsFree(vC, 4) && IsFree(vC, 1))) {
			ran = rand() % 3;
			if (ran == 0) return 1;
			else if (ran == 1) return 4;
			else if (ran == 2) return 6;
			else if (ran == 3) return 8;

		}
	}
	else if (i == 8) {
		if ((IsFree(vC, 6) && IsFree(vC, 7)) && (!IsFree(vC, 2) || !IsFree(vC, 5)) && (!IsFree(vC, 4) || !IsFree(vC, 0))) {
			ran = rand() % 1;
			if (ran == 0) return 6;
			else if (ran == 1) return 7;
		}
		else if ((IsFree(vC, 2) && IsFree(vC, 5)) && (!IsFree(vC, 6) || !IsFree(vC, 7)) && (!IsFree(vC, 4) || !IsFree(vC, 0))) {
			ran = rand() % 2 + 1;
			if (ran == 1) return 2;
			else if (ran == 2) return 5;
		}
		else if ((IsFree(vC, 4) && IsFree(vC, 0)) && (!IsFree(vC, 6) || !IsFree(vC, 7)) && (!IsFree(vC, 2) || !IsFree(vC, 5))) {
			ran = rand() % 2 + 1;
			if (ran == 1) return 4;
			else if (ran == 2) return 0;
		}
		else if ((IsFree(vC, 6) && IsFree(vC, 7)) && (IsFree(vC, 2) && IsFree(vC, 5)) && (!IsFree(vC, 4) || !IsFree(vC, 0))) {
			ran = rand() % 3;
			if (ran == 0) return 6;
			else if (ran == 1) return 7;
			else if (ran == 2) return 2;
			else if (ran == 3) return 5;
		}
		else if ((IsFree(vC, 6) && IsFree(vC, 7)) && (IsFree(vC, 4) && IsFree(vC, 0)) && (!IsFree(vC, 2) || !IsFree(vC, 5))) {
			ran = rand() % 3;
			if (ran == 0) return ran;
			else if (ran == 1) return 4;
			else if (ran == 2) return 6;
			else if (ran == 3) return 7;
		}
		else if ((IsFree(vC, 2) && IsFree(vC, 5)) && (IsFree(vC, 0) && IsFree(vC, 4)) && (!IsFree(vC, 6) || !IsFree(vC, 7))) {
			ran = rand() % 7 + 4;
			if (ran == 4) return 2;
			else if (ran == 5) return 5;
			else if (ran == 6) return 0;
			else if (ran == 7) return 4;
		}
		else if ((IsFree(vC, 6) && IsFree(vC, 7)) && (IsFree(vC, 2) && IsFree(vC, 5)) && (IsFree(vC, 4) && IsFree(vC, 0))) {
			ran = rand() % 5;
			if (ran == 0) return 6;
			else if (ran == 1) return 7;
			else if (ran == 2) return 2;
			else if (ran == 3) return 5;
			else if (ran == 4) return 0;
			else if (ran == 5) return 4;
		}
	}
	else return SetNullToRandomCell(vC);
}
bool IsTwoFromThreeNullsPicked(vector<Cell>&vC) {

	if ((vC[0].Null == TRUE&&vC[1].Null == TRUE)
		|| (vC[0].Null == TRUE&&vC[2].Null == TRUE)
		|| (vC[0].Null == TRUE&&vC[3].Null == TRUE)
		|| (vC[0].Null == TRUE&&vC[4].Null == TRUE)
		|| (vC[0].Null == TRUE&&vC[6].Null == TRUE)
		|| (vC[0].Null == TRUE&&vC[8].Null == TRUE)
		|| (vC[1].Null == TRUE&&vC[2].Null == TRUE)
		|| (vC[1].Null == TRUE&&vC[4].Null == TRUE)
		|| (vC[1].Null == TRUE&&vC[7].Null == TRUE)
		|| (vC[2].Null == TRUE&&vC[4].Null == TRUE)
		|| (vC[2].Null == TRUE&&vC[5].Null == TRUE)
		|| (vC[2].Null == TRUE&&vC[6].Null == TRUE)
		|| (vC[2].Null == TRUE&&vC[8].Null == TRUE)
		|| (vC[3].Null == TRUE&&vC[4].Null == TRUE)
		|| (vC[3].Null == TRUE&&vC[5].Null == TRUE)
		|| (vC[3].Null == TRUE&&vC[6].Null == TRUE)
		|| (vC[4].Null == TRUE&&vC[5].Null == TRUE)
		|| (vC[4].Null == TRUE&&vC[6].Null == TRUE)
		|| (vC[4].Null == TRUE&&vC[7].Null == TRUE)
		|| (vC[4].Null == TRUE&&vC[8].Null == TRUE)
		|| (vC[5].Null == TRUE&&vC[8].Null == TRUE)
		|| (vC[6].Null == TRUE&&vC[7].Null == TRUE)
		|| (vC[6].Null == TRUE&&vC[8].Null == TRUE)
		|| (vC[7].Null == TRUE&&vC[8].Null == TRUE)
		)
		return true;
	else return false;
}
int TwoFromThreeNullsPos(vector<Cell>&vC) {
	if (vC[0].Null == TRUE&&vC[1].Null == TRUE&&IsFree(vC,2)) return 2;
	else if (vC[0].Null == TRUE&&vC[2].Null == TRUE&&IsFree(vC, 1)) return 1;
	else if (vC[0].Null == TRUE&&vC[3].Null == TRUE&&IsFree(vC, 6)) return 6;
	else if (vC[0].Null == TRUE&&vC[4].Null == TRUE&&IsFree(vC, 8)) return 8;
	else if (vC[0].Null == TRUE&&vC[6].Null == TRUE&&IsFree(vC, 3)) return 3;
	else if (vC[0].Null == TRUE&&vC[8].Null == TRUE&&IsFree(vC, 4)) return 4;
	else if (vC[1].Null == TRUE&&vC[2].Null == TRUE&&IsFree(vC, 0)) return 0;
	else if (vC[1].Null == TRUE&&vC[4].Null == TRUE&&IsFree(vC, 7)) return 7;
	else if (vC[1].Null == TRUE&&vC[7].Null == TRUE&&IsFree(vC, 4)) return 4;
	else if (vC[2].Null == TRUE&&vC[4].Null == TRUE&&IsFree(vC, 6)) return 6;
	else if (vC[2].Null == TRUE&&vC[5].Null == TRUE&&IsFree(vC, 8)) return 8;
	else if (vC[2].Null == TRUE&&vC[6].Null == TRUE&&IsFree(vC, 4)) return 4;
	else if (vC[2].Null == TRUE&&vC[8].Null == TRUE&&IsFree(vC, 5)) return 5;
	else if (vC[3].Null == TRUE&&vC[4].Null == TRUE&&IsFree(vC, 5)) return 5;
	else if (vC[3].Null == TRUE&&vC[5].Null == TRUE&&IsFree(vC, 4)) return 4;
	else if (vC[3].Null == TRUE&&vC[6].Null == TRUE&&IsFree(vC, 0)) return 0;
	else if (vC[4].Null == TRUE&&vC[5].Null == TRUE&&IsFree(vC, 3)) return 3;
	else if (vC[4].Null == TRUE&&vC[6].Null == TRUE&&IsFree(vC, 2)) return 2;
	else if (vC[4].Null == TRUE&&vC[7].Null == TRUE&&IsFree(vC, 1)) return 1;
	else if (vC[4].Null == TRUE&&vC[8].Null == TRUE&&IsFree(vC, 0)) return 0;
	else if (vC[5].Null == TRUE&&vC[8].Null == TRUE&&IsFree(vC, 2)) return 2;
	else if (vC[6].Null == TRUE&&vC[7].Null == TRUE&&IsFree(vC, 8)) return 8;
	else if (vC[6].Null == TRUE&&vC[8].Null == TRUE&&IsFree(vC, 7)) return 7;
	else if (vC[7].Null == TRUE&&vC[8].Null == TRUE&&IsFree(vC, 6)) return 6;
	else return SetNullToRandomCell(vC);
}
vector<Rectangles> vR;
vector<Cell> vC;
BOOL RealPlayer = TRUE;
ofstream fout("BattleList.txt", std::ios::app);
ifstream fin("BattleList.txt", std::ios::app);
fstream file("BattleList.txt");
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Game(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Opponent(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Computer(HWND, UINT, WPARAM, LPARAM);


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
    LoadStringW(hInstance, IDC_FIFTHWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIFTHWINAPI));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FIFTHWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FIFTHWINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
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
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
			
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case ID_GAME_STARTNEWGAME:
				if (RealPlayer == TRUE) {
					DialogBox(hInst, MAKEINTRESOURCE(IDD_GAME), hWnd, Game);
					break;
				}
				else if (RealPlayer == FALSE) {
					DialogBox(hInst, MAKEINTRESOURCE(IDD_WITHCOMPUTER), hWnd, Computer);
					break;
				}
				break;
			case ID_GAME_SETOPPONENT:
				
					DialogBox(hInst, MAKEINTRESOURCE(IDD_OPPONENT), hWnd, Opponent);
				
				break;
			case ID_BATTLELIST_CLEARBATTLEHISTORY:
				file.clear();
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
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT Rect;
	static int x, y;
	
	
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
INT_PTR CALLBACK Game(HWND hGam, UINT message, WPARAM wParam, LPARAM lParam) {
	static RECT Rect;
	static int x, y;
	static int a, b;
	static POINT Center;
	static HDC hdc;
	static int halfside = 70;
	static HPEN LinesPen = CreatePen(PS_DOT, 7, RGB(0, 250, 154));
	
	static HPEN RectPen= CreatePen(PS_DOT, 7, RGB(255, 0, 0));
	
	static BOOL Init = TRUE;

	static BOOL FirstPlayer = TRUE;

	static int mas;

	const int SwitcherSize=10;
	
	static int steps = 0;

	
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG: {
		GetClientRect(hGam, &Rect);
		x = Rect.right - Rect.left;
		y = Rect.bottom - Rect.top;
		Center.x = x / 2;
		Center.y = y / 2;

			if (Init) {
				for (int i = 0; i < 9; i++) 
					vC.push_back(Cell(FALSE, FALSE));

					PushInVector(hdc, vR, Center, halfside, RectPen);
				
			}
			Init = FALSE;
			if (!Init) {
				for (int i = 0; i < 9; i++)
					vC[i] = { FALSE, FALSE };
			}

			FirstPlayer = TRUE;
			steps = 0; 
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hGam, NULL);
			return (INT_PTR)TRUE;
		}
		break;

	case WM_PAINT:
	{
		
		PAINTSTRUCT ps;
		hdc = BeginPaint(hGam, &ps);
		DrawLattice(hdc, Center, halfside, LinesPen);
		for (int i = 0; i < vC.size(); i++) {
			
			if (FirstPlayer&&steps!=9) {
				DrawSwitchCross(hdc, x, y, SwitcherSize, RectPen);
			}
			else if (!FirstPlayer&&steps!=9) {
				DrawSwitchNull(hdc, x, y, SwitcherSize, RectPen);
			}
			else if (steps == 9) {
				DrawSwitchLine(hdc, x, y, SwitcherSize, RectPen);
			}

			if (FirstPlWin(vC, FirstPlayer) == 1) {
				DrawAllElements(hdc, vR, vC, halfside, LinesPen);
				DefineAndCross_3_In_a_RowCrosses(hdc, vR, vC, halfside, RectPen);
				fout << "First Player defeated Second Player " <<"("<<__TIMESTAMP__<<")"<< endl;
				mas = MessageBox(hGam, (LPCWSTR)L"FirstPlayer Wins!", (LPCWSTR)L"Congratulations", MB_OK);
				if (mas == IDOK)
				{
					EndDialog(hGam, NULL);
				}
				break;
			}
			else if (FirstPlWin(vC, FirstPlayer) == 2)
			{
				DrawAllElements(hdc, vR, vC, halfside, LinesPen);
				DefineAndCross_3_In_a_RowNulls(hdc, vR, vC, halfside, RectPen);
				fout << "Second Player defeated First Player " << "(" << __TIMESTAMP__ << ")" << endl;
					mas = MessageBox(hGam, (LPCWSTR)L"SecondPlayer Wins!", (LPCWSTR)L"Congratulations", MB_OK);
					if (mas == IDOK)
					{
						EndDialog(hGam, NULL);
					}
				break;
			}
			else if ((FirstPlWin(vC, FirstPlayer) == 0) && (steps == 9))
			{
				DrawAllElements(hdc, vR, vC, halfside, LinesPen);
				fout << "First Player tied with Second Player " << "(" << __TIMESTAMP__ << ")" << endl;
				mas = MessageBox(hGam, (LPCWSTR)L"Friendship Wins!", (LPCWSTR)L"You tied!", MB_OK);
				if (mas == IDOK) {
					EndDialog(hGam, NULL);
				}
				break;
			}

			if (vC[i].Cross==TRUE) {
				DrawCross(hdc, vR, i, halfside, LinesPen);
			}
			else if (vC[i].Null == TRUE) {
				DrawNull(hdc, vR, i, halfside, LinesPen);
			}
		
		}


		
		EndPaint(hGam, &ps);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		a = LOWORD(lParam);
		b = HIWORD(lParam);
		for (int i = 0; i < vR.size(); i++)
		{

			if (InRect(a, b, vR[i].Center, halfside) && vC[i].Cross == FALSE&&vC[i].Null == FALSE)
			{

				steps++;
				if (FirstPlayer == TRUE) {
					vC[i].Cross = TRUE;
					FirstPlayer = FALSE;
				}
				else if (FirstPlayer == FALSE) {
					vC[i].Null = TRUE;
					FirstPlayer = TRUE;
				}

				break;
			}
			
				if (FirstPlWin(vC, FirstPlayer) == 1) {
					mas = MessageBox(hGam, (LPCWSTR)L"FirstPlayer Wins!", (LPCWSTR)L"Congratulations", MB_OK);
					if (mas == IDOK)
					{
						EndDialog(hGam, NULL);
					}
					break;
				}
				else if (FirstPlWin(vC, FirstPlayer) == 2)
				{
					mas = MessageBox(hGam, (LPCWSTR)L"SecondPlayer Wins!", (LPCWSTR)L"Congratulations", MB_OK);
					if (mas == IDOK) {
						EndDialog(hGam, NULL);
					}
					break;
				}
				else if ((FirstPlWin(vC, FirstPlayer) == 0) && (steps == 9))
				{
				mas = MessageBox(hGam, (LPCWSTR)L"Friendship Wins!", (LPCWSTR)L"You tied!", MB_OK);
				if (mas == IDOK) {
				EndDialog(hGam, NULL);
				}
				break;
				}
			}
		
		
	
		InvalidateRect(hGam, NULL, TRUE);
		break;
	}

		
	}
	
	

	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK Opponent(HWND hOpp, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT Rect;
	static int x, y;


	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND: {
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hOpp, NULL);
			return (INT_PTR)TRUE;
		}
		
		switch (LOWORD(wParam)) {
		case IDC_REALPLAYER: {
			RealPlayer = TRUE;
			break;
		}
		case IDC_COMPUTER: {
			RealPlayer = FALSE;
			break;
		}


			break;
		}
		break;
	}

		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK Computer(HWND hCom, UINT message, WPARAM wParam, LPARAM lParam){
	static RECT Rect;
	static int x, y;
	static int a, b;
	static POINT Center;
	static HDC hdc;
	static int halfside = 70;
	static HPEN LinesPen = CreatePen(PS_DOT, 7, RGB(0, 250, 154));

	static HPEN RectPen = CreatePen(PS_DOT, 7, RGB(255, 0, 0));

	static BOOL Init = TRUE;

	static BOOL FirstPlayer = TRUE;

	static int mas;

	const int SwitcherSize = 10;

	static int steps = 0;

	static int random;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG: {
		GetClientRect(hCom, &Rect);
		x = Rect.right - Rect.left;
		y = Rect.bottom - Rect.top;
		Center.x = x / 2;
		Center.y = y / 2;

		if (Init) {
			for (int i = 0; i < 9; i++)
				vC.push_back(Cell(FALSE, FALSE));

			PushInVector(hdc, vR, Center, halfside, RectPen);

		}
		Init = FALSE;
		if (!Init) {
			for (int i = 0; i < 9; i++)
				vC[i] = { FALSE, FALSE };
		}

		FirstPlayer = TRUE;
		steps = 0;
		random = 0;
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hCom, NULL);
			return (INT_PTR)TRUE;
		}
		break;

	case WM_PAINT:
	{

		PAINTSTRUCT ps;
		hdc = BeginPaint(hCom, &ps);
		DrawLattice(hdc, Center, halfside, LinesPen);
		for (int i = 0; i < vC.size(); i++) {

			if (FirstPlayer&&steps != 9) {
				DrawSwitchCross(hdc, x, y, SwitcherSize, RectPen);
			}
			else if (!FirstPlayer&&steps != 9) {
				DrawSwitchNull(hdc, x, y, SwitcherSize, RectPen);
			}
			else if (steps == 9) {
				DrawSwitchLine(hdc, x, y, SwitcherSize, RectPen);
			}

			if (FirstPlWin(vC, FirstPlayer) == 1) {
				DrawAllElements(hdc, vR, vC, halfside, LinesPen);
				DefineAndCross_3_In_a_RowCrosses(hdc, vR, vC, halfside, RectPen);
			mas = MessageBox(hCom, (LPCWSTR)L"FirstPlayer Wins!", (LPCWSTR)L"Congratulations", MB_OK);
			fout << "First Player defeated The Computer " << "(" << __TIMESTAMP__ << ")" << endl;
				if (mas == IDOK)
				{
					EndDialog(hCom,NULL);
				}
				break;
			}
			else if (FirstPlWin(vC, FirstPlayer) == 2)
			{
				DrawAllElements(hdc, vR, vC, halfside, LinesPen);
				DefineAndCross_3_In_a_RowNulls(hdc, vR, vC, halfside, RectPen);
				mas = MessageBox(hCom, (LPCWSTR)L"Computer Wins!", (LPCWSTR)L"Congratulations", MB_OK);
				fout << "The Computer defeated The Player " << "(" << __TIMESTAMP__ << ")" << endl;
				if (mas == IDOK)
				{
					EndDialog(hCom, NULL);
				}
				break;
			}
			else if ((FirstPlWin(vC, FirstPlayer) == 0) && (steps == 9))
			{
				DrawAllElements(hdc, vR, vC, halfside, LinesPen);
				mas = MessageBox(hCom, (LPCWSTR)L"Friendship Wins!", (LPCWSTR)L"You tied!", MB_OK);
				fout << "First Player tied with The Computer " << "(" << __TIMESTAMP__ << ")" << endl;
				if (mas == IDOK) {
					EndDialog(hCom,NULL);
				}
				break;
			}

			if (vC[i].Cross == TRUE) {
				DrawCross(hdc, vR, i, halfside, LinesPen);
			}
			else if (vC[i].Null == TRUE) {
				DrawNull(hdc, vR, i, halfside, LinesPen);
			}

		}



		EndPaint(hCom, &ps);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		a = LOWORD(lParam);
		b = HIWORD(lParam);
		for (int i = 0; i < vR.size(); i++)
		{

			if (InRect(a, b, vR[i].Center, halfside) && IsFree(vC,i))
			{

				
				if (FirstPlayer == TRUE) 
				{
					steps++;
					vC[i].Cross = TRUE;
					FirstPlayer = FALSE;
					
					
				}	

				else if(FirstPlayer==FALSE&&steps == 1)
				{
					steps++;
					bool aa = true;
					while (aa)
					{
						random = rand() % 9;
						if (IsFree(vC,random))
						{
							vC[random].Null = TRUE;
							FirstPlayer = TRUE;
							aa = false;
						}
					}
				}
				else if (FirstPlayer == FALSE&&steps == 3)
				{
					steps++;
					if (IsTwoFromThreeCrossesPicked(vC)) {
						vC[TwoFromThreeCrossesNullPos(vC)].Null = TRUE;
						FirstPlayer = TRUE;
					}
					else { 
						vC[WherePickNullTwoFromThree(vC)].Null = TRUE;
						FirstPlayer = TRUE;
					}
					
				}
				else if (FirstPlayer == FALSE&&steps == 5)
				{
					steps++;
					if(IsTwoFromThreeNullsPicked(vC)){
						vC[TwoFromThreeNullsPos(vC)].Null = TRUE;
						FirstPlayer = TRUE;
					}
					else {
						vC[WherePickNullTwoFromThree(vC)].Null = TRUE;
						FirstPlayer = TRUE;
					}
				/*else {
						vC[SetNullToRandomCell(vC)].Null = TRUE;
						FirstPlayer = TRUE;
					}*/


				}
				else if (FirstPlayer == FALSE&&steps == 7)
				{
					steps++;
					vC[SetNullToRandomCell(vC)].Null = TRUE;
					FirstPlayer = TRUE;
				}
				
			}
	
						
		}
		
	


		InvalidateRect(hCom, NULL, TRUE);
		break;
	}


	}



	return (INT_PTR)FALSE;
}

