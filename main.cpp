#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>             //wav 파일 재생
#pragma comment(lib,"winmm.lib")
using namespace std;
#include "Tetris.h"

int main()
{
	srand(time(NULL));		// 난수 발생기 초기화
	int input;

	cout << ">>>>>>>> Testris <<<<<<<<" << endl;
	cout << ">> 1인용, 2인용 선택 : ";
	cin >> input;

	system("cls");

	if (input == 1)         // 1인용 
    {
		sndPlaySound("bgm.wav",SND_ASYNC |SND_LOOP);
		Tetris tetris(Point(0, 0));
		tetris.Run();
	}
	else                    // 2인용
    {		
		sndPlaySound("bgm.wav", SND_ASYNC | SND_LOOP);
		Tetris tetris1(Point(0, 0), KEY_ESC, 'd', 'a', 'w', 's','q','z');
		Tetris tetris2(Point(38, 0), 'p');
		while (tetris1.IsRunning() || tetris2.IsRunning()) 
        {
			bool key1 = false;
			bool key2 = false;

			if (kbhit())    // 키 입력이 있다면 
            {		
				int key = Controller::GetKey();					
				if (tetris1.IsRunning())
					key1 = tetris1.KeyHandler(key);
				if (tetris2.IsRunning() && !key1)
					key2 = tetris2.KeyHandler(key);				
			}

			if (tetris1.IsRunning() && !key1)
				tetris1.NormalStep();
			if (tetris2.IsRunning() && !key2)
				tetris2.NormalStep();			
		}    
		exit(1);
	}

    return 0;
}
