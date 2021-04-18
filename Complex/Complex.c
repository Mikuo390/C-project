#include "Complex.h"

//————————————————基本函数————————————————
//赋值
void assign(Complex* Com, float real, float imag) {
	Com->realpart = real;//实部赋值
	Com->imagpart = imag;//虚部赋值
}//End of assign()

//加法 
void addi(Complex* Com, Complex A, Complex B) {
	Com->realpart = A.realpart + B.realpart;//实部相加
	Com->imagpart = A.imagpart + B.imagpart;//虚部相加
}//End of addi()

//减法 
void minus(Complex* Com, Complex A, Complex B) {
	Com->realpart = A.realpart - B.realpart;//实部相减
	Com->imagpart = A.imagpart - B.imagpart;//虚部相减
}//End of minus()

//乘法 
void mult(Complex* Com, Complex A, Complex B) {
	Com->realpart = A.realpart * B.realpart - A.imagpart * B.imagpart;
	Com->imagpart = A.imagpart * B.realpart + A.realpart * B.imagpart;
}//End of munlt()

//除法 
void div(Complex* Com, Complex A, Complex B) {
	Com->realpart = (A.realpart * B.realpart + A.imagpart * B.imagpart)
		/ (pow(B.realpart, 2) + pow(B.imagpart, 2));
	Com->imagpart = (A.imagpart * B.realpart - A.realpart * B.imagpart)
		/ (pow(B.realpart, 2) + pow(B.imagpart, 2));
}//End of divide()

//获取实部 
float GetReal(Complex* Com) {
	printf("%.4f\n", Com->realpart);
	return Com->realpart;
}//End of GetReal()

//获取虚部 
float GetImag(Complex* Com) {
	printf("%.4f\n", Com->imagpart);
	return Com->imagpart;
}//End of GetImag()

//绝对值
float fab(Complex* Com) {
	return (float)sqrt(pow(Com->realpart, 2) + pow(Com->imagpart, 2));
}//End of adv

//复数转实数
float rr2c(Complex* Com) {
	return (float)sqrt(pow(Com->realpart, 2) + pow(Com->imagpart, 2));
}//End of rr2c

//打印完整的复数 
void Print_C(Complex* Com) {
	printf("%.4f + %.4f *i\n", Com->realpart, Com->imagpart);
}//End of Print_C()


//————————————————功能函数————————————————
//全局变量部分
Complex z1, z2, z3, z4, z;
float a, b, c;

//菜单
void menu() {
	printf("***********************************\n");
	printf("**********1.加法   2.减法**********\n");
	printf("**********3.乘法   4.除法**********\n");
	printf("**********5.绝对   6.实数**********\n");
	printf("**********     0.退出    **********\n");
	printf("***********************************\n");
}//End of menu()

//赋值函数 
void assignValue(Complex* Com) {
	float a1, a2, b1, b2;

	printf("————————————————\n");
	printf("请输入复数z1的实部：");
	scanf("%f", &a1);
	printf("请输入复数z1的虚部：");
	scanf("%f", &b1);
	assign(&z1, a1, b1);
	printf("复数z1的表达式：");
	Print_C(&z1);

	printf("\n");

	printf("请输入复数z2的实部：");
	scanf("%f", &a2);
	printf("请输入复数z2的虚部：");
	scanf("%f", &b2);
	assign(&z2, a2, b2);
	printf("复数z2的表达式：");
	Print_C(&z2);
	printf("————————————————\n");
}//End of assignValue()

//加法函数
void addCalc(Complex* Com) {
	assignValue(Com);

	addi(&z3, z1, z2);
	printf("复数加法计算结果为：");
	Print_C(&z3);
	printf("————————————————\n\n");
}//End of addCalc()

//减法函数
void minCalc(Complex* Com) {
	assignValue(Com);

	minus(&z3, z1, z2);
	printf("复数减法计算结果为：");
	Print_C(&z3);
	printf("————————————————\n\n");
}//End of minCalc()

