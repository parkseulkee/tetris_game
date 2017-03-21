#include <conio.h>
#include "Controller.h"

void Controller::SetController(int key_esc, int key_right, int key_left, int key_rotate, int key_down, int key_space,int key_angel)
{
	key_esc_ = key_esc;
	key_right_ = key_right;
	key_left_ = key_left;
	key_rotate_ = key_rotate;
	key_down_ = key_down;
	key_space_ = key_space;
	key_angel_ = key_angel;
}

int Controller::GetKey(void)
{
	int ch = getch();			// 일반적으로는 getch에 의해 문자가 입력되지만

	if (ch == 0 || ch == 224)	// 방향키의 경우 0또는 224가 먼저 입력된 후 해당 방향키 값이 입력됨 (2자 입력)
		ch = 256 + getch();		// 원래 일반키와의 입력과의 혼동을 피하기 위해 256을 더해 줌
								// 예) 'H'와 UP키의 값이 72로 동일함
	return ch;
}