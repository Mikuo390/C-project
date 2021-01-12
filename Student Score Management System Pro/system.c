//函数实现

#include"system.h"

//定义显示的菜单 
void showmenu(HANDLE hOut, char** menu, int Usersize, int index)
{
	//定义默认的坐标位置  	
	COORD Defpos = { 0,0 };
	int i;
	//设置显示的文本的颜色 
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | 0x8);
	//初始化控制台显示的X,Y轴的坐标 
	Defpos.X = 46.5;
	Defpos.Y = 0;
	//设置显示到控制台终端的具体位置 
	SetConsoleCursorPosition(hOut, Defpos);
	//调用printf在控制台对应的位置上输出 
	printf("%s", TITLE);//标题

	Defpos.X = 48;
	Defpos.Y = 1;
	SetConsoleCursorPosition(hOut, Defpos);
	printf("%s", AUTHOR);//作者

	Defpos.X = 47.5;
	Defpos.Y = 2;
	SetConsoleCursorPosition(hOut, Defpos);
	struct tm* day;//定义一个接收本地详细时间的结构体变量，在上面有这个结构的详细说明
	time_t tm = 0;
	time(&tm);
	day = localtime(&tm);//将秒数转换为本地详细时间描述
	printf("＊%d年%d月%d日＊", 1900 + day->tm_year, 1 + day->tm_mon, day->tm_mday);

	Defpos.X = 47;
	Defpos.Y = 3;
	SetConsoleCursorPosition(hOut, Defpos);
	printf("%s", TEACHER);//指导老师

	Defpos.X = 46;
	Defpos.Y = 4;
	SetConsoleCursorPosition(hOut, Defpos);
	printf("%s", CLASS);//班级

	for (i = 0; i < Usersize; i++)
	{
		//如果i==index表示在当前选项的位置，默认初始化显示是第一项，显示为红色，
		//当按下上下按键选择的时候，光标会移动，也就看到了列表选择的现象 
		if (i == index)
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | 0x8);//设置选中颜色为红色 
			Defpos.X = 30;
			Defpos.Y = 5 + i;
			//设置光标坐标
			SetConsoleCursorPosition(hOut, Defpos);
			printf("%s", menu[i]);
		}
		//否则显示为白色 
		else
		{
			//白色 
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			Defpos.X = 30;
			Defpos.Y = 5 + i;
			//设置光标坐标
			SetConsoleCursorPosition(hOut, Defpos);    //设置光标坐标
			printf("%s", menu[i]);
		}
	}
	//刷新标准输出缓冲区 
	fflush(stdout);
}

//获取用户输入的接口 
int get_userinput(int* index, int Usersize)
{
	int ch;
	ch = _getch();//vs2019编译器为_getch
	switch (ch)//根据选择的图标，让光标移动/使用
	{
		//上 
	case UP:
		if (*index > 0)  
			*index -= 1;  
		break;
		//下 
	case DOWN:
		if (*index < Usersize - 1)  
			*index += 1;  
		break;
		//左 
	case LEFT:
		return 0;
		//右 
	case RIGHT:
		return 0;
		//回车 
	case ENTER:
		return ENTER;
		//ESC
	case ESC:
		return ESC;
	}
	return 0;
}


//初始化管理系统
void InitStudent(struct Student* ps)
{
	//动态开辟空间，节省内存占用，优化速度
	ps->data = (struct StudentInfo*)malloc(DEFAULT_SZ * sizeof(struct StudentInfo));
	//根据信息大小自动增容大小
	if (ps->data == NULL)
	{
		return 0;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;
	//把文件中已经存放的通讯录的信息加载到通讯录中
	ReadMarkFile(ps);//读取文件
}


//声明检查函数
void CheckCapacity(struct Student* ps);

//从文件 StuMarkSystem.txt 中读入学生成绩
void ReadMarkFile(Student* ps)
{
	StudentInfo tmp = { 0 };//创建结构体变量，用于存放
	FILE* pfRead = fopen("D:\\StuMarkSystem.txt", "rb");
	if (pfRead == NULL)//检测指针是否为空指针
	{
		printf("%s\n", strerror(errno));//打印出错误信息
		return;
	}

	//读取文件，存放到通讯录中
	while (fread(&tmp, sizeof(StudentInfo), 1, pfRead))
	{
		CheckCapacity(ps);
		ps->data[ps->size] = tmp;
		ps->size++;
	}

	fclose(pfRead);//释放内存，防止内存泄漏
	pfRead = NULL;//为fp赋值为空指针
}

//增容函数
void CheckCapacity(struct Student* ps)
{
	//增容
	struct StudentInfo* ptr = realloc(ps->data, (ps->capacity) * sizeof(StudentInfo));
	if (ptr != NULL)//判断是否为空指针
	{
		ps->data = ptr;
		ps->capacity += 2;
		printf("\t\t！！！增容成功！！！\n");
	}
	else//如果是则打印出提示
	{
		printf("\t\t！！！增容失败！！！\n");
	}
	system("cls");
}

//添加学生成绩-函数
void AddStudent(struct Student* ps)
{
	system("cls");
	//检测当前的容量
	//1.如果满了，就增加空间
	//2.如果不满啥事不干
	CheckCapacity(ps);
	//增加数据
	printf("\n请输入学生姓名:\n");
	scanf("%s", ps->data[ps->size].name);
	printf("请输入学生三门功课的成绩:\n");
	scanf("%d%d%d", 
		&(ps->data[ps->size].math),
		&(ps->data[ps->size].chinese),
		&(ps->data[ps->size].english));
	ps->data[ps->size].total = 
		ps->data[ps->size].math + 
		ps->data[ps->size].english + 
		ps->data[ps->size].math;
	ps->size++;
	SaveFile(ps);
	printf("\n添加成功！目前共有%d条数据\n\n", ps->size);
	system("cls");
}


//通过用名字找-函数
static int FindByName(const struct Student* ps, char name[MAX_NAME])
{//因为指针在传参的过程中可能地址会发生变化，const防止指针变化
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (0 == strcmp(ps->data[i].name, name))
		{
			return i;
		}
	}
	//找不到
	return -1;
	system("cls");
}


