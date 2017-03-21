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
    // ������ : ���� ��ġ, ��Ʈ�� Ű ���� ����
	Tetris(Point reference_pos = Point(1, 1), int key_esc = KEY_ESC, int key_right = KEY_RIGHT, int key_left = KEY_LEFT, int key_rotate = KEY_UP, int key_down = KEY_DOWN, int key_space = KEY_SPACE,int key_angel = 'm');
    void Run(void);                             // ��Ʈ���� ���� : running_�� true�� ���� RunStep�� �ݺ������� ����
    void RunStep(void);                         // Ű���� Ű�� ������ ���(kbhit()���� ����) KeyHanler ����, �ƴ� ��� NormalStep ����
    bool KeyHandler(int key);                   // ������ Ű�� ���� ����
    void NormalStep(void);                      // �� ĭ �������� ����
    bool IsRunning(void) { return running_; }   // ������ ���� : running_ �� ��ȯ

protected :
    void DrawBoard();               // ��Ʈ���� ���� Ʋ �׸���
    void PrepareNextStep(void);     // ���� ��Ʈ�ι̳밡 ������ ������ �� ���� ��Ʈ�ι̳� �غ�
    void GenerateNextTetromino();   // ���� ��Ʈ�ι̳� ����
    void GetCurTetrominoFromNext(); // next_tetromino_�κ��� cur_tetromino_�� �̵� (�߽���ġ, ȭ����ġ ����)
	void PassTetormino();
    double GetDiffTime(void);       // ����ð� - ���ؽð�(start_time_) ��ȯ (�̸� ������)
    void SetCursorInvisible(void);  // Ŀ�� �Ⱥ��̰� �ϱ�

private :
    Point reference_pos_;           // ȭ��� ��Ÿ�� ���� ��ġ (1, 1)�� ��� ���� (0, 0)���� ���ε�
    bool running_;                  // ���� ������ ��� �� ���� true�� ��
    Board board_;                   // ��Ʈ�ι̳밡 �������� 2���� �迭 ����
    Score score_;                   // ���� ��� ����
    Tetromino *cur_tetromino_;      // ���� �������� ��Ʈ�ι̳� ����Ŵ
    Tetromino *next_tetromino_;     // ���� ��Ʈ�ι̳� ����Ŵ
    Controller controller_;         // �̵� Ű, ȸ�� Ű, ���� �������� Ű �� ���� ��ư(Ű) ����
    clock_t start_time_;            // ���� �ð� ���� : ���� �ð����� ���̸� ���� �� ĭ�� �������� ���� ����(GetDiffTime()���� ���)
    double falling_speed_;          // �������� �ӵ�(����Ʈ 0.8) : �Ϲ� ��忡�� GetDiffTime()�� ���� falling_speed_ ������ ũ�� �� ĭ ������
	int level_;
	int angel_count_;
};

#endif