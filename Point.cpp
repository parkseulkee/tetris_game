#include <windows.h>
#include <conio.h>
#include <ctime>
#include "Point.h"
using namespace std;

Point::Point(int x, int y) : x_(x), y_(y) 
{ 

}

Point Point::operator+(const Point &pt)
{
	return Point(x_ + pt.x_, y_ + pt.y_);
}

void Point::GotoXY(int x, int y)		// 커서 위치 이동
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Point::GotoXY(Point pos)
{
	GotoXY(pos.GetX(), pos.GetY());
}

Point Point::GetScrPosFromCurPos(const Point &pos)
{
	return Point(2 * pos.x_ + 2, (-1) * pos.y_ + 20);
}