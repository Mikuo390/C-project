#include "CDL.h"

//-----------------基础函数-----------------

//初始化链表
void InitList(CDList* L) {

	assert(L != NULL);//断言

	if (L == NULL) 
		exit(0);
	L->head = NULL;//头结点为空
	L->tail = NULL;//尾结点位空
}

//获取链表长度
int GetListLength(CDList L) {
	CDLinkList curNode = L.head;//标记结点指针，用于标记当前结点
	int length = 0;//链表长度

	if (curNode == NULL)//若线性表为空，则长度为0
		return length;
	do {
		length++;
		curNode = curNode->next;//让当前标记结点指向下一个
	} while (curNode != L.head);
	return length;
}

//检测链表是否为空
int IsEmpty(CDList L) {
	if (L.head == NULL)
		return TRUE;
	else
		return FALSE;
}

//清空表
int ClearList(CDLinkList *L) {

	CDLinkList curNode = *L;
	CDLinkList tmpNode;
	while (curNode->next!= *L){
		tmpNode = curNode;
		curNode = curNode->next;
		tmpNode->data = NULL;
		free(tmpNode);
	}
	free(curNode);
	*L = NULL;

	//CDLinkList p = L;
	//while (L->data) {
	//	L->data = NULL;
	//	L = L->next;
	//}
	return OK;
}

//插入元素
int InsertList(CDList* L, ElemType e) {
	CDLinkList curNode = L->head;//当前标记结点存放头结点
	CDLinkList priNode = L->tail;//当前标记结点的前驱存放尾结点
	CDLinkList newNode;//插入的新结点
	int length = GetListLength(*L);//获取链表长度
	int index = 0;//索引位置

	//链表为空的情况下
	if (curNode == NULL) {
		newNode = (CDLinkList)malloc(sizeof(CDLNode));//为新结点开辟空间
		newNode->data = e;//将数据存放进新结点中
		//空表中插入新结点时
		//本身不存在任何结点
		//所以他的前驱和后继只能指向自己
		newNode->prior = newNode;
		newNode->next = newNode;
		
		//此时只有一个元素的链表内
		//头结点和为结点指向的都是本身
		L->head = newNode;
		L->tail = newNode;

		return index;//返回索引值
	}

	//链表不为空的时候
	//遍历插入位置
	for (index = 0; index < length; index++) {
		if (curNode->data == e) {
			return ERROR;
		}
		//搜寻不到,让标记结点进行后移
		priNode = curNode;//将当前标记结点的位置赋值给前一标记结点
		curNode = curNode->next;//让当前标记标记结点指向下一个
	}
	//插入操作
	newNode = (CDLinkList)malloc(sizeof(CDLNode));//开空间
	newNode->data = e;//存入结点数据
	//结点变化
	newNode->prior = priNode;//新结点的前驱 指向 前一标记结点
	priNode->next = newNode;//前一标记结点next(后继) 指向 新结点
	newNode->next = curNode;//新结点的next(后继) 指向 当前标记结点
	curNode->prior = newNode;//当前标记结点 的pri(后继)指向 新结点
	
	//索引值的特殊情况
	if (index == 0)
		L->head = newNode;
	else if (index == length)
		L->tail = newNode;
	return index;
}

