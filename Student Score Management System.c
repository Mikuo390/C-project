#include<stdio.h>
#include<string.h>

#define N 100
#define MAX_NAME 20


//学生成绩管理系统-类型
struct Student
{
	char name[MAX_NAME];//存放名字
	int math, english, chinese, total;
	//  数学  英语     语文     总分
};

//函数声明

//添加学生成绩
void AddStudent();
//删除学生成绩
void DelStudent();
//修改学生成绩
void UpdateStudent();
//查询学生成绩
void SearchStudent();
//统计并输出每门功课的平局成绩
void Avearage();
//输出学生成绩
void DispStudent();
//按照总分降序
void SortStudent_by_Mark();
//按照总分升序
void SortStudent_by_Name();
//学生成绩写入文件 StuMarkSystem.txt 中
void SaveFile();
//从文件 StuMarkSystem.txt 中读取学生信息
void ReadFile();

struct Student st[N];
int length;

//测试区

//主菜单
void menu()
{
	printf("\n\n\t\t========欢迎使用学生成绩管理系统========\n");
	printf("\n");
	printf("\t\t\t 1.添加学生成绩\n");
	printf("\t\t\t 2.删除学生成绩\n");
	printf("\t\t\t 3.修改学生成绩\n");
	printf("\t\t\t 4.查询学生成绩\n");
	printf("\t\t\t 5.统计学生成绩\n");
	printf("\t\t\t 6.输出学生成绩\n");
	printf("\t\t\t 7.按照总分降序\n");
	printf("\t\t\t 8.按照名字升序\n");
	printf("\t\t\t 0.保存数据,退出系统\n");
	printf("\n");
}


int main()
{
	int select = 0;
	ReadFile();
	printf("\n\t\t以从文件d:\\StuMarkSystem.txt 读入 %d 个学生的数据\n", length);
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			AddStudent();
			break;
		case 2:
			DelStudent();
			break;
		case 3:
			UpdateStudent();
			break;
		case 4:
			SearchStudent();
			break;
		case 5:
			Avearage();
			break;
		case 6:
			DispStudent();
			break;
		case 7:
			SortStudent_by_Mark();
			break;
		case 8:
			SortStudent_by_Name();
			break;
		case 0:
			SaveFile();
			break;
		default:
			printf("！！！！选择错误！！！请重新选择！！！\n");
			break;
		}
	} while (select);

}


//函数实现

//添加学生成绩
void AddStudent()
{
	struct Student t;
	printf("\n请输入学生姓名:\n");
	scanf("%s", t.name);
	printf("请输入学生三门功课的成绩:\n");
	scanf("%d%d%d", &t.math, &t.english, &t.chinese);
	t.total = t.math + t.english + t.math;
	st[length++] = t;
	SaveFile();
	printf("\n添加成功！目前共有%d条数据\n\n", length);
}

//删除学生成绩
void DelStudent()
{
	char name[MAX_NAME];
	int i;
	printf("请输入要删除学生的姓名:\n");
	scanf("%s", &name);
	for (i = 0; i < length; i++)
	{
		if (strcmp(st[i].name, name) == 0)
			break;
		for (; i < length - 1; i++)
		{
			st[i] = st[i + 1];
		}
		length--;
		SaveFile();
		printf("\n删除成功！目前共%d条数据\n\n", length);
	}
}

//修改学生成绩
void UpdateStudent()
{
	struct Student t;
	int i;
	printf("请输入学生姓名：\n");
	scanf("%s", &t.name);
	printf("请输入学生三门功课的成绩:\n");
	scanf("%d%d%d", &t.math, &t.english, &t.chinese);
	t.total = t.math + t.english + t.chinese;
	for (i = 0; i < length; i++)
	{
		if (strcmp(st[i].name, t.name) == 0)
			break;
	}
	st[i] = t;
	SaveFile();
	printf("修改成功！目前共%d条数据\n\n", length);
}

//根据学生姓名进行查询
void SearchStudent()
{
	char name[20];
	int i;
	printf("\n请输入要查找学生的姓名:\n");
	scanf("%s", name);
	for (i = 0; i < length; i++)
	{
		if (strcmp(st[i].name, name) == 0)
		{
			printf("学生姓名:%s\n", st[i].name);
			printf("三门功课成绩\n");
			printf("数学:%d\n", st[i].math);
			printf("语文:%d\n", st[i].chinese);
			printf("英语:%d\n", st[i].english);
			printf("总分:%d\n", st[i].total);
			break;
		}
	}
}

//分别统计输出每门功课的平局成绩
void Avearage()
{
	double mathSum, englishSum, chineseSum;
	int i;
	mathSum = englishSum = chineseSum = 0;
	for (i = 0; i < length; i++)
	{
		mathSum += st[i].math;
		chineseSum += st[i].chinese;
		englishSum += st[i].english;
	}
	printf("\n\t\t 三门功课的平局成绩:\n");
	printf("\t\t数学平均分:%5.2f\n", mathSum / length);
	printf("\t\t语文平均分:%5.2f\n", chineseSum / length);
	printf("\t\t英语平均分:%5.2f\n", englishSum / length);
}

//输出学生成绩
void DispStudent()
{
	int i;
	printf("\n");
	printf("\t\t|学生姓名|数学|语文|英语|总分|\n");
	for (i = 0; i < length; i++)
	{
		printf("\t\t|%-8s|%4d|%4d|%4d|%4d|\n", st[i].name, st[i].math, st[i].chinese, st[i].english, st[i].total);
	}
}

//按照总分排序
void SortStudent_by_Mark()
{
	int i, j, max, k;
	struct Student t;
	for (i = 0; i < length - 1; i++)
	{
		max=st[i].total, k = i;
		for (j = i + 1; j < length; j++)
		{
			if (max<st[j].total)
				max=st[j].total, k = j;
		}
		t = st[i];
		st[i] = st[k];
		st[k] = t;
	}
	printf("\t\t********     按照名字字母升序     ********\n");
	DispStudent();
	SaveFile;
}

//按照姓名排序
void SortStudent_by_Name()
{
	int i, j, max, k;
	char min[20];
	struct Student t;
	for (i = 0; i < length - 1; i++)
	{
		strcpy(min, st[i].name), k = i;
		for (j = i + 1; j < length; j++)
		{
			if (strcmp(min, st[j].name) > 0)
				strcpy(min, st[j].name), k = j;
		}
		t = st[i];
		st[i] = st[k];
		st[k] = t;
	}
	printf("\t\t********     按照名字字母升序     ********\n");
	DispStudent();
	SaveFile;
}

//将学生成绩写入文件 StuMarkSystem.txt 中
void SaveFile()
{
	FILE* fp;
	int i = 0;
	fp = fopen("D:\\StuMarkSystem.txt", "w");
	for (i = 0; i < length; i++)
	{
		fprintf(fp, "%s", st[i].name);
		fprintf(fp, "%d", st[i].math);
		fprintf(fp, "%d", st[i].chinese);
		fprintf(fp, "%d", st[i].english);
		fprintf(fp, "%d", st[i].total);
	}
	fclose(fp);
}

//从文件 StuMarkSystem.txt 中读入学生成绩
void ReadFile()
{
	FILE* fp;
	struct Student t;
	fp = fopen("D:\\StuMarkSystem.txt", "r");
	length = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%s", st[length].name);
		fscanf(fp, "%d", st[length].math);
		fscanf(fp, "%d", st[length].chinese);
		fscanf(fp, "%d", st[length].english);
		fscanf(fp, "%d", st[length].total);
		length++;
	}
	fclose(fp);
}
