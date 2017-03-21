#include <iostream>
#include <windows.h>
#include "Board.h"
using namespace std;

Board::Board()
{
	int i, j;

	for (i = 0; i < 10; i++) 
    {
		for (j = 0; j < 20; j++)
			board_[i][j] = EMPTY;
	}
}

int Board::GetState(Point pos)
{ 
	return board_[pos.GetX()][pos.GetY()]; 
}

void Board::SetState(Point pos, int state) 
{ 
	board_[pos.GetX()][pos.GetY()] = state;	
}

int Board::CheckLineFull(Point reference_pos)
{
	int count = 0;

	for (int i = 0; i < 20; i++)
	{
		int full = 0;
		for (int j = 0; j < 10; j++)
		{
			if (GetState(Point(j, i)) != EMPTY)
				full++;
		}
		if (full == 10)
		{
			count++;
			for (int j = 0; j < 10; j++)
			{
				SetState(Point(j, i), EMPTY);
				Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(j,i)));
				cout << "¡¡";
			}
			for (int k = i ; k < 20; k++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (GetState(Point(j, k)) != EMPTY)
					{
						SetState(Point(j, k - 1), GetState(Point(j, k)));
						SetState(Point(j, k), EMPTY);
						Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(j, k)));
						cout << "¡¡";
						SetColor(GetState(Point(j, k-1)));
						Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(j, k-1)));
						cout << "¡á";
					}
				}
			}
			i--;
		}
	}
	return count;
}
void Board::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 * 16 + color);
}
void Board::LevelUp(Point reference_pos,int line)
{
	for (int k = 19; k >= 0; k--)
	{
		for (int j = 0; j < 10; j++)
		{
			if (GetState(Point(j, k)) != EMPTY)
			{
				SetState(Point(j, k + line), GetState(Point(j, k)));
				SetState(Point(j, k), EMPTY);
				Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(j, k)));
				cout << "¡¡";
				if (Point(j, k + line).GetY() < 20)
				{
					SetColor(GetState(Point(j, k + line)));
					Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(j, k + line)));
					cout << "¡á";
				}
			}
		}
	}
	int k = 0;
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (k % 3 != 0)
			{
				SetState(Point(j, i), 8);
				SetColor(GetState(Point(j, i)));
				Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(j, i)));
				cout << "¡á";
			}
			k++;
		}
	}
}