//删除元素
int DeleteElem(CDList* L, ElemType e) {
	CDLinkList curNode = L->head;//当前标记结点存放头结点
	CDLinkList priNode = L->tail;//当前标记结点的前驱存放尾结点
	int index = 0;

	if (curNode == NULL)
		return ERROR;

	//遍历寻找删除位置
	do {
		//找到元素
		if (curNode->data == e) {
			if (index == 0) {
				if (curNode->next = curNode) {//只有一个结点，直接删除
					L->head = NULL;
					L->tail = NULL;
				}
				else {//存在若干个，删除，结点减少一个
					//结点前移动
					//当前标记结点的后继 赋值给 前一标记结点的后继
					priNode->next = curNode->next;
					//curNode->next->prior = priNode;
					CDLinkList tmp = curNode->next;//暂时存放
					//前一标记结点的位置 赋值 当前标记结点的后继的前驱 
					tmp->prior = priNode;

					L->head = curNode->next;//头结点变化
				}
				free(curNode);
				return index;
			}
			else {//删除的为尾结点
				if (curNode->next == L->head)
					L->tail = priNode;//更新尾结点
				//结点后移
				//当前标记结点的后继 赋值给 前一标记结点的后继
				priNode->next = curNode->next;
				CDLinkList tmp = curNode->next;//暂时存放
				//前一标记结点的位置 赋值 当前标记结点的后继的前驱 
				tmp->prior = priNode;
				free(curNode);
				return index;
			}
		}
		else if (curNode->data != e) {
			//标记点后移
			priNode = curNode;
			curNode = curNode->next;
			index++;
		}
		else//找不到结点
			return ERROR;
	}while (curNode != L->head);
	return ERROR;
}

//搜索元素
int SearchElem(CDList L, ElemType e) {
	CDLinkList Node = L.head;//标记结点
	int index = 0;

	while (Node != NULL){
		if (Node->data == e)
			return index;
		else if (Node->data != e) {
			Node = Node->next;
			index++;
		}
		else
			return ERROR;
	}
	return ERROR;
}

//交换链表中结点
int SwapLinkElem(CDList* L, ElemType e1, ElemType e2) {

	CDLinkList curNode = L->head;//当前标记结点存放头结点
	CDLinkList priNode = L->tail;//当前标记结点的前驱存放尾结点

	CDLinkList tmpNode1 = NULL;
	CDLinkList tmpNode2 = NULL;
	CDLinkList tmpNode = NULL;
	ElemType tmp;

	int length = GetListLength(*L);//获取链表长度
	//while (curNode1->next != L->head) {
	//	if (curNode1->data == e1) {
	//		//tmpNode1->data = curNode->data;
	//		tmpNode1 = curNode1;			
	//		//printf("A");
	//		printf("%d\n", tmpNode1->data);
	//	}
	//	curNode1 = curNode1->next;
	//}
	////printf("C");
	//while (curNode2->next != L->head) {
	//	if (curNode2->data == e2) {
	//		//tmpNode2->data = curNode->data;
	//		tmpNode2 = curNode1;
	//		//printf("B");
	//		printf("%d\n", tmpNode2->data);
	//	}
	//	curNode2 = curNode2->next;
	//}

	//while(curNode != NULL)

	 for(int i = 0; i < length;i++,curNode = curNode->next) {
		if (curNode->data == e1) {
			tmpNode1 = curNode;
			//printf("1:%d\n", tmpNode1->data);
		}
		else if (curNode->data == e2) {
			tmpNode2 = curNode;
			//printf("2:%d\n", tmpNode2->data);
		}
		
		if (tmpNode1 != NULL && tmpNode2 != NULL) {
			//交换
			tmp = tmpNode1->data;
			tmpNode1->data = tmpNode2->data;
			tmpNode2->data = tmp;
			//printf("交换");
			//tmpNode = tmpNode1;
			//tmpNode1 = tmpNode2;
			//tmpNode1 = tmpNode;
			return TRUE;
		}
	}


	if (tmpNode1 == NULL && tmpNode2 == NULL)
		return ERROR;
	//printf("E");
	return ERROR;
}

//倒置链表
int ReversalList(CDList *L) {
	CDLinkList curNode = L->head;
	CDLinkList priNode = L->tail;
	CDLinkList tmpNode = NULL;


	int length = GetListLength(*L);
	int tmp;

	for (int i = 0; i < length / 2; i++) {
		tmp = curNode->data;
		curNode->data = priNode->data;
		priNode->data = tmp;

		curNode = curNode->next;
		priNode = priNode->prior;
		//printf("交换:%d\n",i);
	}
}