//删除学生成绩
void DelStudent(struct Student* ps)
{
	system("cls");
	char name[MAX_NAME];
	int pos = 0;

	printf("\n请输入要删除学生的姓名:\n");
	scanf("%s", name);

	//1.查找要删除的学生在什么位置
	pos = FindByName(ps, name);
	//找到了返回名字所在元素的下标
	//找不到返回 -1

	//2.删除
	if (pos == -1)
	{
		printf("\n删除的学生不存在\n");
	}
	else
	{
		//删除数据
		int j = 0;
		for (j = pos; j < ps->size - 1; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;
		printf("\n删除成功！目前共%d条数据\n\n", ps->size);
		SaveFile(ps);
	}
}



//修改学生名字和成绩
void UpdateStudent(struct Student* ps)
{
	system("cls");
	int pos = 0;
	char name[MAX_NAME];

	printf("请输入要修改学生的名字:>");
	scanf("%s", name);

	//1.查找要删除的学生在什么位置
	pos = FindByName(ps, name);
	//找到了返回名字所在元素的下标
	//找不到返回 -1

	if (pos == -1)
	{
		printf("要修改的学生不存在\n");
	}
	else
	{
		printf("请输入学生姓名：\n");
		scanf("%s", ps->data[pos].name);
		printf("请输入学生三门功课的成绩:\n");
		scanf("%d%d%d", 
			&ps->data[pos].math, 
			&ps->data[pos].english, 
			&ps->data[pos].chinese);
		ps->data[pos].total = 
			ps->data[pos].math + 
			ps->data[pos].english + 
			ps->data[pos].chinese;

		printf("修改成功！目前共%d条数据\n\n", ps->size);
		SaveFile(ps);
	}
}


//根据学生姓名进行查询
void SearchStudent(const struct Student* ps)
{
	system("cls");
	int pos = 0;
	char name[MAX_NAME];

	printf("\n请输入要查找学生的姓名:\n");
	scanf("%s", name);

	//1.查找要删除的学生在什么位置
	pos = FindByName(ps, name);
	//找到了返回名字所在元素的下标
	//找不到返回 -1

	if (pos == -1)
	{
		printf("要查找的学生不存在\n");
	}
	else
	{
		printf("学生姓名:%s\n", ps->data[pos].name);
		printf("三门功课成绩\n");
		printf("数学:%d\n", ps->data[pos].math);
		printf("语文:%d\n", ps->data[pos].chinese);
		printf("英语:%d\n", ps->data[pos].english);
		printf("总分:%d\n", ps->data[pos].total);
	}
}


//分别统计输出每门功课的平局成绩
void Avearage(struct Student* ps)
{
	system("cls");
	double mathSum, englishSum, chineseSum;
	int i;
	mathSum = englishSum = chineseSum = 0;
	for (i = 0; i < ps->size; i++)
	{
		mathSum += ps->data[i].math;
		chineseSum += ps->data[i].chinese;
		englishSum += ps->data[i].english;
	}
	printf("\n\t\t 三门功课的平局成绩:\n");
	printf("\t\t数学平均分:%5.2f\n", mathSum / ps->size);
	printf("\t\t语文平均分:%5.2f\n", chineseSum / ps->size);
	printf("\t\t英语平均分:%5.2f\n", englishSum / ps->size);
}


//输出学生成绩
void DispStudent(struct Student* ps)
{
	system("cls");
	printf("\n");
	printf("\t\t|学生姓名|数学|语文|英语|总分|\n");
	for (int i = 0; i < ps->size; i++)
	{
		printf("\t\t|%-8s|%4d|%4d|%4d|%4d|\n", 
			ps->data[i].name,
			ps->data[i].math,
			ps->data[i].chinese,
			ps->data[i].english,
			ps->data[i].total);
	}
}


//排序部分
//按照总分排序
void SortStudent_by_Mark(struct Student* ps)
{
	system("cls");
	int i, j, max, k;
	StudentInfo t = { 0 };//创建临时结构体变量，用于交换
	for (i = 0; i < ps->size - 1; i++)
	{
		max = ps->data[i].total, k = i;
		for (j = i + 1; j < ps->size; j++)
		{
			if (max < ps->data[j].total)
				max = ps->data[j].total, k = j;
		}
		t = ps->data[i];
		ps->data[i] = ps->data[k];
		ps->data[k] = t;
	}
	printf("\n\t\t********     按照总分成绩降序     ********\n");
	DispStudent(ps);
	SaveFile(ps);
}

//按照姓名排序
void SortStudent_by_Name(struct Student* ps)
{
	system("cls");
	int i, j, k;
	char min[20];
	StudentInfo t = { 0 };
	for (i = 0; i < ps->size - 1; i++)
	{
		strcpy(min, ps->data[i].name), k = i;
		for (j = i + 1; j < ps->size; j++)
		{
			if (strcmp(min, ps->data[j].name) > 0)
				strcpy(min, ps->data[j].name), k = j;
		}
		t = ps->data[i];
		ps->data[i] = ps->data[k];
		ps->data[k] = t;
	}
	printf("\n\t\t********     按照名字字母升序     ********\n");
	DispStudent(ps);
	SaveFile(ps);
}

//按照数学成绩降序
void SortStudent_by_MathMark(struct Student* ps)
{
	system("cls");
	int i, j, max, k;
	StudentInfo t = { 0 };
	for (i = 0; i < ps->size - 1; i++)
	{
		max = ps->data[i].math, k = i;
		for (j = i + 1; j < ps->size; j++)
		{
			if (max < ps->data[j].math)
				max = ps->data[j].math, k = j;
		}
		t = ps->data[i];
		ps->data[i] = ps->data[k];
		ps->data[k] = t;
	}
	printf("\n\t\t********     按照数学成绩降序     ********\n");
	DispStudent(ps);
	SaveFile(ps);
}

//按照语文成绩降序
void SortStudent_by_ChinsesMark(struct Student* ps)
{
	system("cls");
	int i, j, max, k;
	StudentInfo t = { 0 };
	for (i = 0; i < ps->size - 1; i++)
	{
		max = ps->data[i].chinese, k = i;
		for (j = i + 1; j < ps->size; j++)
		{
			if (max < ps->data[j].chinese)
				max = ps->data[j].chinese, k = j;
		}
		t = ps->data[i];
		ps->data[i] = ps->data[k];
		ps->data[k] = t;
	}
	printf("\n\t\t********     按照语文成绩降序     ********\n");
	DispStudent(ps);
	SaveFile(ps);
}

//按照英语成绩降序
void SortStudent_by_EnglishMark(struct Student* ps)
{
	system("cls");
	int i, j, max, k;
	StudentInfo t = { 0 };
	for (i = 0; i < ps->size - 1; i++)
	{
		max = ps->data[i].english, k = i;
		for (j = i + 1; j < ps->size; j++)
		{
			if (max < ps->data[j].english)
				max = ps->data[j].english, k = j;
		}
		t = ps->data[i];
		ps->data[i] = ps->data[k];
		ps->data[k] = t;
	}
	printf("\n\t\t********     按照英语成绩降序     ********\n");
	DispStudent(ps);
	SaveFile(ps);
}



//释放动态内存
void DestoryFile(Student* ps)
{
	free(ps->data);
	ps->data = NULL;
	//避免空间浪费，造成内存泄漏
}


//将学生成绩写入文件 StuMarkSystem.txt 中
void SaveFile(Student* ps)
{
	FILE* pfWrite = fopen("D:\\StuMarkSystem.txt", "wb");
	if (pfWrite == NULL)
	{
		//如果传入为空指针，打印出错误信息
		printf("%s\n", strerror(errno));
		return;
	}
	//将成绩管理系统中数据到文件中
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->data[i]), sizeof(StudentInfo), 1, pfWrite);
	}

	fclose(pfWrite);//释放内存，防止内存泄漏
	pfWrite = NULL;//为pfWrite赋值为空指针
}
