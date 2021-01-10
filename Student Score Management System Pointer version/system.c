//函数实现

#include"system.h"

//打印主菜单-函数
void menu()
{
	printf("\n\n\t\t========欢迎使用学生成绩管理系统========\n");
	printf("\t\t*"), printf("\t\t\t\t       *\n");
	printf("\t\t*\t 1 . 添加学生成绩");
	printf("\t       *\n");
	printf("\t\t*\t 2 . 删除学生成绩");
	printf("\t       *\n");
	printf("\t\t*\t 3 . 修改学生成绩");
	printf("\t       *\n");
	printf("\t\t*\t 4 . 查询学生成绩");
	printf("\t       *\n");
	printf("\t\t*\t 5 . 统计学生成绩");
	printf("\t       *\n");
	printf("\t\t*\t 6 . 输出学生成绩");
	printf("\t       *\n");
	printf("\t\t*\t 7 . 按照总分降序");
	printf("\t       *\n");
	printf("\t\t*\t 8 . 按照名字升序");
	printf("\t       *\n");
	printf("\t\t*\t 9 . 按照数学成绩降序");
	printf("\t       *\n");
	printf("\t\t*\t 10. 按照语文成绩降序");
	printf("\t       *\n");
	printf("\t\t*\t 11. 按照英语成绩降序");
	printf("\t       *\n");
	printf("\t\t*\t 0 . 保存数据,退出系统");
	printf("\t       *\n");
	printf("\t\t*"), printf("\t\t\t\t       *\n");
	printf("\t\t========Version - 动态管理加密版 =======\n");
	printf("\t\t========Pioneer - 叶某某独立制作 =======\n");
	printf("\t\t========    一个孤独の程序员     =======\n");
	printf("\t\t========================================\n");
	printf("\n");
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
	ReadFile(ps);//读取文件
}


//声明检查函数
void CheckCapacity(struct Student* ps);

//从文件 StuMarkSystem.txt 中读入学生成绩
void ReadFile(Student* ps)
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
		printf("\t\t\t！！！增容成功！！！\n");
	}
	else//如果是则打印出提示
	{
		printf("\t\t\t！！！增容失败！！！\n");
	}
}

//添加学生成绩-函数
void AddStudent(struct Student* ps)
{
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
}


//删除学生成绩
void DelStudent(struct Student* ps)
{
	char name[MAX_NAME];
	int pos = 0;

	printf("请输入要删除学生的姓名:\n");
	scanf("%s", name);

	//1.查找要删除的学生在什么位置
	pos = FindByName(ps, name);
	//找到了返回名字所在元素的下标
	//找不到返回 -1

	//2.删除
	if (pos == -1)
	{
		printf("删除的学生不存在\n");
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
	printf("\t\t********     按照总分成绩降序     ********\n");
	DispStudent(ps);
	SaveFile(ps);
}

//按照姓名排序
void SortStudent_by_Name(struct Student* ps)
{
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
	printf("\t\t********     按照名字字母升序     ********\n");
	DispStudent(ps);
	SaveFile(ps);
}

//按照数学成绩降序
void SortStudent_by_MathMark(struct Student* ps)
{
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
	printf("\t\t********     按照数学成绩降序     ********\n");
	DispStudent(ps);
	SaveFile(ps);
}

//按照语文成绩降序
void SortStudent_by_ChinsesMark(struct Student* ps)
{
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
	printf("\t\t********     按照语文成绩降序     ********\n");
	DispStudent(ps);
	SaveFile(ps);
}

//按照英语成绩降序
void SortStudent_by_EnglishMark(struct Student* ps)
{
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
	printf("\t\t********     按照英语成绩降序     ********\n");
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
