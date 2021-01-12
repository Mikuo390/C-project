#define _CRT_SECURE_NO_WARNINGS
//此头文件为该编译器自带,请忽略

//头文件区域

//库函数头文件区域
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include <Windows.h>
#include <conio.h>
#include<time.h>



//预处理定义区
#define MAX_NAME 20//名字数组最大容量
#define DEFAULT_SZ 3//动态开辟单次增容大小
#define NR(x)   (sizeof(x)/sizeof(x[0]+0))//容量大小
#define TITLE	"＊学生成绩管理系统＊"
#define AUTHOR	"＊作者:叶嘉豪＊"
#define TEACHER	"＊指导老师:吕岚＊"
#define CLASS	"＊班级:20级闽台一班＊"

//定义枚举键盘的键值数据
enum
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27,//方便退出
};

//定义结构体

//光标信息
CONSOLE_CURSOR_INFO cci;
//学生成绩管理系统-学生类型
typedef struct StudentInfo
{
	char name[MAX_NAME];//存放名字
	int math;//数学成绩
	int chinese;//语文成绩
	int english;//英语成绩
	int total;//总分
}StudentInfo;

//学生成绩管理系统-系统信息
typedef struct Student
{
	struct StudentInfo* data;//存放学生成绩信息
	int size;//记录当前已有的元素
	int capacity;//当前管理系统最大容量
}Student;


//函数浏览区
//ctrl+鼠标左键查看相关函数代码(编译器vs2019)

//菜单函数
char* menu[];

//显示菜单 
void showmenu(HANDLE hOut, char** menu, int Usersize, int index);

//获取用户输入 
int get_userinput(int* index, int Usesize);

//初始化管理系统
void InitStudent(struct Student* ps);

//添加学生成绩
void AddStudent(struct Student* ps);

//删除学生成绩
void DelStudent(struct Student* ps);

//修改学生成绩
void UpdateStudent(struct Student* ps);

//查询学生成绩
void SearchStudent(const struct Student* ps);

//统计并输出每门功课的平局成绩
void Avearage(struct Student* ps);

//输出学生成绩
void DispStudent(struct Student* ps);

//按照总分降序
void SortStudent_by_Mark(struct Student* ps);

//按照姓名升序
void SortStudent_by_Name(struct Student* ps);

//按照数学成绩降序
void SortStudent_by_MathMark(struct Student* ps);

//按照语文成绩降序
void SortStudent_by_ChinsesMark(struct Student* ps);

//按照英语成绩降序
void SortStudent_by_EnglishMark(struct Student* ps);

//学生成绩写入文件 StuMarkSystem.txt 中
void SaveFile(Student* ps);

//从文件 StuMarkSystem.txt 中读取学生信息
void  ReadMarkFile(Student* ps);

//释放内存
void DestoryFile(Student* ps);


