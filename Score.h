#ifndef JHHWANG_SCORE_H
#define JHHWANG_SCORE_H

#include "Point.h"

class Score 
{
public :
    Score();                                                // score_ ���� 0���� �ʱ�ȭ
    void UpdateScore(Point reference_pos, int increment);   // Increment ��ŭ ������ ���� ��
    void Print(Point reference_pos);                        // ���� ��� ��ġ�� ���� ���
	int GetScore();

private :
    int score_;
    Point score_pos_;
};

#endif