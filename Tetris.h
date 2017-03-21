#ifndef JHHWANG_TETRIS_H
#define JHHWANG_TETRIS_H

#include "Point.h"
#include "Tetromino.h"
#include "Controller.h"
#include "Board.h"
#include "Score.h"
#include <ctime>
using namespace std;

class Tetris 
{
public :
    // 생성자 : 기준 위치, 컨트롤 키 설정 가능
	Tetris(Point reference_pos = Point(1, 1), int key_esc = KEY_ESC, int key_right = KEY_RIGHT, int key_left = KEY_LEFT, int key_rotate = KEY_UP, int key_down = KEY_DOWN, int key_space = KEY_SPACE,int key_angel = 'm');
    void Run(void);                             // 테트리스 실행 : running_이 true인 동안 RunStep을 반복적으로 실행
    void RunStep(void);                         // 키보드 키가 눌러진 경우(kbhit()으로 조사) KeyHanler 실행, 아닌 경우 NormalStep 실행
    bool KeyHandler(int key);                   // 눌러진 키에 따라 실행
    void NormalStep(void);                      // 한 칸 내려오기 실행
    bool IsRunning(void) { return running_; }   // 실행중 여부 : running_ 값 반환

protected :
    void DrawBoard();               // 테트리스 게임 틀 그리기
    void PrepareNextStep(void);     // 현재 테트로미노가 완전히 내려온 후 다음 테트로미노 준비
    void GenerateNextTetromino();   // 다음 테트로미노 생성
    void GetCurTetrominoFromNext(); // next_tetromino_로부터 cur_tetromino_로 이동 (중심위치, 화면위치 갱신)
	void PassTetormino();
    double GetDiffTime(void);       // 현재시간 - 기준시간(start_time_) 반환 (미리 제시함)
    void SetCursorInvisible(void);  // 커서 안보이게 하기

private :
    Point reference_pos_;           // 화면상에 나타낼 기준 위치 (1, 1)인 경우 실제 (0, 0)으로 맵핑됨
    bool running_;                  // 종료 조건인 경우 이 값이 true가 됨
    Board board_;                   // 테트로미노가 떨어지는 2차원 배열 관리
    Score score_;                   // 점수 출력 관리
    Tetromino *cur_tetromino_;      // 현재 떨어지는 테트로미노 가리킴
    Tetromino *next_tetromino_;     // 다음 테트로미노 가리킴
    Controller controller_;         // 이동 키, 회번 키, 빨리 떨어지기 키 등 조정 버튼(키) 관리
    clock_t start_time_;            // 기준 시간 설정 : 현재 시간과의 차이를 통해 한 칸씩 내려오기 여부 결정(GetDiffTime()에서 사용)
    double falling_speed_;          // 떨어지는 속도(디폴트 0.8) : 일반 모드에서 GetDiffTime()의 값이 falling_speed_ 값보다 크면 한 칸 내려옴
	int level_;
	int angel_count_;
};

#endif