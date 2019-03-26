#include <stdio.h>
#include <stack>
#include <thread>
#include <mutex>
#include <memory>
#include <iostream>
using namespace std;
#include <windows.h>
#include <conio.h>
//​ 将光标定位到屏幕上的某个指定位置的坐标上
struct GOTO_XY
{
	GOTO_XY(int Nx=15, int Ny=5)	:y(Ny),x(Nx)	{}

	void operator()()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		HANDLE hConsoleOut;
		hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
		csbiInfo.dwCursorPosition.X = x;
		csbiInfo.dwCursorPosition.Y = y;
		SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);	 
	}
	GOTO_XY& operator+(int n)
	{
		y += n;
		return *this;
	}
	GOTO_XY& operator*(int n)
	{
		x += n;
		return *this;
	}
private:
	int y;
	int x;
};

enum status
{
	no_RuKou,	// 迷宫没有入口！
	have_Lu,	// -->看迷宫出口的路！
	no_Lu		// 没有通往出口的路！！
};

/* 结构体 */
#define EMPTH 0
#define WALL 1
#define MARK 4
#define FOOT 9
struct PosType	//坐标
{
	PosType(int X, int Y)
		:_x(X),_y(Y)
	{}

	int _x;
	int _y;
};
#define EAST	1
#define SORTH	2
#define WEST	3
#define NORTH	4
struct SElemType : public PosType
{
	SElemType(int X, int Y, int DI=5)
		:PosType(X, Y),di(DI)
	{}

	int di;			//方向
};

/* 输出 */
void put_di(int di)
{
	switch(di)
	{
	case EMPTH:
		cout << "  ";
		break;
	case WALL:
		cout << "■";
		break;
	case FOOT:
		cout << "の";
		break;
	case MARK:
		cout << "  ";
		break;
	default:
		// 什么也不干
		break;
	}
}

/* 迷宫游戏界面 */
void maze();
/* 开始寻找路径 */
void Run(int &map, int row, int col);
/* 打印迷宫 */
void Show(int *map, int row, int col);
void Show_one(int *map, int one_row, int one_col, int col);
void _return(status NNN, int row, int col);

/* 『固定案例』界面 */
void fixed();
/* game_1 */
void game_1();
/* game_2 */
void game_2();
/* game_3 */
void game_3();

/* 『手动输入迷宫』寻找出口 */
void shoudong();
/* 『随机迷宫』界面 */
void rand_mian();