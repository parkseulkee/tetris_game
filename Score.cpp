#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;
#include "Score.h"

Score::Score()
{
    score_ = 0;
    score_pos_ = Point(28, 9);
}

void Score::Print(Point reference_pos)
{
    Point::GotoXY(reference_pos + score_pos_);
    cout << "    ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 * 16 + 0);
    Point::GotoXY(reference_pos + score_pos_);
    cout << setw(5) << score_;
}

void Score::UpdateScore(Point reference_pos, int increment)
{
	if (increment != 1)
		score_ += increment * 3; // 여러개 라인 삭제시 라인*3점 증가
	else
		score_ += increment;
    Print(reference_pos);
}

int Score::GetScore()
{
	return score_;
}