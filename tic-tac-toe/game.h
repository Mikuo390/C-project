#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//设置棋盘行列
#define ROW 3 //行
#define COL 3 //列

//函数声明

//声明 初始化棋盘函数
void InitBoard(char board[ROW][COL], int row, int col);

//声明 打印棋盘函数
void DisplayBoard(char board[ROW][COL], int row, int col);

//声明 玩家下棋
void PlayerMove(char board[ROW][COL], int row, int col);

//声明 电脑下棋
void ComputerMove(char board[ROW][COL], int row, int col);

//声明 判断输赢
//玩家赢 '*'
//电脑赢 '#'
//平局 'Q'
//继续 'C'
char IsWin(char board[ROW][COL], int row, int col);

//声明 棋盘是否满了
int IsFull(char board[ROW][COL], int row, int col);
