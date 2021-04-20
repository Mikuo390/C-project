#include "Complex.h"

//主函数
int main() {
	Complex* Com = NULL;
	int choice = 0;
	while (1) {
		menu();
		printf("请输入菜单序号:");
		scanf("%d", &choice);
		system("cls");
		if (choice == 0)
			break;

		switch (choice) {
		case 1:addCalc(Com);
			break;
		case 2:minCalc(Com);
			break;
		case 3:multCalc(Com);
			break;
		case 4:divCalc(Com);
			break;
		case 5:fabCalc(Com);
			break;
		case 6:equationCalc();
			break;
		default:
			printf("输入错误！！！请重新输入\n");
			break;
		}//End of Switch()
	}//End of while()

	//功能测试
	//Complex z1, z2, z3, z4, z;
	//float RealPart = 0, ImagPart = 0;
	//assign(&z1, 8.0, 6.0);//z1 = 8+6i 
	//assign(&z2, 4.0, 3.0);//z2 = 4+3i
	//addi(&z3, z1, z2);//z3 = (8 + 6i) + (4 + 3i)
	//multi(&z4, z1, z2);//z4 = (8 + 6i) * (4 + 3i)
	//div(&z, z4, z3);//z = z4/z3 = (8 + 6i) * (4 + 3i) / ((8 + 6i) + (4 + 3i))
	//GetReal(&z);
	//GetImag(&z);
	//Print_C(&z);

}//End of main()
