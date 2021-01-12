//测试区

#include"system.h"//引入自定义函数头文件

//主菜单
char* menu[] =
{
	"\t\t\t＊  功能选择  ＊",
	"\t\t\t＊添加学生成绩＊",//1
	"\t\t\t＊删除学生成绩＊",//2
	"\t\t\t＊修改学生成绩＊",//3
	"\t\t\t＊查询学生成绩＊",//4
	"\t\t\t＊统计学生成绩＊",//5
	"\t\t\t＊输出学生成绩＊",//6
	"\t\t\t＊按照总分降序＊",//7
	"\t\t\t＊按照姓名升序＊",//8
	"\t\t\t＊按照数学降序＊",//9
	"\t\t\t＊按照语文降序＊",//10
	"\t\t\t＊按照英语降序＊",//11
	"\t\t\t＊  保存退出  ＊",//12
};

int main()
{
	int ret;
	int select = 0;
	HANDLE hOut;
	SetConsoleTitleA(TITLE);
	//获取当前的句柄---设置为标准输出句柄 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//获取光标信息
	GetConsoleCursorInfo(hOut, &cci);
	//设置光标大小   
	cci.dwSize = 1;
	//设置光标不可见 FALSE   
	cci.bVisible = 0;
	//设置(应用)光标信息
	SetConsoleCursorInfo(hOut, &cci);
	struct Student stu; //stu就是管理系统，里边包含:data指针和size, caocaity

	InitStudent(&stu);//初始化管理系统
	while (1)
	{
		showmenu(hOut, menu, NR(menu), select);
		ret = get_userinput(&select, NR(menu));
		if (ret == ESC)//如果输入 ESC 则退出
			break;
		if (ret == ENTER)//输入 ENTER 进入
		{
			switch (select)
			{
			case 1:
				AddStudent(&stu);//添加学生成绩
				break;
			case 2:
				DelStudent(&stu);//删除学生成绩
				break;
			case 3:
				UpdateStudent(&stu);//修改学生成绩
				break;
			case 4:
				SearchStudent(&stu);//查询学生成绩
				break;
			case 5:
				Avearage(&stu);//统计并输出每门功课的平局成绩
				break;
			case 6:
				DispStudent(&stu);//输出学生成绩
				break;
			case 7:
				SortStudent_by_Mark(&stu);//按照总分降序
				break;
			case 8:
				SortStudent_by_Name(&stu);//按照姓名升序
				break;
			case 9:
				SortStudent_by_MathMark(&stu);//按照数学成绩降序
				break;
			case 10:
				SortStudent_by_ChinsesMark(&stu);//按照语文成绩降序
				break;
			case 11:
				SortStudent_by_EnglishMark(&stu);//按照英语成绩降序
				break;
			case 12:
				SaveFile(&stu);//学生成绩写入文件 StuMarkSystem.txt 中
				DestoryFile(&stu);//释放内存
				return 0;
			}
		}
	}
	return 0;
}
