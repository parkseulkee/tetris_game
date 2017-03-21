#include "Tetris.h"
#include "Controller.h"
#include "Tetromino.h"
//#include "GhostTetromino.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

Tetris::Tetris(Point reference_pos, int key_esc, int key_right,int key_left , int key_rotate, int key_down, int key_space,int key_angel ) 
	: reference_pos_(reference_pos)
{ 
    running_ = true; 
    cur_tetromino_ = NULL;
    next_tetromino_ = NULL;
    start_time_ = clock();
    falling_speed_ = 0.8;
	level_ = 0;
	angel_count_ = 0;
    SetCursorInvisible();
	
    controller_.SetController(key_esc, key_right, key_left, key_rotate, key_down, key_space,key_angel);
    DrawBoard();
    GenerateNextTetromino();
    GetCurTetrominoFromNext();
    GenerateNextTetromino();
	cur_tetromino_->Draw(reference_pos_);
	next_tetromino_->Draw(reference_pos_);
    score_.Print(reference_pos_);
}

void Tetris::DrawBoard(void)
{
    int i;

    Point::GotoXY(reference_pos_);
    cout << "▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦";
	for (i = 0; i < 6; i++) {
		Point::GotoXY(reference_pos_ + Point(0, i + 1));
		cout << "▦                    ▦            ▦";
	}
	Point::GotoXY(reference_pos_ + Point(0, i + 1));
	cout << "▦                    ▦▦▦▦▦▦▦▦";
	for (i = 7; i < 10; i++) {
		Point::GotoXY(reference_pos_ + Point(0, i + 1));
		cout << "▦                    ▦            ▦";
	}
	Point::GotoXY(reference_pos_ + Point(0, i + 1));
	cout << "▦                    ▦▦▦▦▦▦▦▦";
	Point::GotoXY(reference_pos_ + Point(0, 11 + 1));
	cout << "▦                    ▦            ▦";
	Point::GotoXY(reference_pos_ + Point(0, 12 + 1));
	cout << "▦                    ▦            ▦";
	Point::GotoXY(reference_pos_ + Point(0, 13 + 1));
	if (controller_.Getkey_right() == KEY_RIGHT)
		cout << "▦                    ▦  → right  ▦";
	else
		cout << "▦                    ▦  d  right  ▦";
	Point::GotoXY(reference_pos_ + Point(0, 14 + 1));
	if (controller_.Getkey_left() == KEY_LEFT)
		cout << "▦                    ▦  ← left   ▦";
	else
		cout << "▦                    ▦  a  left   ▦";
	Point::GotoXY(reference_pos_ + Point(0, 15 + 1));
	if (controller_.Getkey_rotate() == KEY_UP)
		cout << "▦                    ▦ ↑ rotate  ▦";
	else
		cout << "▦                    ▦  w rotate  ▦";
	Point::GotoXY(reference_pos_ + Point(0, 16 + 1));
	if (controller_.Getkey_down() == KEY_DOWN)
		cout << "▦                    ▦ ↓ s/drop  ▦";
	else
		cout << "▦                    ▦  s s/drop  ▦";
	Point::GotoXY(reference_pos_ + Point(0, 17 + 1));
	cout << "▦                    ▦            ▦";
	Point::GotoXY(reference_pos_ + Point(26, 17 + 1));
	cout << (char)controller_.Getkey_angel() << "  pass";
	Point::GotoXY(reference_pos_ + Point(0, 18 + 1));
	cout << "▦                    ▦            ▦";
	Point::GotoXY(reference_pos_ + Point(0, 19 + 1));
	cout << "▦                    ▦            ▦";
	Point::GotoXY(reference_pos_ + Point(0, 20 + 1));
	cout << "▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦";
	Point::GotoXY(reference_pos_ + Point(0, 20 + 2));
	cout << "pass_chance :" << 5 - angel_count_;
}

void Tetris::Run(void)
{
    while (running_) 
    {
        RunStep();
    }
}

void Tetris::RunStep(void)
{
    if (kbhit()) 
    {
        int key = Controller::GetKey();
        KeyHandler(key);
    }
    else 
    {
        NormalStep();		
    }
}

