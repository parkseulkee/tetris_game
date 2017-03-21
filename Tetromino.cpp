#include "Tetromino.h"
#include <iostream>
#include <windows.h>
using namespace std;

Point g_tetromino_pattern[7][4][4] =
{
	{ { Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) }, { Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) },
	{ Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) }, { Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) } },  // I
	{ { Point(0, 1), Point(0, 0), Point(0, -1), Point(-1, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, 1) },
	{ Point(0, 1), Point(0, 0), Point(1, 1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(1, -1) } },  // J
	{ { Point(-1, 1), Point(0, 1), Point(0, 0), Point(0, -1) }, { Point(1, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
	{ Point(0, 1), Point(0, 0), Point(0, -1), Point(1, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, -1) } }, // L
	{ { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) },
	{ Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) } },  // O
	{ { Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) }, { Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) },
	{ Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) }, { Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) } },  // S
	{ { Point(0, 1), Point(-1, 0), Point(0, 0), Point(0, -1) }, { Point(0, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
	{ Point(0, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(0, -1) } },  // T
	{ { Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) },
	{ Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) } }  // Z
	
};

Tetromino::Tetromino(Board *board, TETROMINO_TYPE type) : board_(board), type_(type)
{
	rotate_ = 0;
	switch (type_)
	{
	case TETROMINO_I:
		color_ = 2; break; //어두운 초록
	case TETROMINO_J:
		color_ = 9; break; //파랑
	case TETROMINO_L:
		color_ = 10; break; // 초록
	case TETROMINO_O:
		color_ = 11; break; //하늘
	case TETROMINO_S:
		color_ = 12; break; //빨강
	case TETROMINO_T:
		color_ = 13; break; //보라
	case TETROMINO_Z:
		color_ = 14; break; // 노랑
	}
}
void Tetromino::Draw(Point reference_pos)
{
	SetColor(color_);
	ghost_pos_ = center_pos_;

	while (GhostCheckValidPos())
		ghost_pos_.SetY(ghost_pos_.GetY() - 1);
	ghost_pos_.SetY(ghost_pos_.GetY() + 1);
	for (int i = 0; i < 4; i++)
	{
		Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(ghost_pos_ + g_tetromino_pattern[type_][rotate_][i]));
		if ((ghost_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY()<20 && (ghost_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetX()<10)
			cout << "□";
	}
	for (int i = 0; i < 4; i++)
	{
		Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]));
		if ((center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY()<20)
			cout << "■";
	}
}

void Tetromino::Erase(Point reference_pos)
{
	for (int i = 0; i < 4; i++)
	{
		Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(ghost_pos_ + g_tetromino_pattern[type_][rotate_][i]));
		if ((ghost_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY() < 20 && (ghost_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetX()<10)
			cout << "　"; 
	}
	for (int i = 0; i < 4; i++)
	{
		Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]));
		if ((center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY() < 20)
			cout << "　"; 
	}
}

void Tetromino::SetCenterPos(Point pos)
{
    center_pos_ = pos;
}

bool Tetromino::MoveDown(Point reference_pos)
{
	center_pos_.SetY(center_pos_.GetY() - 1);
	if (CheckValidPos())
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		Erase(reference_pos);
		center_pos_.SetY(center_pos_.GetY() - 1);
		Draw(reference_pos);
	}
	else
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		return false;
	}
    return true;
}

void Tetromino::MoveRight(Point reference_pos)
{
	center_pos_.SetX(center_pos_.GetX() + 1);

    if (CheckValidPos())
    {
		center_pos_.SetX(center_pos_.GetX() - 1);
        Erase(reference_pos);
		center_pos_.SetX(center_pos_.GetX() + 1);
        Draw(reference_pos);
    }
    else
    {
		center_pos_.SetX(center_pos_.GetX() - 1);
	}
}

void Tetromino::MoveLeft(Point reference_pos)
{
	center_pos_.SetX(center_pos_.GetX() - 1);

	if (CheckValidPos())
	{
		center_pos_.SetX(center_pos_.GetX() + 1);
		Erase(reference_pos);
		center_pos_.SetX(center_pos_.GetX() - 1);
		Draw(reference_pos);
	}
	else
		center_pos_.SetX(center_pos_.GetX() + 1);
}

void Tetromino::Rotate(Point reference_pos)
{
	Erase(reference_pos);
	rotate_ = (rotate_ + 1) % ROTATE_COUNT;

	if (CheckValidPos())
		Draw(reference_pos);
	else
	{
		rotate_ = (rotate_ - 1) % ROTATE_COUNT;
		Draw(reference_pos);
	}
}

void Tetromino::GoBottom(Point reference_pos)
{
    while (MoveDown(reference_pos))
    {
    }
}

bool Tetromino::CheckValidPos(void)
{
    for (int i = 0; i < 4; i++)
    {
		Point cur_pos(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());

        if (cur_pos.GetX() < 0 || cur_pos.GetX() > 9)
            return false;
        if (cur_pos.GetY() < 0)
            return false;
        if (cur_pos.GetY() <= 19 && board_->GetState(cur_pos) != EMPTY)
            return false;
    }

    return true;
}
bool Tetromino::GhostCheckValidPos(void)
{
	for (int i = 0; i < 4; i++)
	{
		Point cur_pos(ghost_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), ghost_pos_.GetY() + 
			g_tetromino_pattern[type_][rotate_][i].GetY());

		if (cur_pos.GetX() < 0 || cur_pos.GetX() > 9)
			return false;
		if (cur_pos.GetY() < 0)
			return false;
		if (cur_pos.GetY() <= 19 && board_->GetState(cur_pos) != EMPTY)
			return false;
	}

	return true;
}

void Tetromino::MarkCurTetrominoPos(Point reference_pos)
{
    // board_ 2차원 배열에서 테트로미노의 4개의 각 점 위치를 mark하기
	for (int i = 0; i < 4; i++)
		board_->SetState(center_pos_ + g_tetromino_pattern[type_][rotate_][i], color_);
}

bool Tetromino::CheckEndCondition(void)
{
    //y축으로 20이상이면 게임 종료 
	
	for (int i = 0; i < 10; i++)
	{
		if (board_->GetState(Point(i, 19)) != EMPTY)
			return true;
	}
    return false;
}
void Tetromino::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15*16+color);
}

