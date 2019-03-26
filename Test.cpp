#pragma once
#include "Head.h"
/* 开机线程 */
void thread_Fun()
{
	system("cls");//清屏
	GOTO_XY gotoxy0;(gotoxy0+5)();
	cout << "       " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "欢 " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "迎 " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "进 " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "入 " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "迷 " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "宫 " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "游 " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "戏 " ;this_thread::sleep_for(chrono::milliseconds(300));
	system("cls");GOTO_XY gotoxy1;(gotoxy1+5)();
	cout << "       欢 迎 进 入 迷 宫 游 戏 " ;
	system("cls");this_thread::sleep_for(chrono::milliseconds(50));
	GOTO_XY gotoxy2;(gotoxy2+5)();
	cout << "       欢 迎 进 入 迷 宫 游 戏 " ;
}
/* 主函数 */
int main()
{
	thread th(thread_Fun);
	this_thread::sleep_for(chrono::seconds(5));
	th.join();
	maze();
	return 0;
}

/* 迷宫游戏界面 */
void maze()
{
	while(1)
	{
		system("cls");//清屏
		GOTO_XY gotoxy;
		gotoxy();cout << "欢迎进入迷宫游戏：" ;
		(gotoxy+1)();cout << "================================" ;
	
		(gotoxy+2)();cout << "    1.『固定案例』寻找出口" ;
	
		(gotoxy+2)();cout << "    2.『手动输入迷宫』寻找出口" ;
	
		(gotoxy+2)();cout << "    3.『随机迷宫』寻找出口" ;
	

		(gotoxy+3)();cout << "    0.【退出程序】" ;
	
		(gotoxy+2)();cout << "================================" ;
		(gotoxy+1)();cout << "请输入【正确】序号：" ;
		int NUM = 0;
		cin >> NUM;
		switch(NUM)
		{
			case 0:// 【退出程序】
				system("cls");
				system("cls");
				return;
				break;
			case 1:// 『固定案例』寻找出口
				fixed();
				break;
			case 2:// 『手动输入迷宫』寻找出口
				shoudong();
				break;
			case 3:// 『随机迷宫』寻找出口
				rand_mian();
				break;
			default:
				break;
		}
	}
}

/* 开始寻找路径 */
void Run(int *map, int row, int col)
{
	stack<SElemType> Maze_path;
	int begin_x = 1;
	int begin_y = 1;
	int end_x = row - 2 ;
	int end_y = col - 2 ;
	int x = begin_x;
	int y = begin_y;
	system("cls");//清屏
	Show(map,row,col);
	this_thread::sleep_for(chrono::milliseconds(50));
	// 是否有入口
	if( WALL == map[begin_x * col + begin_y]){
		this_thread::sleep_for(chrono::seconds(1));
		_return(no_RuKou, row, 0);
		return;
	}

	while(true)
	{
		Show_one(map,x,y,col);
		if(EMPTH == map[x * col + y] || FOOT == map[x * col + y])
		{
			if(x == end_x && y == end_y){
				this_thread::sleep_for(chrono::seconds(1));
				_return(have_Lu, row-2, col-1);
				return;
			}

			if( EMPTH == map[x * col + y] ){
				Maze_path.push(SElemType(x, y));
				map[x * col + y] = FOOT;
				Show_one(map,x,y,col);
			}
			if(EMPTH == map[x * col + y +1])	
			{	y++;	Maze_path.push(SElemType(x, y, EAST));	map[x * col + y] = FOOT;	continue;	}
			if(EMPTH == map[(x+1) * col + y])	
			{	x++;	Maze_path.push(SElemType(x, y, SORTH));	map[x * col + y] = FOOT;	continue;	}
			if(EMPTH == map[x * col + y -1])	
			{	y--;	Maze_path.push(SElemType(x, y, WEST));	map[x * col + y] = FOOT;	continue;	}
			if(EMPTH == map[(x-1) * col + y])	
			{	x--;	Maze_path.push(SElemType(x, y, NORTH));	map[x * col + y] = FOOT;	continue;	}

			map[x * col + y] = MARK;
			Show_one(map,x,y,col);
			switch(Maze_path.top().di)
			{
				case EAST:
					y--;
					break;
				case SORTH:
					x--;
					break;
				case WEST:
					y++;
					break;
				case NORTH:
					x++;
					break;
				default:
					this_thread::sleep_for(chrono::seconds(1));
					_return(no_Lu, row, 0);
					return;
			}
			Maze_path.pop();
		}
	}
}

/* 打印迷宫 */
void Show(int *map, int row, int col)
{
	GOTO_XY gotoxy(0,-1);

	for(register int i = 0; i<row ;++i)
	{
		for(register int j = 0; j<col ;++j)
		{
			if(0 == j)
			{
				(gotoxy+1)();
			}
			put_di(map[i*col + j]);
		}
	}
	this_thread::sleep_for(chrono::milliseconds(50));
}
void Show_one(int *map, int one_row, int one_col, int col)
{
	GOTO_XY gotoxy(one_col*2,one_row);
	gotoxy();put_di(map[one_row*col + one_col]);

	this_thread::sleep_for(chrono::milliseconds(50));
}

