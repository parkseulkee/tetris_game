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
	int ch = getch();			// �Ϲ������δ� getch�� ���� ���ڰ� �Էµ�����

	if (ch == 0 || ch == 224)	// ����Ű�� ��� 0�Ǵ� 224�� ���� �Էµ� �� �ش� ����Ű ���� �Էµ� (2�� �Է�)
		ch = 256 + getch();		// ���� �Ϲ�Ű���� �Է°��� ȥ���� ���ϱ� ���� 256�� ���� ��
								// ��) 'H'�� UPŰ�� ���� 72�� ������
	return ch;
}