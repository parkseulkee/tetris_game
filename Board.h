#ifndef JHHWANG_BOARD_H
#define JHHWANG_BOARD_H

#include "Point.h"

#define EMPTY -1

class Board 
{
public :
    Board();
    int GetState(Point pos);                // Pos 위치의 상태를 반환함 : 단순히 board_[][] 값을 반환하면 됨
    void SetState(Point pos, int state);    // Pos 위치의 값을 State 값으로 설정함
    int CheckLineFull(Point reference_pos); // 특정 행이 테트로미노로 가득 차 있는지 조사, 가득 차 있다면 그 위의 라인들을 한 칸씩 내림
                                            // 최종적으로 삭제된 라인 수 반환
	void LevelUp(Point reference_pos,int line);  //라인 추가
	void SetColor(int color);
private :
    int board_[10][20];
};

#endif