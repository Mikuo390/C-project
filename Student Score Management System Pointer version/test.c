//测试区

#include"system.h"//引入自定义函数头文件

//主函数区域
int main()
{
	int select = 0;//设置选择变量
	//创建管理系统
	struct Student stu; //stu就是管理系统，里边包含:data指针和size, caocaity
	
	InitStudent(&stu);//初始化管理系统

	//功能选择器
	do
	{
		menu();//引用主菜单函数
		printf("\t\t请选择:>");
		scanf("%d", &select);
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
		case 0:
			SaveFile(&stu);//学生成绩写入文件 StuMarkSystem.txt 中
			DestoryFile(&stu);//释放内存
			return 0;
		}
	} while (select);

}