//打印链表
void PrintList(CDList L) {
	CDLinkList curNode = L.head;//当前标记结点从头结点开始
	int index = 0;//结点位置

	if (curNode != NULL) {
		while (curNode->next!=L.head){
			printf("%-3d ", curNode->data);
			if ((index + 1) % 10 == 0)
				printf("\n");
			curNode = curNode->next;
			index++;
		}
		printf("%-3d \n", curNode->data);//尾结点
	}
	printf("\n");
}

//创建100个随机数
int CreateRandomNum(CDList* L,int i) {
	int index = 0;
	srand((unsigned)time(NULL));

	while(1) {	
		index = InsertList(L, (rand() % i)) + 1;
		if (index == i) {
			break;
		}
	}
	return OK;
}


//-----------------功能函数-----------------

void MainMenu() {
	printf("\n----------------------------------\n\n");

	printf("1.单链表操作\n");
	printf("2.双链表操作\n");
	printf("0.离开\n");

	printf("\n----------------------------------\n");
}

//菜单
void SingleListFunctionMenu(){
	printf("\n----------------------------------\n\n");

	printf("1.获取链表长度\n");
	printf("2.检测链表是否为空表\n");
	printf("3.清空链表\n");
	printf("4.插入元素\n");
	printf("5.删除元素\n");
	printf("6.搜寻元素\n");
	printf("7.交换链表中元素\n");
	printf("8.打印链表所有元素\n");
	printf("9.倒置链表所有元素\n");
	printf("10.在链表中自动生成i个元素\n");
	printf("0.离开\n");

	printf("\n----------------------------------\n");
}

void DoubleListFunctionMenu() {
	printf("\n----------------------------------\n\n");
	printf("表1：					表2：\n");
	printf("1.获取链表长度				11.获取链表长度\n");
	printf("2.检测链表是否为空表			12.检测链表是否为空表\n");
	printf("3.清空链表				13.清空链表\n");
	printf("4.插入元素				14.插入元素\n");
	printf("5.删除元素				15.删除元素\n");
	printf("6.搜寻元素				16.搜寻元素\n");
	printf("7.交换链表中元素			17.交换链表中元素\n");
	printf("8.打印链表所有元素			18.打印链表所有元素\n");
	printf("9.倒置链表所有元素			19.倒置链表所有元素\n");
	printf("10.在链表中自动生成i个元素		20.在链表中自动生成i个元素\n");
	printf("----------------------------------\n");
	printf("21.交换两个表中的结点\n");
	printf("0.离开\n");
	printf("----------------------------------\n");
}

//获取链表长度
void GetLength(CDList L) {
	printf("链表的长度为：%d\n", GetListLength(L));
}

//检测是否为空表
void Check(CDList L) {
	if (IsEmpty(L))
		printf("表为空！\n");
	else
		printf("表不为空！\n");
}

//清空
void Clear(CDList* L) {

	if(IsEmpty(*L) == TRUE)
		printf("表已清空！\n");
	else if (IsEmpty(*L) == FALSE) {
		ClearList(L);
		printf("表已清空！\n");
	}	
	else
		printf("操作失败！\n");
}

//插入
void Insert(CDList* L) {
	ElemType e;
	int index = 0;
	printf("请输入要插入的元素：>");
	scanf("%d", &e);

	index = InsertList(L, e) + 1;
	if(index)
		printf("元素[%d]以插入至表中第[%d]个位置！\n", e, index);
	else
		printf("插入失败！！！\n");
}

//删除
void Delete(CDList* L) {
	ElemType e;
	int index = 0;
	printf("请输入要删除的元素：>");
	scanf("%d", &e);

	index = DeleteElem(L,e) + 1;
	if (index)
		printf("元素[%d]以从表中第[%d]个位置删除！\n", e, index);
	else
		printf("删除失败！！！\n");
}

//搜索
void Search(CDList L) {
	ElemType e;
	int index = 0;
	printf("请输入要查找的元素：>");
	scanf("%d", &e);

	index = SearchElem(L, e) + 1;
	if (index)
		printf("元素[%d]以在表中第[%d]个位置！\n", e, index);
	else
		printf("搜寻失败！！！\n");
}

