#define _CRT_SECURE_NO_WARNINGS
#include"game.h"

//打印菜单
void menu()
{
	printf("***********************************\n");
	printf("*****   1 . play   0 . exit   *****\n");
	printf("***********************************\n");
}

//游戏实现
void game()
{
	char ret = 0;//接收结果

	//创建数组存放棋盘信息
	char board[ROW][COL] = { 0 };

	//初始化棋盘
	InitBoard(board,ROW,COL);

	//打印棋盘
	DisplayBoard(board, ROW, COL);

	//下棋函数
	while (1)
	{
		//玩家下棋
		PlayerMove(board, ROW, COL);
		//打印棋盘
		DisplayBoard(board, ROW, COL);
		//判断玩家是否赢
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}

		//电脑下棋
		ComputerMove(board, ROW, COL);
		//打印棋盘
		DisplayBoard(board, ROW, COL);
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}
	}
	if (ret == '*')
	{
		printf("玩家赢\n");
	}
	else if (ret == '#')
	{
		printf("电脑赢\n");
	}
	else
	{
		printf("平局\n");
	}
}

//菜单选择界面
void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));//此函数用于随机
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();//开始游戏
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误，请重新选择！\n");
			break;
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}
