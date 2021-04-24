#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

#define OK 1
#define TRUE 1
#define FALSE -1
#define ERROR -1

//定义循环链表结点元素类型
typedef int ElemType;

//循环链表数据结构
typedef struct CDLNode {
	ElemType data;//数据域
	struct DuLNode * prior, * next;//指针域
}CDLNode, * CDLinkList;

typedef struct CDList{
	CDLinkList head;//头指针
	CDLinkList tail;//尾指针
}CDList;

//-----------------基础函数-----------------

//初始化链表
void InitList(CDList* L);

//取得链表的长度
int GetListLength(CDList L);

//检测链表是否为空表
int IsEmpty(CDList L);

//清空表
int ClearList(CDLinkList L);

//插入元素
int InsertList(CDList* L,ElemType e);

//删除元素
int DeleteElem(CDList* L, ElemType e);

//搜索元素
int SearchElem(CDList L, ElemType e);

//倒置链表
int ReversalList(CDList* L);

//交换链表中结点
int SwapLinkElem(CDList* L, ElemType e1, ElemType e2);

//交换双链表
int SwapDoubleLinkElem(CDList* L1, CDList* L2, ElemType e1, ElemType e2);

//打印链表
void PrintList(CDList L);

//创建100个随机数
int CreateRandomNum(CDList* L,int i);

//-----------------功能函数-----------------

//主菜单
void MainMenu();

//单链表功能菜单
void SingleListFunctionMenu();

//双链表功能菜单
void DoubleListFunctionMenu();

//获取链表长度
void GetLength(CDList L);

//检测是否为空表
void Check(CDList L);

//清空表
void Clear(CDList* L);

//插入
void Insert(CDList* L);

//删除
void Delete(CDList* L);

//搜索
void Search(CDList L);

//交换单链表的中的数据
void SwapSingle(CDList* L);

//交换单链表的中的数据
void SwapDouble(CDList* L1, CDList* L2);

//创建i个元素
void CreateElem(CDList* L);

//打印
void Print(CDList L);

//-----------------主函数-----------------
//单链表操作
void SingleList();

//双链表操作
void DoubleList();
