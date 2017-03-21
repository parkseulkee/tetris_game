#ifndef JHHWANG_TETROMINO_H
#define JHHWANG_TETROMINO_H

#include "Point.h"
#include "Board.h"

#define TETROMINO_TYPE_COUNT 7
#define ROTATE_COUNT 4
//const Point g_next_tetromino_init_pos(29, 3);
const Point g_next_tetromino_init_pos(14, 17);
const Point g_cur_tetromino_init_pos(4, 20);
enum TETROMINO_TYPE { TETROMINO_I, TETROMINO_J, TETROMINO_L, TETROMINO_O, TETROMINO_S, TETROMINO_T, TETROMINO_Z };

class Tetromino 
{
public : 
	Tetromino(Board *board, TETROMINO_TYPE type);
    virtual void Draw(Point reference_pos);			        // 현재 화면 중심 위치를 기준으로 그리기
    virtual void Erase(Point reference_pos);		        // 현재 화면 중심 위치를 기준으로 지우기
    bool MoveDown(Point reference_pos);		        // 한 칸 내려오기, 유효한 위치면 다시 그림
    void MoveRight(Point reference_pos);	        // 한 칸 오른쪽으로 이동, 유효한 위치면 다시 그림
    void MoveLeft(Point reference_pos);		        // 한 칸 왼쪽으로 이동, 유효한 위치면 다시 그림
    void Rotate(Point reference_pos);		        // 회전, 유효한 위치면 다시 그림
    void GoBottom(Point reference_pos);		        // 최하단으로 이동, 유효할 때까기 MoveDown() 실행
    virtual void MarkCurTetrominoPos(Point reference_pos);	// 다 내려오고 난 후에 board_의 객체에 대한 값 setting
    bool CheckEndCondition(void);					// 종료 조건 검사, y축 기준으로 20이상(가득 참)이면 종료(return true)
    void SetCenterPos(Point pos);					// 중심 위치 설정   
	void SetColor(int color);
protected :
    virtual bool CheckValidPos(void);	        // 현재 테트로미노 위치가 유효한지 검사, 판을 벗어나지 않고 다른 테트로미노가 쌓여있지 않음
	virtual bool GhostCheckValidPos(void);
    
protected :
    Point center_pos_;			        // 현재 중심 위치 (내부 배열 기준)
	Point ghost_pos_;
    TETROMINO_TYPE type_;               // 테트로니노 타입
	int color_;
    int rotate_;				        // 현재 회전 위치
    Board *board_;			            // Board 객체 정보를 알기 위해 Board 객체와 연결    
};

#endif