void _return(status NNN, int row, int col)
{
	GOTO_XY gotoxy(col*2,row);gotoxy();
	if(no_RuKou == NNN)	
	{
		cout << "迷宫没有入口！" << endl;
	}else if(have_Lu == NNN)
	{
		cout << "-->看迷宫出口的路！" << endl;
		((gotoxy*2)+1)();
	}else
	{
		cout<< "没有通往出口的路！！" <<endl;
	}
	int NUM;
	cout << "输入任意字符【返回】" ;
	cin >> NUM;
}

/* 『固定案例』界面 */
void fixed()
{
	while(1)
	{
		system("cls");//清屏
		GOTO_XY gotoxy;
		gotoxy();cout << "欢迎进入迷宫游戏：" ;
		(gotoxy+1)();cout << "================================" ;
		(gotoxy+1)();cout << "固定案例:" ;

		(gotoxy+2)();cout << "    1.『25 * 25』" ;
	
		(gotoxy+2)();cout << "    2.『12 * 12』" ;
	
		(gotoxy+2)();cout << "    3.『7 * 7』" ;
	

		(gotoxy+3)();cout << "    0.【返回】" ;
	
		(gotoxy+2)();cout << "================================" ;
		(gotoxy+1)();cout << "请输入【正确】序号：" ;
		int NUM = 0;
		cin >> NUM;
		switch(NUM)
		{
			case 0:// 【返回】
				return;
				break;
			case 1:// 『25 * 25』
				game_1();
				break;
			case 2:// 『12 * 12』
				game_2();
				break;
			case 3:// 『7 * 7』
				game_3();
				break;
			default:
				break;
		}
	}
}
/* game_1 */
void game_1()
{
	int map[25][25] = {		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
							1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
							1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1,
							1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
							1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
							1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
							1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
							1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1,
							1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1,
							1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1,
							1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
							1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1,
							1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
							1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1,
							1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1,
							1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
							1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1	};
	Run((int*)map, 25, 25);
}
/* game_2 */
void game_2()
{
	int map[12][12] = {		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
							1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 
							1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 
							1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 
							1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 
							1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 
							1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 
							1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 
							1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 
							1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 
							1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
							1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1	};
	Run((int*)map, 12, 12);
}
/* game_3 */
void game_3()
{
	int map[7][7] = {		1, 1, 1, 1, 1, 1, 1, 
							1, 0, 0, 1, 0, 1, 1,
							1, 1, 0, 0, 0, 1, 1, 
							1, 0, 0, 0, 1, 0, 1, 
							1, 1, 1, 0, 1, 0, 1, 
							1, 0, 0, 0, 0, 0, 1, 
							1, 1, 1, 1, 1, 1, 1 };
	Run((int*)map, 7, 7);
}

/* 『手动输入迷宫』寻找出口 */
void shoudong()
{
	system("cls");//清屏

	cout << "输入时请注意！！！" << endl;
	cout << endl;
	cout << "例如:当你想输入的是 3行 4列的迷宫时..." << endl;
	cout << "请输入【行 列】（注意空格隔开）：3 4" << endl;
	cout << endl;
	cout << "0 0 0 0       1：表示墙（不可走）" << endl;
	cout << "1 0 1 1       0：表示可走" << endl;
	cout << "0 0 0 0" << endl;
	cout << endl;
	cout << "当然，您也可以在 .txt文件下做好，再粘贴过来。。。" << endl;

	cout << endl;
	cout << endl;
	cout << "请输入【行 列】（注意空格隔开）：" ;
	int row = 0;
	int col = 0;
	cin >> row >> col;
	row += 2;
	col += 2;
	cout << endl;

	int *map = (int *)malloc(sizeof(int) * row * col);
	cout << "请您【正确】输入【迷宫】：" << endl;
	cout << "请您【正确】输入【迷宫】：" << endl;
	cout << "请您【正确】输入【迷宫】：" << endl;
	for(int i=0; i<row ;++i)
	{
		for(int j=0; j<col ;++j)
		{
			if(0 == i || 0 == j || row-1 == i || col-1 == j)
			{
				map[i*col + j] = 1;
			}
			else
			{
				cin >> map[i*col + j] ;
			}
		}
	}
	Run(map, row, col);

	free(map);
}
/* 『随机迷宫』界面 */
void rand_mian()
{
	system("cls");//清屏
	GOTO_XY gotoxy;
	gotoxy();cout << "请输入【行 列】（注意空格隔开）如:5 12";(gotoxy+1)();
	int row = 0;
	int col = 0;
	cin >> row >> col;

	int *map = (int *)malloc(sizeof(int) * row * col);
	for(int i=0; i<row ;++i)
	{
		for(int j=0; j<col ;++j)
		{
			if(0 == i || 0 == j || row-1 == i || col-1 == j)
			{
				map[i*col + j] = 1;
			}
			else
			{
				map[i*col + j] = rand()%2 ;
			}
		}
	}
	Run(map, row, col);

	free(map);
}