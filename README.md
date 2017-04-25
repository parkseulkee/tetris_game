# Tetris Game
기존의 테트리스 게임을 C++로 구현하여 콘솔 창에서 할 수 있는 게임이다. 

사용자의 입력에 따라 1인용 또는 2인용으로 게임을 진행할 수 있으며 스테이지는 총 3개로 구성되어있다. 다음 스테이지로 이동할 때마다 테트리스 블록이 떨어지는 속도가 증가하고 방해하는 벽돌 라인들이 추가된다. 테트리스 블록이 게임 틀을 넘게되면 프로그램이 종료된다.

## 프로젝트 개발 기간 및 환경
* **기간 :** 2015-05-14 ~ 2014-06-01
* **OS :** Window 8.1
* **Language :** C++
* **Tools :** Visual Studio 2013 

## 개발 내용
테트리스 게임의 기본적인 동작 이외에 구현한 내용 :
* 1인용 또는 2인용으로 게임을 진행할 수 있게 구현
* 테트리스 블록이 떨어질 위치를 그림자로 보여줌
* 총 3단계의 STAGE로 구현하였고 STAGE를 통과할 때마다 블록이 내려오는 속도가 빨라지며, 방해 블록 라인이 밑에서 올라옴
* 테트리스 블록 PASS권을 추가함. PASS권은 현재 테트리스 블록을 없애고 다음 테트리스 블록으로 바로 넘어가게해줌

## Source
* 테트리스 판 배열의 상태를 관리하는 class : [Board.h](https://github.com/parkseulkee/tetris_game/blob/master/Board.h) [Board.cpp](https://github.com/parkseulkee/tetris_game/blob/master/Board.cpp)
* 키 입력을 처리하는 class : [Controller.h](https://github.com/parkseulkee/tetris_game/blob/master/Controller.h) [Controller.cpp](https://github.com/parkseulkee/tetris_game/blob/master/Controller.cpp)
* 좌표를 처리하는 class : [Point.h](https://github.com/parkseulkee/tetris_game/blob/master/Point.h) [Point.cpp](https://github.com/parkseulkee/tetris_game/blob/master/Point.cpp) 
* 점수를 저장하고 출력하는 class : [Score.h](https://github.com/parkseulkee/tetris_game/blob/master/Score.h) [Score.cpp](https://github.com/parkseulkee/tetris_game/blob/master/Score.cpp)
* 테트리스 블록 하나의 생성, 출력, 이동 관리 class : [Tetromino.h](https://github.com/parkseulkee/tetris_game/blob/master/Tetromino.h) [Tetromino.cpp](https://github.com/parkseulkee/tetris_game/blob/master/Tetromino.cpp)
* 테트리스 게임 하나 관리, 중심 class : [Tetris.h](https://github.com/parkseulkee/tetris_game/blob/master/Tetris.h) [Tetris.cpp](https://github.com/parkseulkee/tetris_game/blob/master/Tetris.cpp) 
* [main.cpp](https://github.com/parkseulkee/tetris_game/blob/master/main.cpp)
