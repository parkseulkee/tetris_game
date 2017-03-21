#ifndef JHHWANG_BOARD_H
#define JHHWANG_BOARD_H

#include "Point.h"

#define EMPTY -1

class Board 
{
public :
    Board();
    int GetState(Point pos);                // Pos ��ġ�� ���¸� ��ȯ�� : �ܼ��� board_[][] ���� ��ȯ�ϸ� ��
    void SetState(Point pos, int state);    // Pos ��ġ�� ���� State ������ ������
    int CheckLineFull(Point reference_pos); // Ư�� ���� ��Ʈ�ι̳�� ���� �� �ִ��� ����, ���� �� �ִٸ� �� ���� ���ε��� �� ĭ�� ����
                                            // ���������� ������ ���� �� ��ȯ
	void LevelUp(Point reference_pos,int line);  //���� �߰�
	void SetColor(int color);
private :
    int board_[10][20];
};

#endif