bool Tetris::KeyHandler(int key)
{
    if (key == controller_.Getkey_esc()) 
    {
        running_ = false;
        return true;
    }
    else if (key == controller_.Getkey_right()) 
    {
        cur_tetromino_->MoveRight(reference_pos_);
        return true;
    }
    else if (key == controller_.Getkey_left()) 
    {
        cur_tetromino_->MoveLeft(reference_pos_);
        return true;
    }
    else if (key == controller_.Getkey_rotate()) 
    {
        cur_tetromino_->Rotate(reference_pos_);
        return true;
    }
	else if (key == controller_.Getkey_down())
	{
		cur_tetromino_->MoveDown(reference_pos_);
		return true;
	}
    else if (key == controller_.Getkey_space()) 
    {
        cur_tetromino_->GoBottom(reference_pos_);
        PrepareNextStep();
        return true;
    }
	else if (key == controller_.Getkey_angel())
	{
		PassTetormino();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 * 16 + 0);
		Point::GotoXY(reference_pos_ + Point(0, 20 + 2));
		cout << "pass_chance :" << 5 - angel_count_;
		return true;
	}

    return false;
}

void Tetris::NormalStep(void)
{
    if (GetDiffTime() >= falling_speed_) 
    {
        if (cur_tetromino_->MoveDown(reference_pos_)) 
        {
            start_time_ = clock();
        }
        else 
        {	// 끝까지 내려왔음. 후처리
            PrepareNextStep();
        }
    }
}

void Tetris::PrepareNextStep(void)
{
    cur_tetromino_->MarkCurTetrominoPos(reference_pos_);
    
    int EraseLineCount = board_.CheckLineFull(reference_pos_); 
    if (EraseLineCount > 0)
        score_.UpdateScore(reference_pos_, EraseLineCount);
	if (score_.GetScore() > 40 && level_==1)
	{
		falling_speed_ -= 0.2;
		board_.LevelUp(reference_pos_, 5);
		level_++;
	}
	else if (score_.GetScore() > 20 &&  level_ == 0)
	{
		falling_speed_ -= 0.1;
		board_.LevelUp(reference_pos_, 3);
		level_++;
	}
    if (cur_tetromino_->CheckEndCondition()) 
    {
        running_ = false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 * 16 + 0);
        Point::GotoXY(reference_pos_ + Point(10, 10));
        cout << "The game is over !!!";
        getch();
    }
    else 
    {
        next_tetromino_->Tetromino::Erase(reference_pos_);		
        GetCurTetrominoFromNext();
        cur_tetromino_->Draw(reference_pos_);
        GenerateNextTetromino();
        next_tetromino_->Draw(reference_pos_);
    }
    start_time_ = clock();
}

void Tetris::GenerateNextTetromino(void)
{
    TETROMINO_TYPE tetromino_type = (TETROMINO_TYPE) (rand() % TETROMINO_TYPE_COUNT);
	next_tetromino_ = new Tetromino(&board_, tetromino_type);
	next_tetromino_->SetCenterPos(g_next_tetromino_init_pos);
} 

void Tetris::GetCurTetrominoFromNext(void)
{
	if (cur_tetromino_ != NULL)
		delete cur_tetromino_;// cur_tetromino_의 값이 NULL이 아니라면 delete
	cur_tetromino_ = next_tetromino_;// next_tetromino_의 테트로미노를 cur_tetromino_로 가져옴
	cur_tetromino_->SetCenterPos(g_cur_tetromino_init_pos);// cur_tetromino_의 시작 위치 setting    
}
void Tetris::PassTetormino()
{
	if (angel_count_ >= 5)
		return;
	cur_tetromino_->Erase(reference_pos_);
	next_tetromino_->Erase(reference_pos_);
	GetCurTetrominoFromNext();
	GenerateNextTetromino();
	cur_tetromino_->Draw(reference_pos_);
	next_tetromino_->Draw(reference_pos_);
	angel_count_++;
}

double Tetris::GetDiffTime(void)
{
    clock_t CurTime;
    CurTime = clock();	//time(&CurTime);
    return ((double) (CurTime - start_time_) / CLOCKS_PER_SEC);
}

// Utility
void Tetris::SetCursorInvisible(void)	// 화면 커서를 안 보이게 함
{
    CONSOLE_CURSOR_INFO ci = { 10, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}