//交换单链表的中的数据
void SwapSingle(CDList* L) {
	ElemType e1;
	ElemType e2;
	
	
	if (IsEmpty(*L) == FALSE) {
		while (1) {
			printf("请输入要交换的第一个元素：>");
			scanf("%d", &e1);
			int index1 = SearchElem(*L, e1)+1;
			printf("元素[%d]以在表中第[%d]个位置\n", e1, index1);
			printf("请输入要交换的第二个元素：>");
			scanf("%d", &e2);
			int index2 = SearchElem(*L, e2)+1;
			printf("元素[%d]以在表中第[%d]个位置\n", e2, index2);

			if (e1 != e2) {
				int isTRUE = SwapLinkElem(L, e1, e2);

				if (isTRUE == TRUE) {
					printf("交换成功\n");
					printf("元素[%d]以在表中第[%d]个位置\n", e1, index2);
					printf("元素[%d]以在表中第[%d]个位置\n", e2, index1);
					break;
				}	
				else
					printf("交换失败\n");
			}
			else if (e1 == e2)
				printf("元素重复，请重新输入\n");
		}
	}
	else if (IsEmpty(*L)) {
		printf("不存在数据表为空！\n");
	}
}

//交换单链表的中的数据
void SwapDouble(CDList* L1, CDList* L2) {
	ElemType e1 = 0;
	ElemType e2 = 0;


	if (IsEmpty(*L1) == FALSE && IsEmpty(*L2) == FALSE) {
		while (1) {
			printf("请输入[L1]要交换的第一个元素：>");
			scanf("%d", &e1);
			int index1 = SearchElem(*L1, e1) + 1;
			printf("元素[%d]以在表[L1]中第[%d]个位置\n", e1, index1);
			printf("请输入[L2]要交换的第二个元素：>");
			scanf("%d", &e2);
			int index2 = SearchElem(*L2, e2) + 1;
			printf("元素[%d]以在表[L2]中第[%d]个位置\n", e2, index2);

			if (e1 != e2) {
				int isTRUE = SwapDoubleLinkElem(L1 ,L2,e1, e2);

				if (isTRUE == TRUE) {
					printf("交换成功\n");
					printf("元素[%d]以在表[L1]中第[%d]个位置\n", e1, index2);
					printf("元素[%d]以在表[L2]中第[%d]个位置\n", e2, index1);
					break;
				}
				else
					printf("交换失败\n");
			}
			//else if (e1 == e2)
			//	printf("元素重复，请重新输入\n");
		}
	}
	else if (IsEmpty(*L1) && IsEmpty(*L2)) {
		printf("不存在数据表为空！\n");
	}
}

//倒置元素
void Reversal(CDList* L) {
	printf("倒置前：\n");
	PrintList(*L);

	printf("倒置后：\n");
	ReversalList(L);
	PrintList(*L);
}

//创建i个元素
void CreateElem(CDList* L) {
	int i = 0;
	printf("输入循环双向链结表 L 的元素个数 (1 与 100 (含)之间)：");
	scanf("%d", &i);
	int isOK = CreateRandomNum(L, i);

	if (isOK == OK) {
		printf("创建成功！");
	}
	else
		printf("创建失败！");
}

//交换双链表
int SwapDoubleLinkElem(CDList* L1, CDList* L2, ElemType e1, ElemType e2) {


	CDLinkList curNode1 = L1->head;//当前标记结点存放头结点
	CDLinkList curNode2 = L1->head;//当前标记结点存放头结点

	CDLinkList tmpNode1 = NULL;
	CDLinkList tmpNode2 = NULL;
	CDLinkList tmpNode = NULL;
	ElemType tmp;

	int length1 = GetListLength(*L1);//获取链表长度
	int length2 = GetListLength(*L2);//获取链表长度

	for (int i = 0; i < length1; i++, curNode1 = curNode1->next) {
		if (curNode1->data == e1) {
			tmpNode1 = curNode1;
			//printf("1:%d\n", tmpNode1->data);
		}
	}

	for (int i = 0; i < length2; i++, curNode2 = curNode2->next) {
		if (curNode2->data == e1) {
			tmpNode2 = curNode2;
			//printf("2:%d\n", tmpNode2->data);
		}
	}

	if (tmpNode1 != NULL && tmpNode2 != NULL) {
		//交换
		tmp = tmpNode1->data;
		tmpNode1->data = tmpNode2->data;
		tmpNode2->data = tmp;
		return TRUE;
	}

	if (tmpNode1 == NULL && tmpNode2 == NULL)
		return ERROR;
	//printf("E");
	return ERROR;
}