//乘法函数
void multCalc(Complex* Com) {
	assignValue(Com);

	mult(&z3, z1, z2);
	printf("复数乘法计算结果为：");
	Print_C(&z3);
	printf("————————————————\n\n");
}//End of multCalc()

//除法
void divCalc(Complex* Com) {
	assignValue(Com);

	div(&z3, z1, z2);
	printf("复数乘法计算结果为：");
	Print_C(&z3);
	printf("————————————————\n\n");
}//End of divCalc()

//绝对值
void fabCalc(Complex* Com) {
	float a, b;
	float fabNum = 0;

	printf("————————————————\n");

	printf("请输入复数z的实部：");
	scanf("%f", &a);
	printf("请输入复数z的虚部：");
	scanf("%f", &b);
	assign(&z, a, b);
	Print_C(&z);
	fabNum = fab(&z);
	printf("复数绝对值计算结果为：%.4f\n", fabNum);

	printf("————————————————\n\n");
} //End of advCalc()


//解方程函数
void equationCalc() {
	//float a, b, c;

	printf("————————————————\n");

	printf("已构建方程 ax^2 + bx + c = 0 !\n");
	printf("请输入a,b,c的值：");
	scanf("%f%f%f", &a, &b, &c);
	printf("\n方程 %.4fx^2 + %.4fx + %.4f = 0构建完成!\n",a,b,c);

	printf("方程已导入求根公式，正在计算中。。。\n");
	formula(a, b, c);
}//End of equationCalc()

//求实根公式
void formula(float a, float b, float c) {
	float delta = 0;
	float realpart = 0, imagpart = 0;
	float x1 = 0, x2 = 0;

	delta = pow(b, 2) - 4 * a * c;

	//realpart = (-b) / (2 * a);
	//imagpart = fabs(delta) / (2 * a);
	printf("\n");

	if (delta > 0) {
		x1 = (-b + sqrt(delta)) / 2 * a;
		x2 = (-b - sqrt(delta)) / 2 * a;
		printf("方程存在两个根:x1=%.4f,x2=%.4f\n", x1, x2);
		printf("方程的复数根为：\n");
		assign(&z1, x1, 0);
		Print_C(&z1);
		assign(&z2, x2, 0);
		Print_C(&z2);
		checkCalc(z1,z2);
	}
	else if (delta == 0) {
		x1 = x2 = (-b) / 2 * a;
		printf("方程存在两个相同的实根:x1=%.4f,x2=%.4f\n", x1, x2);
		printf("方程的复数根为：\n");
		assign(&z, x1, 0);
		Print_C(&z);
		checkCalc(z, z);
	}
	else if (delta < 0) {
		printf("方程的实根不存在\n");
		printf("正在加载复数根计算器\n");
		realpart = (-b) / (2 * a);
		imagpart = sqrt(fabs(delta)) / (2 * a);
		printf("方程的复数根为：\n");
		assign(&z1, realpart, imagpart);
		Print_C(&z1);
		assign(&z2, realpart, -imagpart);
		Print_C(&z2);
		checkCalc(z1, z2);
	}
	else {
		printf("%s\n", strerror(errno));//打印出错误信息
	}

	printf("————————————————\n\n");
}//End of formula()

//验算函数
void checkCalc(Complex Com1, Complex Com2) {
	float a0 = 0, b0 = 0, c0 = 0;
	
	addi(&z3, Com1, Com2);
	b0 = rr2c(&z3);

	mult(&z4, Com1, Com2);
	c0 = rr2c(&z4);

	if (b0 == b && c0 == c) {
		printf("原方程		%.4fx^2 + %.4fx + %.4f = 0 \n", a, b, c);
		printf("还原方程	1.0000x^2 + %.4fx + %.4f = 0\n", b, c);
		printf("两方程式相同\n");
		printf("验算结果正确，r1 和 r2 是一元二次方程式的根\n");
	}	
	else
		printf("验算结果错误，r1 和 r2 不是是一元二次方程式的根\n");	
}//End of checkCalc
D
