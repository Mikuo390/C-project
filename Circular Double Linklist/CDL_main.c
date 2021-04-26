#include "CDL.h"

int main() {
	int choice = 0;
	
	while (1){
		MainMenu();
		printf("请输入选项:>");
		scanf("%d", &choice);
		if (choice == 0)
			break;
		system("cls");
		switch (choice)
		{
		case 1:SingleList();
			break;
		case 2:DoubleList();
			break;
		default:printf("输入错误！！！\n");
		}
	}
}
