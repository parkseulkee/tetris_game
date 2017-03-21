#ifndef JHHWANG_SCORE_H
#define JHHWANG_SCORE_H

#include "Point.h"

class Score 
{
public :
    Score();                                                // score_ 값을 0으로 초기화
    void UpdateScore(Point reference_pos, int increment);   // Increment 만큼 점수를 더해 줌
    void Print(Point reference_pos);                        // 점수 출력 위치에 점수 출력
	int GetScore();

private :
    int score_;
    Point score_pos_;
};

#endif