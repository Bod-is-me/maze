#pragma once
#include "Head.h"
/* �����߳� */
void thread_Fun()
{
	system("cls");//����
	GOTO_XY gotoxy0;(gotoxy0+5)();
	cout << "       " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "�� " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "ӭ " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "�� " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "�� " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "�� " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "�� " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "�� " ;this_thread::sleep_for(chrono::milliseconds(200));
	cout << "Ϸ " ;this_thread::sleep_for(chrono::milliseconds(300));
	system("cls");GOTO_XY gotoxy1;(gotoxy1+5)();
	cout << "       �� ӭ �� �� �� �� �� Ϸ " ;
	system("cls");this_thread::sleep_for(chrono::milliseconds(50));
	GOTO_XY gotoxy2;(gotoxy2+5)();
	cout << "       �� ӭ �� �� �� �� �� Ϸ " ;
}
/* ������ */
int main()
{
	thread th(thread_Fun);
	this_thread::sleep_for(chrono::seconds(5));
	th.join();
	maze();
	return 0;
}

/* �Թ���Ϸ���� */
void maze()
{
	while(1)
	{
		system("cls");//����
		GOTO_XY gotoxy;
		gotoxy();cout << "��ӭ�����Թ���Ϸ��" ;
		(gotoxy+1)();cout << "================================" ;
	
		(gotoxy+2)();cout << "    1.���̶�������Ѱ�ҳ���" ;
	
		(gotoxy+2)();cout << "    2.���ֶ������Թ���Ѱ�ҳ���" ;
	
		(gotoxy+2)();cout << "    3.������Թ���Ѱ�ҳ���" ;
	

		(gotoxy+3)();cout << "    0.���˳�����" ;
	
		(gotoxy+2)();cout << "================================" ;
		(gotoxy+1)();cout << "�����롾��ȷ����ţ�" ;
		int NUM = 0;
		cin >> NUM;
		switch(NUM)
		{
			case 0:// ���˳�����
				system("cls");
				system("cls");
				return;
				break;
			case 1:// ���̶�������Ѱ�ҳ���
				fixed();
				break;
			case 2:// ���ֶ������Թ���Ѱ�ҳ���
				shoudong();
				break;
			case 3:// ������Թ���Ѱ�ҳ���
				rand_mian();
				break;
			default:
				break;
		}
	}
}

/* ��ʼѰ��·�� */
void Run(int *map, int row, int col)
{
	stack<SElemType> Maze_path;
	int begin_x = 1;
	int begin_y = 1;
	int end_x = row - 2 ;
	int end_y = col - 2 ;
	int x = begin_x;
	int y = begin_y;
	system("cls");//����
	Show(map,row,col);
	this_thread::sleep_for(chrono::milliseconds(50));
	// �Ƿ������
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

/* ��ӡ�Թ� */
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
		cout << "�Թ�û����ڣ�" << endl;
	}else if(have_Lu == NNN)
	{
		cout << "-->���Թ����ڵ�·��" << endl;
		((gotoxy*2)+1)();
	}else
	{
		cout<< "û��ͨ�����ڵ�·����" <<endl;
	}
	int NUM;
	cout << "���������ַ������ء�" ;
	cin >> NUM;
}

/* ���̶����������� */
void fixed()
{
	while(1)
	{
		system("cls");//����
		GOTO_XY gotoxy;
		gotoxy();cout << "��ӭ�����Թ���Ϸ��" ;
		(gotoxy+1)();cout << "================================" ;
		(gotoxy+1)();cout << "�̶�����:" ;

		(gotoxy+2)();cout << "    1.��25 * 25��" ;
	
		(gotoxy+2)();cout << "    2.��12 * 12��" ;
	
		(gotoxy+2)();cout << "    3.��7 * 7��" ;
	

		(gotoxy+3)();cout << "    0.�����ء�" ;
	
		(gotoxy+2)();cout << "================================" ;
		(gotoxy+1)();cout << "�����롾��ȷ����ţ�" ;
		int NUM = 0;
		cin >> NUM;
		switch(NUM)
		{
			case 0:// �����ء�
				return;
				break;
			case 1:// ��25 * 25��
				game_1();
				break;
			case 2:// ��12 * 12��
				game_2();
				break;
			case 3:// ��7 * 7��
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

/* ���ֶ������Թ���Ѱ�ҳ��� */
void shoudong()
{
	system("cls");//����

	cout << "����ʱ��ע�⣡����" << endl;
	cout << endl;
	cout << "����:������������� 3�� 4�е��Թ�ʱ..." << endl;
	cout << "�����롾�� �С���ע��ո��������3 4" << endl;
	cout << endl;
	cout << "0 0 0 0       1����ʾǽ�������ߣ�" << endl;
	cout << "1 0 1 1       0����ʾ����" << endl;
	cout << "0 0 0 0" << endl;
	cout << endl;
	cout << "��Ȼ����Ҳ������ .txt�ļ������ã���ճ������������" << endl;

	cout << endl;
	cout << endl;
	cout << "�����롾�� �С���ע��ո��������" ;
	int row = 0;
	int col = 0;
	cin >> row >> col;
	row += 2;
	col += 2;
	cout << endl;

	int *map = (int *)malloc(sizeof(int) * row * col);
	cout << "��������ȷ�����롾�Թ�����" << endl;
	cout << "��������ȷ�����롾�Թ�����" << endl;
	cout << "��������ȷ�����롾�Թ�����" << endl;
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
/* ������Թ������� */
void rand_mian()
{
	system("cls");//����
	GOTO_XY gotoxy;
	gotoxy();cout << "�����롾�� �С���ע��ո��������:5 12";(gotoxy+1)();
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