//打印
void Print(CDList L) {

	if (IsEmpty(L) == TRUE)
		printf("表为空！\n");
	else if (IsEmpty(L) == FALSE) {
		printf("链表内元素如下\n");
		GetLength(L);
		PrintList(L);
	}
	else
		printf("操作失败！\n");

}
//-----------------主函数-----------------
//单链表操作
void SingleList() {
	CDList L;
	InitList(&L);//初始化链表
	int choice = 0;

	while (1) {
		SingleListFunctionMenu();
		printf("请输入选项:>");
		scanf("%d", &choice);
		if (choice == 0) break;
		system("cls");
		switch (choice)
		{
		case 1:GetLength(L);
			break;
		case 2:Check(L);
			break;
		case 3:Clear(&L);
			break;
		case 4:Insert(&L);
			break;
		case 5:Delete(&L);
			break;
		case 6:Search(L);
			break;
		case 7:SwapSingle(&L);
			break;
		case 8:Print(L);
			break;
		case 9:Reversal(&L);
			break;
		case 10:CreateElem(&L);
			break;
		default:printf("输入错误！！！\n");
		}
	}
}

//双链表操作
void DoubleList() {
	CDList L1;
	CDList L2;
	//初始化链表
	InitList(&L1);
	InitList(&L2);
	int choice = 0;

	while (1) {
		DoubleListFunctionMenu();
		printf("请输入选项:>");
		scanf("%d", &choice);
		if (choice == 0) break;
		system("cls");
		switch (choice)
		{
		case 1: {
			printf("表1\n");
			GetLength(L1);
		}break;			
		case 2: {
			printf("表1\n");
			Check(L1);
		}break;	
		case 3: {
			printf("表1\n");
			Clear(&L1);
		}break;	
		case 4: {
			printf("表1\n");
			Insert(&L1);
		}break;	
		case 5: {
			printf("表1\n");
			Delete(&L1);
		}break;			
		case 6: {
			printf("表1\n");
			Search(L1);
		}break;		
		case 7: {
			printf("表1\n");
			SwapSingle(&L1);
		}break;	
		case 8: {
			printf("表1\n");
			Print(L1);
		}break;		
		case 9: {
			printf("表1\n");
			Reversal(&L1);
		}break;		
		case 10: {
			printf("表1\n");
			CreateElem(&L1);
		}break;
		case 11: {
			printf("表2\n");
			GetLength(L2);
		}break;
		case 12: {
			printf("表2\n");
			Check(L2);
		}break;
		case 13: {
			printf("表2\n");
			Clear(&L2);
		}break;
		case 14: {
			printf("表2\n");
			Insert(&L2);
		}break;
		case 15: {
			printf("表2\n");
			Delete(&L2);
		}break;
		case 16: {
			printf("表2\n");
			Search(L2);
		}break;
		case 17: {
			printf("表2\n");
			SwapSingle(&L2);
		}break;
		case 18: {
			printf("表2\n");
			Print(L2);
		}break;
		case 19: {
			printf("表2\n");
			Reversal(&L2);
		}break;
		case 20: {
			printf("表2\n");
			CreateElem(&L2);
		}break;
		case 21: {
			SwapDouble(&L1, &L2);
		}break;
			
		default:printf("输入错误！！！\n");
		}
	}
}
