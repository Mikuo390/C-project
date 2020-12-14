#define _CRT_SECURE_NO_WARNINGS

#include"game.h"

//构造函数

//初始化棋盘函数
void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}

//棋盘样式
// c |   |
//---|---|---
//   |   |
//---|---|---
//   |   |

//打印棋盘函数
void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < col; i++)
	{
		//1.打印一行 
		//   |   |    //
		int j = 0;
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);//打印字符
			if (j < col - 1)
				printf("|");
		}
		printf("\n");//换行

		//2.打印分割线 
		//---|---|---//
		if (i < row - 1)
		{
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
					printf("|");
			}
			printf("\n");//换行
		}
	}
}

//玩家下棋函数
void PlayerMove(char board[ROW][COL], int row, int col)
{
	//设立坐标
	int x = 0;
	int y = 0;
	printf("玩家走:>\n");

	while (1)
	{
		printf("请输入坐标:>");
		scanf("%d%d", &x, &y);
		//判断x,y坐标的合法性
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//判断玩家的坐标是否为空格
			if (board[x - 1][y - 1] == ' ')//x-1,y-1因为数组下标原因
			{
				//为该坐标赋值，写入棋盘中
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("该坐标已被占用\n");
			}
		}
		else
		{
			printf("坐标非法,请重新输入！\n");
		}
	}
}

//电脑下棋函数
void ComputerMove(char board[ROW][COL], int row, int col)
{
	//设定电脑下棋坐标
	int x = 0;
	int y = 0;
	printf("电脑走:>\n");

	while (1)
	{
		//设定随机数范围
		x = rand() % row;
		y = rand() % col;
		//电脑下棋
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
}

//判断输赢函数
char IsWin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	//横三行
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ')
		{
			return board[i][1];
		}
	}

	//竖三列
	for (i = 0; i < col; i++)
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != ' ')
		{
			return board[1][i];
		}
	}

	//两个对角线
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
		return board[1][1];
	if (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[1][1] != ' ')
		return board[1][1];

	//判断是否平局
	if (1 == IsFull(board, ROW, COL))
	{
		return 'Q';
	}

	return 'C';
}

//判断棋盘是否满函数
int IsFull(char board[ROW][COL], int row, int col)
{
	//返回1表示棋盘满了，返回0表示棋盘没满
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;//没满
			}
		}
	}
	return 1;//满了
}
